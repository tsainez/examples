import java.util.Random;
import java.util.Scanner;

public class GenCheeseShopv2 {

	/*
	 * Displays the intro message informing the user of various cheeses sold 
	 * while populating the names and prices arrays, and initializing the
	 * amounts array.
	 */
	public static void intro(String[] names, double[] prices, double[] amounts) {
		// Fill-in
		Random rand = new Random();
		if(names.length > 0)
		{
			names[0] = "Humboldt Fog";
			prices[0] = 25;
			if(names.length > 1)
			{
				names[1] = "Red Hawk";
				prices[1] = 40.5;
				if(names.length > 2)
				{
					names[2] = "Teleme";
					prices[2] = 17.25;
				}
			}
			for (int i = 3; i < names.length; i++) {
				names[i] = "Cheese Type " + (char)('A' + i);
				prices[i] = rand.nextInt(1000)/100.0;
				amounts[i] = 0;
			}
		}	
		System.out.printf("\nWe sell %d types of Cheese (in 0.5 lb packages)\n", names.length);
		
		for(int i = 0; i < names.length; i++) 
			System.out.printf("%s: $%.2f per pound\n", names[i], prices[i]);
		System.out.println();
		
		
		
	}
	
	/*
	 * Gets the amount of each cheese the user would like to purchase and populates
	 * the amounts array with the user inputs. Performs with input validation 
	 * (amount >= 0 and multiple of 0.5).
	 */
	public static void getAmount(Scanner sc, String[] names, double[] amounts) {
		// Fill-in
		for(int i = 0; i < names.length; i++)
		{
			System.out.printf("Enter the amount of %s in lb: ", names[i]);
			amounts[i] = sc.nextDouble();
			while(amounts[i] < 0 || amounts[i] % .5 != 0)
			{
				if(amounts[i] < 0) 
				{
					System.out.printf("Invalid Input. Enter a value >= 0: \n");
					amounts[i] = sc.nextDouble();
				}
				if(amounts[i] % .5 != 0)
				{
					System.out.printf("Invalid Input. Enter a value that's multiple of 0.5: ");
					amounts[i] = sc.nextDouble();
				}
			}
		}
	}

	/*
	 * Displays the itemized list of all cheeses bought or a special message if none 
	 * were purchased.
	 */
	public static void itemizedList(String[] names, double[] prices, double[] amounts) {
		// Fill-in
		if(names.length != 0)
		{
			for(int i = 0; i < names.length; i++)
			{
				System.out.printf("%.1f lb of %s @ $%.2f = $%.2f\n", amounts[i], names[i], prices[i], prices[i] * amounts[i]);
			}
			System.out.println();
		}
	}
	
	/*
	 * Calculates the Original Sub Total, which is the price*amount of each 
	 * cheese added together. Returns the Original Sub Total.
	 */
	public static double calcSubTotal(double[] prices, double[] amounts) {
		double sub = 0;
		for(int i = 0; i < prices.length; i++)
		{
			sub += prices[i] * amounts[i];
		}
		return sub;
		
	}

	/*
	 *  Calculates discounts based on special offers on Humboldt Fog and Red Hawk, 
	 *  stores them in disSpecials[0] and disSpecials[1], and returns the array. 
	 */
	public static double[] discountSpecials(double[] amounts, double[] prices){
		// Fix
		
		double[] disSpecials = new double[3];
		if(amounts.length > 0)
			disSpecials[0] = (float)((int)amounts[0]) / 2 * prices[0];
		if(amounts.length > 1)
			disSpecials[1] = (amounts[1] * 2 % 3 == 0) ? (amounts[1]) / 3 * prices[1]:((int)amounts[1] / 3 * prices[1]);

		return disSpecials;		
	}

	/*
	 * Displays the Original Sub Total, discounts based on specials, and the New Sub 
	 * Total. Returns the New Sub Total.
	 */
	public static double printSubTotals(double subTotal, double[] disSpecials) {
		// Fix
		System.out.printf("Original Subtotal\t\t  $%.2f\nSpecials...\n", subTotal);
		if(disSpecials[0] > 0)
			System.out.printf("Humboldt Fog (Buy 1 Get 1 Free): -$%.2f\n", disSpecials[0]);
		
		if(disSpecials[1] > 0)
			System.out.printf("Red Hawk (Buy 2 Get 1 Free):\t -$%.2f\n", disSpecials[1]);
		if(disSpecials[1] + disSpecials[0] == 0)
			System.out.printf("None\t\t\t\t -$%.1f\n", 0.0);
	
		return subTotal - disSpecials[0] - disSpecials[1];
	}

	/*
	 * Calculates the additional discount based on the New Sub Total and displays 
	 * the Final Total.
	 */
	public static void printFinalTotal(double newSubTotal) {
		// Fill-in
		System.out.printf("New Sub Total\t\t\t  $%.2f\n", newSubTotal);
		double AD = 0;
		if (newSubTotal > 150)
			AD = newSubTotal > 250 ? .25:.10;
		if(AD != 0)	
			System.out.printf("Additional %.0f%% Discount:\t -$%.2f\t\t\nFinal Total:\t\t\t  $%.2f", AD * 100,(newSubTotal * AD), newSubTotal - (AD * newSubTotal));	
		else
			System.out.printf("Additional %.0f%% Discount:\t\t -$%.1f\t\t\nFinal Total:\t\t\t  $%.2f", AD * 100,(newSubTotal * AD), newSubTotal - (AD * newSubTotal));

	}
	
	/*
	 * Program starts here
	 */
	public static void main(String[] args) {

		final int MAXCHEESE;
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the number of Cheeses for shop setup: ");
		MAXCHEESE = sc.nextInt();

		// DO NOT CHANGE ANYTHING BELOW
		String[] names = new String[MAXCHEESE];
		double[] prices = new double[MAXCHEESE];
		double[] amounts = new double[MAXCHEESE];

		intro(names, prices, amounts);

		getAmount(sc, names, amounts);

		double subTotal = calcSubTotal(prices, amounts);
		
		
		if (MAXCHEESE != 0 ) {
			System.out.print("\nDisplay the itemized list? (1 for yes) ");
			int display = sc.nextInt();
			
			if (display == 1) {
				itemizedList(names, prices, amounts);
			}
		}

		double newSubTotal = printSubTotals(subTotal, discountSpecials(amounts, prices));
		
		printFinalTotal(newSubTotal);
		
		sc.close();
	}
}