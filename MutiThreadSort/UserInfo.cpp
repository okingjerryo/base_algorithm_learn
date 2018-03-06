//
//  UserInfo.cpp
//  数据结构课程设计
//
//  Created by 万能的仓鼠 on 16/6/27.
//  Copyright © 2016年 UryuoHamusta. All rights reserved.
//
//100w 数据规模 注意由于时间仓促排序算法采用递归型快速排序 1000w数据量会导致内存超量占用产生死机现象。。
#include "UserInfo.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
//Linux下的读取当前目录头文件
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
//引入生成随机数函数 为了给自动生成的文件分配一个随机数
//引入C++11多线程处理文件分块
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <time.h>
//引入 MD5加密验证头文件，目的是判断目标目录下的分块文件状态索引的信息与文件的MD5是否匹配
//也是判断一个文件是否被修改过的标准
#include "MD5.h"

using namespace std;
//加入 共享锁 防止分配List时候产生意外
bool queueLock;
bool exchangeLock=false;
mutex pushLock;
//vector 合并用的模板函数
template <typename type> void printvector(std::vector<type> const &v)
{
    for (typename std::vector<type>::size_type sz = 0; sz != v.size(); ++sz);
}
//优先级队列比较的数据结构
struct CmpMinFirst{
    bool  operator ( )(ULRindex &a,ULRindex &b){
        return a.pos>b.pos;
    }
};

//通过后缀读取 并确认是否读取该文件 
vector<string> getFiles(string cate_dir,string houzhui,bool readHide)
{
    vector<string> files;//存放文件名
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
    
    if ((dir=opendir(cate_dir.c_str())) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }
    
    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8) {   ///file 允许最后有数字作为通配符号忽略
            string name=ptr->d_name;
           
            //通配段
            
            if (readHide==false && name.substr(0,1)==".") //隐藏文件不读取
                continue;
            else{
                //后缀名与目标相同
                if (houzhui==".*"){//全读取
                    files.push_back(name);
                }
                
                unsigned short int instart;
                unsigned short int lastNumC=0;
                string thisHouZhui=findFileKuoZhan(name);
                if (houzhui[houzhui.length()-1]=='*'){
                    
                for (int i=thisHouZhui.length()-1;i>=0;i--){
                    if (thisHouZhui[i]>='0'&&thisHouZhui[i]<='9')
                        lastNumC++;
                }
               instart=name.length()-houzhui.length()-lastNumC+1;
                string testCom=name.substr(instart,houzhui.length()-1);
                if (testCom==houzhui.substr(0,houzhui.length()-1)||name.substr(instart,houzhui.length())==houzhui)
                    files.push_back(name);
                }else{
                    if (name.substr(instart,houzhui.length())==houzhui.substr(0,houzhui.length()-1))
                        files.push_back(name);
                }
            }
            
        }
        else if(ptr->d_type == 10)    ///link file
            continue;
        else if(ptr->d_type == 4)    ///dir
        {
            /*string name=ptr->d_name;
            name+="/";
            files.push_back(name);*/
            continue;
        }
    }
    closedir(dir);
    sort(files.begin(), files.end());
    return files;
}
//=======================================================
void User::infoCopy(const User &dest){
    name=dest.name;
    id=dest.id;
    age=dest.age;
    date=dest.date;
    address=dest.address;
}

void User::showinfo(){
    cout<<id<<" "<<name<<" "<<age<<" "<<date<<" "<<address<<endl;
}

unsigned short int User::ageCalc(){
    stringstream intmp;
    unsigned int yearNum;
    string year=id.substr(6,4);
    intmp<<year;
    intmp>>yearNum;
    return 2016-yearNum;
}

User::User(string inid,string inname,string inaddress){
    id=inid;
    name=inname;
    address=inaddress;
    age=ageCalc();
    date=id.substr(6,4)+"/"+id.substr(10,2)+"/"+id.substr(12,2);
}

User::User(){
    id="";
    name="";
    date="1979/01/01";
    age=0;
    address="";
}

