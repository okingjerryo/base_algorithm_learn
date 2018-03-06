//
//  2008.cpp
//  OnlieJudgeHunter

//  Problem Description
//  统计给定的n个数中，负数、零和正数的个数。

//  Input
//  输入数据有多组，每组占一行，每行的第一个数是整数n（n<100），表示需要统计的数值的个数，然后是n个实数；如果n=0，则表示输入结束，该行不做处理。

//  Output
//  对于每组输入数据，输出一行a,b和c，分别表示给定的数据中负数、零和正数的个数。

//  Sample Input

//  6 0 1 2 3 -1 0
//  5 1 2 3 4 0.5
//  0

//  Sample Output
//  1 2 3
//  0 0 5

//  Author
//  lcy

//  run:0MS	1672K
//  Created by UryuoHamusta on 17/2/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>

using namespace std;

int main(){
    string inputStr = "";
    
    //输入数据处理
    getline(cin, inputStr);
    while (inputStr != ""){
        stringstream ssControl(inputStr);
        int num = 0,plus = 0,zero = 0, minus = 0; //当前行数量 正数 0 负数

        ssControl>>num;
        //num 为0 输入结束
        if (!num) break;
        for (int i=0;i<num;i++){
            double thisElem;
            ssControl>>thisElem;
            if (thisElem>0)
                plus++;
            else if (thisElem == 0)
                zero++;
            else minus++;
        }
        
        //计算完成 输出
        cout<<minus<<" "<<zero<<" "<<plus<<endl;
        //处理 下一个事件
        inputStr = "";
        getline(cin, inputStr);
    }
    
    
    return 0;
}
