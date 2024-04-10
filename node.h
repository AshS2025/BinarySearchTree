#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>

class Node {

 private:
 char data;
 Node* right;
 Node* left;
 Node* parent;

 public:

 //constructors
 Node();
 Node(char Data);

 //getters and setters

 char getData();
 void setData(char Data);

 Node* getRight();
 void setRight(Node* Right);

 Node* getLeft();
 void setLeft(Node* Left);

  Node* getParent();
  void setParent(Node* Parent);

};

#endif
