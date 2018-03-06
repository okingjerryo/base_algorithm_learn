//
//  qsort.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/21.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
using namespace std;
int getPer(int* input,int start,int last){
    int x= input[last];
    int i = start-1;
    for (int j=start;j<last;j++){
        if (input[j]<x){
            i++;
            int tmp = input[i];
            input[i] = input [j];
            input[j] = tmp;
        }
    }
    int tmp = input[i+1];
    input[i+1] = input[last];
    input[last] = tmp;
    return i+1;
}

void quicksort(int *input,int first,int last){
    if (first>=last) return;
    int p = getPer(input,first,last);
    quicksort(input, first, p-1);
    quicksort(input,p+1, last);
}
int main(){
    int input[] = {5,3,1,2,4};
    quicksort(input,0,5);
    for (int i= 0;i<5;i++){
        cout<<input[i]<<" ";
    }
    return 0;
}
