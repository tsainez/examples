import java.util.Random;

public class Error {

	public static void main(String[] args) {


		final int MAXCHEESE = 0;

		String[] names = new String[MAXCHEESE];
		double[] prices = new double[MAXCHEESE];
		double[] amounts = new double[MAXCHEESE];

		// Three Special Cheeses
		if(MAXCHEESE > 0) {
			names[0] = "Humboldt Fog";
			prices[0] = 25.00;
			if(MAXCHEESE > 1) {
				names[1] = "Red Hawk";
				prices[1] = 40.50;
			}
			if(MAXCHEESE > 2) {
				names[2] = "Teleme";
				prices[2] = 17.25;
			}
		}
		//display the cheese rates
		System.out.println("\nWe sell " + MAXCHEESE + " kinds of Cheese (in 0.5 lb packages)");

		System.out.print(MAXCHEESE > 0 ? names[0] + ": $" + prices[0] + " per pound\n":"");
		System.out.print(MAXCHEESE > 1 ? names[1] + ": $" + prices[1] + " per pound\n":"");
		System.out.print(MAXCHEESE > 2 ? names[2] + ": $" + prices[2] + " per pound\n":"");

		Random ranGen = new Random(100);

		for (int i = 3; i < MAXCHEESE; i++) {
			names[i] = "Cheese Type " + (char)('A' + i);
			prices[i] = ranGen.nextInt(1000)/100.0;
			amounts[i] = 0;

			System.out.println(names[i] + ": $" + prices[i] + " per pound");
		}

	}

}
