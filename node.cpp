#include <iostream>
#include <cstring>
#include "node.h"


//main constructor
Node:: Node() {
}

Node:: Node(char Data){
  data = Data;
  //next = NULL;
  right = NULL;
  left = NULL;
}

char Node:: getData(){
  return data;
}

void Node:: setData(char Data){
  data = Data;
}


Node* Node:: getRight(){
  return right;
}

void Node:: setRight(Node* Right){
  right = Right;
}

Node* Node:: getLeft(){
  return left;
}

void Node:: setLeft(Node* Left){
  left = Left;
}

Node* Node:: getParent(){
  return parent;
}

void Node:: setParent(Node* Parent){
  parent = Parent;
}


