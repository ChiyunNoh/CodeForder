# 430.211 프로그래밍 방법론 : Project1

Student ID : 2017-13092 \
이 름 : 노치윤

## Introduction

### Bubble sort
Bubble sort는 단순히 인접한 두 원소의 크기를 비교해 나감으로써 오름차순/내림차순으로 정렬하는 알고리즘이다.

``` c++
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
```
>2중 반복문을 사용함으로 bubble sort를 구현하였다. 
Arr[0]부터 시작하여 가장 큰 원소가 맨 뒤로 이동하는 일련의 과정을 level이라고 하자. 이 때 첫 번째 반복문은 i번째 level을 의미한다.(0~n-2번째, 총 n-1번)

>두 번째 반복문은 한 level에서 인접한 두 원소의 크기를 비교해 가며 만일 a[j]>a[j+1]인 경우 두 원소를 swap 해 줌으로써 큰 원소를 오른쪽으로 위치시켜 오름차순을 만들어가는 과정을 의미한다.

### Selection sort

Selection sort는 두 개의 sub-array로 나누어 왼쪽의 array는 정렬된 상태라고 가정하고, 오른쪽 array에서 가장 작은 원소를 찾아내어 왼쪽 array의 마지막 수로 insert하는 과정을 반복함으로써 오름차순 정렬을 만드는 과정이다.

``` c++
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
```
>Selection sort도 2개의 반복문으로 구성된다. 첫 번째 반복문의 경우는 반복의 횟수를 의미한다. 마찬가지로 하나의 반복을 level이라고 하겠다. 이는 왼쪽 sub-array의 원소 수 와도 동일하다.
오른쪽 subarray의 원소 수가 0개이면 sorting 이 끝이 나므로 왼쪽 sub-array의 원소 수가 num-1일 때까지 반복을 진행한다.

>오른쪽 sub-array의 첫 번째 원소의 index 값을 min으로 가정하고 다른 index원소들과 비교하며 만일 arr[min] 보다 더 작은 원소가 존재하면 min의 값을 그 index로 바꾸는 과정을 통해 가장 작은 원소를 찾는다.
그 후 왼쪽 sub-array의 마지막 원소의 다음 원소(오른쪽 sub-array의 첫 번째 원소)와 최소값을 갖는 원소를 swap하면 하나의 level이 끝이 난다.


### Merge sort 


Merge sort는 배열을 앞, 뒷 부분 두 개의 sub-array로 나누어 각각을 정렬 하고, 다시 merge하는 과정을 반복하여 오름차순 정렬을 만드는 sort 이다.
``` c++
void mergeSort(int* arr, int left, int right, int num)//main.cpp 에서 mergeSort 를 호출할 수 있게 해주는 함
{
	int mid = (left + right) / 2;
	merge(arr, left, mid, right, num);
}

int* merge(int* arr, int left, int mid, int right, int num)
//배열을 두 부분으로 나누어 sorting을 진행하고, sorting 된 배열을 리턴하는 함수
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
```
이 sort는 총 3개의 부분으로 나누어 볼 수 있다.

#### 첫 번째 부분

``` c++
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
```

> 이 부분은 2개의 array로 divide 하는 과정이다. Array의 인덱스 0-mid 까지를 arr1, mid+1-num-1 까지를 arr2로 각각 분할 해 주었다.

####  두 번째 부분
``` c++
 arr1 = merge(arr1, 0, mid / 2, mid, mid + 1);
 arr2 = merge(arr2, 0, (num - mid - 2) / 2, num - mid - 2, num - mid - 1);
```
>이 부분은 merge sort 를 재귀호출 하는 과정이다. 이러한 재귀호출이 끝이 나는 시점은 바로 num==1 일 때 이며 이 때는 자기 자신의 arr를 리턴해 줌으로 재귀호출이 끝이 난다.

