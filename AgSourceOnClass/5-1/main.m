//
//  main.m
//  5-1
//
//  Created by 万能的仓鼠 on 4/20/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
double particalBag(NSMutableArray *,NSUInteger );

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableArray *input=[[NSMutableArray alloc]init];
        char buf[100];
        NSUInteger count,size=0;
        //输入模块
        NSLog(@"请输入背包的最大容量");
        scanf("%lu",&size);
        NSLog(@"请输入背包物品种类的数量");
        scanf("%lu",&count);
        getchar();
        NSLog(@"请按输入物品的 重量 价值");
        for (int i=0;i<count;i++){
            gets(buf);
            NSArray *inputT=[[[NSString alloc]initWithUTF8String:buf]componentsSeparatedByString:@" " ];
            [input addObject:[[NSMutableArray alloc]init]];
            for (NSString *elem in inputT) {
                [input[i] addObject:[NSNumber numberWithDouble:[elem doubleValue]]];
            }
        }
        //函数调用
        NSLog(@"部分背包的最大收益 ： %0.2f",particalBag(input, size));
    }
    return 0;
}

double particalBag(NSMutableArray *input,NSUInteger weight){
    double re=0;
    //构造比较器排序 将具有单位重量最大价值的物品放在前面
    [input sortedArrayUsingComparator:^(id obj1,id obj2){
        double ow1=[obj1[0] doubleValue];
        double ov1=[obj1[1] doubleValue];
        double ow2=[obj2[0] doubleValue];
        double ov2=[obj2[1] doubleValue];
        if ((ov1/ow1)>(ov2/ow2))
            return (NSComparisonResult)NSOrderedAscending;
        else if ((ov1/ow1)<(ov2/ow2))
            return (NSComparisonResult)NSOrderedDescending;
        else return (NSComparisonResult)NSOrderedSame;
    }];
    //遍历单位价值最大的物品项目，如果当前剩余重量小于总重，就只放该单位价值的对应重量
    for (NSMutableArray *elem in input) {
        double thisW=[elem[0] doubleValue ];
        double thisV=[elem[1] doubleValue];
        if (weight<thisW){
            re+=weight*(thisV/thisW);
            break;
        }else{
            re+=thisV;
            weight-=thisW;//记得减重
        }
    }
    return re;
}