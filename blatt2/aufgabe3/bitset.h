#ifndef BITSET_H_INCLUDED
#define BITSET_H_INCLUDED

/**
 * Gibt den Wert des Bits an Position `bit_pos` zurück, also 0, wenn es nicht
 * gesetzt ist und 1, wenn es gesetzt ist.
 */
extern int bitsetGet(unsigned char bits[], unsigned int bit_pos);

/**
 * Aktiviert das Bit an Position `bit_pos`.
 */
extern void bitsetSet(unsigned char bits[], unsigned int bit_pos);

/**
 * Deaktiviert das Bit an Position `bit_pos`.
 */
extern void bitsetClear(unsigned char bits[], unsigned int bit_pos);

/**
 * Wechselt das Bit an Position `bit_pos` auf 1, wenn es vorher 0 war
 * und auf 0, wenn es vorher an war.
 */
extern void bitsetFlip(unsigned char bits[], unsigned int bit_pos);

/**
 * Gibt die Anzahl der gesetzten Bits im Bitset mit Länge `len_in_bits` zurück.
 */
extern unsigned int bitsetCount(unsigned char bits[], unsigned int len_in_bits);

/**
 * Gibt eine kommaseparierte Liste der nullbasierten Indizes aller gesetzten
 * Bits auf die Standardausgabe aus.
 */
extern void bitsetPrint(unsigned char bits[], unsigned int len_in_bits);

/**
 * Gibt alle Bits als Zahl 0 oder 1 aus, abhängig davon,
 * ob sie aktiv sind
*/
extern void bitsetPrintBinary(unsigned char bits[], unsigned int len_in_bits);
#endif
