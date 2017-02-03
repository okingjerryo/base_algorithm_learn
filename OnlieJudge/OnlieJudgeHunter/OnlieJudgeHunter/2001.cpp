//  HDU OJ
//  2001.cpp
//
//  Problem Description
//  输入两点坐标（X1,Y1）,（X2,Y2）,计算并输出两点间的距离。
//  Input
//  输入数据有多组，每组占一行，由4个实数组成，分别表示x1,y1,x2,y2,数据之间用空格隔开。
//  Output
//  对于每组输入数据，输出一行，结果保留两位小数。
//  Sample Input
//  0 0 0 1
//  0 1 1 0
//  Sample Output
//  1.00
//  1.41
//  Author
//  lcy
//
//  Created by UryuoHamusta on 2017/1/19.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <math.h>       // 提供一些常用的数学函数头文件
#include <sstream>      //C++ string与任意格式互转
#include <iomanip>      //C++ 输出流控制
using namespace std;


#define PI 3.1415927
//点的封装类，封装了一个这道题要求的计算点距离的函数
class pt{
public:
    double x;
    double y;
    pt(){
        x = 0;
        y = 0;
    }
    double getTDistance(pt& othPt){
        double re = pow(x - othPt.x, 2)+pow(y - othPt.y, 2);    //两点距离求和公式
        //注意 负数开不了方。。 必须要分开处理
        if (re < 0) return sqrt(0-re);
        return sqrt(re);
    }
};

//string->double 函数 输出转换结果
double StrConverDouble(string &input){
    
    stringstream ss; //字符转换用类
    double re=0;    //转换输出类
    
    ss<<input;
    ss>>re;
    return re;
}


int Cmain(int argc, const char * argv[]) { //运行时请注意main函数更名~
    
    string inStr,x1,x2,y1,y2;
    pt a,b;
    //输入模块
    getline(cin, inStr);
    while(inStr != ""){
        //对一行进行处理
        istringstream hanStr(inStr);    //对字符进行处理
        hanStr>>x1>>y1>>x2>>y2;         //带空格时会分割为4个子str
        
        //构造pt类
        a.x = StrConverDouble(x1);
        a.y = StrConverDouble(y1);
        b.x = StrConverDouble(x2);
        b.y = StrConverDouble(y2);
        
        //计算并按格式输出小数点后两位
        cout<<fixed<<showpoint<<setprecision(2)<<a.getTDistance(b)<<endl;
        
        //准备下一次输入
        inStr = "";       //必须重新初始化一下，否则会出现不能跳出循环的问题
        getline(cin, inStr);
        
    }
    
    return 0;
}
