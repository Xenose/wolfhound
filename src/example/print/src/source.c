#define USE_NAMESPACE_WOLFHOUND
#include <wh-posix/stdio.h>
#include <wh/print.h>
#include <wh/debug/benchmark.h>

int main(int arc, char* const* arv) {
    wh_benchmark_s wh_bench = { 0 };
    wh_benchmark_s std_bench = { 0 };

    wh_benchmark(&std_bench, 1000000) {
        printf("Test number 1 -> %i\n", 1);
    }

    wh_benchmark(&wh_bench, 1000000) {
        print(("Test number 1 -> %i\n"), 1);
    }

    wh_benchmark_print(&wh_bench);
    wh_benchmark_print(&std_bench);
    return 0;
}
