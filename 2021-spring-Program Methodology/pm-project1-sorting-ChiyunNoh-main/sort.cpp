#include "sort.hpp"

void swap(int* a, int* b)
{
	int temp = (*a);
	(*a) = (*b);
	(*b) = temp;
}

void selectionSort(int* arr, int num)
{
	for (int i = 0; i <= num - 1; i++) {
		int min = i;
		for (int j = i + 1; j <= num - 1; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		swap(arr + i, arr + min);
	}
}

void bubbleSort(int* arr, int num)
{
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr + j, arr + (j + 1));
			}
		}
	}
}

void mergeSort(int* arr, int left, int right, int num)
{
	int mid = (left + right) / 2;
	merge(arr, left, mid, right, num);
}

int* merge(int* arr, int left, int mid, int right, int num)
{
	if (num == 1) {
		return arr;
	}
	int* arr1 = new int[mid + 1];
	int* arr2 = new int[num - mid - 1];
	for (int i = 0; i < mid + 1; i++) {
		arr1[i] = arr[i];
	}
	for (int i = 0; i < num - mid - 1; i++) {
		arr2[i] = arr[i + mid + 1];
	}
	arr1 = merge(arr1, 0, mid / 2, mid, mid + 1);
	arr2 = merge(arr2, 0, (num - mid - 2) / 2, num - mid - 2, num - mid - 1);

	int point{ 0 };
	int lpoint{ 0 };
	int rpoint{ 0 };
	int l_len = mid + 1;
	int r_len = num - mid - 1;
	while (lpoint < l_len && rpoint < r_len) {
		if (arr1[lpoint] > arr2[rpoint]) {
			arr[point] = arr2[rpoint];
			point += 1;
			rpoint += 1;
		}
		else {
			arr[point] = arr1[lpoint];
			point += 1;
			lpoint += 1;
		}
	}
	if (lpoint < l_len) {
		while (true) {
			arr[point] = arr1[lpoint];
			point += 1;
			lpoint += 1;
			if (lpoint == l_len)
				break;
		}
	}

	if (rpoint < r_len) {
		while (true) {
			arr[point] = arr2[rpoint];
			point += 1;
			rpoint += 1;
			if (rpoint == r_len)
				break;
		}
	}
  delete[] arr1;
  delete[] arr2;
	return arr;
}

