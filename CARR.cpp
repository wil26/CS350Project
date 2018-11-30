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
  remove_all();
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
      if(array[i] == NULL)
      {
        array[i] = new node_CARR;
        array[i]->data = new char [strlen(to_add)+1];
        strcpy(array[i]->data, to_add);
        array[i]->owed = owes;
        array[i]->next = NULL;
        added = 1;
      }
    }
    if(added ==1)
      return 1;
    else
    {
      for(int i=0; i < place && added ==0; ++i)
      {
        if(array[i] == NULL)
        {
          array[i] = new node_CARR;
          array[i]->data = new char [strlen(to_add)+1];
          strcpy(array[i]->data, to_add);
          array[i]->owed = owes;
          array[i]->next = NULL;
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

int closedtable::display_all()
{
  for(int i =0; i<hash_table_size; ++i)
  {
    if(array[i]!= NULL)
    {
      cout<<"User: " <<array[i]->data<<endl;
      cout<<"Owed: "<<array[i]->owed<<endl;
    }
  }
  return 1;
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
        //cout<<" Owed: "<<array[j]->data<<endl;
        cout<<" Owed: "<<array[j]->owed<<endl;
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
          //cout<<" Owed: "<<array[j]->data<<endl;
          cout<<" Owed: "<<array[j]->owed<<endl;
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

int closedtable:: display2(char * value)
{
  int i = hash(value);
  int found = 0;

  for(int j = i; j < hash_table_size && found ==0; ++j)
  {
    if(array[j] != NULL)
    {
      if(strcmp(value, array[j]->data)==0)
      {
        //cout<<" Owed: "<<array[j]->data<<endl;
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
          //cout<<" Owed: "<<array[j]->data<<endl;
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
      if(strcmp(value, array[j]->data) == 0)
      {
        cout<<" Owed: "<<array[j]->data<<endl;
        delete [] array[j]->data;
        delete array[j];
        array[j] = NULL;
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
          delete [] array[j]->data;
          delete array[j];
          array[j] = NULL;
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

int closedtable::load(char * filename)
{
  ifstream file_in;
  int count = 0;

  remove_all();

  //file_in.open("../large1.txt");
  file_in.open(filename);
  if(!file_in) {
    cerr << "Unable to open file " << filename << endl;
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
double closedtable::time_search(char * filename)
{
  ifstream file_in;
  int count = 0;
  int miss = 0;
  clock_t start, end;
  double cpu_time_used;
  //file_in.open("../large1.txt");
  file_in.open(filename);
  if(!file_in) {
    cerr << "Unable to open file large1.txt...\n";
    return -1;
  }
  char temp_name[25];
  int temp_owed = 0;
  //while(file_in >> temp)
  start = clock();
  while(!file_in.eof())
  {
    ++count;
    //file_in >> temp;
    file_in.get(temp_name, 25, ':');
    file_in.ignore(100, ':');
    file_in >> temp_owed;
    file_in.ignore(100, '\n');
    //cout << temp_name << ", " << temp_owed << endl;
    if(display2(temp_name) == -1)
      ++miss;
  }
  end = clock();
  cout << "number of misses: " << miss << endl;
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  file_in.close();
  return cpu_time_used;
}

double closedtable::time_remove(char * filename)
{
   ifstream file_in;
  int count = 0;
  clock_t start, end;
  double cpu_time_used;
  //file_in.open("../large1.txt");
  file_in.open(filename);
  if(!file_in) {
    cerr << "Unable to open file large1.txt...\n";
    return -1;
  }
  char temp_name[25];
  int temp_owed = 0;
  //while(file_in >> temp)
  start = clock();
  while(!file_in.eof())
  {
    ++count;
    //file_in >> temp;
    file_in.get(temp_name, 25, ':');
    file_in.ignore(100, ':');
    file_in >> temp_owed;
    file_in.ignore(100, '\n');
    //cout << temp_name << ", " << temp_owed << endl;
    cout << "Removing: " << temp_name << endl;
    remove(temp_name);
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  file_in.close();
  return cpu_time_used;
}
