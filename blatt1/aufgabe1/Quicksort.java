public class Quicksort {
	public static void main(String[] args) {
		// create the list from the command line
		int[] list = new int[args.length];
		
		for (int i = 0; i < args.length; ++i) {
			list[i] = Integer.parseInt(args[i]);
		}
		
		// print the unsorted list
		System.out.println("---- Unsortiert: " + list_is_sorted(list) + " ----");
		list_print(list);
		
		// sort it
		quicksort(list, 0, list.length);
		
		// print the sorted list
		System.out.println("---- Sortiert:   " + list_is_sorted(list) + " ----");
		list_print(list);
	}
	
	static boolean list_is_sorted(int[] list) {
		for (int i = 0; i < list.length-1; ++i) {
			if (list[i] > list[i+1])
				return false;
		}
		
		return true;
	}
	
	static void list_print(int[] list) {
		String sep = "";
		
		System.out.print("[");
		for (int i = 0; i < list.length; ++i, sep = ", ") {
			System.out.print(sep + list[i]);
		}
		System.out.println("]");
	}
	
	static void quicksort(int[] list, int start, int end) {
		if (end - start <= 1)
			return;
		
		int mid = partition(list, start, end);
		quicksort(list, start, mid);
		quicksort(list, mid + 1, end);
	}
	
	static int partition(int[] list, int start, int end) {
		int pivot = end - 1;
		int l = start, r = end - 2;
		int t;
		
		while (true) {
			while (l < r && list[l] <  list[pivot]) ++l;
			while (l < r && list[r] >= list[pivot]) --r;
			
			if (l >= r) break;
			
			t = list[l];
			list[l] = list[r];
			list[r] = t;
		}
		
		if (list[l] >= list[pivot]) {
			t = list[l];
			list[l] = list[pivot];
			list[pivot] = t;
			return l;
		}
		
		return pivot;
	}
}
