//
//  test.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/12.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main(){
    
    int num;
    cin>>num;   //总数
    vector<int> input;
    vector<int> memo(num);  //dp 记录从起点到当前位置的能跳过来的总数
    //输入模块
    for (int i=0;i<num;i++){
        int tmpInput;
        cin>>tmpInput;
        input.push_back(tmpInput);
    }
    memo[0] = 1;//初始化第一位 一种方法
    for (int i=1;i<num;i++){//生成动态规划到最后
        for (int j=i-1;j>=0;j--){//从当前点前一位开始搜索
            if(j+input[j]>=i){//从之前位置可以跳到当前点
                memo[i]+=memo[j];   //当前点能到的种数就是到之前点的种数 （例：之前能能跳到1 1能跳到这，那么肯定存在跳到1的方法使其能跳到这）
            }
        }
    }
    cout<<memo[num-1]<<endl;
    
    return 0;
}
