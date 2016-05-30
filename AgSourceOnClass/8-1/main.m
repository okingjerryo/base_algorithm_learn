//
//  main.m
//  8-1
//
//  Created by 万能的仓鼠 on 5/18/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>

NSArray *fileInput(NSString *);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"请将数据文件1 放在Downloads 目录下");
        NSArray *inputT=fileInput(@"filename");
    }
    return 0;
}
NSArray *fileInput(NSString *filename){
    NSFileManager *fm=[[NSFileManager alloc]init];
    NSMutableString *thisPath=[[NSMutableString alloc]initWithString:@"~/Downloads/"];
    [thisPath appendString:filename];
    NSData *reading=[fm contentsAtPath:thisPath];
    
    return nil;
}