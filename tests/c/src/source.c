#include<stdio.h>
#include<wh_tests/maths/core.h>

int main(int arc, char** arv) {
	i64 failed = 0;
	i64 passed = 0; 

	testing_math(&failed, &passed);

	printf("%li of %li failed\n", failed, failed + passed);
	return 0;
}
