//
//  2016year.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/3/20.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

int main1(){
    cout<<"1题"<<endl;
    //循环输入 input0时候就输入结束，就是没有输入
    long int input = 0;
    cin>>input;
    while (input){
        
        
        
        bool flag = true;
        //范围是从1~√（input)区间只要能除尽就是素数 否则就是合数
        for (int i=2;i<=sqrt(input);i++){
            if (!(input%i)){
                flag = false;
                break;
            }
        }
        if (flag) cout<<"yes"<<endl;
        else cout<<"no"<<endl;
        
        
        
        //吸收下一个输入
        input = 0;
        cin>>input;
    }
    return 0;
}
void Lsort(vector<vector<int> >&input,int line){
    for (int i=0;i<input.size();i++){
        for (int j=0;j<input.size()-i-1;j++){
            if (input[j][line]>input[j+1][line]){
                vector<int> tmp = input[j];
                input[j]=input[j+1];
                input[j+1]= tmp;
            }
        }
    }
    
}
int main2(){
    
    int num;
    cin>>num;
    //这里
    vector<vector<int> > input;
    //封装动态二维数组
    for (int i=0;i<num;i++){
        vector<int> tmpLine;
        int tmpElem;
        cin>>tmpElem;
        tmpLine.push_back(tmpElem);
        cin>>tmpElem;
        tmpLine.push_back(tmpElem);
        input.push_back(tmpLine);
    }
    //基数排序 但是排序方法是冒泡，实际上效率和暴力求解一样
    Lsort(input, 1);
    Lsort(input, 0);
    //最后相邻两个比较取最小
    int min = 0x8fff;//最大数
    for (int i=0;i<input.size()-1;i++){
        //两点距离公式
        int thisResult =
        sqrt(pow(input[i][0]-input[i+1][0],2)+pow(input[i][1]-input[i+1][1],2));
        if (thisResult<min) min = thisResult;
    }
    cout<<min<<endl;
    return 0;
}

struct student{
    int num=0;
    int course1;
    int course2;
    int sum;
};
struct course{
    int coursenum;
    int courseSum;
};
bool cmp1(student const &first,student const &second ){
    return first.num<second.num;
}
bool cmp2(student const &first,student const &second){
    return first.sum>second.sum;
}
//思路 用两个类实现+基数排序
int main3(){
    //读取和写文件 C++流处理
    ifstream fin("/Users/uryuo/test.txt"); //这是文件读入流 具体使用可以像C++那样使用
    if (!fin.is_open()) {
        cout<<"read Error"<<endl;
        return 1;
    }
    student tmpInput;
    fin>>tmpInput.num>>tmpInput.course1>>tmpInput.course2;
    tmpInput.sum = tmpInput.course1+tmpInput.course2;
    //给两个链表装载信息
    vector<student> stuList;
    vector<course> courseList(2);
    courseList[0].coursenum = 1;
    courseList[1].coursenum = 2;
    while (tmpInput.num){
        courseList[0].courseSum+=tmpInput.course1;
        courseList[1].courseSum+=tmpInput.course2;
        stuList.push_back(tmpInput);
        //再次准备装配
        tmpInput.num = 0;//初始化
        fin>>tmpInput.num>>tmpInput.course1>>tmpInput.course2;
        tmpInput.sum = tmpInput.course1+tmpInput.course2;
    }
    //到这 学生和课程信息装配完成 每门课的平均分
    for (int i=0;i<courseList.size();i++){
        cout<<"AVG Course"<<i+1<<" ";
        //保留两位小数
        cout<<fixed<<showpoint<<setprecision(2)<<(double)courseList[i].courseSum/(double)stuList.size()<<endl;// 用doule 强转换的原因是 除法有很大几率除不开
    }
    sort(stuList.begin(), stuList.end(),cmp1);
    sort(stuList.begin(), stuList.end(), cmp2);
    for (int i=0;i<stuList.size();i++){
        cout<<stuList[i].num<<" "<<stuList[i].sum<<endl;
    }
    
    fin.close();
    
    return 0;
}
class point{
public:
    int x;
    int y;
    point(){};
    void setX(int in){
        x = in;
    }
    void setY(int in){
        y = in;
    }
    point(int inX,int inY){
        setX(inX),setY(inY);
    }
};
void inputMetrx(vector<vector<int> >& input,int m,int n){
    for (int i=0;i<m;i++){
        vector<int> line;
        input.push_back(line);
        for (int j=0;j<n;j++){
            int tmp;
            cin>>tmp;
            input[i].push_back(tmp);
        }
        
    }
}
int main4(){
    
    int min = 0x8ffff;
    vector<point> pointList;
    vector<vector<int> > bigMetrx;
    vector<vector<int> > smallMetrx;
    //输入模块
    int m = 0,n = 0;
    cin>>m>>n;
    inputMetrx(bigMetrx, m, n);
    cin>>m>>n;
    inputMetrx(smallMetrx, m, n);
    //输入完成 开始暴力枚举位置
    for (int i=0;i<=bigMetrx.size()-smallMetrx.size();i++){
        for (int j=0;j<=bigMetrx[i].size()-smallMetrx[i].size();j++){
            //开始算矩阵
            
            point thisPos;
            point startPos;
            int thissum = 0;
            bool flag = false;
            for (int m=0;m<smallMetrx.size();m++){
                
                
                for (int n=0;n<smallMetrx.size();n++){
                    thisPos.setX(i+m);
                    thisPos.setY(j+n);
                    if (!flag){
                        flag = true;
                        startPos.setX(i+m+1);
                        startPos.setY(j+n+1);
                    }
                    thissum += abs((bigMetrx[thisPos.x][thisPos.y]-smallMetrx[m][n]));//计算结果
                }
            }
            //在加完后 发现小 则更新
            if(thissum<min){
                min = thissum;
                pointList.clear();
                pointList.push_back(startPos);
            }else if (thissum == min){
                pointList.push_back(startPos);
            }
            
        }
    }
    cout<<"min: "<<min<<endl;
    cout<<"最小点: ";
    for (int i= 0;i<pointList.size();i++){
        cout<<"("<<pointList[i].x<<","<<pointList[i].y<<") ";
    }
    return 0;
}

void wuxian(){
    int input = 0,input2 = 0;
    cin>>input>>input2;
    while(input){
        //chuli
        
        //input next
        input = 0,input2 = 0;
        cin>>input>>input2;
    }
    
    double baoliuxiaoshu = 0;
    cout<<fixed<<showpoint<<setprecision(2)<<baoliuxiaoshu<<endl;
    
}



int main21(){
    
    int num;
    cin>>num;
    
    int pointList[num][2];
    for (int i=0;i<num;i++){
        cin>>pointList[i][0]>>pointList[i][1];
    }
    int min = 0x8fff;
    for(int i=0;i<num;i++){
        for (int j=i+1;j<num;j++){
            int thisDis =
            sqrt(pow(pointList[i][0]-pointList[j][0],2) + pow(pointList[i][0]-pointList[i][1], 2));
            if (thisDis<min)
                min = thisDis;
        }
    }
    cout<<min<<endl;
    
    return 0;
}
int main(){
    
    /*main1();
     main2();
    main3();
    main4();
    */
    //wuxian();
    //main21();
    // int <->string
    
    string input;
    cin>>input;
    
    cout<<input[2]<<endl;
    double output;
    stringstream ss;
    
    ss<<input;
    ss>>output;
    
    return 0;
}
