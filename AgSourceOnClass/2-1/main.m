//
// Coding Language by Objective-C
//  main.m
//  2-1
//
//  Created by 万能的仓鼠 on 3/13/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
//10->n 进制算法 输入 OC风格无符号整数
NSMutableArray* ExchangeScale (unsigned int ,NSUInteger);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int input=0,scale=0;
        NSLog(@"请输入待转换数字 及 进制，用空格区分");
        scanf("%i %i",&input,&scale);
        NSMutableArray *output = ExchangeScale(input, scale);
        NSLog(@"result is ");
        for (NSObject *c in output){ //在 OC 中 for-in 循环 利用的是快速枚举  前面的那个类型就是 NSMutableArray的类型
            printf("%c",[(NSNumber *)c charValue]);
        }
        printf("\n");
    }
    return 0;
}

NSMutableArray* ExchangeScale (unsigned int input, NSUInteger scale){
    unsigned int mod=0,divided=1;
    NSMutableArray* output=[[NSMutableArray alloc]init];
    
    divided=input/scale;
    mod=input%scale;
    if (divided==0){
        if (mod>9)
            [output addObject:[NSNumber numberWithChar:mod+55]];
        else
            [output addObject:[NSNumber numberWithChar:mod+48]];
        
        return output;
    }else{
        output=ExchangeScale(divided, scale);
        if (mod>9)
            [output addObject:[NSNumber numberWithChar:mod+55]];
        else
            [output addObject:[NSNumber numberWithChar:mod+48]];
        return output;
    }
    
}


