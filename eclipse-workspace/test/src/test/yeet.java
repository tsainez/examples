package test;
import java.util.Scanner;
public class yeet {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in); 
		int[] tally = new int[3];
		//hi(1);
		System.out.print(hi(1));
		//int a = 0, b = 1;
		
		int[]a = {5};
		int[]b = a;
		a[0] = 3;
		System.out.print(a[0]);
		System.out.print(b[0]);
	

	}
	
	static long hi(int i)
	{
		return i;
	}

}
