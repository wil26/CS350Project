#include "ARR.h"


hashtable::hashtable(int size)
{
  hash_table_size = size;

  array = new node * [hash_table_size];

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

  node * temp = new node;
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


int hashtable:: display(node * head, char * value)
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

int hashtable:: remove_all()
{
  if(!array)
    return 0;

  int index =0;
  return remove_all(array, index);

}

int hashtable:: remove_all(node ** array, int &index)
{
  if(index >= 0 && index < hash_table_size)
  {
    int hold = remove_all(array[index]);
    return remove_all(array, ++index);
  }
  return 0;

}

int hashtable:: remove_all(node *&head)
{
  if(!head)
    return 0;
  int hold = remove_all(head->next)+1;

  delete head;
  head = NULL;
  return hold;

}


