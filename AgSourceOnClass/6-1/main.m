//
//  main.m
//  6-1
//
//  Created by 万能的仓鼠 on 4/25/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//
//数列是否存在几项加和为数值
#import <Foundation/Foundation.h>
BOOL isThisSumExsit(NSMutableArray *,NSUInteger ,NSInteger ,NSInteger);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableArray *input=[[NSMutableArray alloc]init];
        char buf[50];
        NSInteger judge=0;
        //information getting
        NSLog(@"请输入待判断序列内容");
        gets(buf);
        NSLog(@"请输入待判断值");
        scanf("%ld",&judge);
        getchar();
        //输入信息处理  分割->存储->转存为Int
        NSArray *inputT=[[[NSString alloc]initWithUTF8String:buf]componentsSeparatedByString:@" "];
        for (NSString *elem in inputT)
            [input addObject:[NSNumber numberWithInteger:[elem integerValue]]];
        //数列判断主体
        NSString* re=(isThisSumExsit(input,0,judge,0))?@"存在":@"不存在";
        NSLog(@"结果%@",re);
    }
    return 0;
}

BOOL isThisSumExsit(NSMutableArray *input, NSUInteger index,NSInteger judge,NSInteger sum){
    static BOOL flag=false;
    for (NSUInteger i=index;i<[input count];i++){
    if (index== [input count]-1){
        flag=(sum==judge);
        return flag;
    }
    if (sum+[[input objectAtIndex:index]integerValue]<judge){
        if (isThisSumExsit(input,i+1,judge,sum+[[input objectAtIndex:index]integerValue])){
            flag=true;
            return flag;
        }
        if (isThisSumExsit(input, i+1,judge,sum)){
            flag=true;
            return flag;
        }
    
    }else if (sum+[[input objectAtIndex:index]integerValue]==judge){
        flag=true;
    }
        continue;
    }
    return flag;
}