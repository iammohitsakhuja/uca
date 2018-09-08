#include <cstdio>
#include <functional>
#include <queue>

#include "Heap.hh"
#include "benchmark.hh"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;

// Tests for the output sorted array.
template <class T> void test(vector<T> &sorted_elements);
template <class T, class Compare = less<typename vector<T>::value_type>>
void test(vector<T> &sorted_elements, Compare &&__comparator);

// Tests for heap.
template <typename T, typename Compare = less<typename vector<T>::value_type>>
void test_is_heap(Heap<T, Compare> &heap);

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

    // Create heaps.
    Heap<int>               max_heap_single_insert;
    Heap<int, greater<int>> min_heap_single_insert;
    Heap<int>               max_heap_batch_insert;
    Heap<int, greater<int>> min_heap_batch_insert;

    // Create vectors to store processed elements.
    vector<int> max_heap_single_insert_elements;
    vector<int> min_heap_single_insert_elements;
    vector<int> max_heap_batch_insert_elements;
    vector<int> min_heap_batch_insert_elements;

    // Structures for timing data.
    struct rusage before, after;

    // Benchmarks.
    double time_loading_max_heap_single_insert = 0.0;
    double time_popping_max_heap_single_insert = 0.0;
    double time_loading_min_heap_single_insert = 0.0;
    double time_popping_min_heap_single_insert = 0.0;
    double time_loading_max_heap_batch_insert  = 0.0;
    double time_popping_max_heap_batch_insert  = 0.0;
    double time_loading_min_heap_batch_insert  = 0.0;
    double time_popping_min_heap_batch_insert  = 0.0;

    // Benchmark the time taken to push the elements of the array into the Max
    // Heap one-by-one.
    printf("Loading elements (single insert) into Max Heap... ");
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < SIZE; i++)
        max_heap_single_insert.push(array[i]);
    getrusage(RUSAGE_SELF, &after);
    time_loading_max_heap_single_insert = calculate(&before, &after);
    printf("DONE\n");

    // Benchmark the time taken to push the elements of the array into the Min
    // Heap one-by-one.
    printf("Loading elements (single insert) into Min Heap... ");
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < SIZE; i++)
        min_heap_single_insert.push(array[i]);
    getrusage(RUSAGE_SELF, &after);
    time_loading_min_heap_single_insert = calculate(&before, &after);
    printf("DONE\n");

    // Benchmark the time taken to heapify the whole array into a Max heap via
    // batch insertions.
    printf("Loading elements (batch insert) into Max Heap... ");
    getrusage(RUSAGE_SELF, &before);
    max_heap_batch_insert.heapify(array);
    getrusage(RUSAGE_SELF, &after);
    time_loading_max_heap_batch_insert = calculate(&before, &after);
    printf("DONE\n");

    // Benchmark the time taken to heapify the whole array into a Min heap via
    // batch insertions.
    printf("Loading elements (batch insert) into Min Heap... ");
    getrusage(RUSAGE_SELF, &before);
    min_heap_batch_insert.heapify(array);
    getrusage(RUSAGE_SELF, &after);
    time_loading_min_heap_batch_insert = calculate(&before, &after);
    printf("DONE\n\n");

    // Test whether the heaps formed have the heap property.
    printf("Testing all heaps for satisfying heap property...\n");
    test_is_heap(max_heap_single_insert);
    test_is_heap(min_heap_single_insert);
    test_is_heap(max_heap_batch_insert);
    test_is_heap(min_heap_batch_insert);
    printf("Heap tests passed successfully!\n\n");

    // Benchmark the time taken to remove the elements of the single insert Max
    // Heap from the top one-by-one.
    printf("Popping elements (single insert) from Max Heap... ");
    getrusage(RUSAGE_SELF, &before);
    while (!max_heap_single_insert.empty()) {
        max_heap_single_insert_elements.push_back(
            max_heap_single_insert.top());
        max_heap_single_insert.pop();
    }
    getrusage(RUSAGE_SELF, &after);
    time_popping_max_heap_single_insert = calculate(&before, &after);
    printf("DONE\n");

    // Benchmark the time taken to remove the elements of the single insert Min
    // Heap from the top one-by-one.
    printf("Popping elements (single insert) from Min Heap... ");
    getrusage(RUSAGE_SELF, &before);
    while (!min_heap_single_insert.empty()) {
        min_heap_single_insert_elements.push_back(
            min_heap_single_insert.top());
        min_heap_single_insert.pop();
    }
    getrusage(RUSAGE_SELF, &after);
    time_popping_min_heap_single_insert = calculate(&before, &after);
    printf("DONE\n");

    // Benchmark the time taken to remove the elements of the batch insert Max
    // Heap from the top one-by-one.
    printf("Popping elements (batch insert) from Max Heap... ");
    getrusage(RUSAGE_SELF, &before);
    while (!max_heap_batch_insert.empty()) {
        max_heap_batch_insert_elements.push_back(max_heap_batch_insert.top());
        max_heap_batch_insert.pop();
    }
    getrusage(RUSAGE_SELF, &after);
    time_popping_max_heap_batch_insert = calculate(&before, &after);
    printf("DONE\n");

    // Benchmark the time taken to remove the elements of the batch insert Min
    // Heap from the top one-by-one.
    printf("Popping elements (batch insert) from Min Heap... ");
    getrusage(RUSAGE_SELF, &before);
    while (!min_heap_batch_insert.empty()) {
        min_heap_batch_insert_elements.push_back(min_heap_batch_insert.top());
        min_heap_batch_insert.pop();
    }
    getrusage(RUSAGE_SELF, &after);
    time_popping_min_heap_batch_insert = calculate(&before, &after);
    printf("DONE\n\n");

    // Final testing.
    printf("Performing some final tests...\n");
    test(max_heap_single_insert_elements);
    test(min_heap_single_insert_elements, greater<int>());
    test(max_heap_batch_insert_elements);
    test(min_heap_batch_insert_elements, greater<int>());
    printf("All tests passed!\n\n");

    // Display the benchmark results.
    printf("TIME IN loading the Max Heap via single insertions:   %6.2fs\n",
        time_loading_max_heap_single_insert);
    printf("TIME IN loading the Min Heap via single insertions:   %6.2fs\n",
        time_loading_min_heap_single_insert);
    printf("TIME IN popping the Max Heap after single insertions: %6.2fs\n",
        time_popping_max_heap_single_insert);
    printf("TIME IN popping the Min Heap after single insertions: %6.2fs\n",
        time_popping_min_heap_single_insert);
    printf("TIME IN loading the Max Heap via batch insertion:     %6.2fs\n",
        time_loading_max_heap_batch_insert);
    printf("TIME IN loading the Min Heap via batch insertion:     %6.2fs\n",
        time_loading_min_heap_batch_insert);
    printf("TIME IN popping the Max Heap after batch insertion:   %6.2fs\n",
        time_popping_max_heap_batch_insert);
    printf("TIME IN popping the Min Heap after batch insertion:   %6.2fs\n\n",
        time_popping_min_heap_batch_insert);

    printf("TOTAL TIME IN single insertions method (Max Heap):    %6.2fs\n",
        time_loading_max_heap_single_insert
            + time_popping_max_heap_single_insert);
    printf("TOTAL TIME IN single insertions method (Min Heap):    %6.2fs\n",
        time_loading_min_heap_single_insert
            + time_popping_min_heap_single_insert);
    printf("TOTAL TIME IN batch insertion method (Max Heap):      %6.2fs\n",
        time_loading_max_heap_batch_insert
            + time_popping_max_heap_batch_insert);
    printf("TOTAL TIME IN batch insertion method (Min Heap):      %6.2fs\n\n",
        time_loading_min_heap_batch_insert
            + time_popping_min_heap_batch_insert);

    printf("TIME IN total:                                        %6.2fs\n",
        time_loading_max_heap_single_insert
            + time_loading_min_heap_single_insert
            + time_loading_max_heap_batch_insert
            + time_loading_min_heap_batch_insert
            + time_popping_max_heap_single_insert
            + time_popping_min_heap_single_insert
            + time_popping_max_heap_batch_insert
            + time_popping_min_heap_batch_insert);

    return 0;
}

template <class T> void test(vector<T> &sorted_elements)
{
    less<int> __comparator;
    for (unsigned int i = 1; i < sorted_elements.size(); i++)
        assert(!__comparator(sorted_elements[i - 1], sorted_elements[i]));
}

template <class T, class Compare>
void test(vector<T> &sorted_elements, Compare &&__comparator)
{
    for (unsigned int i = 1; i < sorted_elements.size(); i++)
        assert(!__comparator(sorted_elements[i - 1], sorted_elements[i]));
}

template <class T, class Compare> void test_is_heap(Heap<T, Compare> &heap)
{
    assert(heap.is_heap());
}
