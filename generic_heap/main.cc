#include <cstdio>
#include <functional>

#include "Heap.hh"
#include "benchmark.hh"
#include "randomize_array.hh"
#include "tests.hh"

using namespace std;

void test_structures(void);
void test_strings(void);

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

    // Tests on other datatypes.
    printf("Testing other datatypes...\n");
    test_strings();
    test_structures();
    printf("Tests for other datatypes passed!\n\n");

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

void test_structures(void)
{
    // Structure definition.
    struct TestStructure {
        int num1;
        int num2;

        TestStructure(int num1, int num2)
            : num1(num1)
            , num2(num2)
        {
        }
    };

    // Comparator definitions.
    struct ComparatorNum1 {
        bool operator()(const TestStructure &a, const TestStructure &b)
        {
            return a.num1 < b.num1;
        }
    };

    auto comparator_num2 = [](const TestStructure &a, const TestStructure &b) {
        return a.num2 < b.num2;
    };

    // Setup.
    const int      SIZE = 10;
    TestStructure *array
        = (TestStructure *)malloc(SIZE * sizeof(TestStructure));
    for (int i = 0; i < SIZE; i++) {
        array[i].num1 = i;
        array[i].num2 = SIZE - i;
    }

    // Vectors for storing elements after they've been heapified.
    vector<TestStructure> test_heapified_elements_num1;
    vector<TestStructure> test_heapified_elements_num2;

    // Randomize the actual array.
    randomize_array(array, SIZE, sizeof(TestStructure));

    // Create heaps and insert elements into them.
    Heap<TestStructure, ComparatorNum1>            heap_num1;
    Heap<TestStructure, decltype(comparator_num2)> heap_num2(comparator_num2);

    for (int i = 0; i < SIZE; i++) {
        heap_num1.push(array[i]);
        heap_num2.push(array[i]);
    }

    // Get the elements back from the heaps.
    while (!heap_num1.empty()) {
        test_heapified_elements_num1.push_back(heap_num1.top());
        heap_num1.pop();
    }

    while (!heap_num2.empty()) {
        test_heapified_elements_num2.push_back(heap_num2.top());
        heap_num2.pop();
    }

    // Test that the elements are sorted accordingly.
    for (unsigned int i = 1; i < test_heapified_elements_num1.size(); i++)
        assert(test_heapified_elements_num1[i - 1].num1
            > test_heapified_elements_num1[i].num1);

    for (unsigned int i = 1; i < test_heapified_elements_num2.size(); i++)
        assert(test_heapified_elements_num2[i - 1].num2
            > test_heapified_elements_num2[i].num2);

    // Housekeeping.
    free(array);

    printf("Struct tests passed successfully!\n");
}

void test_strings(void)
{
    // Setup.
    const int  SIZE                  = 10;
    const int  LENGTH                = 4;
    const char strings[SIZE][LENGTH] = { "ABC", "DEF", "GHI", "JKL", "MNO",
        "PQR", "STU", "VWX", "YZA", "BCD" };
    char **    array                 = (char **)malloc(SIZE * sizeof(char *));
    for (int i = 0; i < SIZE; i++) {
        array[i] = (char *)malloc(LENGTH * sizeof(char));
        strcpy(array[i], strings[i]);
    }

    // Comparator definitions.
    struct ComparatorAscending {
        bool operator()(const char *a, const char *b)
        {
            return strcmp(a, b) < 0;
        }
    };

    auto comparator_desc
        = [](const char *a, const char *b) { return strcmp(a, b) > 0; };

    // Vectors for storing elements after they've been heapified.
    vector<char *> heap_desc_elements;
    vector<char *> heap_asc_elements;

    // Randomize the strings before sorting.
    randomize_array(array, SIZE, sizeof(char *));

    // Create heaps and insert elements into them.
    Heap<char *, ComparatorAscending>       heap_desc;
    Heap<char *, decltype(comparator_desc)> heap_asc(comparator_desc);
    for (int i = 0; i < SIZE; i++) {
        heap_desc.push(array[i]);
        heap_asc.push(array[i]);
    }

    // Get the elements back from the heaps.
    while (!heap_desc.empty()) {
        heap_desc_elements.push_back(heap_desc.top());
        heap_desc.pop();
    }

    while (!heap_asc.empty()) {
        heap_asc_elements.push_back(heap_asc.top());
        heap_asc.pop();
    }

    // Test that the elements are sorted accordingly.
    for (unsigned int i = 1; i < heap_desc_elements.size(); i++)
        assert(strcmp(heap_desc_elements[i - 1], heap_desc_elements[i]) >= 0);

    for (unsigned int i = 1; i < heap_asc_elements.size(); i++)
        assert(strcmp(heap_asc_elements[i - 1], heap_asc_elements[i]) <= 0);

    // Housekeeping.
    for (int i = 0; i < SIZE; i++)
        free(array[i]);
    free(array);

    printf("String tests passed successfully!\n");
}
