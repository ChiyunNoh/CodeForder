#ifndef SORT_H_
#define SORT_H_

/**
 * This header file contains the declarations of swap functions.
 * Implement the definitions of swap functions in sort.cpp file, not in this file.
 * We recommend not modifying the declaration.
 */ 

void swap(int *a, int *b);

void bubbleSort(int *arr, int num);

void selectionSort(int *arr, int num);

void mergeSort(int* arr, int left, int right, int num); 

int* merge(int *arr, int left, int mid, int right, int num);

#endif // SORT_H_
