Quelques remarques :

- 	3 projets Eclipse, les projets Server et Client nécessitent le projet Interfaces qui définit, 
	comme son nom l’indique, les interfaces de données et de communication

- 	Le client se connecte au serveur, récupère les données existantes et s’inscrit comme « observer »

- 	Le serveur possède une base de données fictive qu’il remplit de manière aléatoire. Lorsque de 
	données ont été générées, le serveur notifie les « Observers » (les clients) qui en retour 
	récupère la liste des dernières données

