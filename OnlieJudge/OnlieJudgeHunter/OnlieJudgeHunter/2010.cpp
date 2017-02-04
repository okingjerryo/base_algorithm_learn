//
//  2010.cpp
//  OnlieJudgeHunter

//  Problem Description
//  春天是鲜花的季节，水仙花就是其中最迷人的代表，数学上有个水仙花数，他是这样定义的：
//  “水仙花数”是指一个三位数，它的各位数字的立方和等于其本身，比如：153=1^3+5^3+3^3。
//  现在要求输出所有在m和n范围内的水仙花数。

//  Input
//  输入数据有多组，每组占一行，包括两个整数m和n（100<=m<=n<=999）。

//  Output
//  对于每个测试实例，要求输出所有在给定范围内的水仙花数，就是说，输出的水仙花数必须大于等于m,并且小于等于n，如果有多个，则要求从小到大排列在一行内输出，之间用一个空格隔开;
//  如果给定的范围内不存在水仙花数，则输出no;
//  每个测试实例的输出占一行。

//  Sample Input
//  100 120
//  300 380

//  Sample Output
//  no
//  370 371

//  Author
//  lcy

//  RUN:0MS	1628K
//  Created by UryuoHamusta on 17/2/4.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;

int main(){
    
    string inputStr = "";
    getline(cin, inputStr);
    
    while (inputStr != ""){
        stringstream ss(inputStr);
        int a = 0, b = 0 , counter = 0;
        
        ss>>a>>b;
        for (int i=a;i<=b;i++){
            short unsigned int hr = i/100, tr = (i % 100)/10 ,r = i % 10; //百位 十位 个位
            if (i == pow(hr,3)+pow(tr,3)+pow(r, 3)){
                if (counter != 0)
                    cout<<" ";
                cout<<i;
                counter++;
            }
        }
        if (!counter)
            cout<<"no";
        cout<<endl;
        
        inputStr = "";
        getline(cin, inputStr);
    }
    
}
