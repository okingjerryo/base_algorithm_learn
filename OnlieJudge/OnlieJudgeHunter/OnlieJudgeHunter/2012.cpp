//
//  2012.cpp
//  OnlieJudgeHunter

//  Problem Description
//  对于表达式n^2+n+41，当n在（x,y）范围内取整数值时（包括x,y）(-39<=x<y<=50)，判定该表达式的值是否都为素数。

//  Input
//  输入数据有多组，每组占一行，由两个整数x，y组成，当x=0,y=0时，表示输入结束，该行不做处理。

//  Output
//  对于每个给定范围内的取值，如果表达式的值都为素数，则输出"OK",否则请输出“Sorry”,每组输出占一行。

//  Sample Input
//  0 1
//  0 0

//  Sample Output
//  OK

//  Author
//  lcy

//  RUN:15MS	1628K
//  Created by UryuoHamusta on 17/2/4.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;
bool isSu(int &input){ //这里复杂度过高 可以优化
    bool flag=true;
    for (int i=2 ;i<=sqrt(input);i++){
        if (!(input%i)){
            flag = false;
            break;
        }
    }
    return flag;
}

int main(){
    string inputStr = "";
    getline(cin,inputStr);
    while (inputStr != ""){
        
        stringstream ss(inputStr);
        int a = 0,b = 0;
        ss>>a>>b;
        if (!a && !b) break; //全0结束
        bool flag = true;
        for (int i=a;i<=b;i++){
            int test = pow(i,2)+i+41;
            if (!isSu(test)){
                flag = false;
                break;
            }
        }
        if (flag)
            cout<<"OK"<<endl;
        else
            cout<<"Sorry"<<endl;
        
        //下一个输入
        inputStr = "";
        getline(cin, inputStr);
    }
    return 0;
}
