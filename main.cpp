#include <iostream>
#include <cstring>
#include "node.h"
#include <vector>
#include <fstream>

using namespace std;

void addNode(Node*&, Node*, Node*);
void removeNode(int, Node*, int);
void searchTree(Node*&, Node*, int);
void printTree(Node*, int);

int main() {

  bool running = true;
  Node* root = NULL;
  
  while (running == true) {
  cout << "what do you wanna do? type ADD, DELETE, SEARCH, PRINT, or QUIT" << endl;

  char command[10];
  cin >> command;

  if (strcmp(command, "ADD") == 0){
    cout << "would you like to add manually or by file? type m or f." << endl;
    char inputType;
    cin >> inputType;

    if (inputType == 'f'){
      //did this with help from vikram

       vector<int> input;
       fstream first_stream;
       first_stream.open("numbers.txt");
       int num;
       while(first_stream >> num){
       input.push_back(num);
        }
       vector <int> ::iterator iter = input.begin();
       for(iter = input.begin(); iter < input.end(); iter++){
       Node* newNode = new Node();
       newNode->setData(*iter);
       addNode(root, root, newNode);
       }
    }

    else {
      //manual string of numbers
      cout << "how many numbers do you want to enter?" << endl;
      int numOfNums;
      cin >> numOfNums;

      cout << "enter each number as you are prompted" << endl;

      //im too lazy to make a vector or break at spaces so users will have to enter one by one

      for (int i = 0; i < numOfNums; i++) {
	int entry;
	cout << "enter a number" << endl;
	cin >> entry;
	Node* newNode = new Node();
	newNode->setData(entry);
	addNode(root, root, newNode);
      }

      cout << "all numbers have been added" << endl;
    }
    
  }

  if (strcmp(command, "DELETE") == 0){
    cout << "what value do you want to delete?" << endl;
    int toDelete;
    cin >> toDelete;
    removeNode(0, root, toDelete);
  }

  if (strcmp(command, "SEARCH") == 0){
    cout << "what value are you searching for" << endl;
    int searchValue;
    cin >> searchValue;
    
    searchTree(root, root, searchValue);
  }

  if (strcmp(command, "PRINT") == 0){
    printTree(root, 0);
  }

  if (strcmp(command, "QUIT") == 0){
    running = false;
  }

}
  
}

void addNode(Node* &root, Node* current, Node* newNode){

  if (root == NULL){
    root = newNode;
  }

  else if (newNode->getData() < current->getData()){
    /*
      if added node is smaller than current, check if left is null
      if left is null then set the left as the newnode
      else recursion
     */
    if (current->getLeft() == NULL){
      current->setLeft(newNode);
      newNode->setParent(current);
      cout << "added left" << endl;
    }
    else{
      current = current->getLeft();
      addNode(root, current, newNode);
    }
  }

  else if (newNode->getData() >= current->getData()){
    if (current->getRight() == NULL){
      current->setRight(newNode);
      newNode->setParent(current);
      cout << "added right" << endl;
    }
    else {
      current = current->getRight();
      addNode(root, current, newNode);
    }
  }

}

void searchTree(Node* &root, Node* current, int searchValue){
//this function recursively checks if a given value exists in a tree
  //cout << "got inside the search tree function" << endl;  
  //case 1: tree is empty
  if (root == NULL){
    cout << "tree is empty" << endl;
  }

  if (current == NULL){
    cout << "doesn't exist" << endl;
  }

    else if (searchValue < current->getData()){
      current = current->getLeft();
      searchTree(root, current, searchValue);
    }

    else if (searchValue > current->getData()){
      current = current->getRight();
      searchTree(root, current, searchValue);
    }

    else if (searchValue == current->getData()){
      cout << "the value you are searching for does indeed exist in the tree" << endl;
    }
    
    else {
      cout << "value you are searching for does not exist in the tree" << endl;
    }
  
}

/*
void printTree(Node* root, int count){
  if (root == NULL){
    cout << "NOTHING IN THE TREE" << endl;
    return;
  }

  //iuterates to left of tree
  else if (root->getRight() != NULL){
    //cout << "inside right not null loop" << endl;
    printTree(root->getRight(), count +1);
  }

  //prints out appropriate number of tabs
  for (int i = 0; i < count; i++){
    cout << '\t';
    //cout << "inside for loop" << endl;
  }

  //prints
  cout << root->getData() << endl;
  //cout << "thing should've been printed" << endl;
  //runs on the right side

  if (root->getLeft() != NULL){
    //cout << "inside left not null loop" << endl;
    printTree (root->getLeft(), count + 1);
  }
}*/

