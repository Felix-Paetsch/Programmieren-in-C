#include <stdio.h>
#include "bitset.h"

int main(void) {
	unsigned char set[2] = {0, 0};
	
	bitsetSet(set, 6);
	bitsetFlip(set, 8);
	
	if (!bitsetGet(set, 11))
		bitsetSet(set, 11);
	
	bitsetSet(set, 0);
	
	/* erwartet: 4 */
	printf("%u\n", bitsetCount(set, 16));
	
	bitsetClear(set, 0);
	
	/* erwartet: 6, 8, 11 */
	bitsetPrint(set, 16);
	printf("\n");
	
	return 0;
}