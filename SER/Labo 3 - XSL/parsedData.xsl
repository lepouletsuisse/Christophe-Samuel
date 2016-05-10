<?xml version="1.0" ?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="html" media-type="text/html; charset=UTF-8"/>

<xsl:variable name="document_cinema" select="document('parsedData.xml')"/>

<xsl:template match="/Projections">
<html>
    <head>
        <title>Listes des projections</title>
        <style type="text/css">
            @import url("./css/style.css");
        </style>
    </head>
    <body>
        <a name="home"/>
        <xsl:apply-templates select="projections" mode="organisee_par_date"/>
    </body>
</html>
</xsl:template>

<xsl:template name="entete_tableau">
    <thead>
        <th>projection</th>
    </thead>
</xsl:template>

<xsl:template match="film" mode="liste">
    <xsl:variable name="titre_du_film" select="titre" />
    <a name="{$titre_du_film}">
        <li>
            <b><xsl:value-of select="titre"/></b>
            <br/>
            <xsl:value-of select="duree"/>
            <br/>
            <a href="#home">Retour</a>
            <br/><br/>
        </li>
    </a>
</xsl:template>

<xsl:template match="projections" mode="organisee_par_date">
    <h1>Liste organisée par date</h1>
    <table cellspacing="10">
        <xsl:call-template name="entete_tableau"/>
        <tbody>
            <xsl:for-each select="projection">
                <xsl:sort order="ascending" select="date"/>
                    <xsl:sort order="ascending" select="film/titre"/>
                <tr>
                    <td><xsl:value-of select="date"/></td>
                    <xsl:apply-templates select="film" mode="tableau"/>
                </tr>
            </xsl:for-each>
        </tbody>
    </table>
</xsl:template>



</xsl:stylesheet>