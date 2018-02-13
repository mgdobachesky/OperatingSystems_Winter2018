/** apples.java by F. M. Carrano 
    Computes the cost per apple of a box of apples 
    Input:  cost of box of apples 
    Output: the input data 
            the cost per apple if bought by the box 
 */ 
import java.util.Scanner;
public class Apples 
{ 
   public static void main(String[] args) 
   {  
      final int APPLES_PER_BOX = 24;
      Scanner keyboard = new Scanner(System.in); //for user input
 
      System.out.print("How much does a box of apples cost? $"); 
      double costPerBox = keyboard.nextDouble(); 
      double costPerApple = costPerBox / APPLES_PER_BOX; 
 
      System.out.println(); 
      System.out.println("Apples per box:  " + APPLES_PER_BOX); 
      System.out.println("Cost per box:   $" + costPerBox); 
      System.out.println("Cost per apple: $" + costPerApple); 
   } // end main 
} // end Apples 