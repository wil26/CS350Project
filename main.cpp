
//Choose which data structure to use by commenting the
//#define for the other structures
#define BST_TEST
//#define ARR_TEST
//#define CARR_TEST

//#ifdef BST_TEST
#include "BST.h"
//#endif

//#ifdef ARR_TEST
#include "ARR.h"
//#endif
//    OR
//#ifdef CARR_TEST
#include "CARR.h"
//#endif

#include <time.h> //used for timing

int main()
{
  char response;
  char name [20];
  clock_t start, end;
  double cpu_time_used;

  //using Hashtable
  //Uncomment this if using hashtable.
#ifdef ARR_TEST
  int size = 0;
  cout<<"What is the size of the hash table? ";
  cin>> size;
  cin.ignore(5,'\n');

  hashtable table(size);
#endif

  //Using BST
#ifdef BST_TEST
  tree BST;
#endif

  //load should go here

  double time_test = 0.0;
  char filename[20];
  char filename2[20];
  strcpy(filename, "../large1.txt");
  strcpy(filename2, "../large2.txt");
  start = clock();
#ifdef BST_TEST
  cout << BST.load(filename) << " nodes loaded.\n";
#endif
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  cout << "BST load time: " << cpu_time_used << endl;

  /*
   * removal not working correctly. free() invalid pointer
  cout << "Testing removal. Dataset: " << filename2 << endl;
#ifdef BST_TEST
  time_test = BST.time_remove(filename2);
   #endif
  cout << "Removal for all nodes took: " << time_test << " sec.\n";
  */

  cout << "Testing search...\n";
#ifdef BST_TEST
  time_test = BST.time_search(filename);
#endif
  cout << "Search for all nodes took: " << time_test << " sec.\n";


  cout<<"Would you like to search for a value? (Y/N) ";
  cin>> response;
  cin.ignore (5, '\n');

  do{
    int hold = 0;
    //obtain name
    cout<<"Name of user to find: ";
    cin.get(name, 25, '\n');
    cin.ignore(25, '\n');

    //catch return
    /*
     * Uncomment this if using hashtable
     */
#ifdef ARR_TEST
    hold = table.display(name);
#endif

#ifdef BST_TEST
    hold = BST.display(name);
#endif

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
    int hold = 0;
    cout<<"Name of user to remove: ";
    cin.get(name, 25, '\n');
    cin.ignore(25, '\n');

    //catch return
    /*
     * Uncomment this if using hashtable
    */
#ifdef ARR_TEST
    hold = table.remove(name);
#endif

#ifdef BST_TEST
    hold = BST.remove(name);
#endif

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


