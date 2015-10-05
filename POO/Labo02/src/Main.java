/*
 -----------------------------------------------------------------------------------
 Laboratoire : 02
 Fichier     : Main.java
 Auteur(s)   : Samuel Darcey & Christophe Peretti
 Date        : 29.09.2015

 But         : Trouver la relation f() entre L et la taille N d'un problème de grille

 Remarque(s) :

 Compilateur : jdk1.8.0_60
 -----------------------------------------------------------------------------------
*/

/*
Testé pour 1000 experimentation par taille en 24 secondes
Testé pour 2000 experimentation par taille en 51 secondes
Testé pour 3000 experimentation par taille en 76 secondes
Testé pour 4000 experimentation par taille en 103 secondes
Testé pour 5000 experimentation par taille en 129 secondes
Testé pour 6000 experimentation par taille en 155 secondes
Testé pour 7000 experimentation par taille en 180 secondes
Testé pour 8000 experimentation par taille en 205 secondes
Testé pour 9000 experimentation par taille en 232 secondes
Testé pour 10000 experimentation par taille en 256 secondes
 */

import java.util.Random;

public class Main {
   //CONSTANTES----------------------------------------------------------------------
   //Constantes pour les directions
   static final int EST = 1;
   static final int NORD_EST = 2;
   static final int NORD = 3;
   static final int NORD_OUEST = 4;
   static final int OUEST = 5;
   static final int SUD_OUEST = 6;
   static final int SUD = 7;
   static final int SUD_EST = 8;

   //Constante pour le robot
   static final int ROBOT_VITESSE_INITIALE = 1;

   //Constante pour l'arithmétique
   static final double LONGUEUR_PAS = 1;
   static final double LONGUEUR_PAS_DIAG = Math.sqrt(2);

   //VARIABLES-----------------------------------------------------------------------
   //Variables du robot
   static int robotX = 0;
   static int robotY = 0;
   static int robotVitesseFacteur = 1;
   static double distance = 0;
   static boolean estTouché = false;
   static boolean nordTouché = false;
   static boolean ouestTouché = false;
   static boolean sudTouché = false;

   //Variables de la grille
   static int grilleTaille = 10;
   static int nbCroisement = grilleTaille + 1;

   //Variables arithmétique & logique
   static double moyenne = 0;

   //Variable utilisateur
   static int nbExperimentation;

   /*
    Axes de la grille:
    0 ------------- X
    |
    |
    |
    |
    Y
    */
   public static void main(String args[]) {
      initialisation();
      for (grilleTaille = 10; grilleTaille <= 100; grilleTaille += 1) {
         nbCroisement = grilleTaille + 1;
         robotX = grilleTaille / 2;
         robotY = grilleTaille / 2;
         for (int i = 0; i < nbExperimentation; i++) {
            while (!estFini()) {
               mouvementAléatoire();
            }
            moyenne += distance;
            /*afficherGraphique();
            afficherInformation();
            Clavier.lireInt();*/
            réinitialiserEtat();
         }
         moyenne /= (double) nbExperimentation;
         System.out.println("Taille de grille: " + grilleTaille + " // Moyenne: "
                 + moyenne);
         moyenne = 0;
      }
   }

   /*
   * Demande le nombre d'expérimentation à l'utilisateur et met le robot à l'état
   * initiale
   * */
   public static void initialisation() {
      System.out.print("Entrez le nombre d'expérimentation (1'000 - 10'000): ");
      nbExperimentation = Clavier.lireInt();
   }

   /*
   * Reinitialise l'état du robot afin de faire une nouvelle experimentation
   * */
   public static void réinitialiserEtat() {
      distance = 0;
      robotVitesseFacteur = 1;
      estTouché = false;
      nordTouché = false;
      ouestTouché = false;
      sudTouché = false;
   }

