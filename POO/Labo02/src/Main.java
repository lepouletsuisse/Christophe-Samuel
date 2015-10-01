/*
 -----------------------------------------------------------------------------------
 Laboratoire : 02
 Fichier     : Main.java
 Auteur(s)   : Samuel Darcey & Christophe Peretti
 Date        : 29.09.2015

 But         : Trouver la relation f() entre L et la taille N d'un problème de grille

 Remarque(s) : Travail à 2

 Compilateur : jdk1.8.0_60
 -----------------------------------------------------------------------------------
*/

import Labo02.Clavier;
import com.sun.org.apache.bcel.internal.generic.NOP;

import java.util.Random;

public class Main {
    //Constant for direction
    static final int EAST = 1;
    static final int NE = 2;
    static final int NORTH = 3;
    static final int NW = 4;
    static final int WEST = 5;
    static final int SW = 6;
    static final int SOUTH = 7;
    static final int SE = 8;

    //Constant for arithmetic
    static final double DIAG_LEN = Math.sqrt(2);
    static int nbExperimentation;
    static double average = 0;
    static int limite = 3;

    //Robot variable
    static int rX = 0;
    static int rY = 0;
    static int rInitialSpeed = 1;
    static int rFactorSpeed = 1;
    static double distance = 0;
    static boolean touchedEast = false;
    static boolean touchedNorth = false;
    static boolean touchedWest = false;
    static boolean touchedSouth = false;

    //Grid variable
    static int gridSize;

    /*
    * Grid axe:
    * /------------X
    * |
    * |
    * |
    * |
    * Y
    * */
    public static void main(String args[]) {
        setInitialState();
        for(gridSize = 10; gridSize <= 100 ; gridSize += 2){
            for(int i = 0 ; i <= nbExperimentation ; i++) {
                while (!isEnd()) {
                    moveRandom();
                    limite = 3;
                }
                average += distance;
                resetInitialState();
            }
            average /= (double)nbExperimentation;
            System.out.println("Gridsize: " + gridSize + " // Average: " + average);
            average = 0;
        }
        System.out.println("Done!");
    }

    public static void setInitialState() {
        System.out.print("Enter the number of experimentation per sample (1'000 - 10'000): ");
        nbExperimentation = Clavier.lireInt();
        rX = gridSize / 2;
        rY = gridSize / 2;
    }

    public static void resetInitialState(){
        rX = gridSize / 2;
        rY = gridSize / 2;
        distance = 0;
        rFactorSpeed = 1;
        touchedEast = false;
        touchedNorth = false;
        touchedWest = false;
        touchedSouth = false;
    }

    public static void printInfo() {
        System.out.println(
                "rX: " + rX +
                        " // rY: " + rY +
                        " // rFactorSpeed: " + rFactorSpeed +
                        " // gridSize: " + gridSize +
                        " // distance: " + distance +
                        " // Wall touched: " +
                        (touchedEast ? "East " : "") +
                        (touchedNorth ? "North " : "") +
                        (touchedWest ? "West " : "") +
                        (touchedSouth ? "South " : ""));
    }

