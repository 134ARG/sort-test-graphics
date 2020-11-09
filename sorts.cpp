#include "mainwindow.h"
#include <thread>
#include <chrono>
#include <random>
#include <functional>
#include <vector>
#include "sorts.h"
// debug
#include <iostream>
#include <algorithm>

using namespace std::chrono;
using namespace std;

const long SAMPLE_UPPER_BOUND = 1000000000;
const long SAMPLE_LOWER_BOUND = 1;




template  <typename T>
QString to_QString(T n){
    return QString::number(n);
}

/*template <typename T>
vector<T> subvector(vector<T> vec, size_t begin, size_t end){
    if(begin > end){
        throw std::invalid_argument("Beginning index is greater than ending!");
    }else if(end >= vec.size()){
        throw std::invalid_argument("Endnig index is out of range!");
    }else if(begin == end){
        vector<T> returned(1);
        returned[0] = vec[begin];
        return returned;
    }else{
        auto i_begin = vec.begin() + int(begin);
        auto i_end = vec.begin() + int(end);
        vector<T> returned(i_begin, i_end);

        return returned;
    }
}*/


// sorts
void selection_sort(std::vector<int> &seq){

    size_t length = seq.size();

    for(size_t i = 0; i < length; i++){
        volatile size_t min = i;
        for(size_t j = i + 1; j < length; j++){
            if(seq[j] < seq[min]) min = j;
        }
        std::swap(seq[i], seq[min]);

    }

}



void insertion_sort(std::vector<int> &seq){

    size_t length = seq.size();

    for (size_t i = 1; i < length; i++){
        for (size_t j = i; j > 0 && seq[j - 1] > seq[j]; j--){         // optimized in loop entrance condition.
            std::swap(seq[j - 1], seq[j]);
        }
    }
}



void shell_sort(std::vector<int> &seq){

    size_t length = seq.size();
    size_t h = 1;

    while (h < length /2) h = 2*h + 1;
    while (h >= 1){
        for (size_t i = h; i < length; i++){
            for (size_t j = i; j >= h && seq[j - h] > seq[j]; j-=h){         // optimized in loop entrance condition.
                std::swap(seq[j - h], seq[j]);
            }
        }
        h /= 2;

    }
}



void merge(vector<int> &a, vector<int> &merged, size_t low, size_t middle, size_t high){
    size_t i = middle + 1, l = low;
    for(size_t j = low; j <= high; j++)
        merged[j] = a[j];
    for(size_t j = low; j <= high; j++)
        if((merged[l] < merged[i] || i > high) && l <= middle)
            a[j] = merged[l++];
        else
            a[j] = merged[i++];
}

void divide(vector<int> &seq, vector<int> &tmp, size_t lo, size_t hi){
    if(lo >= hi){
        return;
    }else{
        size_t middle = lo + (hi - lo) / 2 ;
        divide(seq, tmp, lo, middle);
        divide(seq, tmp, middle + 1, hi);
        merge(seq, tmp, lo, middle, hi);
    }
}

void merge_sort(vector<int> &seq){
    vector<int> tmp(seq.size());
    divide(seq, tmp, 0, seq.size() - 1);
}

void quick_sort(vector<int> &seq) {
    std::sort(seq.begin(), seq.end());
}


std::vector<int> generate_test_seq(size_t size){
    std::vector<int> test_sample(size);

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(SAMPLE_LOWER_BOUND, SAMPLE_UPPER_BOUND);

    for (int &i : test_sample)
        i = dis(gen);

    return test_sample;
}

// comparison func

auto time_sort(std::function<void(std::vector<int> &)> f, std::vector<int> test_sample){
    auto start = steady_clock::now();
    f(test_sample);
    auto stop = steady_clock::now();

    std::cout << std::is_sorted(test_sample.begin(), test_sample.end()) << std::endl;
//    for (int i : test_sample){
//        std::cout << i << std::endl;
//    }

    return duration_cast<milliseconds>(stop - start);

}


void compare_sorts(MainWindow *win, size_t size){
    std::vector<int> test_sample = generate_test_seq(size);


    std::thread th1([=](){
        double time = time_sort(merge_sort, test_sample).count();
        win->display_selection(to_QString(time));
    });


    std::thread th2([=](){
        double time = time_sort(shell_sort, test_sample).count();
        win->display_shell(to_QString(time));
    });


//    std::thread th3([=](){
//        double time = time_sort(insertion_sort, test_sample).count();
//        win->display_insertion(to_QString(time));

//    });

    std::thread th4([=](){
        double time = time_sort(quick_sort, test_sample).count();
        win->display_rate(to_QString(time));
    });

    th1.join();
    th2.join();
//    th3.join();
    th4.join();

    /*double time1 = time_sort(shell_sort, size).count();
    win->display_shell(to_QString(time1));

    double time2 = time_sort(insertion_sort, size).count();
    win->display_insertion(to_QString(time2));*/

    /*if(time1 >= time2){
        win->display_rate(to_QString(time1 / time2));
    }else{
        win->display_rate(to_QString(time2 / time1));
    }*/



}










