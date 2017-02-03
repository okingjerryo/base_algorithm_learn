//
//  2002.cpp
//  CTest
//
//  Problem Description
//  根据输入的半径值，计算球的体积。
//  Input
//  输入数据有多组，每组占一行，每行包括一个实数，表示球的半径。
//  Output
//  输出对应的球的体积，对于每组输入数据，输出一行，计算结果保留三位小数。
//  Sample Input
//  1
//  1.5
//  Sample Output
//  4.189
//  14.137
//  Author
//  lcy
//
//  run: 15MS 1900K
//  Created by UryuoHamusta on 17/2/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;


#define PI 3.1415927

int main(int argc, const char * argv[]) {
    //输入数据处理
    string inputStr="";
    stringstream ssControl; //str->double
    
    getline(cin,inputStr);
    while (inputStr != ""){
        double thisData = 0;
        
        
        ssControl<<inputStr;
        ssControl>>thisData;
        //清空转换流的内存
        ssControl.str("");
        ssControl.clear();
        
        //计算体积
        thisData = (4.0/3.0)*PI*pow(thisData,3);
        //输出保留3位小数
        cout<<fixed<<showpoint<<setprecision(3)<<thisData<<endl;
        
        //准备下一次输入
        inputStr=""; //重新初始化
        getline(cin, inputStr);
    }
    
    
    return 0;
}