    public static void printGraphic() {
        System.out.println("Speed: " + rInitialSpeed * rFactorSpeed);
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (row == rY && col == rX) {
                    System.out.print("X ");
                } else {
                    System.out.print("O ");
                }
            }
            System.out.println();
        }
    }

    public static void debug(int direction, int loop){
        printGraphic();
        System.out.print("Moving ");
        if(direction == EAST) System.out.print("East");
        if(direction == NE) System.out.print("North-East");
        if(direction == NORTH) System.out.print("North");
        if(direction == NW) System.out.print("North-West");
        if(direction == WEST) System.out.print("West");
        if(direction == SW) System.out.print("South-West");
        if(direction == SOUTH) System.out.print("South");
        if(direction == SE) System.out.print("South-East");
        System.out.println(" for " + loop + "x");
        printInfo();

    }

    public static void moveRandom() {
        Random rand = new Random();
        int r = 0;
        while(r <= 0){
            r = (rand.nextInt() % 8) + 1;
        }
        move(r, rInitialSpeed * rFactorSpeed);
    }

    public static void move(int direction, int loop){
        LOOP: for(int i = 0 ; i < loop ; i++){
            switch(direction){
                case EAST: // East
                    if(isAllow(rX + 1, rY)){
                        step(1,0);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
                case NE: // North-East
                    if(isAllow(rX + 1, rY - 1)){
                        step(1,-1);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
                case NORTH: // North
                    if(isAllow(rX, rY - 1)){
                        step(0,-1);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
                case NW: // North-West
                    if(isAllow(rX - 1, rY - 1)){
                        step(-1,-1);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
                case WEST: // West
                    if(isAllow(rX - 1, rY)){
                        step(-1,0);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
                case SW: // South-West
                    if(isAllow(rX - 1, rY + 1)){
                        step(-1,1);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
                case SOUTH: // South
                    if(isAllow(rX, rY + 1)){
                        step(0,1);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
                case SE: // South-East
                    if(isAllow(rX + 1, rY + 1)){
                        step(1,1);
                    }
                    else{
                        bounce(direction);
                        break LOOP;
                    }
                    break;
            }
        }
    }

    public static void step(int x, int y){
        rX += x;
        rY += y;
        if(x != 0 && y != 0) distance += DIAG_LEN;
        else distance += 1;
    }

    public static void bounce(int directionSrc){
        if(limite == 0) return;
        limite--;
        touchedWall(directionSrc);
        int directionDest = (directionSrc + 4) % 8;
        move((directionDest != 0 ? directionDest : 8), 1);
    }

    public static boolean isAllow(int x, int y){
        return x < gridSize && x >= 0 && y < gridSize && y >= 0;
    }

    public static void touchedWall(int direction) {
        if(rX == 0 && rY == 0 && direction == NW
                || rX == gridSize - 1 && rY == 0 && direction == NE
                ||rX == 0 && rY == gridSize - 1 && direction == SW
                || rX == gridSize - 1 && rY == gridSize - 1 && direction == SE) {
            return;
        }
        switch (direction) {
            case EAST:
                if (!touchedEast && rFactorSpeed < 4) rFactorSpeed++;
                touchedEast = true;
                break;
            case NE:
                if(rY - 1 < 0 && !touchedNorth){
                    touchedNorth = true;
                    rFactorSpeed++;
                }
                else if(rX + 1 >= gridSize && !touchedEast){
                    touchedEast = true;
                    rFactorSpeed++;
                }
                break;
            case NORTH:
                if (!touchedNorth && rFactorSpeed < 4) rFactorSpeed++;
                touchedNorth = true;
                break;
            case NW:
                if(rY - 1 < 0 && !touchedNorth){
                    touchedNorth = true;
                    rFactorSpeed++;
                }
                else if(rX - 1 < 0 && !touchedWest){
                    touchedWest = true;
                    rFactorSpeed++;
                }
                break;
            case WEST:
                if (!touchedWest && rFactorSpeed < 4) rFactorSpeed++;
                touchedWest = true;
                break;
            case SW:
                if(rY + 1 >= gridSize && !touchedSouth){
                    touchedSouth = true;
                    rFactorSpeed++;
                }
                else if(rX - 1 < 0 && !touchedWest){
                    touchedWest= true;
                    rFactorSpeed++;
                }
                break;
            case SOUTH:
                if (!touchedSouth && rFactorSpeed < 4) rFactorSpeed++;
                touchedSouth = true;
                break;
            case SE:
                if(rY + 1 >= gridSize && !touchedSouth){
                    touchedSouth = true;
                    rFactorSpeed++;
                }
                else if(rX + 1 >= gridSize && !touchedEast){
                    touchedEast = true;
                    rFactorSpeed++;
                }
                break;
            default:
        }
    }

    public static boolean isEnd() {
        return touchedNorth && touchedEast && touchedSouth && touchedWest;
    }
}
