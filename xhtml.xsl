<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0"
  xmlns="http://www.w3.org/1999/xhtml"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:msxsl="urn:schemas-microsoft-com:xslt"
  xmlns:exslt="http://exslt.org/common"
  xmlns:str="http://exslt.org/strings"
  xmlns:doc="http://www.example.com/postrisc"
  extension-element-prefixes="msxsl exslt str"
  exclude-result-prefixes="doc"
>

<xsl:output
  media-type="text/html"
  method="xml"
  encoding="utf-8"
  indent="yes"
  omit-xml-declaration="no"
  doctype-public="-//W3C//DTD XHTML 1.1//EN"
  doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"
/>

<!-- preserve -->
<xsl:preserve-space elements="*"/>
<xsl:preserve-space elements="doc:p"/>
<xsl:preserve-space elements="doc:td"/>
<xsl:preserve-space elements="doc:li"/>
<xsl:preserve-space elements="doc:note"/>
<xsl:preserve-space elements="doc:div"/>

<xsl:template match="prebook">
  <!-- preload all includes into root non-xhtml 'book' tag without default namespace -->
  <xsl:variable name="first">
    <xsl:element name="book" namespace="">  <!-- namespace="doc" http://www.example.com/postrisc -->
      <xsl:apply-templates/>
    </xsl:element>
  </xsl:variable>
  <!-- parse included data, node-set problem -->
  <xsl:choose>
    <xsl:when test="function-available('msxsl:node-set')">
      <xsl:apply-templates select="msxsl:node-set($first)"/>
    </xsl:when>
    <xsl:when test="function-available('exslt:node-set')">
      <xsl:apply-templates select="exslt:node-set($first)"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:apply-templates select="$first"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template match="prebook/doc:title">
  <title>
    <xsl:apply-templates/>
  </title>
</xsl:template>

<!-- second stage tags -->

<!-- expects title element in current element -->
<xsl:template name="page_head">
  <xsl:param name="description" select="@description"/>
  <head>
  <title>
    <xsl:for-each select="./doc:title">
      <xsl:apply-templates/>
    </xsl:for-each>
  </title>
  <!-- <meta charset="utf-8"/> -->
  <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
  <meta http-equiv="content-language" content="ru"/>
  <meta name="language" content="ru"/>

  <xsl:element name="meta">
    <xsl:attribute name="name">
       <xsl:text>description</xsl:text>
    </xsl:attribute>
    <xsl:attribute name="content">
      <xsl:value-of select="$description"/>
    </xsl:attribute>
  </xsl:element>

  <meta name="viewport" content="width=device-width"/>
  <link href="/styles.css" rel="stylesheet" type="text/css"/>
  </head>
</xsl:template>

<xsl:template name="footer">
<div class="chapter">
<br/><br/><hr/>
</div>
</xsl:template>

<xsl:template name="chapter_content">
  <xsl:if test="not(parent::*)">
    <h2>Содержание</h2>
  </xsl:if>
  <xsl:for-each select="doc:section">
    <p class="toc2">
      <xsl:text>&#167; </xsl:text>
      <xsl:number count="doc:chapter|doc:section" level="multiple" format="1.1. "/>
    <a>
    <xsl:attribute name="href">
      <xsl:value-of select="@href"/>#<xsl:value-of select="@id"/> <!-- generate-id() -->
    </xsl:attribute>
    <xsl:for-each select="doc:title">
      <xsl:apply-templates/>
    </xsl:for-each>
    </a></p>

    <xsl:for-each select="doc:subsection">
      <p class="toc3">
        <xsl:text>&#167; </xsl:text>
        <xsl:number count="doc:chapter|doc:section|doc:subsection" level="multiple" format="1.1.1. "/>
      <a>
      <xsl:attribute name="href">
        <xsl:value-of select="@href"/>#<xsl:value-of select="@id"/> <!-- generate-id() -->
      </xsl:attribute>
      <xsl:for-each select="doc:title">
        <xsl:apply-templates/>
      </xsl:for-each>
      </a></p>

    </xsl:for-each>
  </xsl:for-each>
</xsl:template>

<xsl:template name="book_content">
  <div class="chapter">
  <h1>Содержание</h1>
  <xsl:for-each select="./doc:chapter">
    <p class="toc1">
      <xsl:text>Раздел </xsl:text>
      <xsl:number count="doc:chapter" format="1. "/>
    <a>
    <xsl:attribute name="href">
      <xsl:value-of select="@href"/>#<xsl:value-of select="@id"/>
    </xsl:attribute>
    <xsl:for-each select="doc:title">
      <xsl:apply-templates/>
    </xsl:for-each>
    </a></p>
    <xsl:call-template name="chapter_content"/>
  </xsl:for-each>
  </div>
</xsl:template>

