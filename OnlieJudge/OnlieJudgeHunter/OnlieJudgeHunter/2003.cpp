//
//  2003.cpp
//  OnlieJudgeHunter

//  Problem Description
//  求实数的绝对值。

//  Input
//  输入数据有多组，每组占一行，每行包含一个实数。

//  Output
//  对于每组输入数据，输出它的绝对值，要求每组数据输出一行，结果保留两位小数。

//  Sample Input
//  123
//  -234.00

//  Sample Output
//  123.00
//  234.00

//  Author
//  lcy

//  run:0MS	1896K

//  Created by UryuoHamusta on 17/2/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

int main(int argc, const char * argv[]) {
    
    string inputStr = "";
    stringstream ssControl;
    double re=0;
    
    //输入部分
    getline(cin, inputStr);
    while (inputStr != ""){
        ssControl<<inputStr;
        ssControl>>re;
        //清空ssControl内存
        ssControl.str("");
        ssControl.clear();
        
        //进行绝对值运算并格式化输出
        if(re<0) re=0.0-re;
        cout<<fixed<<showpoint<<setprecision(2)<<re<<endl;
        
        //处理下一个输入
        inputStr = "";
        getline(cin,inputStr);
    }
    
}
