//  Written language:Objective-C
//  main.m
//  cha1-2
//
//  Created by 黄菲 on 3/3/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
static void WordList(const char* ,int,int);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        //输入部分
        char buffer[100];//缓冲区
        NSLog(@"请输入待全排序的字符串");
        scanf("%s",buffer);
        NSString *inputEncap= [NSString stringWithUTF8String:buffer];//封装成一个 NSString 。
        int size=[inputEncap length];
        //全排列算法
        NSLog(@"全排列为:");
        WordList([inputEncap UTF8String],0, size);
        
    }
    return 0;
}
static void WordList(const char* a,int k, int m){
    static char tmpLis[100];
    static BOOL used[100];
    
    if (k==m){
        for (int i=0;i<m;i++)
            printf("%c",tmpLis[i]);
        printf("\n");
    }
    else {
        for(int i=0;i<m;i++){
            if(!used[i]){//如果这一位还没排序
                tmpLis[k]=a[i]; //字符排到里面
                used[i]=TRUE;   //这一位使用过了
                WordList(a, k+1, m);    //生成下一位的全排列
                used[i]=FALSE;  //生成好了 这一位释放掉
            }
        }
    }
}