#include <stdio.h>

int is_char_in_string(char target, const char* str);
int stricmp(const char *lhs, const char *rhs);

// Diese Funktion wandelt Kleinbuchstaben in Großbuchstaben um.
static char toupper(char c) {
	if (c >= 'a' && c <= 'z'){
		return c - 'a' + 'A';
	}
	return c;
}

// Diese Funktion vergleicht zwei Strings ohne Berücksichtigung von Groß- und Kleinschreibung.
int stricmp(const char *lhs, const char *rhs) {
	if (lhs[0] == '\0' && rhs[0] == '\0') return 0; // Both strings ended
	if (lhs[0] == '\0') return -1; // 1st string ended, but not 2nd
	if (rhs[0] == '\0') return 1;  // 2nd string ended, but not 1st

	const char L = toupper(lhs[0]);
	const char R = toupper(rhs[0]);

	if (L == R){
		return stricmp(lhs + 1, rhs + 1);
	}

	if (L < R){
		return -1;
	}
	
	return 1;
}

// Diese Funktion give 1 zurück, falls char im string enthalten ist
int is_char_in_string(char target, const char* str) {
	if (str[0] == '\0') return 0;
	if (str[0] == target) return 1;
	return is_char_in_string(target, str + 1);
}

// Diese Funktion gibt 1 zurück, wenn der Buchstabe ein Leerzeichen (' ', '\t' oder '\n') ist, ansonsten 0.
static int isspace(char c) {
	return is_char_in_string(c, " \n\t");
}

// Diese Funktion schreibt jeden Anfangsbuchstaben jedes Wortes groß.
void strcaps(char *str) {
	if (str[0] == '\0') return;

	str[0] = toupper(str[0]);
	for (int i = 1; str[i] != '\0'; i++) {
		if (isspace(str[i - 1])){
			str[i] = toupper(str[i]);
		}
    }
}

// Diese Funktion bricht Text bei gegebener Zeilenlänge an Wortgrenzen um.
void strwrap(char text[], unsigned int line_len) {
	if (text[0] == '\0') return;

	int current_line_length = 0;
	int last_whitespace = -1;

	for (int i = 0; text[i] != '\0'; i++) {
		if (text[i] == "\n"){
			return strwrap(text + 1, line_len);
		}

		if (text[i] == ' '){
			last_whitespace = current_line_length;
		}

		current_line_length += 1;

		if (current_line_length > line_len && last_whitespace > -1){
			text[last_whitespace] = '\n';
			return strwrap(text + last_whitespace + 1, line_len);
		}
    }
}

int main(void) {
	// Testfall Stringvergleich
	const char *(pairs[6])[2] = {
		{ "magenta", "Magenta" }, // ==  0
		{ "Green", "green" },     // ==  0
		{ "Blue", "Purple" },     // == -1
		{ "white", "Red" },       // == +1
		{ "cyan", "cyanblue" },   // == -1
		{ "orangered", "Orange" } // == +1
	};

	for (int i = 0; i < 6; ++i) {
		printf(
			"(%s, %s) = %i\n",
			pairs[i][0], pairs[i][1], stricmp(pairs[i][0], pairs[i][1])
		);
	}
	
	
	// Testfall Kapitalisierung
	{
		char string[] = "Vogel Quax zwickt Johnys Pferd Bim.";
		strcaps(string);
		printf("%s\n", string);
	}
	{
		// UTF8 not supportet
		char string[] = "Ob Schwyz’ Vamp dünkt\n\t„Fix, quäle Jörg“?";
		strcaps(string);
		printf("%s\n", string);
	}
	{
		char string[] = "\nThe quick brown fox\njumps over the lazy\ndog\n";
		strcaps(string);
		printf("%s\n", string);
	}
	
	// Testfall Wortumbruch
	{
		#define INCLUDE_FILE(...) #__VA_ARGS__
		char text[] =
			#include "faust.txt"
		;
		#undef INCLUDE_FILE
		strwrap(text, 80);
		printf("%s\n", text);
	}

	return 0;
}
