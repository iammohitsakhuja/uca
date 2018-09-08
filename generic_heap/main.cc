#include <cstdio>
#include <functional>
#include <queue>

#include "Heap.hh"
#include "benchmark.hh"

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

void test(vector<int> &sorted_elements);

template <typename T> void test_is_heap(Heap<T> &heap);

int main(int argc, char **argv)
{
    // Ensure proper usage.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s num\n", argv[0]);
        return 1;
    }

    // Get the input array size.
    const int SIZE = atoi(argv[1]);

    // Create an array to store all the inputs.
    vector<int> array(SIZE);

    // Get the inputs.
    for (int i = 0; i < SIZE; i++)
        scanf("%i", &array[i]);

    // Create a heap.
    Heap<int> heap;

    // Create vector to store processed heap elements.
    vector<int> elements;

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_loading = 0.0;
    double time_popping = 0.0;

    // Benchmark the time taken to push the elements of the array into the heap
    // one-by-one.
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < SIZE; i++)
        heap.push(array[i]);
    getrusage(RUSAGE_SELF, &after);
    time_loading = calculate(&before, &after);

    // Test whether the two heaps formed have the heap property.
    test_is_heap(heap);

    // Benchmark the time taken to remove the elements of the heap from the top
    // one-by-one.
    getrusage(RUSAGE_SELF, &before);
    while (!heap.empty()) {
        elements.push_back(heap.top());
        heap.pop();
    }
    getrusage(RUSAGE_SELF, &after);
    time_popping = calculate(&before, &after);

    // Display the benchmark results.
    printf("TIME IN loading the heap via single insertions: %6.2fs\n",
        time_loading);
    printf("TIME IN popping after single insertions:        %6.2fs\n",
        time_popping);
    printf("TOTAL TIME IN single insertions method:         %6.2fs\n",
        time_loading + time_popping);

    // Final testing.
    test(elements);
    printf("\nAll tests passed!\n");

    // Housekeeping.
    return 0;
}

void test(vector<int> &sorted_elements)
{
    for (unsigned int i = 1; i < sorted_elements.size(); i++)
        assert(sorted_elements[i] <= sorted_elements[i - 1]);
}

template <typename T> void test_is_heap(Heap<T> &heap)
{
    assert(heap.is_heap());
}
