#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

class Node {
public:
  int value;
  Node *next;
  Node (int v) : value(v), next(NULL) {}
  void append(Node *n) {
    next = n;
  }
  bool hasNext() {
    return next;
  }
};

Node* buildLinkedList(int length) {
  srand(time(NULL));
  Node *head = new Node(rand() % 10);
  Node *tail = head;
  for (int i = 0; i < length - 1; i++) {
    Node *newNode = new Node(rand() % 10);
    tail->append(newNode);
    tail = newNode;
  }
  return head;
}

Node *buildCorruptList(int length) {
  Node *head = new Node(0);
  Node *tail = head;
  for (int i = 0; i < length - 1; i++) {
    Node *newNode = new Node(i + 1);
    tail->append(newNode);
    tail = newNode;
  }
  tail->next = head->next->next->next->next->next;
  return head;
}

void printLinkedList(Node *head) {
  Node *current = head;
  while (current) {
    cout << current->value << " ";
    current = current-> next;
  }
  cout << endl;
}

void printCorruptList(Node *head, int length) {
  Node *current = head;
  for (int i = 0; i <= length; i++) {
    cout << current->value << " ";
    current = current-> next;
  }
  cout << endl;
}

void freeList(Node *head) {
  if (!head)
    return;
  freeList(head->next);
  free(head);
}

// Answer 1
void removeDuplicate(Node *head) {
  std::set<int> lookingTable;
  Node *current = head;
  Node *previous = head;
  while (current) {
    if (lookingTable.count(current->value)) {
      previous->next = current->next;
    } else {
      lookingTable.insert(current->value);
      previous = current;
    } 
    current = current->next;
 }
}

// Answer 2
int nToLast(Node *head, int n) {
  Node *current = head;
  Node *nPtr = head;
  int length = 0;
  while (current) {
    length++;
    current = current->next;
    if (length > n + 1) {
      nPtr = nPtr->next;
    }
  }
  if (length > n)
    return nPtr->value;
  else
    return -1;
}

// Answer 3
void deleteMiddleNode(Node *middle) {
  if (!middle || !(middle->next))
    return;
  Node *ptr = middle->next;
  middle->value = ptr->value;
  middle->next = ptr->next;
  free(ptr);
}

// Answer 4
Node *addList(Node *first, Node *second) {
  if (!first && !second)
    return NULL;
  if (!first)
    return second;
  if (!second)
    return first;

  Node *resultHead = new Node((first->value + second->value) % 10);
  Node *result = resultHead;
  Node *firstPtr = first->next;
  Node *secondPtr = second->next;
  int var1, var2, overflow = (first->value + second->value) / 10;

  while (firstPtr || secondPtr || overflow) {
    if (firstPtr) {
      var1 = firstPtr->value;
      firstPtr = firstPtr->next;
    } else {
      var1 = 0;
    }
    if (secondPtr) {
      var2 = secondPtr->value;
      secondPtr = secondPtr->next;
    } else {
      var2 = 0;
    }
    Node *newNode = new Node((var1 + var2 + overflow) % 10);
    result->next = newNode;
    result = newNode;
    overflow = (var1 + var2 + overflow) / 10;
  }
  return resultHead;
}

// Answer 5
Node *findLoopHead(Node *head) {
  Node *ptr1 = head;
  Node *ptr2 = head;

  while (ptr2) {
    ptr1 = ptr1->next;
    ptr2 = ptr2->next->next;
    if (ptr1 == ptr2)
      break;
  }

  ptr1 = head;
  while (ptr1 != ptr2) {
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
  return ptr1;
}


int main() {
  // Test Question 1
  cout << endl << "Answer 1" << endl;
  Node *list1 = buildLinkedList(20);
  printLinkedList(list1);
  removeDuplicate(list1);
  printLinkedList(list1);

  // Test Question 2
  cout << endl << "Answer 2" << endl;
  cout << "1 To Last Element: " << nToLast(list1, 1) << endl;
  cout << "5 To Last Element: " << nToLast(list1, 5) << endl;
  cout << "20 To Last Element: " << nToLast(list1, 20) << endl;

  // Test Question 3
  cout << endl << "Answer 3" << endl;
  Node *middle = list1->next->next;
  cout << "delete " << middle->value << endl;
  deleteMiddleNode(middle);
  printLinkedList(list1);

  // Test Question 4
  cout << endl << "Answer 4" << endl;
  Node *list2 = buildLinkedList(4);
  Node *list3 = buildLinkedList(4);
  Node *result1 = addList(list2, list3);
  Node *result2 = addList(list1, list2);
  printLinkedList(list2);
  printLinkedList(list3);
  cout << "Add Result" << endl;
  printLinkedList(result1);
  cout << endl;
  printLinkedList(list2);
  printLinkedList(list1);
  cout << "Add Result" << endl;
  printLinkedList(result2);

  // Test Question 5
  cout << endl << "Answer 5" << endl;
  Node *list4 = buildCorruptList(20);
  printCorruptList(list4, 20);
  Node *loopHead = findLoopHead(list4);
  cout << "Loop Head: " << loopHead->value << endl;

  freeList(list1);
  freeList(list2);
  freeList(list3);
  freeList(result1);
  freeList(result2);
  return 0;
}