//taken from shunting yard 
void printTree(Node* current, int count){
    if(current->getRight() != NULL){
      //count = count + 1;
        printTree(current->getRight(), count+1);
    }
    for(int i = 0; i < count; i++){
        cout << '\t';
    }

    int temp = current->getData();
    cout << temp << endl;
    
    if(current->getLeft() != NULL){
      //count = count + 1;
        printTree(current->getLeft(), count+1);
    }

}

//vikram and I rewrote the remove function while doign RBT
void removeNode(int direction, Node* current, int value){
    if(current->getData() == value){
        if(current->getRight() == NULL && current->getLeft() == NULL){
            if(current->getParent() != NULL){
                if(direction == 0){
                    current->getParent()->setLeft(NULL);
                }
                else if(direction == 1){
                    current->getParent()->setRight(NULL);
                }
            }
            delete current;
        }
        else if(current->getLeft() == NULL){
            cout << "1" << endl;
            if(direction == 0){
                current->getParent()->setLeft(current->getRight());
            }
            else if(direction == 1){
                current->getParent()->setRight(current->getRight());
            }
            current->getRight()->setParent(current->getParent());
            delete current;
        }
        else if(current->getRight() == NULL){
            cout << current->getParent()->getData() << endl;
            if(direction == 0){
                current->getParent()->setLeft(current->getLeft());
            }
            else if(direction == 1){
                current->getParent()->setRight(current->getLeft());
            }
            current->getLeft()->setParent(current->getParent());
            delete current;
        }
        else{
            Node* tempNode = current->getRight();
            int counter = 0;
            while(tempNode->getLeft() != NULL){
                tempNode = tempNode->getLeft();
                counter++;
            }
            current->setData(tempNode->getData());
            if(counter == 0){
                current->setRight(tempNode->getRight());
                tempNode->getParent()->setRight(tempNode->getRight());
            }
            else{
                tempNode->getParent()->setLeft(tempNode->getLeft());
            }
            delete tempNode;
        }
    }
    else if(current->getData() > value){
        removeNode(0, current->getLeft(), value);
    }
    else if(current->getData() < value){
        removeNode(1, current->getRight(), value);
    }

}

//void deleteNode(Node* &root, Node* current, int toDelete){
  /*
    case 1: tree is empty
    case 2: toDelete is root
    case 3: toDelete has one child
    case 4: toDeelete has two children

    we have to traverse through the tree until we find a node with the right value
    and then check conditions 3 and 4
   */

  //case 1

/*
if(root == NULL){

    cout << "tree is empty" << endl;
  }

  else if (current->getData() == toDelete){

    //case 1: leaf node
    if ((current->getLeft() == NULL) && (current->getRight() == NULL)){
      Node* temp = current;
      if (current->getParent()->getRight() == current){
	current->getParent()->setRight(NULL);
      }
      if (current->getParent()->getLeft() == current){
	current->getParent()->setLeft(NULL);
      }
      delete temp;
      //cout << "deleted through case 1" << endl;
      return;
      }

    //case 2: one child - right child
    else if (current->getRight() != NULL && current->getLeft() == NULL){
	Node* temp = current;
	if (current->getParent()->getRight() == current){
	  current->getParent()->setRight(current->getRight());
	}
	else if (current->getParent()->getLeft() == current){
	  current->getParent()->setLeft(current->getRight());
	}
	//cout << "deleted through case 2 part 1" << endl;
	delete temp;
	return;
    }

    //case 2, part 1: one child - left child
    //this might be the most inefficient way to do this ever but i dont care
    else if (current->getLeft() != NULL && current->getRight() == NULL){
      Node* temp = current;
      if (current->getParent()->getRight() == current){
	current->getParent()->setRight(current->getLeft());
      }
      else if (current->getParent()->getLeft() == current){
	current->getParent()->setLeft(current->getLeft());
      }
      delete temp;
      //cout << "deleted thru case 2 pt 2" << endl;
      return;
    }


    //case 3: two children
    else if (current->getLeft() != NULL && current->getRight() != NULL){
      Node* temp = current;
      if (current->getLeft() != NULL){
	temp = current->getLeft();
	while (temp->getRight() != NULL){
	  temp = temp->getRight();
	}
	current->setData(temp->getData());
	if (temp->getParent()->getRight() == temp){
	  temp->getParent()->setRight(NULL);
	}
	else if (temp->getParent()->getLeft() == temp){
	  temp->getParent()->setLeft(NULL);
	}
	
	delete temp;
      }
    }
    
  } //big else if

   else if (current->getData() > toDelete){
        deleteNode(root, current->getLeft(), toDelete);
    }
    else if(current->getData() < toDelete){
        deleteNode(root, current->getRight(), toDelete);
    }

} //function

*/
  