//List的类实现
void HMUserList::exchangeUser(int dest,int tar){
    User tmp((User)list[tar]);
    list[tar].infoCopy(list[dest]);
    list[dest].infoCopy(tmp);
}


void HMUserList::showAll(){
    for (int i=0;i<list.size();i++){
        list[i].showinfo();
    }
}

void HMUserList::createNode(User input){
    list.push_back(input);
}

void HMUserList::createNode(string inputid,string name,string address){
    User tmpinput(inputid,name,address);
    list.push_back(tmpinput);
}

HMUserList::HMUserList(){
    count=0;
    max="";
    min="";
}

string HMUserList::FileMD5(string path){
    ifstream in(path.c_str());
    if (in.good()){
        MD5 aMd5(in);
        return aMd5.toString();
    }
    else return "errorReadingMD5!";
}

void HMUserList::clearAll(){
    list.clear();
}

string findFileName(string path){
    stringstream intmp;
    string result,tmp;
    intmp<<path;
    while(getline(intmp, tmp, '/'))
        result=tmp;
    return result;
}
string findFileKuoZhan(string path){
    string filename=findFileName(path);
    for (int i=filename.length()-1;i>=0;i--){
        if (filename[i]=='.') filename=filename.substr(i);
    }
    return filename;
}


bool HMUserList::readFile(string filePath){
    fileName=filePath;
    ifstream initfile(filePath.c_str());
    if (!initfile.good()){
        cout<<"文件："<<findFileName(filePath)<<"未读取成功！"<<endl;
        initfile.close();
        return false;
    }
    
    string readLine;
    
    while (!initfile.eof()) {
        stringstream conRead;
        getline(initfile, readLine);
        if (readLine!=""){
        conRead<<readLine;
        User userInput;
        conRead>>userInput.id;
        conRead>>userInput.name;
        conRead>>userInput.age;
        conRead>>userInput.date;
        conRead>>userInput.address;
        list.push_back(userInput);
            count++;
        }
    }
    initfile.close();
    return true;
}

string HMUserList::getMax(){
    return max;
}
string HMUserList::getMin(){
    return min;
}
unsigned int HMUserList::getCount(){
    return count;
}
// ============================快速排序算法部分================================
  ULRindex HMUserList::sortList(HMUserList* obj,int pos, int end){
    //作为快速排序的分区点
    int partedQ=0;
    ULRindex out;
    if (pos>=end) {
        out.id=obj->fileName;
        return out;
    }
    partedQ=obj->partition(pos, end);
    sortList(obj,pos, partedQ-1);
    sortList(obj,partedQ+1, end);
    out.id=obj->fileName;
    out.tarList = &obj->list;
    out.pos=pos;
    out.end=end;
    out.max=obj->list[obj->count-1].id;
    out.min=obj->list[0].id;
    return out;
}
unsigned int HMUserList::partition(int pos, int end){
    string comElem=list[end].id;
    int parBuf=pos-1;
    for (int i=pos; i<=end-1; i++) {
        string thisElem=list[i].id;
        if (thisElem<=comElem){
            parBuf+=1;
            while (exchangeLock){
                
            }
            exchangeLock=true;
            exchangeUser(parBuf,i);
            exchangeLock=false;
        }
        
    }
    exchangeUser(parBuf+1, end);
    return parBuf+1;
}

