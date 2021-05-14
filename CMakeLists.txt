cmake_minimum_required (VERSION 3.10)

project(website)

set(CMAKE_VERBOSE_MAKEFILE OFF)

add_subdirectory(highlighter)

add_custom_target(${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} highlighter)

####################################################################################################
# place for artifacts for github-pages
####################################################################################################
set(ARTIFACTS_DIR ${CMAKE_BINARY_DIR}/artifacts)
file(MAKE_DIRECTORY ${ARTIFACTS_DIR})

list(APPEND DIRS
    client-server
    compilation
    compilation/sss
    cpp
    cpp/book
    cpp/labs
    edm
    parallel
    sysprog
    xml
)

foreach(src ${DIRS})
    file(MAKE_DIRECTORY ${ARTIFACTS_DIR}/${src})
endforeach(src)

####################################################################################################
# for local testing prepared ${ARTIFACTS_DIR}
####################################################################################################
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/test_local.bash"
               "${CMAKE_BINARY_DIR}/test_local.bash" COPYONLY)

####################################################################################################
# files to copy as is
####################################################################################################
list(APPEND RAW_LIST
    robots.txt
    avatar.jpg
    cv.html
    favicon.ico
    google7d43edcd91d8040a.html
    yandex_5a6ec76d0d680364.html
    index.html
    science.html
    tralfamador.html
    styles.css

    client-server/client.zip
    client-server/index.html
    client-server/server.zip
    client-server/src.rar
    client-server/web20.html
    client-server/xmlrpc.html
    client-server/xmlrpc.zip

    compilation/index.html
    compilation/individ.html
    compilation/lab_01.doc
    compilation/lab_02.doc
    compilation/lab_03.doc
    compilation/lab_04.doc
    compilation/lab_1.html
    compilation/lab_2.html
    compilation/lab_3.html
    compilation/lab_4.html
    compilation/quest.html

    compilation/sss/assembler.doc
    compilation/sss/cross.doc
    compilation/sss/loader.doc
    compilation/sss/macroprocessor.doc
    compilation/sss/ustarelo.doc
    compilation/sys_mod_1.doc
    compilation/sys_mod_2.doc

    cpp/mod1.doc
    cpp/mod2.doc
    cpp/mod2.pdf
    cpp/module_1_examples.pdf
    cpp/quest_1.html
    cpp/quest_2.html
    cpp/quest_final.html

    edm/arc.html
    edm/generator_cpp_example.zip
    edm/index.html

    parallel/parallel.doc
    parallel/test.c

    sysprog/index.html
    sysprog/individ2.doc
    sysprog/individ.doc
    sysprog/individ.html
    sysprog/kkr.doc
    sysprog/kkr.xls
    sysprog/kursova.html
    sysprog/labs_c2.html
    sysprog/question.html
    sysprog/sys_mod_3.doc
    sysprog/sys_mod_4.doc
    sysprog/sysprex.zip

    win32gui/ex1.c
    win32gui/ex2.c
    win32gui/ex3.c
    win32gui/ex4.c
    win32gui/index.html

)

foreach(src ${RAW_LIST})
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${src}"
                   "${ARTIFACTS_DIR}/${src}" COPYONLY)
endforeach(src)

####################################################################################################
# xml files to highlight (yet not verify)
####################################################################################################
list(APPEND XML_LIST_SPE
)

foreach(xml_file ${XML_LIST_SPE})
    set(src "${CMAKE_CURRENT_SOURCE_DIR}/${xml_file}.xml")
    set(dst "${ARTIFACTS_DIR}/${xml_file}.html")
    add_custom_command(
        OUTPUT ${dst}
        COMMAND $<TARGET_FILE:highlighter> <${src} >${dst}
        DEPENDS ${src} highlighter ${transformator}
        COMMENT "Create xhtml ${dst}"
    )
    string(SHA256 hash ${xml_file})
    add_custom_target("target_${hash}" ALL DEPENDS ${dst})
    add_dependencies(${PROJECT_NAME} "target_${hash}")
endforeach(xml_file)

####################################################################################################
# files to highlight and verify
####################################################################################################
list(APPEND XML_LIST
    client-server/dcom

    cpp/index

    cpp/labs/lab1_class
    cpp/labs/lab2_virtfunc
    cpp/labs/lab3_overload
    cpp/labs/lab4_new_exception
    cpp/labs/lab5_textfile
    cpp/labs/lab6_binfile
    cpp/labs/lab7_template
    cpp/labs/lab8_stl

    cpp/individ

    edm/xslfo

    parallel/index
    parallel/labs
    parallel/parallel

    xml/index
    xml/xml_test
    xml/dom_app
    xml/dtd
    xml/individ
    xml/xml
    xml/xpath
    xml/xsd
    xml/xslt
)

