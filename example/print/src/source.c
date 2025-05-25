#include<wh/print.h>

int main(int arc, char* const* arv) {
	wh_print(("Test number 1 -> %i\n"), 1);
	wh_print(("Test number str -> %s\n"), "str");
	wh_print(("Test number oct 16 -> %o\n"), 16);
	wh_print(("Test number hex 16 -> %x\n"), 16);
	wh_print(("Test number nullptr -> %p\n"), nullptr);

	wh_print(("Test string length %%s -> %.9s\n"), "hello wolrd! hello world! hello wolrd!");
	wh_print(("Test string length %%s -> | %9s |\n"), "hello");
	wh_print(("Test string length %%s -> | %-9s |\n"), "hello");
	wh_print(("Test string length %%s -> %#s\n"), "hello");
	wh_print(("Test string length %%s -> | %.6s |\n"), "hello");

	wh_print(("Errnor test [ %m ]\n"), 2);

	return 0;
}
