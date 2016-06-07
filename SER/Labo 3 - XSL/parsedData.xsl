<?xml version="1.0" ?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:output method="html" media-type="text/html; charset=UTF-8"/>

<xsl:variable name="document_cinema" select="document('parsedData.xml')"/>

<xsl:template match="/">

<!-- Generation du fichier index.html -->
    <xsl:result-document method="html" href="index.html" >
        <html>
			<head>
				<xsl:call-template name="entete_html"/>
			</head>
			<body>
				<a name="home"/>
				<h1>Liste des projections</h1>
				<xsl:apply-templates select="cinema" mode="organisee_par_date"/>
				<xsl:apply-templates select="cinema" mode="organisee_par_titre"/>
				<xsl:apply-templates select="cinema" mode="organisee_par_note"/>
				<footer>
				</footer>
			</body>
		</html>
    </xsl:result-document>
	
<!-- Generation des fichiers des films -->    
    <xsl:for-each select="//film">
        <xsl:variable name="titre" select="titre" />
        <xsl:result-document method="html" href="film_{$titre}.html" >
            <html>
                <head>
                    <xsl:call-template name="entete_html"/>
                </head>
                <body>
                    <xsl:call-template name="menu" />
                    <xsl:apply-templates select="." mode="detail"/>
				<footer>
				</footer>
                </body>
            </html>
        </xsl:result-document>
    </xsl:for-each>
</xsl:template>

<xsl:template name="menu">
    <a href="index.html">Projections</a>
</xsl:template>

<xsl:template name="entete_tableau">
    <thead>
        <th>Date</th>
		<th>Salle</th>
        <th>Titre</th>
        <th>Durée</th>
		<th>Note moyenne</th>
    </thead>
</xsl:template>

<xsl:template name="entete_html">
    <title>Listes des projections</title>
    <style type="text/css">
        @import url("./css/style.css");
    </style>
</xsl:template>

<xsl:template match="film" mode="detail">
    <h1><xsl:value-of select="titre"/></h1>
	<xsl:variable name="url_img" select="image" />
	<img src="{$url_img}" width="300" height="auto"/>
	<h2>Durée</h2>
	<xsl:value-of select="duree" />min
	<h2>Synopsis</h2>
    <xsl:value-of select="synopsis" />
	<h2>Critiques</h2>
	<table>
		<thead>
			<th>Note</th>
			<th>Avis</th>
		</thead>
		<tbody>
			<xsl:for-each select="critiques/critique">
			<xsl:sort data-type="number" order="descending" select="note"/>
				<tr>
					<td><xsl:value-of select="note" /></td>
					<td><xsl:value-of select="texte" /></td>
				</tr>
			</xsl:for-each>
		</tbody>
	</table>
	<h2>Genres</h2>
    <xsl:value-of select="genres" />
	<h2>Mots-clés</h2>
    <xsl:value-of select="motCle" />
	<h2>Langues</h2>
    <xsl:value-of select="langages" />
	<h2>Acteurs</h2>
	<table>
		<thead>
			<th>Nom</th>
			<th>Rôle</th>
		</thead>
		<tbody>
			<xsl:for-each select="roles/role">
			<xsl:sort data-type="number" order="ascending" select="@place"/>
				<xsl:variable name="id_acteur" select="idActeur" />
				<tr>
					<td class="infoActeur"><xsl:value-of select="../../../acteurs/acteur[@id=$id_acteur]/nom" />
						<span>
							<table>
								<tr>
									<td>Genre :</td>
									<td><xsl:value-of select="../../../acteurs/acteur[@id=$id_acteur]/sexe" /></td>
								</tr>
								<tr>
									<td>Date Naissance :</td>
									<td><xsl:value-of select="../../../acteurs/acteur[@id=$id_acteur]/dateNaissance" /></td>
								</tr>
								<tr>
									<td>Date décès :</td>
									<td><xsl:value-of select="../../../acteurs/acteur[@id=$id_acteur]/dateDeces" /></td>
								</tr>
							</table>
							Biographie :<br/>
							<xsl:value-of select="../../../acteurs/acteur[@id=$id_acteur]/biographie" />
						</span>
					</td>
					<td><xsl:value-of select="personnage" /></td>
				</tr>
			</xsl:for-each>
		</tbody>
	</table>
</xsl:template>

<xsl:template match="film" mode="tableau">
	<td><xsl:value-of select="../date"/></td>
	<td><xsl:value-of select="../numeroSalle"/></td>
	<xsl:variable name="titre_film" select="titre" />
	<td><a href="film_{$titre_film}.html"><xsl:value-of select="titre"/></a></td>
	<td><xsl:value-of select="duree"/></td>
	<td><xsl:value-of select="noteMoyenne"/></td>
	<br/><br/>
</xsl:template>

<xsl:template match="cinema" mode="organisee_par_date">
    <h2>Liste organisée par date</h2>
    <table class="index" cellspacing="10">
        <xsl:call-template name="entete_tableau"/>
        <tbody>
            <xsl:for-each select="//projection">
                <xsl:sort order="ascending" select="@date"/>
                <tr>
                    <xsl:apply-templates select="film" mode="tableau"/>
                </tr>
            </xsl:for-each>
        </tbody>
    </table>
</xsl:template>

<xsl:template match="cinema" mode="organisee_par_titre">
    <h2>Liste organisée par titre</h2>
    <table class="index" cellspacing="10">
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

<xsl:template match="cinema" mode="organisee_par_note">
    <h2>Liste organisée par note moyenne</h2>
    <table class="index" cellspacing="10">
        <xsl:call-template name="entete_tableau"/>
        <tbody>
            <xsl:for-each select="//projection">
                <xsl:sort order="descending" select="film/noteMoyenne"/>
                <tr>
                    <xsl:apply-templates select="film" mode="tableau"/>
                </tr>
            </xsl:for-each>
        </tbody>
    </table>
</xsl:template>



</xsl:stylesheet>