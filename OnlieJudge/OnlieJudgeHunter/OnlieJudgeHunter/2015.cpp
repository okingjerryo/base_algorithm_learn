//
//  2015.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/21.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//
#include <iostream>

using namespace std;

int main(){
    
    int n , m,thisnum = 2;
    cin>>n>>m;
    while (n&&m){
    double thisGroupSum = 0,couter = m;
    
    while(n){
        thisGroupSum += thisnum;
        thisnum +=2;
        couter--;
        if (!couter){
            cout<<thisGroupSum/m<<" ";
            couter = m;
            thisGroupSum = 0;
        }
        n--;
    }
    if (m-couter)
    cout<<thisGroupSum /(m-couter)<<endl;
    //input
    n = 0,m = 0,thisnum = 2;
        cin>>n>>m;
    }
    return 0;
}

