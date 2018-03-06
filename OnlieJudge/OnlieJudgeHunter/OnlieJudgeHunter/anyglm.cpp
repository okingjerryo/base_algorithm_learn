//
//  anyglm.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/21.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>

using namespace std;
int gcd(int a,int b){
    if (b == 0) return a;
    return gcd(b,a%b);
}
int glm(int a,int b){
    int _gcd = gcd(a,b);
    return (a/_gcd)*_gcd*(b/_gcd);
}
int main(){
    int num;
    cin>>num;
    while (num) {
    int _glm = 1,next;
    for (int i=0;i<num;++i){
        cin>>next;
        _glm = glm(next,_glm); // 最小公倍
        //最大公约 _glm = gcd(next,_glm);
    }
    cout<<_glm<<endl;
        num = 0;
        cin>>num;
    }
    return 0;
}
