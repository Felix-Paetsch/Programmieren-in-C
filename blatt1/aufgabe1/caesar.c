#include <stdio.h>
#include <stdlib.h>

// ceasar.exe <offset> <to_encode>
int main(int argc, const char *argv[]) {
	if (argc < 2) { exit(-1); }
	
	// Stores the defined offset into k
	int k = strtol(argv[1], NULL, 10) % 26;
	
	const char *remaining_text = argv[2];
	while (*remaining_text != '\0') {
		const char crypt = *remaining_text;
		char encrypted = crypt;

		if (crypt >= 'a' && crypt <= 'z') {
			encrypted = (((crypt - 'a') + k) % 26) + 'a';
		} else if (crypt >= 'A' && crypt <= 'Z') {
			encrypted = (((crypt - 'A') + k) % 26) + 'A';
		}

		printf("%c", encrypted);
		remaining_text++;
    }
	
	return 0;
}
