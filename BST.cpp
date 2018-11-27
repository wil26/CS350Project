#include "BST.h"

node :: node(char * to_add, int owes, int ascii)
{
  data = new char[strlen(to_add)+1];
  strcpy(data, to_add);

  data_value = ascii;
  owed = owes;
  left = NULL;
  right = NULL;
}
// USE IF WE DONT WANT TO STORE ALPHABETICALLY
node ::node (char * to_add, int owes)
{
  data = new char[strlen(to_add)+1];
  strcpy(data, to_add);

  owed = owes;
  left = NULL;
  right = NULL;
}

node::~node()
{
  if(data)
    delete [] data;
  data_value = 0;
}

tree::tree()
{
  root= NULL;
}

tree::~tree()
{
  remove_all(root);
}

int tree::hash(char * value)
{
  int length = strlen(value);
  int val = 0;

  for(int i = 0; i < length; ++i)
  {
    val += value[i];
  }
  return val;
}

int tree::load(char * filename)
{
  ifstream file_in;
  int count = 0;

  if(root) //remove all if tree already exists
    remove_all(root);

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

int tree::add(char * value, int owes)
{
  //if we want to do this based on ascii values
  int hold = hash(value);

  return add(root, hold, value, owes);
}

int tree::add(node *& root, int value, char * to_add, int owes)
{
  if(!root)
  {
    root = new node(to_add, owes, value);
    return 1;
  }

  if(value < root->data_value)
    return add(root->left, value, to_add, owes);
  else
    return add(root->right, value, to_add, owes);
}


// for alphabetically sorting

int tree::add_alp(char * value, int owes)
{
  return add_alp(root, value, owes);

}

int tree::add_alp(node *& root, char * to_add, int owes)
{
  if(!root)
  {
    root = new node(to_add, owes);
    return 1;
  }

  int diff = strcmp(root->data, to_add);

  if(diff > 0)//root is greater alphabetically
  {
    return add_alp(root->left, to_add, owes);
  }
  else
    return add_alp(root->right, to_add, owes);
}

int tree::display_all()
{
  return display_all(root);
}

int tree::display_all(node * root)
{
  if(!root)
    return 0;
  display_all(root->left);
  root->display();
  display_all(root->right);
}

int tree::display(char * to_find)
{
  if(!root)
    return 0;
  int ascii = hash(to_find);
  return display(root, to_find, ascii);
}

int tree::display(node * root, char * to_find, int ascii)
{
  //we reached the end so the value does not exist.
  if(!root)
    return -1;

  if(root->data_value > ascii)//if roots value is greater, go left.
    return display(root->left, to_find, ascii);
  else if(root->data_value < ascii)//if roots value is lesser, go right.
    return display(root->right, to_find, ascii);
  else if(root->data_value == ascii)//otherwise they have the same ascii value
  {
    //still must check if it is the same word, as multiple words can have the same ascii value.
    if(strcmp(root->data, to_find) ==0)
    {
      cout<<"Amount Owed: "<<root->owed <<endl;
      return 1;
    }
    else//otherwise go right, as the IOS will be in the right subtree.
      return display(root->right, to_find, ascii);
  }
}

// use for alphabetical sorting
int tree:: display_alp(char * to_find)
{
  if(!root)
    return 0;
  return display_alp(root, to_find);
}


int tree:: display_alp(node * root, char * to_find)
{
  if(!root)
    return -1;
  
  int diff = strcmp(root->data, to_find);

  if(diff > 0)//root is greater alphabetically
  {
    return display_alp(root->left, to_find);
  }
  else if (diff < 0)
    return display_alp(root->right, to_find);
  else if(diff == 0)
  {
    cout<<"Amount Owed: "<< root->owed<<endl;
    return 1;
  }
}

int tree::remove_all(node *& root)
{
  if(!root)
    return 0;
  remove_all(root->left);
  remove_all(root->right);

  delete root;
  root = NULL;
  return 1;
}

int tree:: remove(char * value)
{
  if(!root)
    return 0;

  int ascii = hash(value);

  return remove(root, value, ascii);
}


int tree::remove(node *& root, char * value, int ascii)
{
  if(!root)
    return -1;

  if(root->data_value > ascii)//if the ascii value is less than root go left.
    return remove(root->left, value, ascii);
  else if(root->data_value < ascii)//if its greater than root go right
    return remove(root->right, value, ascii);
  else if(root->data_value == ascii){//if they are equal, still strcmp to make sure they match, if so, remove.
    if(strcmp(root->data, value) ==0){

      //we have found a match! now check if we only have one child. if we do, update it to be the new root.
      if(!root->left)
      {
        // this would double as a check if they have NO children, as hold will be NULL,
        // if hold is null, its just like deleting a no child item.

        node * hold = root->right;
        //delete [] root->data;
        delete root;
        root = hold;
        return 1;
      }
      else if(!root->right)//would only get to this if root->left EXISTS, but root->right does not.
      {
        node * hold = root->left;
        //delete [] root->data;
        delete root;
        root = hold;
        return 1;
      }
      else//we have two children, we need to find the IOS
      {
        //find the IOS
        node * IOS = find_ios(root->right, root->right);
        //delete the array currently in root, set it to name stored in IOS
        //delete [] root->data;
        root->data = new char[strlen(IOS->data)+1];
        strcpy(root->data, IOS->data);

        //set roots other data items to IOS' data items, theoretically "removing" root
        root->data_value = IOS->data_value;
        root->owed = IOS->owed;
        
        //delete the IOS
        //delete [] IOS;
        delete IOS;
        IOS = NULL;
        return 1;
      }

    }//end the if(strcmp) case.
    else//otherwise go right as IOS will be toward right
      return remove(root->right, value, ascii);
  }


}



//FOR ALPHABETICAL SORTING

int tree::remove_alp(char * value)
{
  if(!root)
    return 0;
  return remove_alp(root, value);
}



int tree::remove_alp(node *& root, char * value)
{
  if(!root)
    return -1;

  int diff = strcmp(root->data, value);
  if(diff > 0)//if the ascii value is less than root go left.
    return remove_alp(root->left, value);
  else if(diff < 0)//if its greater than root go right
    return remove_alp(root->right, value);
  else if(diff ==0){//if they are equal, still strcmp to make sure they match, if so, remove.

      //we have found a match! now check if we only have one child. if we do, update it to be the new root.
      if(!root->left)
      {
        // this would double as a check if they have NO children, as hold will be NULL,
        // if hold is null, its just like deleting a no child item.

        node * hold = root->right;
        delete [] root->data;
        delete root;
        root = hold;
        return 1;
      }
      else if(!root->right)//would only get to this if root->left EXISTS, but root->right does not.
      {
        node * hold = root->left;
        delete [] root->data;
        delete root;
        root = hold;
        return 1;
      }
      else//we have two children, we need to find the IOS
      {
        //find the IOS
        node * IOS = find_ios(root->right,root->right);
        //delete the array currently in root, set it to name stored in IOS
        delete [] root->data;
        root->data = new char[strlen(IOS->data)+1];
        strcpy(root->data, IOS->data);

        //set roots other data items to IOS' data items, theoretically "removing" root
        root->data_value = IOS->data_value;
        root->owed = IOS->owed;
        
        //delete the IOS
        delete [] IOS;
        delete IOS;
        IOS = NULL;
        return 1;
      }

    }//end the if(strcmp) case.
    else//otherwise go right as IOS will be toward right
      return remove_alp(root->right, value);

}



node *& tree:: find_ios(node *& root, node *& temp)
{
  //check if we're all the way left
  if(!root->left)
  {
    //make sure we dont have a right.
    if(!root->right)
      return root;
    else
    {
      //we have a right, so update root to point to it, and return the original root.
      temp = root;
      root = root->right;
      return temp;
    }
  }
  return find_ios(root->left, temp);
}

double tree::time_search(char * filename)
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
    display(temp_name);
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  file_in.close();
  return cpu_time_used;
}

double tree::time_remove(char * filename)
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
