import java.util.Scanner; // for keyboard input

public class RainbowConnection
{
	// Ranbow alpha angle constant
	final static double RAINBOW_ALPHA = Math.toRadians(42.0 + 1.0 / 3.0);
	
	public static void main(String[] args)
	{
		// Create Scanner object for input
		Scanner keyboard = new Scanner(System.in);
		
		// Get user input
		System.out.print("Please enter you eye height (in meters): ");
		double eyeHeight = keyboard.nextDouble();
		
		System.out.print("Please enter the rainbow height (in meters): ");
		double rainbowHeight = keyboard.nextDouble();
		
		// Compute the distance to teh pot of gold using given formula
		double distanceToGold = (heightOfRainbow - yourHeight) / RAINBOW_ALPHA;
		
		// Report on user input and distance to gold
		System.out.print("Based ona viewer height of  " + eyeHeight + " meters and ");
		System.out.print("a rainbow height of " + rainbowHeight + ", ");
		System.out.print("the distance from you to the pot of gold is ");
		System.out.println(distanceToGold + ". Get walking!");
	}
}