   /*
   * Affiche les différentes informations concernant le robot ainsi que la grille
   * */
   public static void afficherInformation() {
      System.out.println(
              "robotX: " + robotX +
                      " // robotY: " + robotY +
                      " // robotVitesseFacteur: " + robotVitesseFacteur +
                      " // grilleTaille: " + grilleTaille +
                      " // nbCroisement: " + nbCroisement +
                      " // distance: " + distance +
                      " // Mur touché: " +
                      (estTouché ? "Est " : "") +
                      (nordTouché ? "Nord " : "") +
                      (ouestTouché ? "Ouest " : "") +
                      (sudTouché ? "Sud " : ""));
   }

   /*
   * Affiche le robot et la grille de manière graphique ou X est le robot
   * */
   public static void afficherGraphique() {
      System.out.println("Vitesse: " + ROBOT_VITESSE_INITIALE * robotVitesseFacteur);
      for (int ligne = 0; ligne < nbCroisement; ligne++) {
         for (int colonne = 0; colonne < nbCroisement; colonne++) {
            if (ligne == robotY && colonne == robotX) {
               System.out.print("X "); //Affiche le robot
            } else {
               System.out.print("O "); //Affiche un croisement vide
            }
         }
         System.out.println();
      }
   }

   /*
   * Fonction de debug affichant des informations supplémentaire utilisant la
   * direction actuelle du robot et son nombre de pas
   * */
   public static void déverminer(int direction, int nbPas) {
      afficherGraphique();
      System.out.print("Bouge direction ");
      if (direction == EST) System.out.print("Est");
      if (direction == NORD_EST) System.out.print("Nord-Est");
      if (direction == NORD) System.out.print("Nord");
      if (direction == NORD_OUEST) System.out.print("Nord-Ouest");
      if (direction == OUEST) System.out.print("Ouest");
      if (direction == SUD_OUEST) System.out.print("Sud-Ouest");
      if (direction == SUD) System.out.print("Sud");
      if (direction == SUD_EST) System.out.print("Sud-Est");
      System.out.println(" pour " + nbPas + " pas");
      afficherInformation();
      Clavier.lireInt();
   }

   /*
   * Demande au robot de faire un mouvement aléatoire avec sa vitesse actuelle
   * */
   public static void mouvementAléatoire() {
      Random aléatoire = new Random();
      int nombreAléatoire = 0;
      while (nombreAléatoire <= 0) { // Ne prends que les nombre positif
         nombreAléatoire = (aléatoire.nextInt() % 8) + 1;
      }
      mouvement(nombreAléatoire, ROBOT_VITESSE_INITIALE * robotVitesseFacteur);
   }

