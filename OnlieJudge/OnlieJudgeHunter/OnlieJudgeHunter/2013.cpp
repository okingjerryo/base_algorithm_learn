//
//  2013.cpp
//  OnlieJudgeHunter

//  Problem Description
//  喜欢西游记的同学肯定都知道悟空偷吃蟠桃的故事，你们一定都觉得这猴子太闹腾了，其实你们是有所不知：悟空是在研究一个数学问题！
//  什么问题？他研究的问题是蟠桃一共有多少个！
//  不过，到最后，他还是没能解决这个难题，呵呵^-^
//  当时的情况是这样的：
//  第一天悟空吃掉桃子总数一半多一个，第二天又将剩下的桃子吃掉一半多一个，以后每天吃掉前一天剩下的一半多一个，到第n天准备吃的时候只剩下一个桃子。聪明的你，请帮悟空算一下，他第一天开始吃的时候桃子一共有多少个呢？

//  Input
//  输入数据有多组，每组占一行，包含一个正整数n（1<n<30），表示只剩下一个桃子的时候是在第n天发生的。

//  Output
//  对于每组输入数据，输出第一天开始吃的时候桃子的总数，每个测试实例占一行。

//  Sample Input
//  2
//  4

//  Sample Output
//  4
//  22

//  Author
//  lcy

//  RUN:0MS	1628K
//  Created by UryuoHamusta on 17/2/4.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void preNext(string &init){
    init = "";
    getline(cin,init);
}
int main(){
    string inputStr = "";
    getline(cin,inputStr);
    //为了减小复杂度，采用备忘录方式生成从第一天到输入中最大天数的全部记录
    vector<int> note;
    
    note.push_back(1);
    while (inputStr != ""){
        stringstream ss(inputStr);
        int num = 0;
        ss>>num;
        
        //备忘录里有记录
        if (note.size() > num){
            //直接取出 注意-1
            cout<<note[num-1]<<endl;
        }else{
            //从备忘录最后一位生成
            int back = note.size();
            for(int i=back;i<num;i++){
                int pre = note[i-1];
                note.push_back(2*(pre+1));
            }
            cout<<note[note.size()-1]<<endl;
            
        }
        preNext(inputStr);
    }
    
}
