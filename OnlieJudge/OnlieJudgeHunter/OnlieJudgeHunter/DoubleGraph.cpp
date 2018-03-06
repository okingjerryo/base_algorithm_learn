//
//  test.cpp
//  OnlieJudgeHunter
//
//  Created by UryuoHamusta on 17/2/21.
//  Copyright © 2017年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct point{
    short int x;
    short int y;
};
struct dpsQueueElem{
    point thispoint;
    int lenth;
};
int countingFun();
int mazeFun();
int getLakeCount(vector<vector<char> >&,point&);
bool dfsGraph(point,vector<vector<char> >&,point&);
int findMazeShortPath(point& end,vector<vector<char> >& maze,point startPoint,point range);
void dpsFindMaze(vector<vector<char> >&maze,point thisPoint,int lenth,point range);

int main(){
    short unsigned int opintion = 0;
    cout<<"please select the question."<<endl;
    cout<<"1.Lake Counting (POJ 2386)"<<endl;
    cout<<"2.Shortest path of maze"<<endl;
    cin>>opintion;
    if (opintion == 1)
        countingFun();
    else if (opintion == 2)
        mazeFun();
    
        return 0;
}

int countingFun(){
    cout<<"please input n m (nxm)"<<endl;
    short int longth = 0,width = 0;
    cin>>longth;
    cin>>width;
    //input mode
    cout<<"please input graph "<<longth<<" x "<<width<<endl;
    vector<vector<char> > thismaze(longth);
    for (int i =0;i<longth;i++){
        for(int j=0;j<width;j++){
            //init graph with input char
            char tmpInput;
            cin>>tmpInput;
            thismaze[i].push_back(tmpInput);
        }
        
    }
    point maxRange;
    maxRange.x=longth;
    maxRange.y=width;
    int lakeCount = getLakeCount(thismaze,maxRange);
    cout<<"the number of lake is "<<lakeCount<<endl;
    return 0;
}

int getLakeCount(vector<vector<char> >&maze,point& range){
    int counter = 0;
    for (int i=0;i<maze.size();i++){
        for (int j=0;j<maze[i].size();j++){
            point thispoint;
            thispoint.x=i;
            thispoint.y=j;
            if (dfsGraph(thispoint, maze,range))
                counter++;
        }
    }
    return counter;
}

bool dfsGraph(point thispoint,vector<vector<char> > &maze,point &range){
    short int x=thispoint.x,y=thispoint.y;
    bool flag =false;
    //排除意外
    if (x>=range.x||y>=range.y||x<0||y<0){
        return false;
    }else if(maze[x][y] == 'W'){
        flag = true;
        //防止再次搜索原点
        maze[x][y]='.';
        //搜索附近点
        for(int xMove=-1;xMove<=1;xMove++){
            for (int yMove=-1;yMove<=1;yMove++){
                point nextPoint;
                nextPoint.x=x+xMove;
                nextPoint.y=y+yMove;
                dfsGraph(nextPoint, maze,range);
            }
        }
    }
    return flag;
}
//迷宫问题解答方法
int mazeFun(){
    //input mode
    int n = 0,m = 0;
    cout<<"please input maze size m x n"<<endl;
    cin>>m>>n;
    cout<<"please input maze"<<m<<" x "<<n<<endl;
    
    point mStart,mEnd;
    //配置输入迷宫 x为竖着 y为横着
    vector<vector<char> >maze(m);
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            char inputTmp;
            cin>>inputTmp;
            //输入时把起点终点记录下来，提高效率
            if (inputTmp == 'S'){
                mStart.x = i;
                mStart.y = j;
            }else if(inputTmp == 'G'){
                mEnd.x = i;
                mEnd.y = j;
            }
                
            maze[i].push_back(inputTmp);
        }
    }
    /*
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            cout<<maze[i][j];
        }
        cout<<endl;
    }*/
    point range;
    range.x = m;
    range.y = n;
    int shortPath = findMazeShortPath(mEnd,maze,mStart,range);
    return 0;
}
int findMazeShortPath(point& end,vector<vector<char> >& maze,point thisPoint,point range){
    int shortlenth = 0;
    dpsFindMaze(maze,thisPoint,shortlenth,range);
    shortlenth = maze[end.x][end.y];
    cout<<shortlenth<<endl;
    return shortlenth;
}

void dpsFindMaze(vector<vector<char> >&maze,point thisPoint,int lenth,point range){
    //this point 置当前最短路径
    
    dpsQueueElem thisPElem;
    thisPElem.lenth = 0;
    thisPElem.thispoint.x=thisPoint.x;
    thisPElem.thispoint.y=thisPoint.y;
    
    queue<dpsQueueElem> dpsQueue;
    dpsQueue.push(thisPElem);
    
    
    while(!dpsQueue.empty()){
    
        //取出当前队列元素
        dpsQueueElem thisElem = dpsQueue.front();
        dpsQueue.pop();
        //组装当前点
        int tx=thisElem.thispoint.x,ty=thisElem.thispoint.y;
        //排除特殊情况
        if (tx<0||ty<0||tx>=range.x||ty>=range.y||maze[tx][ty] == '#'){
            continue;
        }else if (maze[tx][ty] == '.'||maze[tx][ty]>thisElem.lenth){
        maze[tx][ty] = thisElem.lenth;
        //终点情况
        }else if (maze[tx][ty] == 'G'){
            maze[tx][ty] = thisElem.lenth;
            return;
        }else
            continue;
        
        //装配下一个点 这个方式略蠢。。要是有用for可以的，欢迎修改
        dpsQueueElem nextUp,nextDown,nextRight,nextLeft;
        nextUp.lenth=thisElem.lenth+1;
        nextDown.lenth=thisElem.lenth+1;
        nextLeft.lenth=thisElem.lenth+1;
        nextRight.lenth=thisElem.lenth+1;
        
        nextUp.thispoint.x=tx-1;
        nextUp.thispoint.y=ty;
        nextDown.thispoint.x=tx+1;
        nextDown.thispoint.y=ty;
        nextLeft.thispoint.x=tx;
        nextLeft.thispoint.y=ty-1;
        nextRight.thispoint.x=tx;
        nextRight.thispoint.y=ty+1;
        //下面的点 入队
        dpsQueue.push(nextRight);
        dpsQueue.push(nextLeft);
        dpsQueue.push(nextUp);
        dpsQueue.push(nextDown);
    }
}
