#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>

using namespace std;

template<class T>
class Node {
public:
  T value;
  Node *prev;
  Node (T v) : value(v), prev(NULL) {}
};

template<class T>
class Stack {
public:
  Node<T> *top;
  string index;

  Stack():top(NULL) {}
  Stack(string s):top(NULL), index(s) {}

  T pop() {
    if (top) {
      T v = top->value;
      top = top->prev;
      return v;
    } else {
      return -1;
    }
  }

  void push(T v) {
    Node<T> *n = new Node<T>(v);
    n->prev = top;
    top = n;
  }

  T peek() {
    if (top)
      return top->value;
    else
      return -1;
  }

  bool isEmpty() {
    return top == NULL;
  }

  void printStack() {
    Node<T> *current = top;
    while (current) {
      cout << current->value << " ";
      current = current->prev;
    }
    cout << endl;
  }
};

// Answer 3.2
template<class T>
class StackWithMin {
  Stack<T> s;
  Stack<T> minStack;
  unordered_map<T, int> occurence;

public:
  void push(T v) {
    s.push(v);
    if (minStack.isEmpty()) {
      minStack.push(v);
    } else {
      if (v < minStack.peek())
	minStack.push(v);
    }
    if (occurence.count(v))
      occurence[v] = occurence[v] + 1;
    else
      occurence[v] = 1;
  }

  T pop() {
    T v = s.pop();
    if (minStack.peek() == v) {
      if (occurence[v] == 1)
	minStack.pop();      
    }
    return v;
  }

  bool isEmpty() {
    return s.isEmpty();
  }

  T min() {
    if (!minStack.isEmpty())
      return minStack.peek();
    return -1;
  }

  void printStack() {
    s.printStack();
  }
};

// Answer 3.4
void Hanoi(int n, Stack<int> &src, Stack<int> &dest, Stack<int> &buf) {
  if (n > 0) {
    Hanoi(n - 1, src, buf, dest);
    dest.push(src.pop());
    cout << "Move " << dest.peek() << " from " << src.index << " to " << dest.index << endl;
    Hanoi(n - 1, buf, dest, src);
  }
}

void HanoiExtra(int n, Stack<int> &src, Stack<int> &dest,
		 Stack<int> &buf1, Stack<int> &buf2) {
  if (n > 1) {
    HanoiExtra(n - 2, src, buf1, dest, buf2);
    buf2.push(src.pop());
    cout << "Move " << buf2.peek() << " from " << src.index << " to " << buf2.index << endl;
    dest.push(src.pop());
    cout << "Move " << dest.peek() << " from " << src.index << " to " << dest.index << endl;
    dest.push(buf2.pop());
    cout << "Move " << dest.peek() << " from " << buf2.index << " to " << dest.index << endl;
    HanoiExtra(n - 2, buf1, dest, src, buf2);
  } else if (n == 1) {
    dest.push(src.pop());
    cout << "Move " << dest.peek() << " from " << src.index << " to " << dest.index << endl;    
  }
}

// Answer 3.5
template<class T>
class MyQueue {
  Stack<T> input;
  Stack<T> output;
public:
  void enQueue(T v) {
    input.push(v);
  }

  T deQueue() {
    if (!output.isEmpty()) {
      return output.pop();
    } else {
      if (input.isEmpty()) {
	return -1;
      } else {
	while (!input.isEmpty())
	  output.push(input.pop());
	return output.pop();
      }
    }
  }

  bool isEmpty() {
    return input.isEmpty() && output.isEmpty(); 
  }

  void printQ() {
    cout << "Queue: ";
    output.printStack();
    cout << "Reversed: ";
    input.printStack();
  }
};

// Answer 3.6
void sortStack(Stack<int> &s) {
  Stack<int> buffer;
  int temp;
  
  while (!s.isEmpty()) {
    temp = s.pop();
    while (!buffer.isEmpty() && temp > buffer.peek())
      s.push(buffer.pop());
    buffer.push(temp);
  }

  while (!buffer.isEmpty())
    s.push(buffer.pop());
}

int main() {
  srand(time(NULL));
  
  // Test 3.2
  StackWithMin<int> sMin;
  for (int i = 0; i < 25; i++) {
    if (rand() % 2) {
      sMin.push(rand() % 100);
      sMin.printStack();
      cout << "Min is " << sMin.min() << endl << endl;
    } else {
      if (!sMin.isEmpty()) {
	sMin.pop();
	sMin.printStack();
	cout << "Min is " << sMin.min() << endl << endl;      
      }
    }
  }
  

  // Test 3.4
  Stack<int> src("Source"), buf("Buffer"), dest("Destination"), buf2("Buffer2");
  for (int i = 20; i > 0; i--)
    src.push(i);
  cout << "Source:" << endl;
  src.printStack();
  HanoiExtra(5, src, dest, buf, buf2);
  cout << "Final Destination Look: " << endl;
  dest.printStack();
  cout << endl;

  // Test 3.5
  MyQueue<int> q;
  for (int i = 0; i < 25; i++) {
    if (rand() % 2) {
      int v = rand() % 20;
      cout << "Enqueue " << v << endl;
      q.enQueue(v);
      q.printQ();
      cout << endl;
    } else {
      if (q.isEmpty()) {
	cout << "Empty Queue" << endl << endl;
      } else {
	int v = q.deQueue();
	cout << "Dequeue " << v << endl;
	q.printQ();
	cout << endl;
      }
    }
  }

  // Test 3.6
  Stack<int> sStack;
  for (int i = 0; i < 20; i++) {
    sStack.push(rand() % 100);
  }
  sStack.printStack();
  sortStack(sStack);
  sStack.printStack();
  
  return 0;
}
