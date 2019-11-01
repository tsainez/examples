import java.util.Random;
import java.util.Scanner;
public class GenCheeseShop{

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		System.out.print("Enter the number of Cheeses for shop setup: ");
		final int MAXCHEESE = input.nextInt();
		String[] names = new String[MAXCHEESE];
		double[] prices = new double[MAXCHEESE];
		double[] amounts = new double[MAXCHEESE];
		double sub = 0;
		double hawkD = 0, fogD = 0;
		double test = 0;

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


		//get the amounts > 0 and % of 0.5
		System.out.println();
		for(int i = 0; i < MAXCHEESE; i++) {
			System.out.print("Enter the amount of " + names[i] + " in lb: ");
			amounts[i] = input.nextDouble();
			while(amounts[i] < 0 || amounts[i] % 0.5 !=0) {
				if(amounts[i] < 0) {
					System.out.print("Invalid input. Enter a value >= 0: " );
					amounts[i] = input.nextDouble();
				}
				if(amounts[i] % 0.5 != 0) {
					System.out.print("Invalid input. Enter a value that's multiple of 0.5: " );
					amounts[i] = input.nextDouble();
				}
			}
		}

		System.out.print("\nDisplay the itemized list? (1 for yes) ");
		if(input.nextInt() > 0) {
			for(int j = 0; j < MAXCHEESE; j++) {
				test = test +  amounts[j];
			}
			if(test > 0) {
				for(int i = 0; i < MAXCHEESE; i++) {
					System.out.printf("%.1f lb of %s @ $%.2f = $%.2f\n", amounts[i], names[i], prices[i], prices[i] * amounts[i]);
					sub = sub + (prices[i] * amounts[i]);
				}}
			else
				System.out.printf("No items were purchased. \n");
		}
		else {
			for(int i = 0; i < MAXCHEESE; i++) {
				sub = sub + (prices[i] * amounts[i]);
			}
		}

		System.out.printf("\nOriginal Sub total:\t\t  $%.2f\n", sub);
		System.out.println("Specials...");
		switch(MAXCHEESE) {
		case 0:
			System.out.printf("None\t\t\t\t -$%.1f", 0.0);
			break;
		case 1:
			if(amounts[0] > 0)
			{
				fogD = (float)(int)amounts[0] / 2 * prices[0];
				System.out.printf("%s (Buy 1 Get 1 Free): -$%.2f\n", names[0], fogD);

			}
			else 
				System.out.printf("None\t\t\t\t -$%.1f", 0.0);
			break;
		case 2:
			if(amounts[0] > 0 && amounts[1] > 0)
			{
				fogD = (float)((int)amounts[0]) / 2 * prices[0];
				System.out.printf( "%s (Buy 1 Get 1 Free): -$%.2f\n",names[0], fogD);
				if(amounts[1] * 2 % 3 ==0)
					hawkD = (amounts[1]) / 3 * prices[1];
				else
					hawkD =((int)(amounts[1] / 1.5) * (prices[1]/2));
				System.out.printf( "%s (Buy 2 Get 1 Free):\t -$%.2f",names[1], hawkD);

			}
			else if(amounts[0] > 0) {
				fogD = (float)((int)amounts[0]) / 2 * prices[0];
				System.out.printf( "%s (Buy 1 Get 1 Free): -$%.2f\n",names[0], fogD);
			}
			else if(amounts[1] > 0) {
				if(amounts[1] * 2 % 3 ==0)
					hawkD = (amounts[1]) / 3 * prices[1];
				else
					hawkD =(((int)amounts[1]) / 3 * prices[1]);
				System.out.printf( "%s (Buy 2 Get 1 Free):\t -$%.2f",names[1], hawkD);
			}
			else
				System.out.printf("None\t\t\t\t -$%.1f", 0.0);
			break;
		default:
			if(amounts[0] > 0 && amounts[1] > 0)
			{
				fogD = (float)((int)amounts[0]) / 2 * prices[0];
				System.out.printf( "%s (Buy 1 Get 1 Free): -$%.2f\n",names[0], fogD);
				if(amounts[1] * 2 % 3 == 0)
					hawkD = (amounts[1]) / 3 * prices[1];
				else
					hawkD =((int)amounts[1] / 3 * prices[1]);
				System.out.printf( "%s (Buy 2 Get 1 Free):\t -$%.2f",names[1], hawkD);

			}
			else if(amounts[0] > 0) {
				fogD = (float)((int)amounts[0]) / 2 * prices[0];
				System.out.printf( "%s (Buy 1 Get 1 Free): -$%.2f\n",names[0], fogD);
			}
			else if(amounts[1] > 0) {
				if(amounts[1] * 2 % 3 ==0)
					hawkD = (amounts[1]) / 3 * prices[1];
				else
					hawkD =(((int)amounts[1]) / 3 * prices[1]);
				System.out.printf( "%s (Buy 2 Get 1 Free): \t -$%.2f",names[1], hawkD);
			}
			else
				System.out.print("None\t\t\t\t -$0.0");


			break;
		}

		sub = sub - hawkD - fogD;
		System.out.printf("\nNew Sub Total:\t\t\t  $%.2f", sub);
		if(sub > 250 ) {

			System.out.printf("\nAdditional 15%% Discount\t\t\t -$%.2f", sub * .15);
			sub = sub - (sub * .15);
		}
		else if(sub > 150) {

			System.out.printf("\nAdditional 10%% Discount\t\t -$%.2f", sub * .1);
			sub = sub - (sub * .1);
		}
		else
			System.out.printf("\nAdditional 0%% Discount\t\t -$%.2f", 0.00);
		System.out.printf("\nFinal Total:\t\t\t  $%.2f", sub);

	}

}
