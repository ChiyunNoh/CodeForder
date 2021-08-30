#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <ctime>

#include "sort.hpp"

using namespace std;

void generate_random_data(int* arr, int num);
void generate_sorted_data(int* arr, int num);
void check_result(int* arr, int* ansArr, int num);


int main(int argc, char *argv[])
{

  if( argc < 2)
  {
    cout << " 사용법 : " << argv[0] << " <array 크기>" << endl;
    return 1;
  }

  int numData = stoi(argv[1]);

  int* inArr = new int[numData];
  int* ansArr = new int[numData];

  int* bubbleArr = new int[numData];
  int* selectArr = new int[numData];
  int* mergeArr = new int[numData];


  clock_t bubbleTime;
  clock_t selectTime;
  clock_t mergeTime;

	// TODO : report the results of both random and sorted array in your readme file.
  generate_random_data(inArr, numData);


  for(int i = 0; i < numData; i++)
  {
    ansArr[i] = inArr[i];
    bubbleArr[i] = inArr[i];
    selectArr[i] = inArr[i];
    mergeArr[i] = inArr[i];
  }

  // STL Sort (for comparision)
  std::sort(ansArr, ansArr + numData);  

  // Bubble Sort
  cout << "Bubble Sort" << endl;
  bubbleTime = clock();
  bubbleSort(bubbleArr, numData);
  bubbleTime = clock() - bubbleTime;
  check_result(bubbleArr, ansArr, numData);
  cout << "  Execution time : " << fixed << setprecision(5) << (float)bubbleTime/CLOCKS_PER_SEC << " seconds" << endl << endl;

  // Selection Sort
  cout << "Selection Sort" << endl;
  selectTime = clock();
  selectionSort(selectArr, numData);
  selectTime = clock() - selectTime;
  check_result(selectArr, ansArr, numData);
  cout << "  Execution time : " << fixed << setprecision(5) << (float)selectTime/CLOCKS_PER_SEC << " seconds" << endl << endl;

  // Merge Sort
  cout << "Merge Sort" << endl;
  mergeTime = clock();
  mergeSort(mergeArr, 0, numData-1, numData);
  mergeTime = clock() - mergeTime;
  check_result(mergeArr, ansArr, numData);
  cout << "  Execution time : " << fixed << setprecision(5) << (float)mergeTime/CLOCKS_PER_SEC << " seconds" << endl << endl;


  delete[] inArr;
  delete[] ansArr;
  delete[] bubbleArr;
  delete[] selectArr;
  delete[] mergeArr;

  return 0;
}


void generate_random_data(int* arr, int num)
{
  srand(time(NULL));
	
  for(int i = 0 ; i  < num ; i++)
  {
    arr[i] = rand();
  }

}
void generate_sorted_data(int* arr, int num)
{
	
  for(int i = 0 ; i  < num ; i++)
  {
    arr[i] = i;
  }

}

void check_result(int* arr, int* ansArr, int num)
{
  bool correct = 0;
  for(int i = 0; i < num; i++)
  {
    if(arr[i] != ansArr[i])
    {
      cout << "  Fail !!" << endl;
      return;
    }
  }
  cout << "  Success !!" << endl;
}

