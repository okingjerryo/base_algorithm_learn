//
//  greedy.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/6.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>    //优先级队列也在
using namespace std;
//POJ 3609

struct TreeNode{
    int data;
    TreeNode* LNode = NULL;
    TreeNode* RNode = NULL;
};
struct HaffTree{
    TreeNode* Root;
    int deep;
};
//haffTree 构造+递归方法
void _initTreeFF(TreeNode* thisNode,HaffTree& haffTree){
    //先序创建haff树木
}
HaffTree initTreeFF(priority_queue<int,vector<int>,greater<int> >& inputQ){
    TreeNode *firstNode = new TreeNode;
    HaffTree haff;
    _initTreeFF(firstNode,haff);
    
    return haff;
}

int main3609(){
    int num,ran;
    // input mode
    cin>>num>>ran;
    vector<int> input(num);
    for (int i=0;i<num;i++){
        int tmpInput;
        cin>>tmpInput;
        input[i] = tmpInput;
    }
    
    //小到大排序 注意容器要用begin end
    sort(input.begin(), input.end());
    int reSet;      //结果点集
    int thisNum = 0;
    while (num-1-thisNum){  //如果到最后点则退出
        while (ran-input[thisNum]>0) thisNum++;
        reSet++;    //结果集计数
        thisNum++;
    }
    cout<<reSet<<endl;
    return 0;
}

//POJ 3253 :initHaffMan+GetBestVault
int main3253 (){
    int num;
    priority_queue<int,vector<int>,greater<int> > inputQ; //用3个参数初始化
    cin>>num;
    for (int i=0;i<num;i++){
        int tmpInput;
        cin>>tmpInput;
        inputQ.push(tmpInput);
    }
    return 0;
}
int main(){
    cout<<"POJ 3609"<<endl;
    main3609();
    cout<<"POJ 3253"<<endl;
    main3253();
    return 0;
}
