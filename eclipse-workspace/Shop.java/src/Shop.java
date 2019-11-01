import java.util.Scanner;
public class Shop {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int choice;
		int status = 1;
		displayMenu();
		choice = input.nextInt();
		checkInput(input, choice, status);
		status++;
		
		System.out.print("Please enter the number of items to setup shop: ");
		
		theShop shop = new theShop(input.nextInt());
		shop.setItems(input);
		
		displayMenu();
		choice = input.nextInt();
		checkInput(input, choice, status);
		input.close();

	}
	static int checkInput(Scanner input, int choice, int status)
	{
		while(choice > status)
		{
			if(status == 1)
					System.out.println("Shop is not set up yet!\n");
			else if(status == 2)
				System.out.println("You have not bought anyting yet!\n");
			System.out.print("This program supports 4 functions:\n\t1. Set up Shop\n\t2. Buy\n\t3. List Items\n\t4. Checkout\nPlease choose the function you want: ");
			choice = input.nextInt();
		}
		return choice;
	}
	static void displayMenu()
	{
		System.out.print("This program supports 4 functions:\n\t1. Set up Shop\n\t2. Buy\n\t3. List Items\n\t4. Checkout\nPlease choose the function you want: ");
		
	}

}

class theShop{
	items[] theItems;
	
	theShop(int numOfItems)
	{
		theItems = new items[numOfItems];
		for(int i = 0; i < numOfItems; i++)
		{
			theItems[i] = new items();
		}
	}
	
	
	void setItems(Scanner input)	
	{
		String name;
		double price;
		int discount;
		for(int i = 0; i < theItems.length;i++)
		{
			System.out.print("Enter the name of the " + Suffix(i) + " product: "); theItems[i].setName(input.next());
			System.out.print("Enter the per pacakge price of " + theItems[i].getName() + ": "); theItems[i].setPrice(input.nextDouble());
			System.out.print("Enter the number of packages ('x') to qualify for Special Discount (buy 'x' get 1 free) \nfor " + theItems[i].getName() + ", or 0 if no special Discount offered: ");
			theItems[i].setDiscount(input.nextInt());
			
			
		}
	}
	
	String Suffix(int i)
	{
		i++;
		int rem = i % 10;
		switch(rem) {
		case 0:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			return (i + "th");
		case 1:
			if(i % 100 != 11)
				return (i + "st");
			else
				return (i + "th");
		case 2:
			if(i % 100 != 12)
				return (i + "nd");
			else
				return (i + "th");
		case 3:
			if(i % 100 != 13)
				return (i + "rd");
			else
				return (i + "th");
		}
		return "";
	}
	
}

class items{
	String name;
	double price;
	int discount;
	items()
	{
		name = "";
		price = 0;
		discount = 0;
	}
	
	void setItem(String theName, double thePrice, int theDiscount)
	{
		name = theName;
		price = thePrice;
		discount = theDiscount;
	}
	
	void setName(String theName) {
		name = theName;
	}
	void setPrice(double thePrice) {
		price = thePrice;
	}
	void setDiscount(int theDiscount) {
		discount = theDiscount;
	}
	
	String getName() {
		return name;
	}
	
}
