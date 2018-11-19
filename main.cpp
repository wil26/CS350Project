#include "ARR.h"
//    OR
//#include"BST.h"


int main()
{
  int size = 0;
  char response;
  char name [20];

  cout<<"What is the size of the hash table? ";
  cin>> size;
  cin.ignore(5,'\n');

  hashtable table(size);



  //load should go here


  cout<<"Would you like to search for a value? (Y/N) ";
  cin>> response;
  cin.ignore (5, '\n');

  do{
    //obtain name 
    cout<<"Name of user to find: ";
    cin.get(name, 25, '\n');
    cin.ignore(25, '\n');

    //catch return
    int hold = table.display(name);
    
    //display returns 0 in wrapper if the array is NULL
    if(hold == 0)
    {
      cout<<"No table exists!" <<endl;
      break;
    }
    //display return -1 if we reach the end of the LLL, meaning no match.
    else if(hold == -1)
    {
      cout<<"Could not find user." <<endl;
    }
    //otherwise, display already displayed our info, ask if we want to go again.

    cout<<"Would you like to search again? (Y/N) ";
    cin>> response;
    cin.ignore (5, '\n');

  }while(response == 'Y' || response == 'y');



  return 0;
}
