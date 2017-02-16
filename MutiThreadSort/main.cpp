//
//  main.cpp
//  数据结构课程设计
//
//  Created by 万能的仓鼠 on 16/6/27.
//  Copyright © 2016年 UryuoHamusta. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <string>
#include "UserInfo.h"

using namespace std;


int main(int init,char** args){
    
    
    string dir="/Users/UryuoHamusta/Desktop/DSData/";
    cout<<"开始生成文件 数量1000000"<<endl;
    randomCreateFile(dir, "test",1000000,5);
     cout<<"数据生成完毕"<<endl;
    HMUserList test(dir,"test");
    return 0;
}