#include <iostream>
#include <vector>
#include "sorts.h"

using namespace std;

static int result_x = 0;
static vector<int> differences(0);

void input_vectors(vector<int> a, vector<int> b, size_t n){
    for(size_t i = 0; i < n; i++){
        cin >> a[i];
    }
    for (size_t i = 0; i < n; i++){
        cin >> b[i];
    }
}

void get_differences(vector<int> a, int m){
    size_t i = 0;
    for(int ele : a){
        differences[i++] = ele % m;
    }
    merge_sort(differences);
}

void main_process(vector<int> a, vector<int> b, int m, int x, size_t n){
    int sum_a = 0, sum_b = 0, d = 0;

    for(int i : a)
        sum_a += (i % m);
    for(int i : b)
        sum_b += i;
    d = sum_b - sum_a;
    x = d / int(n);
    if(d % int(n) == 0 && x < differences[0])
        result_x += x;
    else {
        for(size_t i = 0; i < n; i++)
            a[i] += differences[0];
        result_x += differences[0];
        main_process(a, b, m, 0, n);
    }
}
