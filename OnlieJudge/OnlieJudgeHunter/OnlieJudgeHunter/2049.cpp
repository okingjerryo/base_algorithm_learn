//
//  2049.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/7.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
using namespace std;

int main(){
    int bian = 0;
    cin>>bian;
    for (int i=0;i<bian;i++){
        int n = 0,m = 0;
    
        cin>>n>>m;
        double re=1;
        for(int i=n;i>=m;i--){
            re*=i;
        }
        double bottom = 1;
        for(i=1;i<=m;i++)
            bottom*=i;
        re/=bottom;
            cout<<re<<endl;
    }
    return 0;
}
