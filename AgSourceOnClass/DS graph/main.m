//  programming language:Objective-C
//  main.m
//
//
//  Created by 黄菲 on 3/2/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>

BOOL isArraySort(NSMutableArray *);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        //创建3个动态Array 分别加入用 NSNumber 封装好的整形数据
        NSMutableArray *Arr1=[[NSMutableArray alloc]init];//Arr 1
        NSMutableArray *Arr2=[[NSMutableArray alloc]init];//Arr 2
        NSMutableArray *Arr3=[[NSMutableArray alloc]init];//Arr 3
        
        //向几组Array 添加数字元素
        //注意 OC 中 基本数字类型进 NSArray 需预封装为 NSNumber 类
        //Arr 1
        [Arr1 addObject:[NSNumber numberWithInt:185]];
        [Arr1 addObject:[NSNumber numberWithInt:236]];
        [Arr1 addObject:[NSNumber numberWithInt:512]];
        [Arr1 addObject:[NSNumber numberWithInt:351]];
        [Arr1 addObject:[NSNumber numberWithInt:133]];
        [Arr1 addObject:[NSNumber numberWithInt:52]];
        //Arr 2
        [Arr2 addObject:[NSNumber numberWithInt:0]];
        [Arr2 addObject:[NSNumber numberWithInt:0]];
        [Arr2 addObject:[NSNumber numberWithInt:1]];
        [Arr2 addObject:[NSNumber  numberWithInt:3]];
        //Arr3
        [Arr3 addObject:[NSNumber numberWithInt:7]];
        [Arr3 addObject:[NSNumber numberWithInt:5]];
        [Arr3 addObject:[NSNumber numberWithInt:5]];
        [Arr3 addObject:[NSNumber numberWithInt:3]];
        
        //进入测试函数并 输出结果
        NSLog(@"%@",isArraySort(Arr1)?@"数列为顺序序列":@"数列不为顺序数列");
        NSLog(@"%@",isArraySort(Arr2)?@"数列为顺序序列":@"数列不为顺序数列");
        NSLog(@"%@",isArraySort(Arr3)?@"数列为顺序序列":@"数列不为顺序数列");
    }
    return 0;
}

BOOL isArraySort(NSMutableArray *input){//数每次与状态字进行比较，如果非等于 同时状态字异常，则返回false。时间复杂度O(n)
    int state=1;//状态字：1相等  0 小 2大
    for ( int i=0; i<[input count]-1; i++) {
        if ([(NSNumber *)input [i]intValue]>[(NSNumber *)input [i+1]intValue]) {
            if (state==1) state=2;
            else if(state==0) return false;
        }else if([(NSNumber *)input[i] intValue]< [(NSNumber *)input[i+1] intValue]){
            if(state==1) state=0;
            else if(state==2) return false;
        }
    }
    return true;
}

