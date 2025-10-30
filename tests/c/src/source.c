#include<wh_tests/maths/core.h>

int main(int arc, char** arv) {
	testing_intlog(0, 0, 10);
	testing_intlog(1, 10, 10);
	testing_intlog(2, 100, 10);
	testing_intlog(3, 1000, 10);
	testing_intlog(4, 10000, 10);
	return 0;
}
