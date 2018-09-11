/**
 * Author: Mohit Sakhuja
 * Dated: 11/09/2018
 *
 * Contains test declarations for Generic Heap program.
 */

#ifndef TESTS_HH
#define TESTS_HH

#include "Heap.hh"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

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

#endif
