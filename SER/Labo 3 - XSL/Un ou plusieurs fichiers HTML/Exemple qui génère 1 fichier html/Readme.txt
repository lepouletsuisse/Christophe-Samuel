Exemple de traitement XSL/CSS pour une liste de visites organisées par un office de tourisme

Chaque visite est caractérisée par:
1/ Une date de visite
2/ Un parcours choisi parmi un certain nombre de parcours prédéfinis
	
Chaque parcours est lui-même caractérisé par la liste des monuments historiques qui seront visités

Dans cet exemple, les descriptions de parcours sont redondantes: Si le même parcours est prévu dans plusieurs visites, il sera décrit entièrement pour chacune des visites.

Pour voir le résultat: Ouvrir le fichier visites.xml avec le navigateur Firefox ou InternetExplorer



Un petit complément d’information.
La feuille XSL est relativement simple. 
A un moment donné, toutefois, elle fait appel à une expression XPath un peu tordue:

    <xsl:for-each select="//monument[not( preceding::monument/nom_monument = nom_monument)] »>

Il s’agit d’une boucle dans laquelle sont recherchés tous les monuments décrits dans le fichiers XML. 
Comme le fichiers XML est construit sur de la redondance, et qu’un monument fait partie de plusieurs visites, le même monument se retrouve décrit plusieurs fois dans le fichier XML.

L’expression XPath permet d’opérer une espèce de « distinct » SQL. Dans la boucle for-each, le noeud-élément monument n'est conservé que s’il n’a pas déjà été rencontré dans les noeuds monument qui le précèdent.






