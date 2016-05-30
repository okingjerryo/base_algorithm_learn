//
//  main.m
//  5-3
//
//  Created by 万能的仓鼠 on 4/21/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
//无向图最小路径 算法主程序
NSMutableString* graphShortestPath(NSArray *);
//构造查找集 函数
NSMutableDictionary *initFindingDIc(NSArray *);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        NSMutableArray *inputT=[[NSMutableArray alloc]init];
        
        //input mode
        NSLog(@"请输入点点之间的序列");
        while (1) {
            NSLog(@"请输入 格式：point point lenth");
            char buf[20];
            char flag=' ';
            gets(buf);
            [inputT addObject:[[NSString alloc]initWithUTF8String:buf]];
            NSLog(@"继续输入？ q 退出 其他 继续");
            scanf("%c",&flag);
            getchar();
            if (flag=='q')
                break;
            
        }
        //无向图 添加相反路径行走方式
        NSUInteger size=[inputT count];
        for(NSUInteger i=0;i<size;i++){
            NSString *thisS=[inputT objectAtIndex:i];
            NSMutableString *reverS=[[NSMutableString alloc]initWithString:[thisS substringWithRange:NSMakeRange(2, 2)]];
            [reverS appendString:[thisS substringToIndex:1]];
            [reverS appendString:[thisS substringFromIndex:3]];
            [inputT addObject:[[NSString alloc]initWithString:(NSString *)reverS ]];
        }
        //利用NSSet 特性去重
        NSArray *input=[[[NSSet alloc]initWithArray:inputT]allObjects];
        NSLog(@"start!");
        NSLog(@"最短路径为:%@",graphShortestPath(input));
    }
    return 0;
}

NSMutableString *graphShortestPath(NSArray *input){
    NSMutableString * re=[[NSMutableString alloc]init];
    NSMutableArray *beforeP=[[NSMutableArray alloc]init];
    NSMutableArray *usedP=[[NSMutableArray alloc]init];
    NSUInteger  allB=0;
    //组装用过点
    for (NSString *elem in input)
        [beforeP addObject:[elem substringToIndex:1]];
    //过程 1. before 队列拆包 2. 队列拆包进入 Set(利用 Set的不重复特性去重) 3. Set输出所有元素至 NSArray（但这里 不是我们之后要用的可变数组）
    //4.新 init一个 NSMutableArray 用结果集Array重新封装
    beforeP=[[NSMutableArray alloc]initWithArray:[[[NSSet alloc]initWithArray:beforeP]allObjects]];
    
    //组装使用字典
    NSMutableDictionary *findingQuaty=initFindingDIc(input);
    //算法核心本体
    [usedP addObject:[beforeP objectAtIndex:0]];
    [beforeP removeObjectAtIndex:0];
    while ([beforeP count]>0) {
        NSString *bestP=[[NSString alloc]init];
        NSUInteger bestL=1<<30;
        
        for (NSString *elem in beforeP) {
            NSMutableString *path=[[NSMutableString alloc]init];
            NSUInteger lenth=0;
            //构造查询字符
            [path appendString:elem];
            [path appendString:@"-"];
            [path appendString:[usedP objectAtIndex:[usedP count]-1]];
            if (![findingQuaty valueForKey:path])
                continue;
                lenth=[[findingQuaty valueForKey:path]unsignedIntegerValue];
            
            if (lenth<bestL) {
                bestL=lenth;
                bestP=elem;
            }
        }
        [usedP addObject:bestP];
        [beforeP removeObject:bestP];
        allB+=bestL;
    }
       //构造结果集序列
    [re appendString:[usedP objectAtIndex:0]];
    [usedP removeObjectAtIndex:0];
    for (NSString *elem in usedP) {
        [re appendString:@"-->"];
        [re appendString:elem];
    }
    [re appendFormat:@" 同时 最小权重为：%lu",allB];
    return re;
}
NSMutableDictionary *initFindingDIc(NSArray *input){
    //存储路径
    NSMutableDictionary *reFindDic=[[NSMutableDictionary alloc]init];
    NSMutableString *path=[[NSMutableString alloc]init];
    //存储权值
    NSUInteger len=0;
    for (NSString *elem in input) {
        path=[[NSMutableString alloc]init];
        //构造字典用 路径 格式 ‘A-B’
        [path appendString:[elem substringToIndex:1]];
        [path appendString:@"-"];
        [path appendString:[elem substringWithRange:NSMakeRange(2, 1)]];
        //构造字典用长度
        len=(NSUInteger )[[elem substringFromIndex:4]integerValue];
        //创建查询字典项目
        [reFindDic setValue:[NSNumber numberWithUnsignedInteger:len] forKey:path];
    }
    return reFindDic;
}
