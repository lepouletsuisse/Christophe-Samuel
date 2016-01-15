import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class JDBCTest extends Thread {
    
    private static final Logger mLog = Logger.getLogger(JDBCTest.class.getName()); 
    private static final Scanner mScanner = new Scanner(System.in);
    private Connection mConnection;
    
    public static void main(String... args) {
        new JDBCTest().start();
    }
    
    @Override
    public void run() {
        try {
            init();
            query1();
            query2();
            query3();
            query4();
            query5();
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
        // Example URL, update accordingly !
        String url = "jdbc:mysql://localhost:3306/sakila?user=root&password=toor";
        mConnection = DriverManager.getConnection(url);
    }
    
    private void query1() throws SQLException {
        System.out.println("Query 1 :");
        try (Statement statement = mConnection.createStatement()) {
            ResultSet result = null; 
            // ...
        }
    }
    
    private void query2() throws SQLException {
        System.out.println("Query 2 :");
        // ...
    }
    
    private void query3() throws SQLException {
        System.out.println("Query 3 :");
        // Get your staff number
        // Get an actor's last name
        // Print the list of actors with this last name
        // Get the user's choice
        // Print the list of movies of this actor
        // Get the user's choice
        // Print the list of availables inventory movies
        // Get the user's choice
        // Get the user's first name
        // Get the user's last name
        // Check if client already exists
        // If not, create him (country, city, district, etc...)
        // Create the rental accordingly (if already 10 rentals or more...)
        // Insert the rental in the database
    }
    
    private void query4() throws SQLException {
        System.out.println("Query 4 :");
        String[] category = {"action", "animation", "children", "classics", "comedy", 
                             "documentary", "drama", "family", "foreign", "games", "horror", 
                             "music", "new", "sci-fi", "sports", "travel"};
        
        // ...
    }
    
    private void query5() throws SQLException {
        System.out.println("Query 5 :");
        // ...
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
            if (value >= choices.length) {
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