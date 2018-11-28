//CARR HEADER FILE
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <time.h> //used for timing
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
    int load(char * filename);
    double time_search(char * filename);
    double time_remove(char * filename);

  private:
    
    //data members
    int hash_table_size;
    node_CARR ** array;

};

