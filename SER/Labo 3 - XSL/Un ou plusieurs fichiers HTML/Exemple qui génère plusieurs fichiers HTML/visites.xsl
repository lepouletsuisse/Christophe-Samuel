<?xml version="1.0" ?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="html" media-type="text/html; charset=UTF-8"/>

<xsl:variable name="document_visites" select="document('visites.xml')"/>

<xsl:template match="/">

    <!-- Generation du fichier index.html - Visites triées par nom -->
    <xsl:result-document method="html" href="index.html" >
        <html>
            <head>
                <xsl:call-template name="entete_html"/>
            </head>
            <body>
                <xsl:call-template name="menu" />
                <xsl:apply-templates select="visites" mode="organisee_par_nom"/>
                <xsl:call-template name="pied_de_page" />
            </body>
        </html>
    </xsl:result-document>

    <!-- Generation du fichier visites_par_date.html - Visites triées par date -->    
    <xsl:result-document method="html" href="visites_par_date.html" >
        <html>
            <head>
                <xsl:call-template name="entete_html"/>
            </head>
            <body> 
                <xsl:call-template name="menu" />
                <xsl:apply-templates select="visites" mode="organisee_par_date"/>
                <xsl:call-template name="pied_de_page" />
            </body>
        </html>
    </xsl:result-document>

    <!-- Generation du fichier liste_des_parcours.html -->    
    <xsl:result-document method="html" href="liste_des_parcours.html" >
        <html>
            <head>
                <xsl:call-template name="entete_html"/>
            </head>
            <body>
                <xsl:call-template name="menu" />
                <xsl:call-template name="liste_des_parcours"/>
                <xsl:call-template name="pied_de_page" />
            </body>
        </html>
    </xsl:result-document>

    <!-- Generation du fichier liste_des_monuments.html -->    
    <xsl:result-document method="html" href="liste_des_monuments.html" >
        <html>
            <head>
                <xsl:call-template name="entete_html"/>
            </head>
            <body>
                <xsl:call-template name="menu" />
                <xsl:call-template name="liste_des_monuments"/>
                <xsl:call-template name="pied_de_page" />
            </body>
        </html>
    </xsl:result-document>


    <!-- Generation des fichiers de monuments -->    
    <xsl:for-each select="//monument[not( preceding::monument/nom_monument = nom_monument)]">
        <xsl:variable name="nom_du_monument" select="nom_monument" />
        <xsl:result-document method="html" href="monument_{$nom_du_monument}.html" >
            <html>
                <head>
                    <xsl:call-template name="entete_html"/>
                </head>
                <body>
                    <xsl:call-template name="menu" />
                    <xsl:apply-templates select="." mode="detail"/>
                    <xsl:call-template name="pied_de_page" />
                </body>
            </html>
        </xsl:result-document>
    </xsl:for-each>

    <!-- Generation des fichiers de parcours -->    
    <xsl:for-each select="//parcours[not( preceding::parcours/nom = nom)]">
        <xsl:variable name="nom_du_parcours" select="nom" />
        <xsl:result-document method="html" href="parcours_{$nom_du_parcours}.html" >
            <html>
                <head>
                    <xsl:call-template name="entete_html"/>
                </head>
                <body>
                    <xsl:call-template name="menu" />
                    <xsl:apply-templates select="." mode="detail"/>
                    <xsl:call-template name="pied_de_page" />
                </body>
            </html>
        </xsl:result-document>
    </xsl:for-each>
</xsl:template>

<xsl:template name="entete_html">
    <title>Listes visites guidées</title>
    <style type="text/css">
        @import url("./css/style.css");
    </style>
</xsl:template>

<xsl:template name="menu">
    <a href="index.html">Liste par nom</a>
    <xsl:text> </xsl:text>
    <a href="visites_par_date.html">Liste par date</a> 
</xsl:template>

<xsl:template name="pied_de_page">
    <br/>
    <br/>
    <a href="liste_des_parcours.html">Liste des parcours</a>
    <xsl:text> </xsl:text>
    <a href="liste_des_monuments.html">Liste des monuments</a> 
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
        <a href="parcours_{$nom_du_parcours}.html">
            <xsl:value-of select="nom"/>
        </a>
    </td>
    <td>
        <xsl:for-each select="./monuments/monument">
            <xsl:variable name="nom_du_monument" select="nom_monument" />
            <a href="monument_{$nom_du_monument}.html">
                <xsl:value-of select="nom_monument" />
            </a>
            <br/>
        </xsl:for-each>
    </td>
</xsl:template>

<xsl:template match="parcours" mode="liste">
    <xsl:variable name="nom_du_parcours" select="nom" />    
    <li>
        <b>
            <a href="parcours_{$nom_du_parcours}.html">
                <xsl:value-of select="nom"/>
            </a>
        </b>
        <xsl:text> </xsl:text>
        <xsl:value-of select="description" />
        <br/>
        <br/>
    </li>
</xsl:template>

<xsl:template match="parcours" mode="detail">
    <h1>Parcours <xsl:value-of select="nom"/> </h1>
    <xsl:value-of select="description" />
</xsl:template>

<xsl:template match="monument" mode="liste">
    <xsl:variable name="nom_du_monument" select="nom_monument" />
    <li>
        <b>
            <a href="monument_{$nom_du_monument}.html">
                <xsl:value-of select="nom_monument"/>
            </a>
        </b>
        <xsl:text> </xsl:text>
        <xsl:value-of select="description_monument" />
        <br/>
        <br/>
    </li>
</xsl:template>

<xsl:template match="monument" mode="detail">
    <h1>Monument <xsl:value-of select="nom_monument"/> </h1>
    <xsl:value-of select="description_monument" />
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