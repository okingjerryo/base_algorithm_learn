//
//  main.m
//  3-1
//
//  Created by 万能的仓鼠 on 3/17/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
NSMutableArray * qSortLtoR(NSMutableArray *,NSUInteger,NSUInteger);
NSUInteger FindMiddleLR(NSMutableArray *,NSUInteger pos,NSUInteger range);
NSMutableArray * qSortRtoL (NSMutableArray *,NSUInteger,NSUInteger);
NSUInteger FindMiddleRL(NSMutableArray *,NSUInteger,NSUInteger);
NSMutableArray * TwoRouteS(NSMutableArray *,NSUInteger,NSUInteger);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableArray *inputI = [[NSMutableArray alloc]init];//数字封装动态数组，进入函数用
        NSMutableArray *inputS =[[NSMutableArray alloc]init];// 字符封装数组 用于接受键盘输入
        char buffer [100]; //输入tmp;
        NSString *tmpInput =nil;
        NSLog(@"请输入数字序列 元素用空格分割");
        gets(buffer);
        tmpInput=[NSString stringWithUTF8String:buffer];
        inputS=[tmpInput componentsSeparatedByString:@" "];
        for (NSString *str in inputS) {
            [inputI addObject:[NSNumber numberWithInt:[str intValue]]];
        }
        
        NSLog(@"原数列 %@",inputI);
       NSLog(@"排序后数列LR  %@",qSortLtoR(inputI,0,[inputI count]-1));
        //NSLog(@"排序后数列RL  %@",qSortRtoL(inputI,0,[inputI count]-1));
        //NSLog(@"排序后数列TS  %@",TwoRouteS (inputI,0,[inputI count]-1));
    }
    return 0;
}

NSMutableArray * qSortLtoR (NSMutableArray *input,NSUInteger pos,NSUInteger range){//快速排序从左到右
    if (pos<range){
    NSUInteger mid=FindMiddleLR(input,pos,range);//找到中间标
        input=qSortLtoR(input, pos, mid-1);
        input=qSortLtoR(input, mid+1, range);
    }
    return input;
}

NSUInteger FindMiddleLR (NSMutableArray *input,NSUInteger pos,NSUInteger range){
    NSInteger sam=[(NSNumber *)input[range] intValue];
    NSUInteger i=pos-1;
    for (NSUInteger j=pos; j<range; j++) {
        if ([(NSNumber *) input[j] intValue]<=sam){
            i++;
            [input exchangeObjectAtIndex:i withObjectAtIndex:j];
        }
    }
    [input exchangeObjectAtIndex:i+1 withObjectAtIndex:range];
    return i+1;
}

NSMutableArray *qSortRtoL(NSMutableArray *input,NSUInteger pos,NSUInteger  range){
    if (pos<range){
        NSUInteger mid=FindMiddleRL(input, pos, range);
        input=qSortRtoL(input, pos, mid-1);
        input=qSortRtoL(input, mid+1,range);
    }
    return input;
}

NSUInteger FindMiddleRL (NSMutableArray *input,NSUInteger pos ,NSUInteger range){
    NSInteger sam=[(NSNumber *)input[pos] intValue];
    NSUInteger i=pos;//右到左的比较方式和左到右略有不同1
    for (NSUInteger j=i+1;j <=range;j++){//不同3
        if ([(NSNumber *)input [j] intValue]<=sam){
            i++;
            [input exchangeObjectAtIndex:i withObjectAtIndex:j];
        }
    }
    [input exchangeObjectAtIndex:i withObjectAtIndex:pos];
    return i;//不同2
}

NSMutableArray * TwoRouteS(NSMutableArray *input,NSUInteger pos,NSUInteger range ){
    if (pos<range) {
        NSUInteger mid=(pos+range)/2;
        NSMutableArray *lnew=TwoRouteS(input, pos, mid);
        NSMutableArray *Rnew=TwoRouteS(input, mid+1, range);
        //递归分割
        //回来合并
        NSMutableArray* newA=[[NSMutableArray alloc]init];
        NSUInteger  lCount=[lnew count];
        NSUInteger  rCount=[Rnew count];
        NSUInteger lBuffer=0;
        NSUInteger rBuffer=0;
        while (1) {
            if ((lBuffer<lCount)&&(rBuffer<rCount)){
                int l=[(NSNumber *) lnew[lBuffer]intValue];
                int r=[(NSNumber *) Rnew[rBuffer] intValue];
                if (l<r) {
                    [newA addObject:[[NSNumber alloc]initWithInt:l]];
                    lBuffer++;
                }
                else {
                    [newA addObject:[[NSNumber alloc]initWithInt:r]];
                    rBuffer++;
                }
            }else if(lBuffer==lCount){
                for (NSUInteger i=rBuffer;i<[Rnew count] ; i++) {
                    [newA addObject:Rnew[i]];
                }
                break;
            }else if(rBuffer==rCount){
                for (NSUInteger i=lBuffer; i<[lnew count]; i++) {
                    [newA addObject:lnew[i]];
                }
                break;
            }
        }
        return newA;
    }
    NSMutableArray *new=[[NSMutableArray alloc]initWithObjects:input[pos], nil];
    return new;
}

