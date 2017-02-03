//
//  2006.cpp
//  OnlieJudgeHunter

//Problem Description
//给你n个整数，求他们中所有奇数的乘积。

//Input
//输入数据包含多个测试实例，每个测试实例占一行，每行的第一个数为n，表示本组数据一共有n个，接着是n个整数，你可以假设每组数据必定至少存在一个奇数。

//Output
//输出每组数中的所有奇数的乘积，对于测试实例，输出一行。

//Sample Input

//3 1 2 3
//4 2 3 4 5

//Sample Output

//3
//15

//Author
//lcy

//  run:0MS	1644K
//  Created by UryuoHamusta on 17/2/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
using namespace std;

int strToInt(string& inputStr){
    stringstream ssControl;
    int re = 0 ;
    ssControl<<inputStr;
    ssControl>>re;
    return re;
}

int main(){
    
    string inputStr = "";
    getline(cin,inputStr);
    while (inputStr != "") {
        //对输入进行处理
        //获取个数
        int sum = 1;// 最后的总和
        stringstream ss(inputStr);
        string tmp;
        ss>>tmp;
        
        int num = strToInt(tmp);
        //进行奇数检查
        for (int i=0;i<num;i++){
            int thisNum = 0;    //当前数字
            ss>>tmp;
            thisNum = strToInt(tmp);
            //如果是奇数
            if (thisNum%2)
                sum *= thisNum;
        }
        
        //遍历完成 输出结果
        cout<<sum<<endl;
        
        //准备下一次输入
        inputStr = "";
        getline(cin, inputStr);
        
    }
    return 0;
}
