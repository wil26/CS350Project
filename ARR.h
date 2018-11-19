//ARR HEADER FILE
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;


struct node{
  node * next;
  char * data;//name of person
  int owed;//money they owe
};

class hashtable{

  public:
    hashtable(int size);
    ~hashtable();
    //wrappers
    int hash(char * value);
    int display(char * value);
    int remove_all();
    int add(char * to_add, int owes);//for addition to LLL



  private:
    int display(node * head, char * value);
    int remove_all(node ** array, int & index);
    int remove_all(node *&head);
    
    //data members
    int hash_table_size;
    node ** array;

};