//============================随机生成文件==================================
bool randomCreateFile(string fileDir,string name,unsigned int count,unsigned short int spliot=1){
    unsigned int trueCount=0;
    
    for (int fileC=0;fileC<spliot;fileC++){
        //构造文件名
        string thisZhui;
        stringstream tmp;
        tmp<<fileC+1;
        tmp>>thisZhui;
        thisZhui=".li"+thisZhui;
        
        string filePath=fileDir+name+thisZhui;
        ofstream write(filePath.c_str());
        
        if (!write.good()){
            cout<<"随机生成文件时出错"<<endl;
            return false;
        }
        //覆盖同名文件
        write.seekp(ios::beg);
        for (int allC=0;allC<count/spliot;allC++){
            //随机生成身份证号部分
            //身份证号前5位 从100000-599999生成一个随机数
            unsigned int front=randomInt(100000, 599999);
            unsigned int birY=randomInt(1950, 2010);
            unsigned int birM=randomInt(1, 12);
            unsigned int birD=randomInt(1, 28);
            unsigned int last=randomInt(1110,3999);
            string birCM;
            string birCD;
            
            stringstream tmp;
            tmp<<birM;
            tmp>>birCM;
               if (birM<10)
                   birCM="0"+birCM;
            tmp.clear();
            tmp<<birD;
            tmp>>birCD;
            if (birD<10)
                birCD="0"+birCD;
            stringstream tmpCon;
            string finalID;
            
            tmpCon<<front<<birY<<birCM<<birCD<<last;
            tmpCon>>finalID;
            string thisUName;
            trueCount++;
            //生成名字
            tmpCon.clear();
            tmpCon<<trueCount;
            tmpCon>>thisUName;
            thisUName="name"+thisUName;
            User readyinput(finalID,thisUName,"这是测试用例的地址");
            
            //写入一条记录
            write<<endl<<readyinput.id<<" "<<readyinput.name<<" "<<readyinput.age<<" "<<readyinput.date<<" "<<readyinput.address;
        }
        write.close();
    }
    cout<<"文件生成成功！"<<endl;
    cout<<"实际生成记录 "<<trueCount<<endl;
    return true;
}
unsigned int randomInt(unsigned int pos,unsigned int end){
    if (pos>end) return 0;
    srand(clock());
    return rand()%(end-pos)+pos;
}
void HMUserList::sortListWithID(){
    //首先以10w为分割点确定文件要分割为几份
    unsigned int spolit=(count/100000)+1;
    if (count%100000==0) spolit-=1;
    //对于承载带参数的多线程必须的结果集承载部分
    vector< future<ULRindex> > resultSet(spolit);
    //开启多线程进行并行计算 部分
    //这里方式选择在获得get时再进行计算，这样就实现了一起进行排序
    for (int i=0;i<spolit;i++){
        //如果i是最后一位
        if (i==spolit-1) {
            resultSet[i]=async(std::launch::async,HMUserList::sortList,this,i*100000,(int)this->count-1);
            
        }else{
            resultSet[i]=async(launch::async, HMUserList::sortList, this,i*100000,(int)(i+1)*100000-1);
           
        }
    }
    //线程开始执行
    // 最后获得结果
    //接受结果部分
    priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst>  sortReIndexSet;
    for(int i=0;i<resultSet.size();i++){
        sortReIndexSet.push(resultSet[i].get());
    }
    //此时结果集合中装的就是根据spolit的结果
    //之后进入两路归并模式（应用一个队列，通过进程不断入队出队的方式进行对任务的两路归并，注意需要加锁）
    sortSortedListByRanIndex(&sortReIndexSet);

     cout<<"整个List"<< fileName <<"排序已经完成！"<<endl;
    
    
}
ULRindex::ULRindex(){
    
}
ULindex::ULindex(){
    
}
void HMUserList::vReplace(HMUserList* obj,vector<User> &input, int pos, int end){
    for(int i=0;i<=pos-end;i++)
        obj->list[pos+i]=input[i];
}
void vMerge(vector<User>& pre,vector<User> &add){
    pre.insert(pre.end(), add.begin(),add.end());
}
void HMUserList::sortSortedListByRanIndex( priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst>*indexlist){
    unsigned short int mission=indexlist->size();
    vector < future<priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst>* > >resultQ;
    
    while (indexlist->size()>1) {
        //先两个两个分割
        for (int i=0; i<mission/2; i++) {
            resultQ.push_back(async(launch::async, HMUserList::twoWaySorted,this,indexlist));
        }
        /*if (mission%2!=0) {
            //剩余单元素滞后
            ULRindex tmp=indexlist->top();
            indexlist->pop();
            indexlist->push(tmp);
        }*/
        for (int i=0;i<resultQ.size();i++){
            indexlist=resultQ[i].get();
        }
        //这一行执行后再进行重新分配任务
        //必须记住清空resultQ
        resultQ.clear();
        mission=indexlist->size();
    }
    //执行到这里 这个list 已经全部排序，更新list中的相关信息
    ULRindex final=indexlist->top();
    flag=true;
    max=final.max;
    min=final.min;
}
priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst>* HMUserList::twoWaySorted(HMUserList * obj, priority_queue<ULRindex,vector<ULRindex>,CmpMinFirst> *input){
    ULRindex ind1;
    ULRindex ind2;
    //一次只允许一个线程对一个要使用的队列进行加锁和解锁
    while (queueLock) {
        
    }
    queueLock=true;
    ind1=input->top();
    input->pop();
    ind2=input->top();
    input->pop();
    queueLock=false;
    vector<User> com1=*ind1.tarList;
    vector<User>com2=*ind2.tarList;
    
    vector<User> newList;
    ULRindex now;
    int pos1=ind1.pos;
    int end1=ind1.end;
    int pos2=ind2.pos;
    int end2=ind2.end;
    //取最大
    //开始共同部分的两路归并
    int ptr1=pos1;
    int ptr2=pos2;
    while (!(ptr1==end1+1 ||ptr2==end2+1)) {
        if (com1[ptr1].id<com2[ptr2].id){
            newList.push_back(com1[ptr1]);
            ptr1++;
        }
        else{
            newList.push_back(com2[ptr2].id);
            ptr2++;
        }
    }
    if (ptr1==end1+1){
        while (ptr2<end2+1) {
            newList.push_back(com2[ptr2]);
            ptr2++;
        }
    }else{
        while (ptr1<end1+1) {
            newList.push_back(com2[ptr1]);
            ptr1++;
        }
    }
    int trPos=pos1;
    if (pos2<pos1) trPos=pos2;
    //至此两路归并结束，将新队列内容复制到老的里面
    //com1作为老的
    for (int i=0;i<newList.size();i++){
        obj->list[trPos+i]=newList[i];
    }
    now.end=trPos+newList.size()-1;
    now.pos=trPos;
    //注意不要取com1的地址
    now.tarList=ind1.tarList;
    now.min=newList[0].id;
    now.max=newList[newList.size()-1].id;
    input->push(now);
    return input;
}

