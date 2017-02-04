//
//  2011.cpp
//  OnlieJudgeHunter

//  Problem Description
//  多项式的描述如下：
//  1 - 1/2 + 1/3 - 1/4 + 1/5 - 1/6 + ...
//  现在请你求出该多项式的前n项的和。

//  Input
//  输入数据由2行组成，首先是一个正整数m（m<100），表示测试实例的个数，第二行包含m个正整数，对于每一个整数(不妨设为n,n<1000），求该多项式的前n项的和。

//  Output
//  对于每个测试实例n，要求输出多项式前n项的和。每个测试实例的输出占一行，结果保留2位小数。
                                                        
//  Sample Input
//  2
//  1 2
                                                        
//  Sample Output
//  1.00
//  0.50
                                                        
//  Author
//  lcy

//  RUN:0MS	1892K
//  Created by UryuoHamusta on 17/2/4.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int main(){
    
    string inputStr = "";
    getline(cin,inputStr);
    stringstream ss;
    short unsigned int num = 0;
    //第一行输入
    ss<<inputStr;
    ss>>num;
    
    ss.clear();
    getline(cin, inputStr);
    ss<<inputStr;
    for (int i=0 ;i<num;i++){
        double thisElem = 0;
        ss>>thisElem;
        double sum = 0;
        for (double i=1;i<=thisElem;i++){
            int flag = i;
            if (flag%2)
                sum += 1.0/i;
            else
                sum-= 1.0/i;
        }
        cout<<fixed<<showpoint<<setprecision(2)<<sum<<endl;
        
    }
    
    return 0;
}
