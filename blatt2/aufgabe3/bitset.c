#include <stdio.h>
#include "bitset.h"

static const unsigned int BITS_PER_WORD = 8;

// [Nicht benötigt] Hilfsfunktion, die die Anzahl gesetzter Bits in einem Wort zählt.
static unsigned int pop_count1(unsigned char bits) {
	unsigned char temp[1] = { bits };
	return bitsetCount(temp, BITS_PER_WORD);
}

int bitsetGet(unsigned char bits[], unsigned int bit_pos) {
	const unsigned int word_index = bit_pos % BITS_PER_WORD;
	const unsigned int bitset_word  = (bit_pos - word_index) / BITS_PER_WORD;

	return (bits[bitset_word] >> word_index) & 1;
}

void bitsetSet(unsigned char bits[], unsigned int bit_pos) {
	const unsigned int word_index = bit_pos % BITS_PER_WORD;
	const unsigned int bitset_word  = (bit_pos - word_index) / BITS_PER_WORD;

	const unsigned char mask = (1 << word_index);
	bits[bitset_word] = bits[bitset_word] | mask;
}

void bitsetClear(unsigned char bits[], unsigned int bit_pos) {
	const unsigned int word_index = bit_pos % BITS_PER_WORD;
	const unsigned int bitset_word  = (bit_pos - word_index) / BITS_PER_WORD;

	const unsigned char mask = ~(1 << word_index);
	
	bits[bitset_word] = bits[bitset_word] & mask;
}

void bitsetFlip(unsigned char bits[], unsigned int bit_pos) {
	const unsigned int word_index = bit_pos % BITS_PER_WORD;
	const unsigned int bitset_word  = (bit_pos - word_index) / BITS_PER_WORD;

	const unsigned char mask = (1 << word_index);
	bits[bitset_word] = bits[bitset_word] ^ mask;
}

unsigned int bitsetCount(unsigned char bits[], unsigned int len_in_bits) {
	int total = 0;
	for (int i = 0; i < len_in_bits; i++){
		total += bitsetGet(bits, i);
	}
	return total;
}

void bitsetPrint(unsigned char bits[], unsigned int len_in_bits) {
	int printed_first_el = 0;

	for (int i = 0; i < len_in_bits; i++){
		if (bitsetGet(bits, i)){
			if (printed_first_el == 0){
				printed_first_el = 1;
				printf("%u", i);
			} else {
				printf(", %u", i);
			}
		}
	}

	printf("\n");
}

void bitsetPrintBinary(unsigned char bits[], unsigned int len_in_bits){
	for (int i = 0; i < len_in_bits; i++){
		printf("%u", bitsetGet(bits, i));
	}
	printf("\n");
}
