package Labo02;// classe fournissant des fonctions de lecture au clavier
import java.io.* ;

public class Clavier {

   // lecture d'une chaine
   public static String lireString() {
      String ligne_lue = null;
      try {
         InputStreamReader lecteur = new InputStreamReader(System.in);
         BufferedReader entree = new BufferedReader(lecteur);
         ligne_lue = entree.readLine();
      } catch (IOException err) {
         System.exit(-1);
      }
      return ligne_lue;
   }
   
   // lecture d'un float
   public static float lireFloat() {
      float x = 0;
      try {
         String ligne_lue = lireString();
         x = Float.parseFloat(ligne_lue);
      } catch (NumberFormatException err) {
         System.out.println("*** Erreur de donnee ***");
         System.exit(-1);
      }
      return x;
   }
  
   // lecture d'un double
   public static double lireDouble() {
      double x = 0;
      try {
         String ligne_lue = lireString();
         x = Double.parseDouble(ligne_lue);
      } catch (NumberFormatException err) {
         System.out.println("*** Erreur de donnee ***");
         System.exit(-1);
      }
      return x;
   }

   // lecture d'un int
   public static int lireInt() {
      int n = 0;
      try {
         String ligne_lue = lireString();
         n = Integer.parseInt(ligne_lue);
      } catch (NumberFormatException err) {
         System.out.println("*** Erreur de donnee ***");
         System.exit(-1);
      }
      return n;
   }
}