<xsl:template match="doc:book">
  <html lang="en">
  <xsl:call-template name="page_head"/>
  <body>
  <xsl:apply-templates select="./doc:preface"/>
  <xsl:call-template name="book_content"/>
  <xsl:for-each select="./doc:chapter">
    <xsl:apply-templates select="."/>
  </xsl:for-each>
  <xsl:call-template name="footer"/>
  </body>
  </html>
</xsl:template>

<xsl:template match="doc:comment">
</xsl:template>

<xsl:template match="doc:book/doc:preface">
  <div>
    <xsl:attribute name="class">chapter</xsl:attribute>
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
    <xsl:apply-templates/>
  </div>
</xsl:template>

<xsl:template match="/doc:preface">
  <html lang="en">
  <xsl:call-template name="page_head"/>
  <body>
  <div class="chapter">
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
    <xsl:apply-templates/>
  </div>
  <xsl:call-template name="footer"/>
  </body>
  </html>
</xsl:template>

<xsl:template match="doc:preface/doc:title">
  <p class="docname">
    <xsl:apply-templates/>
  </p>
</xsl:template>

<xsl:template match="doc:chapter">
  <div>
    <xsl:attribute name="class">chapter</xsl:attribute>
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
    <xsl:apply-templates/>
  </div>
</xsl:template>

<xsl:template match="/doc:chapter">
  <html lang="ru">
  <xsl:call-template name="page_head">
    <xsl:with-param name="description">
      <xsl:value-of select="@description"/>
    </xsl:with-param>
  </xsl:call-template>
  <body>
  <div class="chapter">
    <xsl:apply-templates select="doc:title"/>
    <xsl:apply-templates select="doc:preface"/>
    <xsl:call-template name="chapter_content"/>

    <xsl:for-each select="doc:section">
        <xsl:element name="div"> <!-- xhtml doesn't support section -->
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
            </xsl:attribute>
        <xsl:apply-templates/>
        </xsl:element>
    </xsl:for-each>
  </div>
  <xsl:call-template name="footer"/>
  </body>
  </html>
</xsl:template>

<xsl:template match="doc:chapter/doc:title">
  <h1>
  <xsl:text>Раздел </xsl:text><xsl:number count="doc:chapter" format="1. "/>
  <xsl:apply-templates/>
  </h1>
</xsl:template>

<xsl:template match="doc:chapter/doc:preface">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="doc:section">
  <div>
    <xsl:attribute name="class">section</xsl:attribute>
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
    <xsl:apply-templates/>
  </div>
</xsl:template>

<xsl:template match="doc:section/doc:title">
  <h2>
    <xsl:text>&#167; </xsl:text>
    <xsl:number count="doc:chapter|doc:section" level="multiple" format="1.1. "/>
    <xsl:apply-templates/>
  </h2>
</xsl:template>

<xsl:template match="doc:subsection">
  <div>
    <xsl:attribute name="class">subsection</xsl:attribute>
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
    <xsl:apply-templates/>
  </div>
</xsl:template>

<xsl:template match="doc:subsection/doc:title">
  <h3>
    <xsl:text>&#167; </xsl:text>
    <xsl:number count="doc:chapter|doc:section|doc:subsection" level="multiple" format="1.1.1. "/>
    <xsl:apply-templates/>
  </h3>
</xsl:template>

<!-- listing -->
<xsl:template match="doc:listing">
  <div>
    <xsl:if test="@class">
      <xsl:attribute name="class">
        <xsl:value-of select="@class"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:apply-templates/>
  </div>
</xsl:template>

<!-- span -->
<xsl:template match="doc:span">
  <span>
  <xsl:if test="@class">
    <xsl:attribute name="class">
      <xsl:value-of select="@class"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@id">
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </span>
</xsl:template>

<!-- paragraph -->
<xsl:template match="doc:p">
  <p>
  <xsl:if test="@id">
    <xsl:attribute name="id">
      <xsl:value-of select="@id"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </p>
</xsl:template>

<!-- note paragraph -->
<xsl:template match="doc:note">
  <p><strong>Notes: </strong>
    <xsl:apply-templates/>
  </p>
</xsl:template>

<xsl:template match="doc:li">
<li>
    <xsl:apply-templates/>
</li>
</xsl:template>

<xsl:template match="doc:ol">
  <ol>
    <xsl:if test="@start">
      <xsl:attribute name="start">
        <xsl:value-of select="@start"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:apply-templates/>
  </ol>
</xsl:template>

<xsl:template match="doc:samp">
<samp>
    <xsl:apply-templates/>
</samp>
</xsl:template>

<xsl:template match="doc:div">
  <xsl:element name="div">
    <xsl:if test="@class">
      <xsl:attribute name="class">
        <xsl:value-of select="@class"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:apply-templates/>
  </xsl:element>
