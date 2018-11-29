
//Choose which data structure to use by commenting the
//#define for the other structures
//#define BST_TEST
#define ARR_TEST
//#define CARR_TEST

//#define REMOVAL //comment if you don't want to test removal

#include "BST.h"
#include "ARR.h"
#include "CARR.h"

#include <time.h> //used for timing

const int NUM_FILES = 5; //number of test files (pairs)

int main()
{
  char response;
  char name [20];
  clock_t start, end;
  double cpu_time_used;
  double time_test = 0.0;

  //Using BST
#ifdef BST_TEST
  tree BST;
#endif

  //using Hashtable
#ifdef ARR_TEST
  int size_table = 0;
  cout<<"What is the size of the hash table? ";
  cin>> size_table;
  cin.ignore(5,'\n');

  hashtable table(size_table);
#endif

  //using closed Hashtable
#ifdef CARR_TEST
  int size_ctable = 0;
  cout<<"What is the size of the closed hash table? ";
  cin>> size_ctable;
  cin.ignore(5,'\n');

  closedtable ctable(size_ctable);
#endif

  char filenames[NUM_FILES][25];
  char filenames2[NUM_FILES][25];
  for(int i = 0; i < NUM_FILES; ++i)
  {
    switch (i)
    {
      case 0:
        strcpy(filenames[0], "../5000.txt");
        strcpy(filenames2[0], "../5000_2.txt");
        break;
      case 1:
        strcpy(filenames[1], "../10000.txt");
        strcpy(filenames2[1], "../10000_2.txt");
        break;
      case 2:
        strcpy(filenames[2], "../large1.txt");
        strcpy(filenames2[2], "../large2.txt");
        break;
      case 3:
        strcpy(filenames[3], "../100000_1.txt");
        strcpy(filenames2[3], "../100000_2.txt");
        break;
      case 4:
          strcpy(filenames[4], "../200000_1.txt");
          strcpy(filenames2[4], "../200000_2.txt");
          break;
    }
  }

  for(int i = 0; i < NUM_FILES; ++i) {
    //INSERT LOAD TEST
#ifdef BST_TEST
    BST.remove_all();
    start = clock();
    int num_nodes_BST = BST.load(filenames[i]);
    cout << "\n--------------------" << num_nodes_BST << " nodes --------------------\n";
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "BST: Inserting " << num_nodes_BST << " nodes time: " << cpu_time_used << endl;
#endif

#ifdef ARR_TEST
    start = clock();
    int num_nodes_ARR = table.load(filenames[i]);
    cout << "\n--------------------" << num_nodes_ARR << " nodes --------------------\n";
    end = clock();
    //cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    //cout << "\nstart ticks: " << start << " , end ticks: " << end << endl;
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    cout << "Hash table: Inserting " << num_nodes_ARR << " nodes time: " << cpu_time_used << endl;
#endif

#ifdef CARR_TEST
    start = clock();
    int num_nodes_CARR = ctable.load(filenames[i]);
    cout << "\n--------------------" << num_nodes_CARR << " nodes --------------------\n";
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Hash table: Inserting " << num_nodes_CARR << " nodes time: " << cpu_time_used << endl;
#endif

    //SEARCH TEST
#ifdef BST_TEST
    //cout << "Testing BST search by searching for every node.\n";
    time_test = BST.time_search(filenames[i]);
    cout << "BST: Search for all nodes took: " << time_test << " sec.\n";
#endif

#ifdef ARR_TEST
    cout << "Testing Hash Table search by searching for every node.\n";
    time_test = table.time_search(filenames[i]);
    cout << "Hash table: Search for all nodes took: " << time_test << " sec.\n";
#endif

#ifdef CARR_TEST
    cout << "Testing Closed Hash Table search by searching for every node.\n";
    time_test = ctable.time_search(filenames[i]);
    cout << "Closed Hash table: Search for all nodes took: " << time_test << " sec.\n";
#endif

    //RUN TEST FOR REMOVAL
#ifdef REMOVAL
#ifdef BST_TEST
    //removal not working correctly. free() invalid pointer
    cout << "*File used for order of removals: " << filenames2[i] << endl;
    time_test = BST.time_remove(filenames2[i]);
    cout << "BST: Removal for all nodes took: " << time_test << " sec.\n";
#endif

#ifdef ARR_TEST
    cout << "Testing hash table removal. File used for order of removals: " << filenames2[i] << endl;
    time_test = table.time_remove(filenames2[i]);
    cout << "Hash table: Removal for all nodes took: " << time_test << " sec.\n";
#endif

#ifdef CARR_TEST
    cout << "Testing closed hash table removal. File used for order of removals: " << filenames2[i] << endl;
    time_test = ctable.time_remove(filenames2[i]);
    cout << "Closed Hash table: Removal for all nodes took: " << time_test << " sec.\n";
#endif
#endif //REMOVAL
  }
  cout << endl;

  //UI
  cout << "Would you like to search for a value? (Y/N) ";
  cin >> response;
  cin.ignore (5, '\n');

  if(response =='y' || response == 'Y')
  {
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

#ifdef CARR_TEST
    hold = ctable.display(name);
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
  }


  //NOW FOR REMOVALS
  //
  cout<<"Would you like to remove? ";
  cin>>response;
  cin.ignore(5,'\n');

  if(response =='y' || response == 'Y')
  {
    do{
      //obtain name
      int hold = 0;
      cout<<"Name of user to remove: ";
      cin.get(name, 25, '\n');
      cin.ignore(25, '\n');

#ifdef ARR_TEST
      hold = table.remove(name);
#endif

#ifdef CARR_TEST
      hold = ctable.remove(name);
      cout<<endl;
      ctable.display_all();
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
  }
  return 0;
}
