public class Caesar {
	static void caesar_chiffre(int k, String msg) {
		char[] letter = msg.toCharArray();
		
		for (int i = 0; i < letter.length; ++i) {
			char crypt = letter[i];
			
			if (crypt >= 'a' && crypt <= 'z') {
				System.out.print((char) ((((crypt - 'a') + k) % 26) + 'a'));
			} else if (crypt >= 'A' && crypt <= 'Z') {
				System.out.print((char) ((((crypt - 'A') + k) % 26) + 'A'));
			} else {
				System.out.print(crypt);
			}
		}
	}
	
	public static void main(String[] args) {
		int k = Integer.parseInt(args[0]) % 26;
		
		if (k < 0) 
			k += 26;
		
		for (int i = 1; i < args.length; ++i) {
			caesar_chiffre(k, args[i]);
			System.out.println();
		}
	}
}