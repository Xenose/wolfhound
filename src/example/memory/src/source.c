#include<wh-sys/memory.h>


int main(int arc, char* const* arv) {
    wh_heap_init("main", WH_4MB);

    void* p3 = wh_alloc(nullptr, WH_1MB, &p3, WH_ALLOC_TAIL);
    wh_heap_print();

    void* p4 = wh_alloc(nullptr, WH_1MB, &p4, WH_ALLOC_TAIL);
    wh_heap_print();

    void* p1 = wh_alloc(nullptr, 400, &p1);
    wh_heap_print();

    void* p2 = wh_alloc(nullptr, 400, &p2);
    wh_heap_print();

    return 0;
}
