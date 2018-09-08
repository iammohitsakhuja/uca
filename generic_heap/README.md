# Generic Heap

A generic implementation of a Heap (i.e. Priority Queue) data structure.

## Usage

The API expushposes the following operations:

- Push (Pushes an element to the heap)
- Pop (Removes the top-most element from the heap)
- Heapify (Given an array, it inserts its values to the heap in O(n) time)
- Top (Returns the top-most element without removing it from the heap)
- Empty (Returns true/false depending on whether the heap is empty or not)
- Size (Returns the number of elements in the heap)
- Is Heap (Returns true if the container satisfies the heap property)

All the user needs to provide to the API is the `type` and the `comparator`.

**Default behavior:** The default comparator used is `std::less` and it creates
a Max Heap. This behavior can be overriden by providing a custom comparator.

## Requirements

- C++17 compiler.

## How to run

To run and test out the program for yourself, run the following:

```bash
$ make ../rand
$ make
$ ../rand 10000000 100000000 | ./heap_operations 10000000
Loading elements (single insert) into Max Heap... DONE
Loading elements (single insert) into Min Heap... DONE
Loading elements (batch insert) into Max Heap... DONE
Loading elements (batch insert) into Min Heap... DONE

Testing all heaps for satisfying heap property...
Heap tests passed successfully!

Popping elements (single insert) from Max Heap... DONE
Popping elements (single insert) from Min Heap... DONE
Popping elements (batch insert) from Max Heap... DONE
Popping elements (batch insert) from Min Heap... DONE

Performing some final tests...
All tests passed!

TIME IN loading the Max Heap via single insertions:     1.09s
TIME IN loading the Min Heap via single insertions:     1.07s
TIME IN popping the Max Heap after single insertions:  17.11s
TIME IN popping the Min Heap after single insertions:  16.88s
TIME IN loading the Max Heap via batch insertion:       0.82s
TIME IN loading the Min Heap via batch insertion:       0.82s
TIME IN popping the Max Heap after batch insertion:    17.19s
TIME IN popping the Min Heap after batch insertion:    17.16s

TOTAL TIME IN single insertions method (Max Heap):     18.20s
TOTAL TIME IN single insertions method (Min Heap):     17.96s
TOTAL TIME IN batch insertion method (Max Heap):       18.01s
TOTAL TIME IN batch insertion method (Min Heap):       17.98s

TIME IN total:                                         72.15s
```

**Disclaimer:** The time to operate on 10 million numbers that has been shown
here may vary depending on your machine.
