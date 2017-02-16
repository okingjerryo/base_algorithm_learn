//
//  UserInfo.h
//  数据结构课程设计
//
//  Created by 万能的仓鼠 on 16/6/27.
//  Copyright © 2016年 UryuoHamusta. All rights reserved.
//

#ifndef UserInfo_h
#define UserInfo_h
#include <string>
#include <vector>
#include <queue>
using namespace std;
class User;
//================准备工作部分============================
//利用Linux的内核文件获取当前路径指定后缀名的文件
vector<string> getFiles(string cate_dir,string houzhui,bool readHide=false);//
//获取路径的文件名 和 后缀
string findFileName(string path); //
string findFileKuoZhan(string path); //
//生成随机的文件，并且判断是否分割注意文件自动生成时会重写源文件
bool randomCreateFile(string fileDir,string name, unsigned int count,unsigned short int spliot);//
//生成随机数的函数
unsigned int randomInt(unsigned int pos,unsigned int end);//

void vMerge(vector<User>& pre,vector<User> &add);//
struct CmpMinFirst;//
//====================实现需求需要的主要类===================
class User{
    private:
    //自动计算年龄函数
    unsigned short int ageCalc();//
public:
    string id;
    string name;
    unsigned short int age;
    string date;
    string address;
    //对一个其他信息的复制
    void infoCopy(const User & dest);//
    void showinfo();//
    User();//
    User(string id,string name="name",string address="Random");//
};
//存对于多文件存储or 长序列排序时，处理的索引文件信息的集合
class ULindex;
class ULRindex;
//主要实现的类函数 HMUserList
class HMUserList{
private:
    bool flag=false;
    string max;//排好序的Max
    string min;//排好序的Min
    //对两个列内用户进行置换
    void exchangeUser(int dest,int tar);//
   
public:
    vector<User> list;
    unsigned int count;//这个文件的条目数量
    string fileName;
    
    //快速排序递归中需要的查找分区的函数 注意传的是下标 不是size
    unsigned int partition(int pos , int end);//
     //获得一个文件的MD5值
    string FileMD5(string path);//
    //通过文件位置重载
    HMUserList();//
    //该函数的执行思路->枚举所有文件->对每一个文件进行排序->两路合并所有文件
    HMUserList(string dir,string name);
    //读当前目录下与目标文件名相符的文件
    void sortListByFileDir(string dirPath,string fileName);//
    //只初始化一个
    bool readFile(string filePath);//
    //存储文件也可以分块存储,后缀 .li1 .li2 spolit 是总数据分的文件个数
    
    bool saveListToFile(string fileDir, string name,unsigned short int spolit);
    
    void createNode(string inputi0,string name,string address="Random");//
    void createNode(User input);//
    //作为多线程的原子元素一次排一个指定下标范围的List ,不过注意 线程的启动函数必须是静态的成员函数！
    //注意对本类的引用必须用指针 当要使用this指针时！
    static ULRindex sortList(HMUserList* obj,int pos, int end);//
    //对可能会拆分的一个list做index索引记录的两路归并
    void sortSortedListByRanIndex(priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst>*);//
    //两路归并源算法
    static priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst>* twoWaySorted(HMUserList * obj ,priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst>*);//
    //对整个进行排序，每个原子的数据量为<=200000 不读入新子文件
    void sortListWithID();//
    //对几个已经排好序的List进行归并排序，注意这个操作会将结果存到当前的列中 同时注意 由于递归问题 此文件排序只能使用单线程排序
    queue<ULindex> * sortSortedListByIndex(queue<ULindex> *indexlist);//
    //检查是否已经排好了序
    bool checkList(int pos,int end);//
    void clearAll();//
    void showAll();//
    string getMax();//
    string getMin();//
    User getIndexUser(unsigned index);//
    //对vector进行一个替换函数封装
    static void vReplace(HMUserList * obj,vector<User>& input,int pos,int end);//
    unsigned int getCount();//
    HMUserList *returnListAddr();//
};

class ULindex{
public:
    string id;//filename or id
    HMUserList *tarList;//存储一个分块list的header
    ULindex();
    
};
//作为对普通对文件list的继承 它具有标示标号的作用，为了对内部的（不拆解的）List排序提供索引帮助
class ULRindex {
public:
    string id;//filename or id
    vector<User> *tarList;//存储一个分块list的header
    string MD5;//排好序生成文件的MD5
    unsigned int pos;
    unsigned int end;
    string max;
    string min;
    ULRindex();
};

//对于vector的合并补充的模板编程
template <typename type> void printvector(std::vector<type> const &v);

#endif /* UserInfo_h */
