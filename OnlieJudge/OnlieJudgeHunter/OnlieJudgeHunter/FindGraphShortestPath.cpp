//
//  FindGraphShortestPath.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/2/24.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//  类单元最短路径

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//存储数组中一个点权值以及是否被访问过
struct pointElem{
    int shortestDis = numeric_limits<int>::max(); //默认为int的最大值
    int distance;   //当前点的花销
    bool isKnown = false;   //在使用Dijkstra算法时是否已访问过
};
class Point{
public:
    int x = 0,y = 0;
    //利用初始构造函数 直接可以构造点，方便初始化使用
    Point(const int& inputX,const int& inputY){
        x = inputX,y = inputY;
    }
    //顺便创建一个设置点的成员函数
    void setPoint(const int& inputX,const int& inputY){
        x = inputX,y = inputY;
    }
    Point(){}
};
class PathQueElem{
public:
    Point thisPoint;
    int lastShortest = numeric_limits<int>::max();
    PathQueElem(const int& x,const int& y,const int& shortest){ //初始化 设置最初值
        thisPoint.setPoint(x, y);
        lastShortest = shortest;
    }
};
int findMinPath(vector<vector<pointElem> >&,Point range);

int main(){
    int line = 0,column = 0;
    
    //输入模块
    //cout<<"please input the line number of the Graph"<<endl;
    
    cin>>line>>column;
    //cout<<"please input the Graph,size:"<<line<<" x "<<column<<endl;
    //使用STL容器类作为动态数组
    vector<vector<pointElem> >graph(line);
    for (int i=0;i<line ;i++ ){
        for (int j=0;j<column ;j++){
            //获取输入的点花销，及封装Dij算法需要的变量的初始状态
            pointElem tmpIn;
            cin>>tmpIn.distance;
            /*
            tmpIn.isKnown = false;
            tmpIn.shortestDis = MaxDis;*/
            //存入动态数组
            graph[i].push_back(tmpIn);
            
        }
    }
    graph[0][0].shortestDis = graph[0][0].distance;// 原点最短距离为原点消耗
    /* 测试输入是否存入
    for (int i=0;i<line ;i++ ){
        for (int j=0;j<column ;j++){
            cout<<graph[i][j].distance<<" ";
        }
        cout<<endl;
    }*/
    
    //将边界存入
    Point range(line,column);
    int minPath = findMinPath(graph,range);
    cout<<minPath<<endl;
    return 0;
    
}

int findMinPath(vector<vector<pointElem> >& inputGraph,Point range){
    
    
    queue<Point> handleQ;//广搜处理队列
    handleQ.push(Point(0,0)); //初始0,0点放入
    while (!handleQ.empty()) {
        //取出前一个点
        Point thisPoint = handleQ.front();
        int thisX = thisPoint.x, thisY = thisPoint.y;
        handleQ.pop();
        
        pointElem* targetPoint = &inputGraph[thisX][thisY];//当前的目标点，防止对目标点过长引用
        //边界和特殊情况检查
        if (thisX<0||thisY<0||thisX>=range.x||thisY>=range.y||targetPoint->isKnown){
            continue; //满足上面任何一个条件及继续寻找
        }else{
            //Dijkstra 算法
            //当前访问过
            inputGraph[thisX][thisY].isKnown = true;
            //探测队列
            queue<Point> testNext;
            //将当前点周围的点作为待探测点
            testNext.push(Point(0,1));
            testNext.push(Point(1,0));
            testNext.push(Point(-1,0));
            testNext.push(Point(0,-1));
            while (!testNext.empty()) {
                //装载探测点
                Point nextPoint = testNext.front();
                int movedX = nextPoint.x+thisX,movedY = nextPoint.y+thisY;
                testNext.pop();
                pointElem * movedPoint = &inputGraph[movedX][movedY];
                //探测点边界检查
                if (movedX>=0 && movedY>=0 && movedX<range.x && movedY<range.y && !movedPoint->isKnown){
                    
                    //如果这个点的最小值加上到探测点的代价小于探测点最小值 则更新探测点最小值
                    if (targetPoint->shortestDis+movedPoint->distance < movedPoint->shortestDis){
                        movedPoint->shortestDis = targetPoint->shortestDis+movedPoint->distance;
                    }
                }
            }

            //将上下左右四点放入队列继续执行
            handleQ.push(Point(thisX+1,thisY));  //下
            handleQ.push(Point(thisX-1,thisY));  //上
            handleQ.push(Point(thisX,thisY+1));  //右
            handleQ.push(Point(thisX,thisY-1));  //左
                         
        }
    }
    
    //执行算法后，最后一个点的最短路径属性就是解
    return inputGraph[range.x-1][range.y-1].shortestDis;
}
