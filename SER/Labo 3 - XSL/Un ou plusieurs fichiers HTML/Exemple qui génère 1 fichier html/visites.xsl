<?xml version="1.0" ?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="html" media-type="text/html; charset=UTF-8"/>

<xsl:variable name="document_visites" select="document('visites.xml')"/>

<xsl:template match="/">
<html>
    <head>
        <title>Listes visites guidées</title>
        <style type="text/css">
            @import url("./css/style.css");
        </style>
    </head>
    <body>
        <a name="home"/>
        <xsl:apply-templates select="visites" mode="organisee_par_nom"/>
        <xsl:apply-templates select="visites" mode="organisee_par_date"/>
        <xsl:call-template name="liste_des_parcours"/>
        <xsl:call-template name="liste_des_monuments"/>
    </body>
</html>
</xsl:template>

<xsl:template name="entete_tableau">
    <thead>
        <th>Date</th>
        <th>Parcours</th>
        <th>Monuments visités</th>
    </thead>
</xsl:template>

<xsl:template name="liste_des_parcours">
    <h1>Liste des parcours</h1>
    <xsl:for-each select="//parcours[not( preceding::parcours/nom = nom)]">
        <xsl:sort order="ascending" select="nom"/>
        <xsl:apply-templates select="." mode="liste"/>
    </xsl:for-each>
</xsl:template>

<xsl:template name="liste_des_monuments">
    <h1>Liste des monuments</h1>
    <xsl:for-each select="//monument[not( preceding::monument/nom_monument = nom_monument)]">
        <xsl:sort order="ascending" select="nom_monument"/>
        <xsl:apply-templates select="." mode="liste"/>
    </xsl:for-each>
</xsl:template>

<xsl:template match="parcours" mode="tableau">
    <xsl:variable name="nom_du_parcours" select="nom" />
    <td>
        <a href="#{$nom_du_parcours}">
            <xsl:value-of select="nom"/>
        </a>
    </td>
    <td>
        <xsl:for-each select="./monuments/monument">
            <xsl:variable name="nom_du_monument" select="nom_monument" />
            <a href="#{$nom_du_parcours}">
                <xsl:value-of select="nom_monument" />
            </a>
            <br/>
        </xsl:for-each>
    </td>
</xsl:template>

<xsl:template match="parcours" mode="liste">
    <xsl:variable name="nom_du_parcours" select="nom" />
    <a name="{$nom_du_parcours}">
        <li>
            <b><xsl:value-of select="nom"/></b>
            <br/>
            <xsl:value-of select="description" />
            <br/>
            <a href="#home">Retour</a>
            <br/><br/>
        </li>
    </a>
</xsl:template>

<xsl:template match="monument" mode="liste">
    <xsl:variable name="nom_du_monument" select="nom_monument" />
    <a name="{$nom_du_monument}">
        <li>
            <b><xsl:value-of select="nom_monument"/></b>
            <br/>
            <xsl:value-of select="description_monument" />
            <br/>
            <a href="#home">Retour</a>
            <br/><br/>
        </li>
    </a>
</xsl:template>

<xsl:template match="visites" mode="organisee_par_date">
    <h1>Liste organisée par date</h1>
    <table cellspacing="10">
        <xsl:call-template name="entete_tableau"/>
        <tbody>
            <xsl:for-each select="visite">
                <xsl:sort order="ascending" select="date"/>
                    <xsl:sort order="ascending" select="parcours/nom"/>
                <tr>
                    <td><xsl:value-of select="date"/></td>
                    <xsl:apply-templates select="parcours" mode="tableau"/>
                </tr>
            </xsl:for-each>
        </tbody>
    </table>
</xsl:template>
    

<xsl:template match="visites" mode="organisee_par_nom">
    <h1>Liste organisée par le nom des parcours</h1>
    <table cellspacing="10">
        <xsl:call-template name="entete_tableau"/>
        <tbody>
            <xsl:for-each select="visite">
                <xsl:sort order="ascending" select="parcours/nom"/>
                    <xsl:sort order="ascending" select="date"/>
                <tr>
                    <td><xsl:value-of select="date"/></td>
                    <xsl:apply-templates select="parcours" mode="tableau"/>
                </tr>
            </xsl:for-each>
        </tbody>
    </table>
</xsl:template>



</xsl:stylesheet>