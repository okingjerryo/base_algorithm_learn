//
//  main.m
//  2-3
//
//  Created by 万能的仓鼠 on 3/13/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
NSString * StringReverse(NSString *);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char tmp[100];//输入缓冲区
        NSLog(@"请输入待反转字符串");
        scanf("%s",&tmp);
        NSString* input = [[NSString alloc]initWithUTF8String:tmp];
        
        NSLog(@"Ordiary string is %@",input);
        NSLog(@"Reverse string is %@",StringReverse(input));
    }
    return 0;
}

NSString * StringReverse(NSString* input){
    if ([input length]<2)
        return input; // 如果长度小于2 意味着就一个字符 于是 直接return 不做处理
    else {
        return [[[input substringWithRange:NSMakeRange([input length]-1, 1)] stringByAppendingString: StringReverse([input substringWithRange:NSMakeRange(1, [input length]-2)])] stringByAppendingString:[ input substringWithRange:NSMakeRange(0, 1)] ];
        //否则 意味这长度大于2
        //构造 反向字符串 “最后一个字母+Reverse(中间的字母)+第一个字母” 然后交给程序递归调用
        //函数注释 :substringWithRange ：用NSMakeRange做参量(指定一个 开头位置，和 后面它需要的长度)
        //                 NSString * stringByAppendingString NSString * 这个函数 是将前后两个NSString 作为媒介连接起来，相当于 C++中的 String a & String b
    }
}