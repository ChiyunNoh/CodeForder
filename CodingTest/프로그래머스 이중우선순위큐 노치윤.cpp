#include <string>
#include <vector>
#include <iostream>

using namespace std;

void insert(vector<int>& Heap, int n) {
    Heap.push_back(n);
    int size = Heap.size();
    int parent = 0;
    for (int i = size - 1; i > 0; i = parent) {
        parent = (i - 1) / 2;
        if (Heap[parent] >= Heap[i]) return;
        int temp = Heap[parent];
        Heap[parent] = Heap[i];
        Heap[i] = temp;
    }
}
void percolateDown(vector<int>& Heap, int n) {
    int child = (2 * n + 1);
    int right = (2 * n + 2);
    while (child < Heap.size()) {
        if (right<Heap.size() && Heap[right]>Heap[child]) child = right;
        if (Heap[child] <= Heap[n]) return;
        else {
            int temp = Heap[child];
            Heap[child] = Heap[n];
            Heap[n] = temp;
            n = child;
        }
    }
}
void deleteMax(vector<int>& Heap) {
    int size = Heap.size();
    Heap[0] = Heap[size - 1];
    Heap.pop_back();
    percolateDown(Heap, 0);
}

int deleteMin(vector<int>& Heap) {
    int min = 0;
    for (int i = 1; i < Heap.size(); i++) {
        if (Heap[i] < Heap[min]) {
            min = i;
        }
    }
    int n = Heap[min];
    for (int i = min; i < Heap.size() - 1; i++) {
        Heap[i] = Heap[i + 1];
    }
    Heap.pop_back();

    return n;
}
vector<int> solution(vector<string> operations) {
    vector<int> answer;
    vector<int> Heap;

    for (int i = 0; i < operations.size(); i++) {
        if (operations[i][0] == 'I') {
            insert(Heap, stoi(operations[i].substr(2)));
        }
        else {
            if (Heap.size() == 0) continue;
            else {
                if (operations[i][2] == '-') {
                    deleteMin(Heap);
                }
                else {
                    deleteMax(Heap);
                }
            }
        }
    }



    if (Heap.size() == 0) {
        answer.push_back(0);
        answer.push_back(0);
    }
    else {
        answer.push_back(Heap[0]);
        answer.push_back(deleteMin(Heap));
    }
    return answer;
}