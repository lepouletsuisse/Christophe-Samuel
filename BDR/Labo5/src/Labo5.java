/*
   Fichier :   Labo5.java
   Auteurs :   Samuel Darcey et Christophe Peretti
   Date    :   04.01.2016
 */

import java.sql.*;
import java.util.Date;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Labo5 extends Thread {

   private static final Logger mLog = Logger.getLogger(Labo5.class.getName());
   private static final Scanner mScanner = new Scanner(System.in);
   private Connection mConnection;

   public static void main(String... args) {
      new Labo5().start();
   }

   @Override
   public void run() {
      try {
         init();
         //query1();
         //query2();
         //query3();
         //query4();
         //query5();
      } catch (SQLException e) {
         mLog.log(Level.SEVERE, e.getMessage());
      } finally {
         if (mConnection != null) {
            try {
               mConnection.close();
            } catch (SQLException e) {
               mLog.log(Level.SEVERE, e.getMessage());
            }
         }
      }
   }

   private void init() throws SQLException {
      String url = "jdbc:mysql://localhost:3306/sakila?user=root&password=toor";
      mConnection = DriverManager.getConnection(url);
   }

   private void query1() throws SQLException {
      System.out.println("Exercice 1 :");
      Statement statement = mConnection.createStatement();
      String query = "select * from film limit 10";
      ResultSet result = statement.executeQuery(query);

      while (result.next()) {
         int film_id = result.getInt("FILM_ID");
         String title = result.getString("TITLE");
         String description = result.getString("DESCRIPTION");
         int release_year = result.getInt("RELEASE_YEAR");
         int language_id = result.getInt("LANGUAGE_ID");
         int original_language_id = result.getInt("ORIGINAL_LANGUAGE_ID");
         int rental_duration = result.getInt("RENTAL_DURATION");
         double rental_rate = result.getDouble("RENTAL_RATE");
         double length = result.getDouble("LENGTH");
         double replacement_cost = result.getDouble("REPLACEMENT_COST");
         String rating = result.getString("RATING");
         String special_features = result.getString("SPECIAL_FEATURES");
         Date last_update = result.getTimestamp("LAST_UPDATE");

         String chaine = String.format("%-2s %-17s %-117s %s %s %s %s %s %-5s %s %-5s %-32s %s ",
            film_id, title, description, release_year, language_id,
            original_language_id, rental_duration, rental_rate, length,
            replacement_cost, rating, special_features, last_update);
         System.out.println(chaine);

      }

   }

   private void query2() throws SQLException {
      System.out.println("Exercice 2 :");
      String[] first_name = {"BOB", "BILL", "PAUL", "JOHN", "JACK", "JOE", "JIM",
                             "EDDY", "MATT", "KEVIN"};
      String[] last_name = {"HOPKINS", "JOHNSON", "BALE", "ALLEN", "CROWE", "JACKMAN",
                            "PRESLEY", "WILLIS", "DEPP", "PITT"};
     PreparedStatement preparedStatement;
      String query = "insert into Sakila.actor (first_name, last_name) values" +
                     "(?, ?)";
      preparedStatement = mConnection.prepareStatement(query);
      for(int i = 0; i < 10; i++){
         preparedStatement.setString(1, first_name[i]);
         preparedStatement.setString(2, last_name[i]);
         preparedStatement.executeUpdate();
      }
   }

   private void query3() throws SQLException {
      ResultSet result, generatedKeys;
      Statement statement;
      PreparedStatement preparedStatement;
      int taille;
      String query;
      System.out.println("Exercice 3 :");

      // Get your staff number
      String staffNumber = getStaffNumber();


      do {
         // Get an actor's last name
         String actorLastName = getActorLastName();

         // Print the list of actors with this last name
         statement = mConnection.createStatement();
         query = "select first_name, last_name from actor where last_name = '" + actorLastName + "'";
         result = statement.executeQuery(query);

         result.last();
         taille = result.getRow();
         result.beforeFirst();
         if (taille == 0){
            System.out.println("Aucun film avec cet acteur, veuillez recommencer...");
         }
      } while (taille == 0);

      String[] tabChoix = new String[taille];
      String[] tabPrenom = new String[taille];
      String[] tabNom = new String[taille];

      int i = 0;
      String choixUtilisateur;
      while (result.next()) {
         String first_name = result.getString("first_name");
         String last_name = result.getString("last_name");

         String chaine = String.format("%-2s : %-12s %s", i + 1, first_name, last_name);
         tabPrenom[i] = first_name;
         tabNom[i] = last_name;
         tabChoix[i++] = chaine;
      }

      // Get the user's choice
      // Attention, ici le choix commence à 1, donc modifié dans getUserChoice() :
      // if (value >= choices.length) ====> if (value > choices.length)
      choixUtilisateur = getUserChoice(tabChoix);

      // Print the list of movies of this actor
      String acteurPrenom = tabPrenom[Integer.valueOf(choixUtilisateur) - 1];
      String acteurNom = tabNom[Integer.valueOf(choixUtilisateur) - 1];
      query = "select distinct title, film.film_id, rental_rate " +
         "from film " +
         "inner join film_actor on film.film_id = film_actor.film_id " +
         "inner join actor  on film_actor.actor_id = actor.actor_id " +
         "where actor.last_name like '" + acteurNom + "' " +
         "and actor.first_name like '" + acteurPrenom + "'";
      result = statement.executeQuery(query);

      result.last();
      taille = result.getRow();

      result.beforeFirst();
      tabChoix = new String[taille];
      String[] tabFilm = new String[taille];
      double[] tabAmount = new double[taille];
      String choixFilm;
      double amount;
      i = 0;
      while (result.next()) {
         choixFilm = result.getString("title");
         amount = result.getDouble("rental_rate");
         String chaine = String.format("%-2s : %s", i + 1, choixFilm);
         tabFilm[i] = choixFilm;
         tabAmount[i] = amount;
         tabChoix[i++] = chaine;
      }


      // Get the user's choice
      choixUtilisateur = getUserChoice(tabChoix);

      choixFilm = tabFilm[Integer.valueOf(choixUtilisateur) - 1];
      amount = tabAmount[Integer.valueOf(choixUtilisateur) - 1];
      System.out.println("Vous avez choisi : " + choixFilm + ", Prix de la location: " + Double.toString(amount) + "$");

      // Listing des inventaires du film choisi. Attention, choix d'implémentation:
      // Tous les inventaires sont listés, y compris ceux des autres magasins.
      // On suppose que le client se débrouille pour aller chercher son exemplaire ailleurs
      query =  "select distinct inventory.inventory_id, inventory.store_id " +
               "from film " +
               "inner join inventory on film.film_id = inventory.film_id " +
               "inner join rental  on inventory.inventory_id = rental.inventory_id " +
               "where  rental.return_date is not null " +
               "and film.title like '" + choixFilm + "'";
      result = statement.executeQuery(query);

      result.last();
      taille = result.getRow();
      result.beforeFirst();
      tabChoix = new String[taille];
      String[] tabInventory = new String[taille];
      String[] tabMagasin = new String[taille];
      String inventory, magasin;

      i = 0;
      while (result.next()) {
         inventory = result.getString("inventory_id");
         magasin = result.getString("store_id");
         String chaine = String.format("%-2s : inventaire %-2s, magasin %s", i + 1, inventory, magasin);
         tabInventory[i] = inventory;
         tabMagasin[i] = magasin;
         tabChoix[i++] = chaine;
      }
      // Get the user's choice
      choixUtilisateur = getUserChoice(tabChoix);

      inventory = tabInventory[Integer.valueOf(choixUtilisateur) - 1];
      magasin = tabMagasin[Integer.valueOf(choixUtilisateur) - 1];
      // Get the user's first name
      String userFirstName = getUserFirstName();
      // Get the user's last name
      String userLastName = getUserLastName();

      // Check if client already exists
      int customerId = 0;
      query =  "select count(*) as present, " +
                      "customer_id " +
               "from customer " +
               "where  first_name like '" + userFirstName + "'" +
               "and last_name like '" + userLastName + "'";
      result = statement.executeQuery(query);
      result.next();
      int present = result.getInt("present");

      if (present == 1){
         customerId = result.getInt("customer_id");
      }
      // If not, create him (country, city, district, etc...)
      if (present == 0){
         int countryId, cityId, addressId;

         String userCountry = getUserCountry();
         String userCity = getUserCity();


         // Vérification de l'existence du pays
         query =  "select count(*) as present, " +
                         "country_id " +
                  "from country " +
                  "where  country like '" + userCountry + "'";
         result = statement.executeQuery(query);
         result.next();
         present = result.getInt("present");

         // Cas où le pays n'existe pas
         if (present < 1){

            query =  "insert into Sakila.country (country) values ('" + userCountry + "')";
            preparedStatement = mConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.executeUpdate();

            generatedKeys = preparedStatement.getGeneratedKeys();
            generatedKeys.next();
            countryId = generatedKeys.getInt(1);
         } else {
            // Cas où le pays existe
            countryId = result.getInt("country_id");
         }

         // Vérification de l'existence de la ville
         query =  "select count(*) as present, " +
                         "country_id, " +
                         "city_id " +
                  "from city " +
                  "where  city like '" + userCity + "' " +
                  "and country_id = '" + Integer.toString(countryId) + "'";
         result = statement.executeQuery(query);
         result.next();
         present = result.getInt("present");

         // Si le couple (ville, country_id) n'existe pas, on insert la ville
         if (present < 1){


            query =  "insert into Sakila.city (city, country_id) values ('" + userCity + "', '" + countryId + "')";
            preparedStatement = mConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.executeUpdate();
            generatedKeys = preparedStatement.getGeneratedKeys();
            generatedKeys.next();
            cityId = generatedKeys.getInt(1);
         } else {
            cityId = result.getInt("city_id");
         }

         // Get user's district
         String userDistrict = getUserDistrict();
         // Get user's phone
         String userPhone =  getUserPhone();
         // Get user's address
         String userAddress = getUserAddress();
         // Get user's postal code
         String userPostalCode = getUserPostalCode();

         // Vérification de l'existence de l'adresse (adresse, ville, tel)
         query =  "select count(*) as present, " +
                         "address_id, " +
                         "city_id " +
            "from address " +
            "where address like '" + userAddress + "' " +
            "and city_id like '" + Integer.toString(cityId) + "' " +
            "and phone like '" + userPhone + "'";
         result = statement.executeQuery(query);
         result.next();
         present = result.getInt("present");

         // Si le tuple (adresse, ville, tel) n'existe pas, on insert l'adresse
         if (present < 1){

            query =  "insert into Sakila.address (address, district, city_id, postal_code, phone) " +
                     "values ('" + userAddress + "', '" + userDistrict + "', '" + cityId + "', '" + userPostalCode + "', '" + userPhone + "')";
            preparedStatement = mConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            preparedStatement.executeUpdate();
            generatedKeys = preparedStatement.getGeneratedKeys();
            generatedKeys.next();
            addressId = generatedKeys.getInt(1);
         } else {
            addressId = result.getInt("address_id");
         }

         // Création du client

         query =  "insert into Sakila.customer (store_id, first_name, last_name, email, address_id, create_date) " +
                  "values ('" + magasin + "', '" + userFirstName + "', '" + userLastName + "', '', '" + addressId + "', NOW() )";
         preparedStatement = mConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
         preparedStatement.executeUpdate();

         generatedKeys = preparedStatement.getGeneratedKeys();
         generatedKeys.next();
         customerId = generatedKeys.getInt(1);

      } else {
         // Si le client existe déjà
         int nombreLocations;
         query =  "select count(*) as nombre " +
                  "from rental " +
                  "where  customer_id = '" + Integer.toString(customerId) + "' " +
                  "and return_date is null";
         result = statement.executeQuery(query);
         result.next();
         nombreLocations = result.getInt("nombre");

         if (nombreLocations >= 10){
            System.out.println("Il y a deja " + Integer.toString(nombreLocations) +
                               " locations en cours... impossible d'en faire plus");
            return;
         }

      }
      // Insertion de la location dans la DB
      int rentalId;

      query =  "insert into Sakila.rental (rental_date, inventory_id, customer_id, return_date, staff_id) " +
               "values (NOW(), '" + inventory + "', '" + customerId + "', null, '" + staffNumber + "')";
      preparedStatement = mConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
      preparedStatement.executeUpdate();
      generatedKeys = preparedStatement.getGeneratedKeys();
      generatedKeys.next();
      rentalId = generatedKeys.getInt(1);

      System.out.println("Prix de la location : " + amount + "$");
      System.out.println("Veuillez payer maintenant...");

      // Insertion du paiement dans la DB
      query =  "insert into Sakila.payment (customer_id, staff_id, rental_id, amount, payment_date) " +
               "values ('" + customerId + "', '" + staffNumber + "', '" + rentalId + "', '" + Double.toString(amount) + "', NOW())";
      preparedStatement = mConnection.prepareStatement(query);
      preparedStatement.executeUpdate();
      System.out.println("Paiement enregistre");
   }

   private void query4() throws SQLException {
      Statement statement;
      ResultSet result;
      int nombreFilms;

      System.out.println("Exercice 4 :");
      String[] category = {"action", "animation", "children", "classics", "comedy",
         "documentary", "drama", "family", "foreign", "games", "horror",
         "music", "new", "sci-fi", "sports", "travel"};

      String dropProcedure = "drop procedure if exists nombreFilmsCategorie";
      statement = mConnection.createStatement();
      statement.execute(dropProcedure);

      //Création de la procédure
      String createProcedure = "create procedure nombreFilmsCategorie (in cat varchar(25)) " +
                               "select count(*) as nombre from film_category inner join category " +
                               "on film_category.category_id = category.category_id " +
                               "where name like cat";
      statement = mConnection.createStatement();
      statement.execute(createProcedure);

      // Utilisation de la procédure
      for(int i = 0; i < category.length; i++){
         CallableStatement callableStatement = mConnection.prepareCall("{call nombreFilmsCategorie('" + category[i] + "')}");
         result = callableStatement.executeQuery();
         result.next();
         nombreFilms = result.getInt("nombre");
         System.out.format("%-13s : %s\n", category[i], Integer.toString(nombreFilms));
      }
   }

   private void query5() throws SQLException {
      Statement statement;
      ResultSet result;
      String pays, ville;
      double somme;
      System.out.println("Exercice 5 :");

      String dropView = "drop view if exists revenu_par_localite";
      statement = mConnection.createStatement();
      statement.execute(dropView);

      //Création de la vue
      String createView = "create view revenu_par_localite as " +
                          "select postal_code as code_postal, city as ville, country as pays, sum(amount) as somme_totale " +
                          "from payment inner join customer on payment.customer_id = customer.customer_id " +
                          "inner join address on customer.address_id = address.address_id " +
                          "inner join city on address.city_id = city.city_id " +
                          "inner join country on city.country_id = country.country_id " +
                          "group by city";
      statement = mConnection.createStatement();
      statement.execute(createView);

      // Utilisation de la vue
      String utilVue = "select ville, pays, somme_totale from revenu_par_localite order by somme_totale desc";
      statement = mConnection.createStatement();
      statement.execute(utilVue);
      result = statement.executeQuery(utilVue);
      while(result.next()){
         pays = result.getString("pays");
         ville = result.getString("ville");
         somme = result.getDouble("somme_totale");
         System.out.format("%-7s: %-27s %-38s\n", Double.toString(somme), ville, pays);
      }

   }

   private String getStaffNumber() {
      System.out.println("Please enter your staff number : ");
      String input = mScanner.nextLine();
      try {
         Integer.valueOf(input);
      } catch (NumberFormatException e ){
         System.out.println("It's not a valid number !");
         return getStaffNumber();
      }
      return input;
   }

   private String getActorLastName() {
      System.out.println("Please enter an actor's last name : ");
      return mScanner.nextLine();
   }

   private String getUserChoice(String[] choices) {
      System.out.println("Please choose one of the next option :");
      for (String s : choices) {
         System.out.println(s);
      }
      String input = mScanner.nextLine();
      try {
         int value = Integer.valueOf(input);
         if (value > choices.length) {
            System.out.println("It's not a valid option !");
            getUserChoice(choices);
         }
      } catch (NumberFormatException e ){
         System.out.println("It's not a valid number !");
         return getUserChoice(choices);
      }
      return input;
   }

   private String getUserFirstName() {
      System.out.println("Please enter the client's first name : ");
      return mScanner.nextLine();
   }

   private String getUserLastName() {
      System.out.println("Please enter the client's last name : ");
      return mScanner.nextLine();
   }

   private String getUserCountry() {
      System.out.println("Please enter a country : ");
      return mScanner.nextLine();
   }

   private String getUserCity() {
      System.out.println("Please enter a city : ");
      return mScanner.nextLine();
   }

   private String getUserPhone() {
      System.out.println("Please enter a phone number : ");
      return mScanner.nextLine();
   }

   private String getUserDistrict() {
      System.out.println("Please enter a district : ");
      return mScanner.nextLine();
   }

   private String getUserPostalCode() {
      System.out.println("Please enter a postal code : ");
      return mScanner.nextLine();
   }

   private String getUserAddress() {
      System.out.println("Please enter an address : ");
      return mScanner.nextLine();
   }
}