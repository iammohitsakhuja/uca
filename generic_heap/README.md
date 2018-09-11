# Generic Heap

A generic implementation of a Heap (i.e. Priority Queue) data structure.

## Usage

The API exposes the following operations:

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

### Custom comparator

There are a few ways how you can provide a custom comparator.

- Create a class & pass the class as the template parameter.

```cpp
class Compare {
    bool operator() (const Structure &a, const Structure &b) {
        return a.some_property > b.some_property;
    }
};

// Create the Heap like this.
Heap<Structure, Compare> heap;
```

Also, note the use of the `const` keyword. It is necessary that your comparator
does not modify anything.

- Create a lambda function. Here, passing the comparator as a constructor
    argument is necessary.

```cpp
auto comparator = [](const Structure &a, const Structure &b) {
    return a.some_property > b.some_property;
};

// Create the Heap like this.
Heap<Structure, decltype(comparator)> heap(comparator);
```

Here again, `const` keyword is necessary.

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

Testing other datatypes...
String tests passed successfully!
Struct tests passed successfully!
Tests for other datatypes passed!

Performing some final tests...
All tests passed!

TIME IN loading the Max Heap via single insertions:     1.14s
TIME IN loading the Min Heap via single insertions:     1.12s
TIME IN popping the Max Heap after single insertions:  17.40s
TIME IN popping the Min Heap after single insertions:  16.94s
TIME IN loading the Max Heap via batch insertion:       0.83s
TIME IN loading the Min Heap via batch insertion:       0.84s
TIME IN popping the Max Heap after batch insertion:    17.20s
TIME IN popping the Min Heap after batch insertion:    17.00s

TOTAL TIME IN single insertions method (Max Heap):     18.54s
TOTAL TIME IN single insertions method (Min Heap):     18.06s
TOTAL TIME IN batch insertion method (Max Heap):       18.03s
TOTAL TIME IN batch insertion method (Min Heap):       17.84s

TIME IN total:                                         72.48s
```

**Disclaimer:** The time to operate on 10 million numbers that has been shown
here may vary depending on your machine.
