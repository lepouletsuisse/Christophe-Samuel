/*
 -----------------------------------------------------------------------------------
 Laboratoire : 02
 Fichier     : Main.java
 Auteur(s)   : Samuel Darcey & Christophe Peretti
 Date        : 29.09.2015

 But         : Trouver la relation f() entre L et N où L est la distance parcourus
               par un robot qui effectue des mouvement aléatoire sur une grille de
               taille N x N

 Remarque(s) :

 Compilateur : jdk1.8.0_60
 -----------------------------------------------------------------------------------
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
   static final int MIN_TAILLE_GRILLE = 10;
   static final int MAX_TAILLE_GRILLE = 100;
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

   //Variable arithmétique
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
      for (grilleTaille = MIN_TAILLE_GRILLE; grilleTaille <= MAX_TAILLE_GRILLE; grilleTaille += 2) {
         nbCroisement = grilleTaille + 1;
         for (int i = 0; i < nbExperimentation; i++) {
            while (!estFini()) {
               mouvementAléatoire();
            }
            moyenne += distance;
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
   * initial
   * */
   public static void initialisation() {
      System.out.print("Entrez le nombre d'expérimentation (1'000 - 10'000): ");
      nbExperimentation = Clavier.lireInt();
      réinitialiserEtat();
   }

   /*
   * Reinitialise l'état du robot afin de faire une nouvelle experimentation
   * */
   public static void réinitialiserEtat() {
      distance = 0;
      robotVitesseFacteur = 1;
      robotX = grilleTaille / 2;
      robotY = grilleTaille / 2;
      estTouché = false;
      nordTouché = false;
      ouestTouché = false;
      sudTouché = false;
   }

   /*
   * Demande au robot de faire un mouvement aléatoire avec sa vitesse actuelle
   * */
   public static void mouvementAléatoire() {
      Random aléatoire = new Random();
      int nombreAléatoire = 0;
      nombreAléatoire = aléatoire.nextInt(8) + 1;
      mouvement(nombreAléatoire, ROBOT_VITESSE_INITIALE * robotVitesseFacteur);
   }

   /*
   * Demande au robot de faire un mouvement dans une direction précise de nbPas pas
   * et effectue le controle si le robot est toujours dans la grille après son
   * mouvement ou si il va rebondir. C'est un mouvement séquentiel, donc le robot
   * ne peut se déplacer que de 1 pas par itération de la boucle.
   * */
   public static void mouvement(int direction, int nbPas) {

      for (int i = 0; i < nbPas; i++) {
         switch (direction) {
            case EST:
               if (estMouvementAutorisé(robotX + 1, robotY)) {
                  pas(1, 0);
               } else {
                  pas(1, 0);
                  rebondie(direction);
                  return;
               }
               break;
            case NORD_EST:
               if (estMouvementAutorisé(robotX + 1, robotY - 1)) {
                  pas(1, -1);
               } else {
                  pas(1, -1);
                  rebondie(direction);
                  return;
               }
               break;
            case NORD:
               if (estMouvementAutorisé(robotX, robotY - 1)) {
                  pas(0, -1);
               } else {
                  pas(0, -1);
                  rebondie(direction);
                  return;
               }
               break;
            case NORD_OUEST:
               if (estMouvementAutorisé(robotX - 1, robotY - 1)) {
                  pas(-1, -1);
               } else {
                  pas(-1, -1);
                  rebondie(direction);
                  return;
               }
               break;
            case OUEST:
               if (estMouvementAutorisé(robotX - 1, robotY)) {
                  pas(-1, 0);
               } else {
                  pas(-1, 0);
                  rebondie(direction);
                  return;
               }
               break;
            case SUD_OUEST:
               if (estMouvementAutorisé(robotX - 1, robotY + 1)) {
                  pas(-1, 1);
               } else {
                  pas(-1, 1);
                  rebondie(direction);
                  return;
               }
               break;
            case SUD:
               if (estMouvementAutorisé(robotX, robotY + 1)) {
                  pas(0, 1);
               } else {
                  pas(0, 1);
                  rebondie(direction);
                  return;
               }
               break;
            case SUD_EST:
               if (estMouvementAutorisé(robotX + 1, robotY + 1)) {
                  pas(1, 1);
               } else {
                  pas(1, 1);
                  rebondie(direction);
                  return;
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
      /* Exception car la direction 0 n'existe pas mais correspond en realiter
      a 8 (SUD_EST).*/
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
   * Signal que le robot a touché un mur et met à jour les booleens
   * */
   public static void murTouché(int direction) {
      //Crée les booleens qui spécifie si notre robot se trouve dans un coin

      //Coin Nord-Ouest
      boolean condNO = robotX == 0 && robotY == 0 && direction == NORD_OUEST;

      //Coin Nord-Est
      boolean condNE = robotX == nbCroisement - 1 && robotY == 0 &&
              direction == NORD_EST;

      //Coin Sud-Ouest
      boolean condSO = robotX == 0 && robotY == nbCroisement - 1 &&
              direction == SUD_OUEST;

      //Coin Sud-Est
      boolean condSE = robotX == nbCroisement - 1 && robotY == nbCroisement - 1 &&
              direction == SUD_EST;

      if (condNO || condNE || condSO || condSE) return;

      /* Si nous sommes pas dans un coin, on set le boolean correspondant au bord
         qu'on touche à TRUE  */
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
