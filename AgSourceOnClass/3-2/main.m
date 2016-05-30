//
//  main.m
//  3-2
//
//  Created by 万能的仓鼠 on 3/22/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
NSMutableArray * getInsort(NSMutableArray * ,NSUInteger,NSUInteger);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char buffer[100];
        NSLog(@"Please input the list");
        gets(buffer);
        NSArray *typeToStr=[[[NSString alloc]initWithUTF8String:buffer] componentsSeparatedByString:@" "];//将输入内容按照空格分割为一个一个的字符型数字
        NSMutableArray *input=[[NSMutableArray alloc]init];
        [input addObject:[NSNumber numberWithInt:0]];//这里就把1位存储为 最后的总和。目的是为了返回数值的方便
        for (NSString *now in typeToStr)
            [input addObject:[NSNumber  numberWithInt:[now intValue]]];//将他们转换为 int 型的数，存入 input 数组待用
        NSLog(@"排序前数组 %@",input);
        NSMutableArray *result=getInsort(input, 1, [input count]-1);//这里注意起始的中间参量 pos 要把0跳过去。。。
        //输出结果
        NSLog(@"排序后数组 %@",result);
        NSLog(@"逆序数数量 %i",[[result objectAtIndex:0]intValue]);
    }
    return 0;
}

NSMutableArray * getInsort(NSMutableArray * input,NSUInteger pos,NSUInteger range){
    int mid=(range+pos)/2;
    int count=0;     NSMutableArray *newA=[[NSMutableArray alloc]init];//用于封装当前结果
    
    if(pos<range){
        
        NSMutableArray* leftA=getInsort(input, pos, mid);//中点分开时 左边数组的元素 包括 结果
        NSMutableArray * rightA=getInsort(input ,mid+1, range);//中点分开时 右边数组元素
        int sum=[[leftA objectAtIndex:0]intValue]+[[rightA objectAtIndex:0]intValue];//为增加可读性 把在两个数组的开头取出的当前两个数组的逆序数大小进行叠加 赋值给一个中间变量tmp
        [newA addObject:[NSNumber  numberWithInt:sum]];//将结果先存入其中
    
    //初始化两路排序的两个buf
        NSUInteger lBuf=1;
        NSUInteger rBuf=1;
    //两路归并排序
        while (1) {
            if (lBuf<[leftA count]&&rBuf<[rightA count]) {
                int left=[(NSNumber *)leftA[lBuf] intValue];
                int right=[(NSNumber *)rightA[rBuf] intValue];
                if (left<=right){
                    [newA addObject:[leftA objectAtIndex:lBuf]];
                    lBuf++;
                }else{
                    [newA addObject:[rightA objectAtIndex:rBuf]];
                    int tmp=[[newA objectAtIndex:0]intValue]+[leftA count]-rBuf;//注意这里的标号计算！
                    [newA replaceObjectAtIndex:0 withObject:[NSNumber numberWithInt:tmp]];//将 原来的封装在Array 最开头的数量表示修改为 sum+mid-当前标号
                    rBuf++;
                }
            }else if (rBuf<[rightA count]){
                for (int i=rBuf; i<[rightA count]; i++) {
                    [newA addObject:[rightA objectAtIndex:i]];
                }
                break;
            }else if (lBuf<[leftA count]){
                for (int i=lBuf; i<[leftA count]; i++) {
                    [newA addObject:[leftA objectAtIndex:i]];
                }
                break;
            }else break;
        }
        return newA;
    }
    [newA addObject:[NSNumber numberWithInt: 0]];
    [newA addObject:[input objectAtIndex:range]];
    return newA;
}
