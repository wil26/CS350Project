//ARR HEADER FILE
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <time.h> //used for timing
using namespace std;


struct node_ARR{
  node_ARR * next;
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
    int remove(char * value);
    int add(char * to_add, int owes);//for addition to LLL
    double load(char * filename);



  private:
    int display(node_ARR * head, char * value);
    int remove_all(node_ARR ** array, int & index);
    int remove_all(node_ARR *&head);
    int remove(node_ARR *&head, char * value);
    
    //data members
    int hash_table_size;
    node_ARR ** array;

};