</xsl:template>

<xsl:template match="doc:tt">
  <tt>
    <xsl:apply-templates/>
  </tt>
</xsl:template>

<xsl:template match="doc:h3">
  <h3>
    <xsl:apply-templates/>
  </h3>
</xsl:template>

<xsl:template match="doc:h4">
  <h4>
    <xsl:apply-templates/>
  </h4>
</xsl:template>

<xsl:template match="doc:ul">
  <ul>
    <xsl:if test="@class">
      <xsl:attribute name="class">
        <xsl:value-of select="@class"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:apply-templates/>
  </ul>
</xsl:template>

<xsl:template match="doc:pre">
  <pre>
    <xsl:if test="@class">
      <xsl:attribute name="class">
        <xsl:value-of select="@class"/>
      </xsl:attribute>
    </xsl:if>
    <xsl:apply-templates/>
  </pre>
</xsl:template>

<!-- anchor -->
<xsl:template match="doc:link">
  <a>
  <xsl:if test="@class">
    <xsl:attribute name="class">
      <xsl:value-of select="@class"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@href">
    <xsl:attribute name="href">
      <xsl:value-of select="@href"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </a>
</xsl:template>

<xsl:template match="doc:label">
  <a>
  <xsl:if test="@class">
    <xsl:attribute name="class">
      <xsl:value-of select="@class"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@name">
    <xsl:attribute name="name">
      <xsl:value-of select="@name"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </a>
</xsl:template>

<xsl:template match="doc:table">
  <table>
  <xsl:if test="@class">
    <xsl:attribute name="class">
      <xsl:value-of select="@class"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@width">
    <xsl:attribute name="width">
      <xsl:value-of select="@width"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </table>
</xsl:template>

<xsl:template match="doc:table/doc:caption">
  <caption>
    <!-- tables numeration across chapter like 'Table XX.YY: caption' -->
    <xsl:text>Table </xsl:text>
    <xsl:number count="doc:chapter" format="1."/>
    <xsl:number count="doc:table" from="doc:chapter" level="any" format="1: "/>
  <xsl:apply-templates/>
  </caption>
</xsl:template>

<xsl:template match="doc:thead">
  <thead>
    <xsl:apply-templates/>
  </thead>
</xsl:template>

<xsl:template match="doc:tbody">
  <tbody>
    <xsl:apply-templates/>
  </tbody>
</xsl:template>

<xsl:template match="doc:th">
  <th>
  <xsl:if test="@class">
    <xsl:attribute name="class">
      <xsl:value-of select="@class"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@colspan">
    <xsl:attribute name="colspan">
      <xsl:value-of select="@colspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@rowspan">
    <xsl:attribute name="rowspan">
      <xsl:value-of select="@rowspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@width">
    <xsl:attribute name="style">
      <xsl:text>width:</xsl:text><xsl:value-of select="@width"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </th>
</xsl:template>


<xsl:template match="doc:td">
  <td>
  <xsl:if test="@class">
    <xsl:attribute name="class">
      <xsl:value-of select="@class"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@colspan">
    <xsl:attribute name="colspan">
      <xsl:value-of select="@colspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@rowspan">
    <xsl:attribute name="rowspan">
      <xsl:value-of select="@rowspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@width">
    <xsl:attribute name="style">
      <xsl:text>width:</xsl:text><xsl:value-of select="@width"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </td>
</xsl:template>

<xsl:template match="doc:tc">
  <td class="cnt">
  <xsl:if test="@colspan">
    <xsl:attribute name="colspan">
      <xsl:value-of select="@colspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@rowspan">
    <xsl:attribute name="rowspan">
      <xsl:value-of select="@rowspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@width">
    <xsl:attribute name="style">
      <xsl:text>width:</xsl:text><xsl:value-of select="@width"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:apply-templates/>
  </td>
</xsl:template>

<xsl:template match="doc:cellc">
  <td style="text-align:center">
  <xsl:if test="@colspan">
    <xsl:attribute name="colspan">
      <xsl:value-of select="@colspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@rowspan">
    <xsl:attribute name="rowspan">
      <xsl:value-of select="@rowspan"/>
    </xsl:attribute>
  </xsl:if>
  <xsl:if test="@width">
    <xsl:attribute name="style">
      <xsl:text>width:</xsl:text><xsl:value-of select="@width"/>
    </xsl:attribute>
  </xsl:if>
    <xsl:apply-templates/>
  </td>
</xsl:template>

<xsl:template match="doc:tr">
  <tr>
    <xsl:apply-templates/>
  </tr>
</xsl:template>

<xsl:template match="doc:p/doc:code">
  <span class="code">
    <xsl:apply-templates/>
  </span>
</xsl:template>

