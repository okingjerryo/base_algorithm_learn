//
//  2018.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//
// 运行效率 0MS	1612K

#include <iostream>
#include <vector>
using namespace std;
//封装一个牛类
class cow{
public:
    short unsigned int cow = 1;//母牛
    short unsigned int smallCow[3]= {0,0,0};//小母牛的生长情况
    short int thisYear = 0;
    void toNextYear();
    short unsigned int getCow(){//获取全部母牛数量
        return cow+smallCow[0]+smallCow[1]+smallCow[2];
    }
};
void cow::toNextYear(){
    //先处理小牛
    //剩余1年期的变为母牛 其余依次减一年期 最后新的总母牛生出了小牛 变为了smallCow[2]的数值
    cow+= smallCow[0];
    smallCow[0] = smallCow[1];
    smallCow[1] = smallCow[2];
    smallCow[2] = cow;
}
int main(){
    //input mode
    short unsigned int thisInput = 0;
    cin>>thisInput;
    //引入备忘录减少不必要的运算
    vector<cow> noteCow;
    //第一年 放入其中
    cow first;
    noteCow.push_back(first);
    //输入不到0
    while(thisInput){
        //如果备忘录中存在牛的数量 则取出这个牛 不存在则继续生成到目标需要位置
        if (noteCow.size()<thisInput){
            for (short unsigned int i = noteCow.size();i<=thisInput;i++){
                cow tYearCow = noteCow[noteCow.size()-1];
                tYearCow.toNextYear();
                noteCow.push_back(tYearCow);
            }
        }
        //输出目标年份的牛
        cow targetCow = noteCow[thisInput-1];
        cout<<targetCow.getCow()<<endl;
        
        //next intput
        cin>>thisInput;
    }
    return 0;
}
