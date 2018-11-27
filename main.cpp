//#include "ARR.h"
//    OR
#include "BST.h"
#include <time.h> //used for timing

int main()
{
  char response;
  char name [20];
  clock_t start, end;
  double cpu_time_used;

  //using Hashtable
  //Uncomment this if using hashtable.
  /* 
  int size = 0;
  cout<<"What is the size of the hash table? ";
  cin>> size;
  cin.ignore(5,'\n');

  hashtable table(size);
  */

  //Using BST
  tree BST;

  //load should go here

  char filename[20];
  strcpy(filename, "../large1.txt");
  start = clock();
  cout << BST.load(filename) << " nodes loaded.\n";
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  cout << "BST load time: " << cpu_time_used << endl;

  cout << "Testing search...\n";
  double time_test = BST.time_search(filename);
  cout << "Search for all nodes took: " << time_test << " sec.\n";


  cout<<"Would you like to search for a value? (Y/N) ";
  cin>> response;
  cin.ignore (5, '\n');

  do{
    //obtain name 
    cout<<"Name of user to find: ";
    cin.get(name, 25, '\n');
    cin.ignore(25, '\n');

    //catch return
    /*
     * Uncomment this if using hashtable
    int hold = table.display(name);

    */
    int hold = BST.display(name);

    
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


  //NOW FOR REMOVALS
  //
  cout<<"Would you like to remove? ";
  cin>>response;
  cin.ignore(5,'\n');

  do{
    //obtain name 
    cout<<"Name of user to remove: ";
    cin.get(name, 25, '\n');
    cin.ignore(25, '\n');

    //catch return
    /*
     * Uncomment this if using hashtable
    int hold = table.remove(name);

    */
    int hold = BST.remove(name);

    
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

    cout<<"Would you like to remove again? (Y/N) ";
    cin>> response;
    cin.ignore (5, '\n');

  }while(response == 'Y' || response == 'y');



  return 0;
}
