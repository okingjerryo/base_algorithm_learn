//
//  main.m
//  4-4
//
//  Created by 万能的仓鼠 on 4/13/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
NSUInteger LuDSL(NSMutableArray * input);//LuDSL=Longest unDecetive sublist 最短不降子序列
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char buffer[100];
        NSLog(@"请输入待求序列，用空格分开");
        gets(buffer);
        NSArray *inputT=[[[NSString alloc]initWithUTF8String:buffer]componentsSeparatedByString:@" " ];
        NSMutableArray *input=[[NSMutableArray alloc]init];
        for (NSString *elem in inputT) {
            [input addObject:[NSNumber numberWithUnsignedInteger:(NSUInteger)[elem integerValue]]];
        }
        NSLog(@"最长不降子序列的元素个数为：%lu",(unsigned long)LuDSL(input));
        
    }
    return 0;
}
NSUInteger LuDSL(NSMutableArray *input){
    NSUInteger iCount=[input count];
    NSMutableArray *reSet=[[NSMutableArray alloc]init];
    [reSet addObject:[NSNumber numberWithUnsignedInteger:1]];
    for (int i=1;i<iCount ;i++){
        NSUInteger now=[[input objectAtIndex:i]unsignedIntegerValue];
        NSUInteger nowM=0;
        for (int j=i-1; j>=0; j--) {
            NSUInteger nowC=[reSet[j]unsignedIntegerValue];
            if ([[input objectAtIndex:i-1]unsignedIntegerValue]<=now && nowM<nowC){
                nowM=nowC;
            }
        }
        [reSet addObject:[NSNumber numberWithUnsignedInteger:nowM+1]];
    }
    NSUInteger re=0;
    for (NSNumber *elem in reSet) {
        NSUInteger now=[elem unsignedIntegerValue];
        if (now>re)
        re=now;
    }
    return re;
}
