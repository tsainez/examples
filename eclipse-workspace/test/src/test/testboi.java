package test;
import java.util.Scanner;
public class testboi 
{

	public static void main(String[] args) 
	{
		Scanner input = new Scanner(System.in);
		int[] a = {0, 0, 0, 0, 0, 0, 0, 0};
		
		System.out.printf("%S", (false) ? "False":"True");

	}
	
	static void printa(int [] a)
	{
		for(int i = 0; i < a.length; i++)
		{
			System.out.printf("%d ", a[i]);
		}
		System.out.println();
	}

}
