import java.util.Scanner;
public class RemainderFunc {

	public static void main(String[] args) {
		int max;
		int div;
		Scanner input = new Scanner(System.in);
		boolean run = true;
		
		while(run)
		{
			
		//max number input
		System.out.print("Please Enter the max number: ");
		max = input.nextInt();
		while(max < 0) //max number check
		{
			System.out.print("Invalid input. Please enter a valid max number (>=0): ");
			max = input.nextInt();
		}
		
		//divisor input
		System.out.print("Please Enter the divisor: ");
		div = input.nextInt();
		while(div <= 0) //divisor check
		{
			System.out.print("Invalid input. Please enter a valid divisor (>0): ");
			div = input.nextInt();
		}
		System.out.print("Multiples of " + div + " between 1 and " + max + " (inclusive) are:\n" );
		multiples(div,max);
		}
		input.close();
	}
	
	static void multiples(int div, int max)
	{
		if(div <= max)
		{
			for(int i = 1; i <= max; i++)
			{
				if(i%div == 0)
					System.out.println(i);
			}
		}
		else
			System.out.println("No number were found.");
		
		System.out.println("--------------------------------------------------------");
	}
	
	
}
