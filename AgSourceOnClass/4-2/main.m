//
//  main.m
//  4-2
//
//  Created by 万能的仓鼠 on 4/6/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>

NSUInteger zeroOneBag(NSMutableArray *,NSUInteger);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSUInteger bWeight;
        NSUInteger count;
        NSLog(@"请输入背包最大容纳重量");
        scanf("%lui",&bWeight);
        getchar();//吸收回车
        NSLog(@"请输入待输入的物品数量");
        scanf("%lui",&count);
        getchar();
        NSLog(@"请输入物品信息 '重量 价值‘");
        //数据输入部分
        char inBuf[300];
        
        NSMutableArray* input=[[NSMutableArray alloc]init];
        for (int i=0; i<count; i++) {
            gets(inBuf);
            NSArray* inputT=[[[NSString alloc]initWithUTF8String:inBuf] componentsSeparatedByString:@" "];//存储转换的用的字符串型
            [input addObject:[[NSMutableArray alloc]init]];//注意 一定要alloc init
            for (NSString *elem in inputT)
                [input[i] addObject:[NSNumber numberWithInt:[elem intValue]]];
        }
        NSLog(@"start!");
        NSLog(@"%lu",(unsigned long)zeroOneBag(input, bWeight));
    }
    
    return 0;
}
//注意 thebest 永远存Best
NSUInteger zeroOneBag(NSMutableArray *input,NSUInteger weight){
    NSMutableArray *baiBei=[[NSMutableArray alloc]init];
    //集体初始化
    for (NSUInteger i=0;i<=weight;i++)
        [baiBei addObject: [NSNumber numberWithUnsignedInteger:0]];
    
    //0-1背包是以物品遍历所有重量
    for (NSUInteger i=0;i<[input count];i++) {
        //把重量和 价值先行提出
        NSUInteger thisW=[[[input objectAtIndex:i]objectAtIndex:0]unsignedIntegerValue];
        NSUInteger thisV=[[[input objectAtIndex:i]objectAtIndex:1]unsignedIntegerValue];
        //注意 for 循环 后向遍历（从后向前，以免新数据对以前数据造成影响）
        for (NSUInteger j=weight; j>=thisW; j--) {
            if (thisW<=j){
                //提取出之前的最好结果
                NSUInteger lastBest=[[baiBei objectAtIndex:j]unsignedIntegerValue];
                NSUInteger now=thisV+[[baiBei objectAtIndex:j-thisW]unsignedIntegerValue];//现在的价值+ 以前的价值
                //如果确定放了，那么这个及后面的重量都会存在这个背包的重量所在的最优解
                if (now>lastBest){
                    
                        baiBei[j]=[NSNumber numberWithUnsignedInteger:now];
                    
                }
            }
        }
    }
    return [[baiBei objectAtIndex:weight]unsignedIntegerValue];
}

