
// TODO: Funktionen a(), b() und c() deklarieren damit das Programm ohne Warnungen compiliert.

int main() {
	// compilieren sollen
	// (void) a(1);
	// (void) b(&a);
	// (void) c(c(&a));
	
	// *nicht* compilieren sollen
	//(void) a(1, 2);
	//(void) b(&a, &a);
	//(void) c(&a, &a);
	return 0;
}
