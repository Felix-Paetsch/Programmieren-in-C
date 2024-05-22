#include <stdio.h>
#include "bitset.h"

int main(void) {
	unsigned char bitset[2] = {0, 0};
	
	bitsetSet(bitset, 6);
	bitsetFlip(bitset, 8);
	
	if (!bitsetGet(bitset, 11))
		bitsetSet(bitset, 11);
	
	bitsetSet(bitset, 0);
	
	/* erwartet: 4 */
	printf("%u\n", bitsetCount(bitset, 16));
	
	bitsetClear(bitset, 0);
	
	/* erwartet: 6, 8, 11 */
	bitsetPrint(bitset, 16);
	printf("\n");
	
	return 0;
}