<xsl:template match="doc:code">
  <pre class="code">
    <xsl:apply-templates/>
  </pre>
</xsl:template>

<xsl:template match="doc:strong">
  <strong>
    <xsl:apply-templates/>
  </strong>
</xsl:template>

<xsl:template match="doc:b">
  <b>
    <xsl:apply-templates/>
  </b>
</xsl:template>

<xsl:template match="doc:var">
  <var>
    <xsl:apply-templates/>
  </var>
</xsl:template>

<xsl:template match="doc:em">
  <em>
    <xsl:apply-templates/>
  </em>
</xsl:template>

<xsl:template match="doc:sup">
  <sup>
    <xsl:apply-templates/>
  </sup>
</xsl:template>

<xsl:template match="doc:sub">
  <sub>
    <xsl:apply-templates/>
  </sub>
</xsl:template>

<xsl:template match="doc:br">
  <br/>
</xsl:template>

<xsl:template match="doc:slot_table">
  <table class="ifmt">
    <xsl:apply-templates/>
  </table>
</xsl:template>

<xsl:template match="doc:q">
  <q>
    <xsl:apply-templates/>
  </q>
</xsl:template>

<!-- Definitions -->
<xsl:template match="doc:dfn">
  <dfn>
    <xsl:apply-templates/>
  </dfn>
</xsl:template>

<xsl:template match="doc:formula">    <span class="formula">    <xsl:apply-templates/> </span> </xsl:template>
<xsl:template match="doc:type">       <span class="type">       <xsl:apply-templates/> </span> </xsl:template>
<xsl:template match="doc:function">   <span class="function">   <xsl:apply-templates/> </span> </xsl:template>
<xsl:template match="doc:param">      <span class="param">      <xsl:apply-templates/> </span> </xsl:template>


<xsl:template match="doc:shy">&#173;</xsl:template>    <!-- soft word-break -->
<xsl:template match="doc:nbsp">&#160;</xsl:template>
<xsl:template match="doc:sect">&#167;</xsl:template>
<xsl:template match="doc:copy">&#169;</xsl:template>
<xsl:template match="doc:laquo">&#171;</xsl:template>
<xsl:template match="doc:not">&#172;</xsl:template>
<xsl:template match="doc:plusmn">&#177;</xsl:template>
<xsl:template match="doc:raquo">&#187;</xsl:template>
<xsl:template match="doc:times">&#215;</xsl:template>
<xsl:template match="doc:ndash">&#8211;</xsl:template>
<xsl:template match="doc:mdash">&#8212;</xsl:template>
<xsl:template match="doc:lsquo">&#8216;</xsl:template>
<xsl:template match="doc:rsquo">&#8217;</xsl:template>
<xsl:template match="doc:sbquo">&#8218;</xsl:template>
<xsl:template match="doc:ldquo">&#8220;</xsl:template>
<xsl:template match="doc:rdquo">&#8221;</xsl:template>
<xsl:template match="doc:bdquo">&#8222;</xsl:template>
<xsl:template match="doc:lsaquo">&#8249;</xsl:template> 
<xsl:template match="doc:rsaquo">&#8250;</xsl:template>
<xsl:template match="doc:minus">&#8722;</xsl:template>
<xsl:template match="doc:hellip">&#8230;</xsl:template>
<xsl:template match="doc:larr">&#8592;</xsl:template>  <!-- left arrow -->
<xsl:template match="doc:uarr">&#8593;</xsl:template>  <!-- up arrow -->
<xsl:template match="doc:rarr">&#8594;</xsl:template>  <!-- right arrow -->
<xsl:template match="doc:darr">&#8595;</xsl:template>  <!-- down arrow -->
<xsl:template match="doc:harr">&#8596;</xsl:template>  <!-- left-right arrow -->
<xsl:template match="doc:ne">&#8800;</xsl:template>    <!-- not equal -->
<xsl:template match="doc:equiv">&#8801;</xsl:template>  <!-- equivalence -->
<xsl:template match="doc:le">&#8804;</xsl:template>    <!-- less than or equal -->
<xsl:template match="doc:ge">&#8805;</xsl:template>    <!-- greater than or equal -->
<xsl:template match="doc:oplus">&#8853;</xsl:template>
<xsl:template match="doc:lt">&lt;</xsl:template>
<xsl:template match="doc:gt">&gt;</xsl:template>
<xsl:template match="doc:lshift">&lt;&lt;</xsl:template>
<xsl:template match="doc:rshift">&gt;&gt;</xsl:template>

<!-- XML DEFAULT RULES
<xsl:template match="*|/">
  <xsl:apply-templates/>
</xsl:template>

<xsl:template match="text()">
  <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="@*">
  <xsl:value-of select="."/>
</xsl:template>
 -->

</xsl:stylesheet>
