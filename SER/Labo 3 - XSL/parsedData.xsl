<?xml version="1.0" ?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="html" media-type="text/html; charset=UTF-8"/>

<xsl:variable name="document_cinema" select="document('parsedData.xml')"/>

<xsl:template match="/">
<html>
    <head>
        <title>Listes des projections</title>
        <style type="text/css">
            @import url("./css/style.css");
        </style>
    </head>
    <body>
        <a name="home"/>
		<h1>Liste des projections</h1>
        <xsl:apply-templates select="cinema" mode="organisee_par_date"/>
		<xsl:apply-templates select="cinema" mode="organisee_par_titre"/>
    </body>
</html>
</xsl:template>

<xsl:template name="entete_tableau">
    <thead>
        <th>Date</th>
        <th>Titre</th>
        <th>Durée</th>
    </thead>
</xsl:template>

<xsl:template match="film" mode="tableau">
	<td><xsl:value-of select="../date"/></td>
	<td><xsl:value-of select="titre"/></td>
	<td><xsl:value-of select="duree"/></td>
	<br/><br/>
</xsl:template>

<xsl:template match="cinema" mode="organisee_par_date">
    <h2>Liste organisée par date</h2>
    <table cellspacing="10">
        <xsl:call-template name="entete_tableau"/>
        <tbody>
            <xsl:for-each select="//projection">
                <xsl:sort order="ascending" select="date"/>
                <tr>
                    <xsl:apply-templates select="film" mode="tableau"/>
                </tr>
            </xsl:for-each>
        </tbody>
    </table>
</xsl:template>

<xsl:template match="cinema" mode="organisee_par_titre">
    <h2>Liste organisée par titre</h2>
    <table cellspacing="10">
        <xsl:call-template name="entete_tableau"/>
        <tbody>
            <xsl:for-each select="//projection">
                <xsl:sort order="ascending" select="film/titre"/>
                <tr>
                    <xsl:apply-templates select="film" mode="tableau"/>
                </tr>
            </xsl:for-each>
        </tbody>
    </table>
</xsl:template>


</xsl:stylesheet>