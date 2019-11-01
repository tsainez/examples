
public class FindDuplicateCount {

	public static void main(String[] args) {
		int[] arr = {1, 2, 2, 3, 4, 2, 4, 3, 0, 5, 3, 2};
		int occ;
		// Fill-in
		for(int i = 0; i < arr.length;i ++)
		{
			occ = 0;
			for(int j = i+1; j < arr.length; j++)
			{
				if(arr[i] == arr[j])
					occ++;
			}
			if(occ >= 1)
				System.out.println("There are " + (occ) + " more occurences of value " + arr[i] + " starting at index: " +  i);
			else
				System.out.println("There are no duplicates with value " + arr[i] + " beyond index: " + i);
		}
		
	}

}
