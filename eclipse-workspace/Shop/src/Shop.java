import java.util.Scanner;
public class Shop {
	static Scanner scan = new Scanner(System.in);
	String[] items, nth = {"th","st","nd","rd","th","th","th","th","th","th"};
	double[] prices; int[] cart, discounts; double addDiscountThresh, addDiscount;
	public Shop() {
		prices = null; cart = discounts = null; items = null;
		addDiscount = addDiscountThresh = 0.0; cart = null;
	}
	public void setup(int max) {
		items = new String[max]; prices = new double[max]; discounts = new int[max]; cart = new int[max];
		for(int i = 0; i < max; i++) {
			System.out.print("\nEnter the name of the " + (i+1) 
					+ ((i+1) % 100 < 20 && (i+1) % 100 > 10 ? "th" : nth[(i+1) % 10]) + " product:\t");
			items[i] = scan.next();
			System.out.print("Enter the per package price of " + items[i] + ":\t");
			prices[i] = scan.nextDouble();
			System.out.print("Enter the number of packages ('x') to qualify for Special Discount (buy 'x' get 1 free) for "
					+ items[i] + ", or 0 if no Special Discount offered:\t");
			discounts[i] = scan.nextInt();
		}
		System.out.print("\nEnter the dollar amount to qualify for additional discount (or 0 if none offered):\t");
		addDiscountThresh = scan.nextDouble();
		if(addDiscountThresh > 0) {
			System.out.print("Enter the Additional Discount Rate (e.g., 0.1 for 10%):\t");
			addDiscount = scan.nextDouble();
			while(addDiscount <= 0 || addDiscount > 0.5) {
				System.out.print("Invalid input. Enter a value > 0 and <= 0.5:\t");
				addDiscount = scan.nextDouble();
			}
		}
	}
	public void buy() {
		if(items == null) System.out.println("Shop is not set up yet!");
		else
			for(int i = 0; i < cart.length; i++) {
				System.out.print("Enter the number of " + items[i] + " packages you would like to buy:\t");
				cart[i] = scan.nextInt();
				while(cart[i] < 0) {
					System.out.print("Invalid input. Enter a value >= 0:\t");
					cart[i] = scan.nextInt();
				}
			}
	}
	public void listCart() {
		if(items == null) System.out.println("Shop is not set up yet!");
		else if(isEmpty(cart)) System.out.println("No items were purchased.");
		else for(int i = 0; i < cart.length; i++) if(cart[i] != 0)
			System.out.printf(cart[i] + " package" + (cart[i] != 1 ? "s" : "") + " of " + items[i] + " @ $%.2f per package = $%.2f\n", prices[i], prices[i] * cart[i]);
	}	
	public boolean checkout() {
		if(items == null) { System.out.println("Shop is not set up yet!"); return false; }
		else if (isEmpty(cart)) { System.out.println("You haven't bought anything!"); return false; }
		else {
			double total = 0.0, discTotal = 0.0;
			for(int i = 0; i < cart.length; i++) total += cart[i] * prices[i];
			System.out.printf("Original Sub Total:\t\t$%.2f\n", total);
			for(int i = 0; i < cart.length; i++)
				if(discounts[i] != 0 && cart[i] != 0)
					discTotal += ((cart[i] - (cart[i] % (discounts[i]+1)))/(discounts[i]+1))*prices[i];
			if(discTotal > 0) System.out.printf("Special Discounts:\t\t-$%.2f\n", discTotal);
			else System.out.println("No Special Discounts applied");
			total -= discTotal;
			System.out.printf("New Sub Total:\t\t\t$%.2f\n", total);
			if(addDiscountThresh != 0 && total >= addDiscountThresh) {
				System.out.printf("Additional " + (addDiscount*100) + " Discount:\t-$%.2f\n", total*addDiscount);
				total *= 1-addDiscount;
			}
			else System.out.println("You did not qualify for an Additional Discount");
			System.out.printf("Final Sub Total:\t\t$%.2f\n\nThanks for coming!\n", total);
			return true;
		}
	}
	public static boolean isEmpty(int[] arr) {
		for(int i : arr)
			if(i != 0) return false;
		return true;
	}
	public static void main(String[] args) {
		Shop shoppe = new Shop(); int choice; boolean checkedOut = false;
		while(!checkedOut) {
			System.out.print("This program supports 4 functions:\n\t1. Setup shop\n\t2. Buy\n\t3. "
					+ "List items\n\t4. Checkout\nPlease choose the function you want:\t");
			choice = scan.nextInt();
			System.out.println();
			switch(choice) {
				case 1: System.out.print("Please enter the number of items to set up shop:\t");
					shoppe.setup(scan.nextInt()); break;
				case 2: shoppe.buy(); break;
				case 3: shoppe.listCart(); break;
				case 4:	if(shoppe.checkout()) {
					System.out.print("\n-------------------------------------------------"
							+ "\nWould you like to rerun (1 for yes, 0 for no)?\t");
					checkedOut = scan.nextInt() == 1 ? false : true;
					System.out.println("-------------------------------------------------");
					shoppe = new Shop();
				} break;
				default: System.out.println("Error: Invalid Option.");
			}
			System.out.println();
		}
	}
}