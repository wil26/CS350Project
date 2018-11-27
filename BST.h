//BST HEADER FILE
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <time.h> //used for timing
using namespace std;


struct node{
  node(char * to_add, int owes, int ascii);//for ascii sorting
  node(char * to_add, int owes);//for alphabetical sorting
  void display(){cout << "Name: " << data << ", Amount owed: $" << owed << endl;};
  node * left;
  node * right;
  char * data;//hold the name of the person
  int data_value;//holds data's ascii value if we use it.
  int owed;//holds amount owed
  ~node(); //default destructor
};

class tree
{
  public:
    tree();
    ~tree();
    int load(char * filename);
    int add(char * value, int owes);
    int add_alp(char * value, int owes);
    int hash(char * value);//if we choose to use this to get the ascii value of a word for insert
    int display_all();
    int display(char * value);
    int display_alp(char * value);
    int remove_alp(char * value);
    int remove(char * value);
    double time_search(char * filename);

  private:
    int add(node *& root, int value, char * to_add, int owes);
    int add_alp(node *& root, char * to_add, int owes);
    int display_all(node * root);
    int display(node * root, char * to_find, int ascii);
    int display_alp(node * root, char * to_find);
    int remove_all(node *& root);
    int remove(node *& root, char * value, int ascii);//for ascii sorting
    int remove_alp(node *& root, char * value);//for alphabetical sorting
    node *& find_ios(node *& root, node *& temp);
    node * root;
};
