# UCA Notes

## Stack and Queue

### Stacks

It is a LIFO data structure.

### Real-time applications of stacks

- Reverse
- Function call trace
- Recursion
- Used by compiler for syntax validation and compiling

### Queues

It is a FIFO data structure.

#### Types of queues

- Queues implemented using arrays.
    1. Normal queue.
    1. Circular queue.

#### Real-time applications of queues

- Used in real-life.
- Used for process queueing and scheduling.
- Shortest distance between two points (BFS).

#### Some softwares that use queues

- JMS (Java Message Service)
- MQ (IBM Message Queue)
- RabbitMQ
- Apache Kafka
- Apache ActiveMQ

### Questions

- [x] Implement queue using 2 stacks
- [ ] Implement stack using 2 queues
- [ ] Sliding window sum
- [x] Sliding window max

## Java Interfaces and MST

08/09/2018

### Little Endian vs Big Endian

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

### Interfaces in Java

- Interfaces are like `abstract` classes in C++.
- They do not contain implementation of the actual code, instead just contain
    the methods.
- By default, all the methods in the interface are `public`.
- The class needs to _implement_ the interface.

### Minimum Spanning Tree problem

Consider a network graph. For transferring a packet from one node to another,
there are two approaches:

1. Flooding
1. Source Routing

#### Algorithms

- Prim's
- Kruskal
- Bellman-Ford
- Dijkstra

#### Data Structures

- Union-Find
- Priority Queue
- Graphs

### Union Find

#### Techniques

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

## BST

### Questions on BST

- Rank in BST
- Red black tree/AVL
- In/Pre/Post/Level/Zig-Zag traversals
- Side view/Top view/Circumference of BST
- Difference of sum of odd level nodes & even level nodes
- Convert BST into circular sorted doubly linked list (in memory)
- Given n, compute number of possible valid BST with nodes i = 1 -> n
- Find first nearest common ancestor of 2 nodes
