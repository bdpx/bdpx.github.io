/********************************************************************************
 source-highlight
 libsource-highlight-dev
 g++ -o cdata cdata.cpp `pkg-config --libs --cflags source-highlight` -I/usr/include/libxml2 -lxml2
 `xml2-config --cflags --libs`
 source-highlight --gen-version --no-doc --out-format=xhtml-css --src-lang=cpp

source-highlight \
    --gen-version \
    --doc \
    --css="hl.css" \
    --out-format=xhtml \
    --src-lang=cpp \
    < test.cpp \
    > test.html
*********************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

#include <srchilite/sourcehighlight.h>
#include <srchilite/langmap.h>
#include <srchilite/parserexception.h>
#include <srchilite/ioexception.h>

#ifndef DATADIR
#define DATADIR ""
#endif

static int highlight(const std::string& code, const std::string& lang, std::ostream& out)
{
    std::istringstream in(code);

    try {
        srchilite::SourceHighlight sourceHighlight("xhtmlcss.outlang");
        sourceHighlight.setGenerateVersion(false);
        // sourceHighlight.setDataDir("/path/to/definition/files");
        sourceHighlight.highlight(in, out, lang + ".lang");
    }
    catch (const srchilite::ParserException& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (const srchilite::IOException& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

static int dump_highlighter(std::ostream& out, const std::string& lang, size_t pos, char const *start, char const *end)
{
    size_t const len = end - start;
    std::cerr << "HLL(" << lang << "): "
              << pos << "-" << (pos + len)
              << " " << len << " bytes\n";

    std::cout << "<div class=\"" << lang << "\">\n";
    std::string in(start, end - start);
    if (highlight(in, lang, out) < 0)
        return -1;
    std::cout << "</div>\n";
    return 0;
}

int ccmain(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<char> data;
    char chr;
    while (std::cin.get(chr)) {
        data.push_back(chr);
    }
    std::cerr << "data size=" << data.size() << std::endl;

    dump_highlighter(std::cout, "cpp", 0, data.data(), &data[data.size()]);
    return 0;
}

static xmlNode *get_from_memory(char const *data, size_t data_size)
{
    xmlDoc *doc = xmlReadMemory(data, data_size, NULL, NULL, 0);
    xmlNode *root = xmlDocGetRootElement(doc);
    xmlNode *copy = xmlCopyNode(root, 1/*recursive*/);
    xmlFreeDoc(doc);
    return copy;
}


static std::map<std::string, unsigned> stat;

static void stat_report(std::ostream& out)
{
    out << "stat:";
    for (auto const& x: stat) {
         out << ' ' << x.first << '(' << x.second << ')';
    }
    out << std::endl;
}

static void stat_listings(xmlDoc *doc, xmlNode *first, xmlNode *parent)
{
    for (xmlNode *node = first; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            std::string tag((char const*) node->name, xmlStrlen(node->name));
            stat[tag]++;
        }
        stat_listings(doc, node->children, node);
    }
}

// <div class="lang-lname">
static xmlChar const lang_prefix[] = "lang-";

static bool is_replacement_target(xmlDoc *doc, xmlNode *node)
{
    if (node->type != XML_ELEMENT_NODE)
        return false;

    if (xmlStrcmp(node->name, BAD_CAST "div") != 0)
        return false;

    xmlChar *lang = xmlGetProp(node, BAD_CAST "class");
    if (lang == NULL) {
        return false;
    }
    if (xmlStrlen(lang) < sizeof(lang_prefix)-1 ||
        memcmp(lang, lang_prefix, sizeof(lang_prefix)-1) != 0)
    {
        return false;
    }
    xmlFree(lang);

    size_t numchilds = 0;
    for (xmlNode *child = node->children; child; child = child->next) {
        if (child->type != XML_TEXT_NODE) {
            fprintf(stderr, "listing has non-text node\n");
            return false;
        }
        numchilds++;
    }
    if (numchilds != 1) {
        fprintf(stderr, "listing has more than 1 text node\n");
        return false;
    }

    return true;
}

static void replace_text(xmlDoc *doc, xmlNode *node)
{
    xmlChar *content = xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
    xmlChar *lang = xmlGetProp(node, BAD_CAST "class");

    xmlChar *lang_value = lang + sizeof(lang_prefix)-1;

         if (xmlStrcmp(lang_value, BAD_CAST "cpp") == 0) {}
    else if (xmlStrcmp(lang_value, BAD_CAST "xml") == 0) {}
    else if (xmlStrcmp(lang_value, BAD_CAST "pascal") == 0) {}
    else if (xmlStrcmp(lang_value, BAD_CAST "javascript") == 0) {}
    else if (xmlStrcmp(lang_value, BAD_CAST "java") == 0) {}
    else {
        fprintf(stderr, "content: unsupported lang=%s\n", lang_value);
        exit(1);
    }

    // fprintf(stderr, "content: lang=%s\n%s\n", lang, content);

    std::string xlang((char const*) lang_value, xmlStrlen(lang_value));

    xmlChar *content_value = content;
    while(*content_value == '\n') content_value++;

    std::string in((char const*) content_value, xmlStrlen(content_value));
    std::ostringstream out;
    if (highlight(in, xlang, out) < 0)
        return;

    xmlNode *new_node = get_from_memory(out.str().c_str(), out.str().length());
    // clear single XML_TEXT_NODE child
    xmlNode *textNode = node->children;
    xmlNodeSetContent(textNode, BAD_CAST "");
    // FIXME: better to replace, but now just add
    xmlAddChild(node, new_node);
    // xmlUnlinkNode(node);
    // xmlFreeNode(node);
    xmlFree(content);
    xmlFree(lang);
}

static void replace_listings(xmlDoc *doc, xmlNode *first, xmlNode *parent)
{
    for (xmlNode *node = first; node; node = node->next) {
        if (is_replacement_target(doc, node)) {
            replace_text(doc, node);
        } else {
            replace_listings(doc, node->children, node);
        }
    }
}

static void save_doc(xmlDoc *doc)
{
    xmlChar *str = NULL;
    int len = 0;
    xmlDocDumpMemoryEnc(doc, &str, &len, "UTF-8");
    fprintf(stdout, "%s", str);
    xmlFree(str);
}

int main(int argc, char **argv)
{
    LIBXML_TEST_VERSION

    xmlDoc *doc = xmlReadFile("-"/*stdin*/, NULL, XML_PARSE_NOCDATA/*replace CDATA*/);
    if (doc == NULL) {
        fprintf(stderr, "error: couldn't parse XML\n");
        return 1;
    }

    xmlNode *root = xmlDocGetRootElement(doc);

    stat_listings(doc, root, NULL);
    stat_report(std::cerr);
    replace_listings(doc, root, NULL);
    save_doc(doc);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
