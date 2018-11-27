#include "ARR.h"


hashtable::hashtable(int size)
{
  hash_table_size = size;

  array = new node_ARR * [hash_table_size];

  for(int i=0; i< hash_table_size; ++i)
  {
    array[i]=NULL;
  }

}

hashtable::~hashtable(){

  remove_all();
  delete [] array;
}


int hashtable:: hash(char * value)
{
  int length = strlen(value);
  int size = 0;

  for(int i=0; i<length;++i)
  {
    size += value[i];
  }

  return size % hash_table_size;



}

//add items to the array
int hashtable:: add(char * to_add, int owes) 
{
  int place = hash(to_add);

  node_ARR * temp = new node_ARR;
  temp-> data = new char[strlen(to_add)+1];
  strcpy(temp->data, to_add);
  temp->owed = owes;
  temp -> next = array[place];
  array[place] = temp;
  return 1;

}



int hashtable:: display(char * value)
{
  if(!array)
    return 0;

  int place = hash(value);

  return display(array[place], value);

}


int hashtable:: display(node_ARR * head, char * value)
{
  if(!head)
    return -1;

  if(strcmp(value, head->data) ==0)
  {
    cout<<"Amount Owed: "<< head->owed<<endl;
    return 1;
  }
  return display(head->next, value);

}

int hashtable:: remove(char * value)
{
  if(!array)
    return 0;
  int i = hash(value);
  return remove(array[i], value);
}

int hashtable:: remove(node_ARR *& head, char * value)
{
  if(!head)
    return -1;

  if(strcmp( value, head->data)==0)
  {
    node_ARR * temp = head->next;
    delete [] head->data;
    delete head;
    head = temp;
    return 1;
  }
  return remove(head->next, value);
}

int hashtable:: remove_all()
{
  if(!array)
    return 0;

  int index =0;
  return remove_all(array, index);

}

int hashtable:: remove_all(node_ARR ** array, int &index)
{
  if(index >= 0 && index < hash_table_size)
  {
    int hold = remove_all(array[index]);
    return remove_all(array, ++index);
  }
  return 0;

}

int hashtable:: remove_all(node_ARR *&head)
{
  if(!head)
    return 0;
  int hold = remove_all(head->next)+1;

  delete [] head->data;//dynamically allocated array for name
  delete head;
  head = NULL;
  return hold;

}


double hashtable::load(char * filename)
{
  ifstream file_in;
  int count = 0;

  remove_all();

  //file_in.open("../large1.txt");
  file_in.open(filename);
  if(!file_in) {
    cerr << "Unable to open file large1.txt...";
    return -1;
  }
  char temp_name[25];
  int temp_owed = 0;
  //while(file_in >> temp)
  while(!file_in.eof())
  {
    ++count;
    //file_in >> temp;
    file_in.get(temp_name, 25, ':');
    file_in.ignore(100, ':');
    file_in >> temp_owed;
    file_in.ignore(100, '\n');
    //cout << temp_name << ", " << temp_owed << endl;
    add(temp_name, temp_owed); //insert into tree
  }
  file_in.close();
  return count;
}
