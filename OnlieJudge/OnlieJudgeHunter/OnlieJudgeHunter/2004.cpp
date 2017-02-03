//
//  2004.cpp
//  OnlieJudgeHunter

//  Problem Description
//  输入一个百分制的成绩t，将其转换成对应的等级，具体转换规则如下：
//  90~100为A;
//  80~89为B;
//  70~79为C;
//  60~69为D;
//  0~59为E;

//  Input
//  输入数据有多组，每组占一行，由一个整数组成。

//  Output
//  对于每组输入数据，输出一行。如果输入数据不在0~100范围内，请输出一行：“Score is error!”。


//  Sample Input

//  56
//  67
//  100
//  123

//  Sample Output

//  E
//  D
//  A
//  Score is error!

//  Author
//  lcy

//  run : 0MS	1628K
//  Created by UryuoHamusta on 17/2/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
using namespace std;

//准备下一次输入
void nextPrepare(string &inputStr){
    inputStr = "";
    getline(cin, inputStr);
}
int main(){
    string inputStr = "";
    stringstream ssControl;
    int com = 0;
    //输入模块
    getline(cin,inputStr);
    while (inputStr != ""){
        ssControl<<inputStr;
        ssControl>>com;
        //转换后清空缓冲区
        ssControl.str("");
        ssControl.clear();
        
        //抛出错误，执行下一个输入
        if (com < 0 || com>100){
            cout<<"Score is error!";
        }else if (com < 60){
            cout<<"E";
        }else if (com <70){
            cout<<"D";
        }else if (com < 80){
            cout<<"C";
        }else if (com < 90){
            cout<<"B";
        }else{
            cout<<"A";
        }
        cout<<endl;
        nextPrepare(inputStr);
    }
    return 0;
}
