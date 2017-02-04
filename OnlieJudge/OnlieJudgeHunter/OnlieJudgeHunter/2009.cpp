//
//  2009.cpp
//  OnlieJudgeHunter

//  Problem Description
//  数列的定义如下：
//  数列的第一项为n，以后各项为前一项的平方根，求数列的前m项的和。

//  Input
//  输入数据有多组，每组占一行，由两个整数n（n<10000）和m(m<1000)组成，n和m的含义如前所述。

//  Output
//  对于每组输入数据，输出该数列的和，每个测试实例占一行，要求精度保留2位小数。

//  Sample Input
//  81 4
//  2 2

//  Sample Output
//  94.73
//  3.41

//  Author
//  lcy

//  RUN:0MS	1924K
//  Created by UryuoHamusta on 17/2/4.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>
using namespace std;
double strToDouble(string &input){
    double re = 0;
    stringstream ss;
    ss<<input;
    ss>>re;
    return re;
}

int main(){
    
    string inputStr = "";
    getline(cin, inputStr);
    while (inputStr != ""){
        stringstream ss(inputStr);
        string nowStr = "",numStr = "";
        double now = 0, num = 0;// now 现在的大小 num 项数
        ss>>nowStr>>numStr;
        
        //初始状态
        now = strToDouble(nowStr);
        num = strToDouble(numStr) - 1;
        
        double sum = now;
        for (int i=0;i<num;i++){
            now = sqrt(now);
            sum += now;
        }
        
        //得到结果 输出
        cout<<fixed<<showpoint<<setprecision(2)<<sum<<endl;
        //装配下一个
        inputStr = "";
        getline(cin, inputStr);
        
    }
    return 0;
}
