//
//  ifstream.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/17.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <fstream>
#include <iostream>
using namespace std;

int main(){
    ifstream input("/Users/uryuo/test.txt");
    int num1,num2;
    if (!input.is_open()) cout<<"readError"<<endl;
    input>>num1>>num2;
    
    cout<<num1<<" "<<num2<<endl;
    
    int out1 = 2,out2 = 4;
    ofstream output("/Users/uryuo/testOut.txt");
    output<<out1<<" "<<out2<<endl;
    
    input.close();
    output.close();
    return 0;
}
