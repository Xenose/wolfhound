#include<wh/memory.h>


int main(int arc, char* const* arv) {
	wh_heap_init("main", WH_4MB);

	void* p1 = wh_alloc(nullptr, 400, &p1);
	void* p2 = wh_alloc(nullptr, 400, &p2);
	void* p3 = wh_alloc(nullptr, WH_1MB, &p2, WH_ALLOC_TAIL);

	wh_heap_print();
	return 0;
}
