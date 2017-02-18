//
//  ChouQian.cpp
//  CTest
//
//  Created by UryuoHamusta on 17/2/18.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//
//抽签问题优化
//描述：抽取4次时看能否取到想要的加和结果 找到输出find 否则输出No
//输入：
//第一行 n = 签的个数
//第二行 m = 期望抽取4次的目标和
//第三行 签的数字情况
//例子输入:
//3
//10
//1 3 5
//例子输出：
//find

//本题采用C++11中的unorder_map头文件 对两次抽取情况的加和生成了hash表进行查找
//时间复杂度 O(n^2)


#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> input;
    int m = 0,n= 0;
    cin>>n>>m;
    //利用容器存放输入签
    for (int i=0;i<n;i++){
        int tmpbuf;
        cin>>tmpbuf;
        input.push_back(tmpbuf);
    }
    //constract a+b hashmap

    unordered_map<int,bool> mapsum;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            mapsum[input[i]+input[j]]=true;
        }
    }
    
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int tofind = m-input[i]-input[j];
            if (mapsum.find(tofind)!=mapsum.end()){
                cout<<"find"<<endl;
                return 0;
            }
        }
    }
    cout<<"No"<<endl;
    return 0;
}