queue<ULindex> * HMUserList::sortSortedListByIndex(queue<ULindex> *indexlist){
    //取出两个文件
    ULindex file1=indexlist->front();
    indexlist->pop();
    ULindex file2=indexlist->front();
    indexlist->pop();
    HMUserList *list1=file1.tarList;
    HMUserList *list2=file2.tarList;
    
    if (!list1->flag){
        list1->sortListWithID();
    }
    if (!list2->flag){
        list2->sortListWithID();
    }
    
    vector<User> newList;
    unsigned int maxUC =list1->getCount();
    if (list2->getCount()<maxUC)
        maxUC=list2->getCount();
    unsigned int ptr1=0;
    unsigned int ptr2=0;
    while (ptr1<list1->count &&ptr2<list2->count) {
        User User1=list1->getIndexUser(ptr1);
        User User2=list2->getIndexUser(ptr2);
        if (User1.id<User2.id){
            newList.push_back(User1);
            ptr1++;
        }else {
            newList.push_back(User2);
            ptr2++;
        }
    }
    if (ptr1==list1->count){
        for (ptr2;ptr2<list2->count;ptr2++){
            newList.push_back(list2->getIndexUser(ptr2));
        }
    }else{
        for (ptr1;ptr1<list1->count;ptr1++){
            newList.push_back(list1->getIndexUser(ptr1));
        }
    }
    //List已经为归并完成的
    list1->list.resize(0);
    for (int i=0;i<newList.size();i++){
        list1->createNode(newList[i]);
    }
    //最后更新所属List的信息
    list1->min=newList[0].id;
    list1->max=newList[newList.size()-1].id;
    list1->count=newList.size();
    list1->flag=true;
    //更新队列的信息
    ULindex now;
    now.id=list1->fileName;
    now.tarList=list1->returnListAddr();
    indexlist->push(now);
    return indexlist;
}
User HMUserList::getIndexUser(unsigned int index){
    return list[index];
}
//首先穷举一个文件夹下所有的list文件,然后对这些list 分批存储到内存的链表
void HMUserList::sortListByFileDir(string dirPath, string fileName){
    vector <string> allFile=getFiles(dirPath, ".li*");
    cout<<"获得的文件共："<<allFile.size()<<"个"<<endl;
    vector<HMUserList > FList(allFile.size());
    queue<ULindex> FileList;
    for (int i=0; i<allFile.size(); i++) {
        FList[i].readFile(dirPath+allFile[i]);
        
        ULindex tmpIndex;
        tmpIndex.id=allFile[i];
        tmpIndex.tarList=&FList[i];
        FileList.push(tmpIndex);
    }
    cout<<"文件读取完成"<<endl<<"开始排序"<<endl;
    //对所有的单文件排序
    for (int i=0; i<FList.size(); i++) {
        FList[i].sortListWithID();
    }
    //进行任务分配
    while (FileList.size()>1) {
        FileList=*sortSortedListByIndex(&FileList);
    }
    //至此在队列中的即为我们要求的列表
    //全部拷贝到我们的类下面作为真正的类列表，由于生存期问题
    ULindex final=FileList.front();
    FileList.pop();
    HMUserList *finallist=final.tarList;
    //由于无法对类指针进行强制修改，所以只能利用拷贝的方式进行赋值
    this->list.resize(0);
    for (int i=0;i<finallist->count;i++){
        createNode(finallist->getIndexUser(i));
    }
    count=finallist->count;
    max=finallist->max;
    min=finallist->min;
    flag=true;
    fileName=finallist->fileName;
    cout<<"全部排序完成！"<<endl;
}
HMUserList * HMUserList::returnListAddr(){
    return this;
}
bool HMUserList::checkList(int pos,int end){
    for (int i=pos;i<end;i++){
        if (list[i].id>list[i+1].id){
                cout<<"检查完毕。。。失败。。。 位置："<<i<<endl;
            return false;
        }
    }
    cout<<"检查完毕~ 成功！"<<endl;
    return true;
}

