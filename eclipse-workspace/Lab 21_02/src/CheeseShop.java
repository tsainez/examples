import java.util.Scanner;
public class CheeseShop {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		int choice;
		double fogLbs, fogD;
		double hawkLbs,hawkD;
		double telLbs;
		double sub;
		System.out.print("We Sell 3 kinds of Cheese (in 0.5 lb packages): "
				+ "\nHumboldt Fog: $25.0 per pound"
				+ "\nRed Hawk: $40.5 per pound"
				+ "\nTeleme: $17.25 per pound\n\n"
				+ "Enter the amount of Humboldt Fog in lbs: ");
		fogLbs = input.nextDouble();
		while(fogLbs < 0 || fogLbs % 0.5 != 0)
		{
			if(fogLbs < 0)
			{
				System.out.print("Invalid input. Enter a value >= 0: " );
				fogLbs = input.nextDouble();
			}
			if(fogLbs % 0.5 != 0)
			{
				System.out.print("Invalid input. Enter a value that's multiple of 0.5: " );
				fogLbs = input.nextDouble();
			}	
		}

		System.out.print("Enter the amount of Red Hawk in lbs: ");
		hawkLbs = input.nextDouble();
		while(hawkLbs < 0 || hawkLbs % 0.5 != 0)
		{
			if(hawkLbs < 0)
			{
				System.out.print("Invalid input. Enter a value >= 0: " );
				hawkLbs = input.nextDouble();
			}
			if(hawkLbs % 0.5 != 0)
			{
				System.out.print("Invalid input. Enter a value that's multiple of 0.5: " );
				hawkLbs = input.nextDouble();
			}	
		}
		hawkD = hawkLbs;
		System.out.print("Enter the maount of Teleme in lbs: ");
		telLbs = input.nextDouble();
		while(telLbs < 0 || telLbs % 0.5 != 0)
		{
			if(telLbs < 0)
			{
				System.out.print("Invalid input. Enter a value >= 0: " );
				telLbs = input.nextDouble();
			}
			if(telLbs % 0.5 != 0)
			{
				System.out.print("Invalid input. Enter a value that's multiple of 0.5: " );
				telLbs = input.nextDouble();
			}	
		}
		
		fogLbs = fogLbs * 2;
		hawkLbs = (hawkLbs + (((int)hawkLbs)) * .5);
		System.out.print("\nDisplay itemized list? (1 for yes) ");
		choice = input.nextInt();
		if(choice == 1)
		{
			if(fogLbs > 0)
				System.out.println(fogLbs + " lb of Humboldt Fog @ $25.0 = $" + fogLbs * 25.0);
			if(hawkLbs > 0)
				System.out.println(hawkLbs + " lb of Red Hawk @ $40.5 = $" + hawkLbs * 40.5);
			if(telLbs > 0)
			System.out.println(telLbs + " lb of Teleme @ $17.25 = $" + telLbs * 17.25);
		}
		sub = ((hawkLbs * 40.5)+  (fogLbs * 25.0) + (telLbs * 17.25));
		
		System.out.println("\nSub total: \t\t\t  $" + sub);
		fogD = (fogLbs/2) * 25.0;
		hawkD = 0 - (hawkD - hawkLbs) * 40.5;
		System.out.println("Discounts...");
		if(fogD > 0 && hawkD > 0)
		{
			System.out.println("Humboldt Fog (Buy 1 Get 1 Free): -$" + fogD);
			System.out.println("Red Hawk (buy 2 Get 1 Free):\t -$" + hawkD);
			
		}
		else if(fogD == 0 && hawkD > 0)
		{
			System.out.println("Red Hawk (buy 2 Get 1 Free):\t -$" + hawkD);
		}
		else if(hawkD == 0 && fogD > 0)
		{
			System.out.println("Humboldt Fog (Buy 1 Get 1 Free): -$" + fogD);
		}
		else
		{
			System.out.println("None:\t\t\t\t -$0.0");
		}

		System.out.println("Total:\t\t\t\t  $" + (sub - hawkD - fogD));
		input.close();

	}

}
