//CARR implementation file

#include "CARR.h"

closedtable::closedtable(int size)
{
  hash_table_size = size;

  array = new node_CARR *[hash_table_size];

  for(int i=0; i< hash_table_size; ++i)
  {
    array[i]=NULL;
  }

}

closedtable::~closedtable()
{

}

int closedtable:: hash(char * value)
{ 
  int length = strlen(value);
  int size = 0;

  for(int i=0; i<length;++i)
  {
    size += value[i];
  }

  return size % hash_table_size;
}

int closedtable:: add(char * to_add, int owes)
{
  int place = hash(to_add);
  int added= 0;

  if(array[place] == NULL)
  {
    array[place] = new node_CARR;
    array[place]->data = new char [strlen(to_add)+1];
    strcpy(array[place]->data, to_add);
    array[place]->owed = owes;
    array[place]->next = NULL;
    return 1;
  }
  else
  {

    for(int i = place +1; i<hash_table_size && added ==0; ++i)
    {
      if(array[place] == NULL)
      {
        array[place] = new node_CARR;
        array[place]->data = new char [strlen(to_add)+1];
        strcpy(array[place]->data, to_add);
        array[place]->owed = owes;
        array[place]->next = NULL;
        added = 1;
      }
    }
    if(added ==1)
      return 1;
    else
    {
      for(int i=0; i < place && added ==0; ++i)
      {
        if(array[place] == NULL)
        {
          array[place] = new node_CARR;
          array[place]->data = new char [strlen(to_add)+1];
          strcpy(array[place]->data, to_add);
          array[place]->owed = owes;
          array[place]->next = NULL;
          added = 1;
        }
      }
    }
    if(added ==1)
      return 1;
    else 
      return -1;//table is full!!

  }
}


int closedtable:: display(char * value)
{
  int i = hash(value);
  int found = 0;

  for(int j = i; j < hash_table_size && found ==0; ++j)
  {
    if(array[j] != NULL)
    {
      if(strcmp(value, array[j]->data)==0)
      {
        cout<<" Owed: "<<array[j]->data<<endl;
        found = 1;
      }
    }
  }
//if its still not found after checkin to the end of the array, check first half
  if(!found)
  {
    for(int j =0; j< i && found ==0; ++j)
    {
      if(array[j] != NULL)
      {
        if(strcmp(value, array[j]->data)==0)
        {
          cout<<" Owed: "<<array[j]->data<<endl;
          found = 1;
        }
      }

    }
  }
  //for loop in if !found case may have added, so we now can check.otherwise, we were either found in first half and got here. 
  if(found)
    return 1;
  else//still not found after checking first half
    return -1;//not found anywhere

}

int closedtable:: remove_all()
{
  if(!array)
    return 0;
  for(int i=0; i<hash_table_size; ++i)
  {
    if(array[i] != NULL)
    {
      delete [] array[i]->data;
      delete array[i];
      array[i] = NULL;
    }
  }
  return 1;
}

int closedtable:: remove(char * value)
{
  if(!array)
    return 0;

  int i = hash(value);
  int found =0;

  for(int j = i; j<hash_table_size && found ==0; ++j)
  {
    if(array[j] != NULL)
    {
      if(strcmp(value, array[j]->data)==0)
      {
        cout<<" Owed: "<<array[j]->data<<endl;
        found = 1;
      }
    }
  }
//if its still not found after checkin to the end of the array, check first half
  if(!found)
  {
    for(int j =0; j< i && found ==0; ++j)
    {
      if(array[j] != NULL)
      {
        if(strcmp(value, array[j]->data)==0)
        {
          cout<<" Owed: "<<array[j]->data<<endl;
          found = 1;
        }
      }

    }
  }
  //for loop in if !found case may have added, so we now can check.otherwise, we were either found in first half and got here. 
  if(found)
    return 1;
  else//still not found after checking first half
    return -1;//not found anywhere   

}
