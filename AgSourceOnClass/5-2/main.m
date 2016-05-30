//
//  main.m
//  5-2
//
//  Created by 万能的仓鼠 on 4/20/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
//优先级队列算法

NSInteger sortedArrayASD(NSString *,NSString * ,void *);
NSInteger gongListAgt(NSMutableArray *input);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        //input mode
        char buf[50];
        NSLog(@"请输入待入队序列");
        gets(buf);
        
        NSMutableArray *input=(NSMutableArray *)[[[NSString alloc]initWithUTF8String:buf]componentsSeparatedByString:@" "];
        NSLog(@"优先序列代价最终结果：%li",gongListAgt(input));
    }
    return 0;
}
//算法本体
NSInteger gongListAgt(NSMutableArray *input){
    static NSInteger re=0;
    //结果集中只有一个，加和出队得到最终结果
    NSInteger front=0;
    if ([input count]<2){
        front=[[input objectAtIndex:0]integerValue];
        return re+front;
    }
    //排序
    //这里注意 sort算法后的Array 是NSArray不是 Mutabal型的 所以，交付指针时务必用initWithArray 重新生成可变数组防止报错
    input=[[NSMutableArray alloc]initWithArray:[input sortedArrayUsingFunction:sortedArrayASD context:nil]];
    //前2出队
    front=[[input objectAtIndex:0]integerValue];
    [input removeObjectAtIndex:0];
    NSInteger back=[[input objectAtIndex:0] integerValue];
    [input removeObjectAtIndex:0];
    //结果加和 重新存入
    NSInteger tmpin=back+front;
    re+=tmpin;
    [input addObject:[[NSString alloc]initWithFormat:@"%li",(long)tmpin ] ];
    //递归调用直到得到结果
    gongListAgt(input);
    return re ;
}
//分离 对序列的排序算法
NSInteger sortedArrayASD(NSString *obj1,NSString *obj2 ,void *context){//注意这里的context 是void 型的指针
    NSInteger ob1R=[obj1 integerValue];
    NSInteger ob2R=[obj2 integerValue];
    if (ob1R>ob2R)
        return (NSComparisonResult)NSOrderedDescending;
    else if (ob1R<ob2R)
        return (NSComparisonResult)NSOrderedAscending;
    else return (NSComparisonResult)NSOrderedSame;
}

