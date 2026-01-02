#define USE_NAMESPACE_WOLFHOUND
#include<wh/print.h>
#include<wh/debug/benchmark.h>

u8 data[] = {
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
	0x01, 0x02, 0x03, 0x04,
};

int main(int arc, char* const* arv) {
	wh_benchmark_s bench = { 0 };

	print(("Test memory: \t$m\n"), data, sizeof(data) / sizeof(data[0]));
	
	wh_benchmark(&bench, 100) {
		print(("Test number 1 -> %i\n"), 1);
		print(("Test number str -> %s\n"), "str");
		print(("Test number oct 16 -> %o\n"), 16);
		print(("Test number hex 16 -> %x\n"), 16);
		print(("Test number nullptr -> %p\n"), nullptr);

		print(("Test string length %%s -> %.9s\n"), "hello wolrd! hello world! hello wolrd!");
		print(("Test string length %%s -> | %9s |\n"), "hello");
		print(("Test string length %%s -> | %-9s |\n"), "hello");
		print(("Test string length %%s -> %#s\n"), "hello");
		print(("Test string length %%s -> | %.6s |\n"), "hello");

		print(("Errnor test [ $n ]\n"), 2);
	}

	return 0;
}
