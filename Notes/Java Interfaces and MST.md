# Java Interfaces and MST

08/09/2018

## Little Endian vs Big Endian

In `Little Endian` form, assembly language instructions for picking up a 1, 2,
4, or longer byte number proceed in exactly the same way for all formats: first
pick up the lowest order byte at offset 0. Also, because of the 1:1
relationship between address offset and byte number (offset 0 is byte 0),
multiple precision math routines are correspondingly easy to write.

In `Big Endian` form, by having the high-order byte come first, you can always
test whether the number is positive or negative by looking at the byte at
offset zero. You don’t have to know how long the number is, nor do you have to
skip over any bytes to find the byte containing the sign information. The
numbers are also stored in the order in which they are printed out, so binary
to decimal routines are particularly efficient.

## Interfaces in Java

- Interfaces are like `abstract` classes in C++.
- They do not contain implementation of the actual code, instead just contain
    the methods.
- By default, all the methods in the interface are `public`.
- The class needs to _implement_ the interface.

## Minimum Spanning Tree problem

Consider a network graph. For transferring a packet from one node to another,
there are two approaches:

1. Flooding
1. Source Routing

### Algorithms

- Prim's
- Kruskal
- Bellman-Ford
- Dijkstra

### Data Structures

- Union-Find
- Priority Queue
- Graphs

## Union Find

### Techniques

- Quick Find

| Operation | Best Case | Worst Case |
| --- | --- | --- |
| Initialization | N | N |
| Connected | 1 | 1 |
| Union | N | N |

Hence, complexity = `O(N + N^2)` = `O(N^2)`.

- Quick Union

| Operation | Best Case | Worst Case |
| --- | --- | --- |
| Initialization | N | N |
| Connected | 1 | NlogN |
| Union | NlogN | NlogN |
