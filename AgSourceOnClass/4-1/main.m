//
//  main.m
//  4-1
//
//  Created by 万能的仓鼠 on 3/31/16.
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
    
    for (int i=1;i<=weight;i++){//完全背包是用重量遍历，0-1背包是用物品遍历（即 物品只能放进去一次）
        NSUInteger lastBest=0;
        if (i>1) lastBest=[baiBei[i-1]unsignedIntegerValue];//如果重量大于1 就先把之前的最优解复制过来
        for (int j=0;j<[input count];j++){
            NSUInteger tmp=[baiBei[i] unsignedIntegerValue];
            if (tmp>lastBest) lastBest=tmp;
            NSUInteger thisW=[(NSNumber *)[[input objectAtIndex:j]objectAtIndex:0]unsignedIntegerValue];
            if (thisW>i) continue;//重量大于当前重量，继续检索下一个
            else{
                //从数组里面取出来解包麻烦一点。。。这里将两个值分开写
                NSUInteger before=lastBest;//不放？ 之前的重量
                NSUInteger now=[(NSNumber *)[[input objectAtIndex:j]objectAtIndex:1]unsignedIntegerValue]+[(NSNumber *)[baiBei objectAtIndex:(i-thisW)]unsignedIntegerValue];//还是放？这个价值+减去这个重量的最大价值
                if (now>before){
                    baiBei[i]=[NSNumber numberWithUnsignedInteger:now];
                }
                    else
                    baiBei[i]=[NSNumber numberWithUnsignedInteger:before];//记得加背包
            }
        }
    }
    return [(NSNumber *)baiBei[weight]unsignedIntegerValue];
}