foreach(xml_file ${XML_LIST})
    set(src "${CMAKE_CURRENT_SOURCE_DIR}/${xml_file}.xml")
    set(dst "${ARTIFACTS_DIR}/${xml_file}.html")
    add_custom_command(
        OUTPUT ${dst}
        COMMAND $<TARGET_FILE:highlighter> <${src} >${dst}
        DEPENDS ${src} highlighter ${transformator}
        COMMENT "Create xhtml ${dst}"
    )
    string(SHA256 hash ${xml_file})
    add_custom_target("target_${hash}" ALL DEPENDS ${dst})
    add_dependencies(${PROJECT_NAME} "target_${hash}")

    # validate result as (X)HTML
    add_custom_command(TARGET "target_${hash}"
        POST_BUILD
        COMMAND xmllint --noout --nonet --quiet --valid ${dst}
        COMMENT "xmllint (X)HTML validation: ${dst}"
    )
endforeach(xml_file)

####################################################################################################
# files to highlight, transform, and verify
####################################################################################################
list(APPEND DEEP_XML_LIST
    credo
    memorium

    cpp/book/introduction
    cpp/book/introduction_next
    cpp/book/instructions
    cpp/book/expressions
    cpp/book/datatypes
    cpp/book/functions
    cpp/book/visibility_scope
    cpp/book/abstract_containers
    cpp/book/namespaces
    cpp/book/function_overloading
    cpp/book/function_templates
    cpp/book/exceptions
    cpp/book/classes
    cpp/book/class_lifetime
    cpp/book/class_subtypes
    cpp/book/class_multiple_inheritance
    cpp/book/class_inheritance
    cpp/book/class_templates
    cpp/book/operator_overloading
    cpp/book/operator_conversions
    cpp/book/iostream
    cpp/book/algorithm_templates
    cpp/book/algorithm_templates_next
)

set(transformator "${CMAKE_CURRENT_SOURCE_DIR}/xhtml.xsl")

# pass each file via highlighter (xml -> xml)
# then pass to xsltproc (xml -> xhtml)
foreach(xml_file ${DEEP_XML_LIST})
    set(src "${CMAKE_CURRENT_SOURCE_DIR}/${xml_file}.xml")
    set(dst "${ARTIFACTS_DIR}/${xml_file}.html")
    add_custom_command(
        OUTPUT ${dst}
        COMMAND $<TARGET_FILE:highlighter> < ${src} | xsltproc ${transformator} - > ${dst}
        DEPENDS ${src} highlighter ${transformator}
        COMMENT "Create xhtml ${dst}"
    )
    string(SHA256 hash ${xml_file})
    add_custom_target("target_${hash}" ALL DEPENDS ${dst} ${transformator})
    add_dependencies(${PROJECT_NAME} "target_${hash}")

    # validate result as XHTML
    add_custom_command(TARGET "target_${hash}"
        POST_BUILD
        COMMAND xmllint --noout --nonet --quiet --valid ${dst}
        COMMENT "xmllint XHTML validation: ${dst}"
    )
endforeach(xml_file)


####################################################################################################
# sitemap
####################################################################################################
execute_process(COMMAND
    git -C "${CMAKE_CURRENT_SOURCE_DIR}" log -1 --format=%cd "--date=iso8601-strict"
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE GIT_PACKAGE_DATE_ISO8601)
message(STATUS "GIT_PACKAGE_DATE_ISO8601 = ${GIT_PACKAGE_DATE_ISO8601}")

set(SITEMAP "${ARTIFACTS_DIR}/sitemap.xml")

file(WRITE ${SITEMAP}
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<urlset\n"
    "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
    "    xsi:schemaLocation=\"http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd\"\n"
    "    xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\"\n"
    ">\n")

set(SITE "https://bdpx.github.io")

foreach(src ${RAW_LIST})
    file(APPEND ${SITEMAP}
      "<url>\n"
      "    <loc>${SITE}/${src}</loc>\n"
      "    <lastmod>${GIT_PACKAGE_DATE_ISO8601}</lastmod>\n"
      "    <changefreq>hourly</changefreq>\n"
      "    <priority>0.9</priority>\n"
      "</url>\n")
endforeach(src)

foreach(xml_file ${XML_LIST})
    file(APPEND ${SITEMAP}
      "<url>\n"
      "    <loc>${SITE}/${xml_file}.html</loc>\n"
      "    <lastmod>${GIT_PACKAGE_DATE_ISO8601}</lastmod>\n"
      "    <changefreq>hourly</changefreq>\n"
      "    <priority>0.9</priority>\n"
      "</url>\n")
endforeach(xml_file)

foreach(xml_file ${DEEP_XML_LIST})
    file(APPEND ${SITEMAP}
      "<url>\n"
      "    <loc>${SITE}/${xml_file}.html</loc>\n"
      "    <lastmod>${GIT_PACKAGE_DATE_ISO8601}</lastmod>\n"
      "    <changefreq>hourly</changefreq>\n"
      "    <priority>0.9</priority>\n"
      "</url>\n")
endforeach(xml_file)

file(APPEND ${SITEMAP} "</urlset>\n")
