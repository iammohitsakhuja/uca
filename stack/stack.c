#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Stack definition.
typedef struct node {
  int data;
  struct node *next;
} Node;

// Stack operations.
void push(Node **head_pointer, int data);
int pop(Node **head_pointer);
int peek(Node *head);
bool is_empty(Node *head);

// Test declarations.
void test(void);

int main(void) {
  // Run all tests.
  test();

  printf("All tests passed!\n");

  return 0;
}

void test(void) {
  Node *head = NULL;

  // Add one element.
  push(&head, 1);
  assert(head != NULL);
  assert(is_empty(head) == false);
  assert(peek(head) == 1);

  // Add more elements, then pop.
  for (int i = 2; i <= 5; i++)
    push(&head, i);
  assert(peek(head) == 5);

  // Remove each element after peeking,
  for (int i = 5; i >= 1; i--) {
    assert(peek(head) == i);
    assert(pop(&head) == i);
  }

  // See that head now points to NULL.
  assert(head == NULL);

  // See that the stack is empty.
  assert(is_empty(head) == true);

  // Popping and peeking return INT_MIN when there are no elements in the list.
  assert(peek(head) == INT_MIN);
  assert(pop(&head) == INT_MIN);
}

static Node *create_new_node(int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  assert(new_node != NULL);
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void push(Node **head_pointer, int data) {
  // Create a new node.
  Node *new_node = create_new_node(data);

  // Update the new node.
  new_node->next = *head_pointer;

  // Update head pointer.
  *head_pointer = new_node;
}

int pop(Node **head_pointer) {
  // If there is no element in the stack, then return INT_MIN.
  if (is_empty(*head_pointer))
    return INT_MIN;

  // Fetch the topmost node.
  Node *top_node = *head_pointer;

  // Update the head pointer to point to the next node in the stack.
  *head_pointer = top_node->next;

  // Free the topmost node.
  int data = top_node->data;
  free(top_node);
  top_node = NULL;

  return data;
}

int peek(Node *head) {
  // If there is no element in the stack, then return INT_MIN.
  if (is_empty(head))
    return INT_MIN;

  // Return the data in the topmost element.
  return head->data;
}

bool is_empty(Node *head) {
  return !head;
}

