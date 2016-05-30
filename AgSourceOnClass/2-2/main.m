//
// Coding Language by Objective-C
//  main.m
//  2-2
//
//  Created by 黄菲 on 3/13/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
int DigitalRoot(int);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int input;
        NSLog(@"请输入数字");
        scanf("%i",&input);
        NSLog(@" 输入 %d 的 数字根为 %d",input,DigitalRoot(input));
    }
    return 0;
}

int DigitalRoot(int input){
    int sum=0;
    while (input>0){
        sum+=input%10;
        input/=10;
    }
    
    if (sum>9){
        sum=DigitalRoot(sum);
    }
    return sum;
}
