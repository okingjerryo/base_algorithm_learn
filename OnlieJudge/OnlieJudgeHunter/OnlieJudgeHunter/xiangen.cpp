//
//  xiangen.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/22.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;
struct TNode{
    int data;
    TNode * r_child;
    TNode * l_child;
};
void todo(TNode * thisNode){
    cout<<thisNode->data<<endl;
}
void xiangen(TNode * thisNode){
    if (thisNode){
    todo(thisNode);
    xiangen(thisNode->l_child);
    xiangen(thisNode->r_child);
    }
}

int main(){
    stack<TNode*> working;
    TNode *root;
    working.push(root);
    while (!working.empty()){
        TNode *thisNode = working.top();
        working.pop();
        
        todo(thisNode);
        if (thisNode->l_child)
            working.push(thisNode->l_child);
        if(thisNode->r_child)
            working.push(thisNode->r_child);
    }
    
    return  0;
}