   /*
   * Demande au robot de faire un mouvement dans une direction précis de nbPas pas
   * et effectue le controle si le robot est toujours dans la grille après son
   * mouvement ou si il va rebondire. C'est un mouvement séquentiel, donc le robot
   * ne peut se déplacer que de 1 pas par itération de la boucle.
   * */
   public static void mouvement(int direction, int nbPas) {
      //déverminer(direction,nbPas);
      BOUCLE:
      //Label pour break la boucle
      for (int i = 0; i < nbPas; i++) {
         switch (direction) {
            case EST: // Est
               if (estMouvementAutorisé(robotX + 1, robotY)) {
                  pas(1, 0);
               } else {
                  pas(1, 0);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
            case NORD_EST: // North-East
               if (estMouvementAutorisé(robotX + 1, robotY - 1)) {
                  pas(1, -1);
               } else {
                  pas(1, -1);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
            case NORD: // North
               if (estMouvementAutorisé(robotX, robotY - 1)) {
                  pas(0, -1);
               } else {
                  pas(0, -1);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
            case NORD_OUEST: // North-West
               if (estMouvementAutorisé(robotX - 1, robotY - 1)) {
                  pas(-1, -1);
               } else {
                  pas(-1, -1);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
            case OUEST: // West
               if (estMouvementAutorisé(robotX - 1, robotY)) {
                  pas(-1, 0);
               } else {
                  pas(-1, 0);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
            case SUD_OUEST: // South-West
               if (estMouvementAutorisé(robotX - 1, robotY + 1)) {
                  pas(-1, 1);
               } else {
                  pas(-1, 1);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
            case SUD: // South
               if (estMouvementAutorisé(robotX, robotY + 1)) {
                  pas(0, 1);
               } else {
                  pas(0, 1);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
            case SUD_EST: // South-East
               if (estMouvementAutorisé(robotX + 1, robotY + 1)) {
                  pas(1, 1);
               } else {
                  pas(1, 1);
                  rebondie(direction);
                  break BOUCLE;
               }
               break;
         }
      }
   }

   /*
   * Effectue un mouvement de 1 pas en ajoutant x et y au positions du robot et
   * incrémente la distance
   * */
   public static void pas(int x, int y) {
      robotX += x;
      robotY += y;
      if (x != 0 && y != 0) distance += LONGUEUR_PAS_DIAG;
      else distance += LONGUEUR_PAS;
   }

   /*
   * Ordonne au robot de rebondir dans le sens opposé dont il vient.
   * */
   public static void rebondie(int directionSource) {
      int directionDestination = (directionSource + 4) % 8;
      murTouché(directionSource);
      if (directionDestination != 0) {
         mouvement(directionDestination, 1);
      } else {
         mouvement(SUD_EST, 1);
      }
   }

   /*
   * Controle si la position du robot + x,y est autorisé (dans la grille)
   * */
   public static boolean estMouvementAutorisé(int x, int y) {
      return x < nbCroisement - 1 && x > 0 && y < nbCroisement - 1 && y > 0;
   }

   /*
   * Signal que le robot à touché un mur et met à jour les booleens
   * */
   public static void murTouché(int direction) {
      boolean condNO = robotX == 0 && robotY == 0 && direction == NORD_OUEST;
      boolean condNE = robotX == nbCroisement - 1 && robotY == 0 && direction ==
              NORD_EST;
      boolean condSO = robotX == 0 && robotY == nbCroisement - 1 && direction ==
              SUD_OUEST;
      boolean condSE = robotX == nbCroisement - 1 && robotY == nbCroisement - 1 &&
              direction == SUD_EST;

      if (condNO || condNE || condSO || condSE) return;

      switch (direction) {
         case EST:
            if (!estTouché && robotVitesseFacteur < 4) robotVitesseFacteur++;
            estTouché = true;
            break;
         case NORD_EST:
            if (robotY - 1 < 0 && !nordTouché) {
               nordTouché = true;
               robotVitesseFacteur++;
            } else if (robotX + 1 >= nbCroisement && !estTouché) {
               estTouché = true;
               robotVitesseFacteur++;
            }
            break;
         case NORD:
            if (!nordTouché && robotVitesseFacteur < 4) robotVitesseFacteur++;
            nordTouché = true;
            break;
         case NORD_OUEST:
            if (robotY - 1 < 0 && !nordTouché) {
               nordTouché = true;
               robotVitesseFacteur++;
            } else if (robotX - 1 < 0 && !ouestTouché) {
               ouestTouché = true;
               robotVitesseFacteur++;
            }
            break;
         case OUEST:
            if (!ouestTouché && robotVitesseFacteur < 4) robotVitesseFacteur++;
            ouestTouché = true;
            break;
         case SUD_OUEST:
            if (robotY + 1 >= nbCroisement && !sudTouché) {
               sudTouché = true;
               robotVitesseFacteur++;
            } else if (robotX - 1 < 0 && !ouestTouché) {
               ouestTouché = true;
               robotVitesseFacteur++;
            }
            break;
         case SUD:
            if (!sudTouché && robotVitesseFacteur < 4) robotVitesseFacteur++;
            sudTouché = true;
            break;
         case SUD_EST:
            if (robotY + 1 >= nbCroisement && !sudTouché) {
               sudTouché = true;
               robotVitesseFacteur++;
            } else if (robotX + 1 >= nbCroisement && !estTouché) {
               estTouché = true;
               robotVitesseFacteur++;
            }
            break;
         default:
      }
   }

   /*
   * Controle si le robot a touché les 4 murs
   * */
   public static boolean estFini() {
      return nordTouché && estTouché && sudTouché && ouestTouché;
   }
}
