//CARR HEADER FILE
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;


struct node_CARR{
  node_CARR * next;
  char * data;//name of person
  int owed;//money they owe
};

class closedtable{

  public:
    closedtable(int size);
    ~closedtable();
    //wrappers
    int hash(char * value);
    int display(char * value);
    int remove_all();
    int remove(char * value);
    int add(char * to_add, int owes);//for addition to LLL



  private:
    
    //data members
    int hash_table_size;
    node_CARR ** array;

};
