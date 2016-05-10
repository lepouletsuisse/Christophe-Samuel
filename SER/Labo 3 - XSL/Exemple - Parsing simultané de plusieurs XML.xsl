<?xml version="1.0" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:variable name="document_1" select="document('document_1.xml')"/>
<xsl:variable name="document_2" select="document('document_2.xml')"/>


<xsl:template match="/">
<html>
	<head>
		<title>Essai</title>
	</head>
	<body>
		<xsl:apply-templates select="$document_1/element_racine" />
	</body>
</html>
</xsl:template>

[ etc.. ]


</xsl:stylesheet>