#### 세 번째 부분
3번째 부분은 정렬이 된 나누어진 배열을 다시 하나의 배열로 합치는 과정이다.
``` c++
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

    if 

  (rpoint < r_len) {
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
  ```
  >이 코드에서 point는 합쳐질 array에 원소가 들어가야할 index, lpoint는 arr1(왼쪽 array), rpoint는 arr2(오른쪽 array)의 비교 대상 index를 가리킨다.

  >두 array를 비교하면서 더 작은 값을 arr[point]에 대입하고, 꺼낸 쪽의 array와 배열 array의 인덱스를 하나씩 이동시켜주는 과정을 반복한다.
  만일 두 개의 array 중 하나의 array의 원소를 다 꺼낸 경우 남은 원소가 있는 array는 순서대로 배열 array에 복사해 주면 된다. 이러한 과정을 통해 오름차순 정렬이 완료된다.

  ## Experimental Result
  ### random data, sorted data 일 때 원소 수에 따른 각 정렬의 수행 시간 비교
  ![1](https://user-images.githubusercontent.com/80042772/114193956-f8487700-9989-11eb-8a16-697bff1b3b68.png)

  ![2](https://user-images.githubusercontent.com/80042772/114202075-cf2be480-9991-11eb-9c28-21ba4241e2a2.png)

  ![gen_ran_data(B,S)](https://user-images.githubusercontent.com/80042772/114202283-fe425600-9991-11eb-99a0-fae7508af4da.png)

  ![gen_sorted_data(B,S)](https://user-images.githubusercontent.com/80042772/114202333-0b5f4500-9992-11eb-8e95-c0c14fd36d82.png)
> Bubble sort와 selection sort의 추세선을 그려보고 R^2값을 나타내보았을 때 R^2 값이 거의 1에 근접하며 이는 거의 Data값들이 추세선에 근접하다고 할 수 있다. 즉, 실행 결과는 O(n^2)을 따른다고 할 수 있다.
 
 ![gen_ran_data(M)](https://user-images.githubusercontent.com/80042772/114202350-0f8b6280-9992-11eb-9e27-f05db802bfd2.png)

  ![gen_sorted_data(M)](https://user-images.githubusercontent.com/80042772/114202359-11552600-9992-11eb-90bc-42aada72ae7e.png)
> Merge sort 같은 경우 O(nlogn)의 실행시간을 따르는데 n이 큰 경우는 log n 보다 n의 영향이 커 일차 함수의 그래프처럼 보인다. N이 작은 경우 수행시간이 너무 짧아 주로 원소 수가 큰 경우에서 수행시간을 구했는데 더 정밀한 시간을 측정할 수가 있다면 O(nlogn)의 실행 결과를 따르는 걸 확인할 수 있을 것이다.

  ![log1](https://user-images.githubusercontent.com/80042772/114202590-4bbec300-9992-11eb-9076-d6d6d953d944.png)
> nlogn 그래프
  
  ![log2](https://user-images.githubusercontent.com/80042772/114202593-4c575980-9992-11eb-87d9-07e1ea5167ff.png)
> nlogn 그래프의 n이 작은 경우의 그래프

  ## Analysis

  ### generate_random_data, generate_sorted_data
  #### Bubble sort & Selection sort
  Sorted data가 주어진 경우 bubble sort 와 selection sort 의 수행시간 차이는 얼마 나지 않았으며 거의 비슷했다. Array의 원소 수가 n개 일 때 bubble sort와 selection sort의 비교 횟수는 n(n-1)/2 회로 동일하다. 또한 이미 sorted 된 상태이기에 두 원소를 교환하는 과정은 이루어 지지 않으므로 이러한 결과가 나온 것으로 예측한다.
  하지만 random data의 결과는 다르다. random으로 주어진 데이터 set의 경우 두 원소의 크기 비교 후 교환하는 과정이 이루어진다. Bubble sort의 경우 비교할 때마다 교환이 이루어 지는 반면 selection sort의 경우 한 개의 level 당 한 번씩만 교환이 이루어진다. 따라서 이는 n이 커지면 커질 수록 차이가 더 커질 것이며 실제로 결과에서 그러한 결과가 나온 걸 확인 할 수 있었다.
  #### Mergesort
  Merge sort는 sorted data가 주어지든 random data 가 주어지든 수행시간에서 별다른 차이를 보이지 않았다. Merge sort는 sorted data든 random data든 원소를 옮기는 횟수는 오로지 전체 원소의 전체 개수에 의존한다. 따라서 이러한 결과가 나온 것이다.

  Bubble sort와 selection sort, merge sort의 수행시간을 비교하면 다음과 같다.
  Bubble sort >> Selection sort > merge sort.
이는 비교 횟수+교환 횟수를 비교해보면 알 수 있는데 Bubble sort와 selection sort의 경우 위에서 비교한 바와 동일하지만, merge sort는 배열을 분할하는데 걸리는 시간 + 비교횟수가 앞의 두 sort에 비해 현저히 작다. n이 커질 수록 merge sort의 수행 시간은 다른 두 sort에 비해 현저하게 작았고, 이로 merge sort의 유용성을 확인할 수 있었다.

