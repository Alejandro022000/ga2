#include <fstream>
#include <iostream>
using namespace std;

struct node {
  string word;
  double priority_val;
  node *next;
};
class my_queue {
private:
  node *top;

public:
  my_queue() { top = nullptr; }
  void enqueue(double, string);
  void dequeue();
  int get_top();
  void print_queue(ofstream &);
};

int my_queue::get_top() { return top->priority_val; }

void my_queue::dequeue() {
  if (top == nullptr) {
    return;
  }
  node *temp = top;
  top = top->next;
  delete temp;
}

void my_queue::enqueue(double num, string str) {
  node *temp = new node;
  temp->priority_val = num;
  temp->word = str;
  temp->next = nullptr;

  if (top == nullptr) {
    top = temp;
    return;
  }
  node *curr = top;
  if (temp->priority_val < top->priority_val) {
    temp->next = top;
    top = temp;
    return;
  }
  node *prev = nullptr;
  while (curr != nullptr && temp->priority_val >= curr->priority_val) {
    prev = curr;
    curr = curr->next;
  }
  prev->next = temp;
  temp->next = curr;
}

void my_queue::print_queue(ofstream &out) {
  if (top == nullptr) {
    return;
  }
  node *temp = top;
  while (temp != nullptr) {
    cout << temp->priority_val << ' ' << temp->word << endl;
    out << temp->word << endl;
    temp = temp->next;
  }
}