bool HMUserList::saveListToFile(string fileDir,string name, unsigned short spolit){
    unsigned int oneFileCount=getCount()/spolit;
    unsigned int counter=0;
    for (unsigned short int i=1;i<spolit+1;i++){
        stringstream tmp;
        tmp<<i;
        string thisPoint;
        tmp>>thisPoint;
        
        string fullFilePath=fileDir+name+".op"+thisPoint;
        ofstream output(fullFilePath);
        output.seekp(ios::beg);
        if (!output.good()){
            cout<<"保存文件时发生了错误"<<fullFilePath<<endl;
            return false;
        }
        if (i==spolit+1){
            for (int j=(i-1)*oneFileCount;j<getCount();j++){
                output<<list[j].id<<" "<<list[j].name<<" "<<list[j].age<<" "<<list[j].date<<" "<<list[j].address<<endl;
                counter++;
            }
        }else{
            for (int j=(i-1)*oneFileCount; j<i*oneFileCount; j++) {
                output<<list[j].id<<" "<<list[j].name<<" "<<list[j].age<<" "<<list[j].date<<" "<<list[j].address<<endl;
                counter++;
            }
        }
    }
    cout<<"写文件成功, 共分"<<spolit<<"文件，写入了"<<counter<<"条记录"<<endl;
    return true;
}

HMUserList::HMUserList(string dir,string name){
    sortListByFileDir(dir, "test");
    cout<<"序列检查开始"<<endl;
    checkList(0, getCount()-1);
    cout<<"开始对文件进行保存"<<endl;
    saveListToFile(dir, "test", 5);
    cout<<"自动负载均衡多线程排序程序结束"<<endl;
}
