//
//  2007.cpp
//  OnlieJudgeHunter

//  Problem Description
//  给定一段连续的整数，求出他们中所有偶数的平方和以及所有奇数的立方和。

//  Input
//  输入数据包含多组测试实例，每组测试实例包含一行，由两个整数m和n组成。

//  Output
//  对于每组输入数据，输出一行，应包括两个整数x和y，分别表示该段连续的整数中所有偶数的平方和以及所有奇数的立方和。
//  你可以认为32位整数足以保存结果。

//  Sample Input

//  1 3
//  2 5

//  Sample Output

//  4 28
//  20 152

//  Author
//  lcy

//  run:0MS	1640K
//  Created by UryuoHamusta on 17/2/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;

int strToInt(string& inputStr){
    stringstream ssControl;
    int re = 0 ;
    ssControl<<inputStr;
    ssControl>>re;
    return re;
}

int main(){
    //对输入进行处理
    string inputStr = "";
    getline(cin,inputStr);
    while (inputStr != "") {
        int sum1 = 0 ,sum2 = 0,a = 0,b = 0;
        stringstream ss(inputStr);
        string ta,tb;
        //a b 分别获取到
        ss>>ta>>tb;
        a = strToInt(ta);
        b = strToInt(tb);
        
        //特别注意 谁大谁小的问题！！
        if(a> b){
            int tmp;
            tmp = a;
            a = b;
            b = tmp;
        }
        //开始遍历区间计算
        for (int i=a;i<=b;i++){
            
            if (i%2) //奇数
                sum2 += pow(i, 3);
            else
                sum1 += pow(i ,2);
            
        }
        
        //遍历完成 输出结果
        cout<<sum1<<" "<<sum2<<endl;
        
        //准备下一次输入
        inputStr = "";
        getline(cin, inputStr);
        
    }
    return 0;
}
