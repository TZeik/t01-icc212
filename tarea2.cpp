#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
#include <chrono>

using namespace std;

priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

double findMedian(int num) {
    if (maxHeap.empty() || num <= maxHeap.top()) {
        maxHeap.push(num);
    } else {
        minHeap.push(num);
    }

    if (maxHeap.size() > minHeap.size() + 1) {
        int val = maxHeap.top();
        maxHeap.pop();
        minHeap.push(val);
    } 
    else if (minHeap.size() > maxHeap.size() + 1) {
        int val = minHeap.top();
        minHeap.pop();
        maxHeap.push(val);
    }

    if (maxHeap.size() == minHeap.size()) {
        if (maxHeap.empty()) {
            return 0.0;
        }
        double med = (maxHeap.top() + minHeap.top()) / 2.0;
        return med;
    } 
    else if (maxHeap.size() > minHeap.size()) {
        return static_cast<double>(maxHeap.top());
    } 
    else {
        return static_cast<double>(minHeap.top());
    }
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        cerr << "Error: no se pudo leer la cantidad de valores (n).\n";
        return 1;
    }

    vector<int> nr(n);
    for(int i = 0; i < n; i++) {
        if (scanf("%d", &nr[i]) == EOF) {
            cerr << "Advertencia: se acabó la entrada antes de leer todos los valores.\n";
            break;
        }
    }

    vector<double> medianas(n, 0.0);

    auto startTime = chrono::high_resolution_clock::now(); // algorythm start

    for(int i = 0; i < n; i++){
        medianas[i] = findMedian(nr[i]);
    }

    auto endTime = chrono::high_resolution_clock::now(); // algorythm end

    chrono::duration<double> diff = endTime - startTime;

    cout << "Tiempo de corrida: " << diff.count() << " segundos.\n";

    cout << "Mediana: " << medianas[n-1] << "\n";

    return 0;
}