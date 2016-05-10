Version 2 - Avec génération d'une hiérarchie de pages HTML

Pour voir le résultat, ouvrir le fichier index.html


Pour générer les fichiers HTML, effectuer une transformation XSLT en passant par l'utilitaire Saxon. La transformation XSL effectuée par le navigateur ne permet pas d'opérer la génération de ces différents fichiers.

Commande Windows permettant d'assurer la transformation XSL:
java -cp .;saxon9he.jar net.sf.saxon.Transform -s:visites.xml -xsl:visites.xsl


