public class Driver
{
	public static void main(String[] args) {
		if (args.length != 1) {
			System.err.println("Usage Driver <integer>");
			System.exit(0);
		}
		
		Sum sumObject = new Sum();
		int upper = Integer.parseInt(args[0]);
		
		Thread worker = new Thread(new Summation(upper, sumObject));
		worker.start();
		try {
			worker.join();
		} catch (InterruptedException ie) { }
		System.out.println("The sum of " + upper + " is " + sumObject.get());
	}
}