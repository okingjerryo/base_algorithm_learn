//
//  2005.cpp
//  OnlieJudgeHunter
//
//  Problem Description
//  给定一个日期，输出这个日期是该年的第几天。


//  Input
//  输入数据有多组，每组占一行，数据格式为YYYY/MM/DD组成，具体参见sample input ,另外，可以向你确保所有的输入数据是合法的。

//  Output
//  对于每组输入数据，输出一行，表示该日期是该年的第几天。

//  Sample Input

//  1985/1/20
//  2006/3/12

//  Sample Output

//  20
//  71

//  Author
//  lcy

//  run:0MS	1612K

//  Created by UryuoHamusta on 17/2/3.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//利用 stringsream特性将string 转换为Int
int conStringToInt(string &elem){
    stringstream ssControl;
    int re = 0;
    ssControl<<elem;
    ssControl>>re;
    
    return re;
}

class Date{
public:
    int year;
    short int month;
    short int day;
    short int monBFullDay[12] = {1,1,2,2,3,3,4,5,5,6,6,7};  //每个满月存在的大月数量 2月经过满月的话，通过标识最后加2月的天数
    bool isFebIn;
    bool Run;
    
    Date(string init); //初始化为日期
    bool isRun();      //判断当年是否为闰年
    int getDayinYear();   //算出当前天数函数
};

int main(){
    
    string inputStr = "";
    //输入处理
    getline(cin,inputStr);
    while (inputStr != ""){
        
        Date date(inputStr);
        cout<<date.getDayinYear()<<endl;
        
        //准备下一个输入
        inputStr = "";
        getline(cin, inputStr);
    }
    
    return 0;
}

Date::Date(string init){
    int preflag=0;
    vector<string> elemTmp;
    //分割字符串
    for (int i=0;i<init.size();i++){
        if (init[i]== '/'){
            string tmp = init.substr(preflag,i-preflag);
            elemTmp.push_back(tmp);
            preflag=i+1;
        }
    }
    elemTmp.push_back(init.substr(preflag,init.size()-preflag));
    year = conStringToInt(elemTmp[0]);
    month = conStringToInt(elemTmp[1]);
    day = conStringToInt(elemTmp[2]);
    
    if (month>2) isFebIn = true;
    else isFebIn = false;
    
    if (isRun()) Run = true;
    else Run = false;
        
}

bool Date::isRun(){
    if(!(year % 100)){
        if (!(year % 400)) return true;
    }else{
        if (!(year % 4)) return true;
    }
    return  false;
}

int Date::getDayinYear(){
    int re = 0;
    //首先month -1 算出前面总共天数
    if(isFebIn){
        //大月天数
        int thisBM = monBFullDay[month-2];//大月个数
        re += thisBM*31;
        re += (month-thisBM-2)*30;
        re += 28;  //二月的天数
        if (Run) re += 1; //如果是闰年 则再加1天
    }else{
        if (month == 2) re += 31;
    }
    //最后加上当月天数
    re += day;
    return re;
}
