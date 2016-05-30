//
//  main.m
//  cha1-3
//
//  Created by 黄菲 on 3/6/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>

void BoxPicture (NSMutableArray *,NSUInteger,NSUInteger);
void BoxPicShow(NSMutableArray *);

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSMutableArray * inputPic=[[NSMutableArray alloc]init];
        NSPoint p=NSMakePoint(0, 0);
        //注意： 在OC 中 NSMutableArray 只能存储类。常用数据类型用NSNumber
        //字符串用 NSString 初始化封装 结构体 用 NSValue封装
        [inputPic addObject:[NSValue value:&p withObjCType:@encode(NSPoint)]];//将初始的图形p点存入Array
        // NSLog(@"point is %@",NSStringFromPoint( [ (NSValue *)inputPic[0] pointValue]));//输出时要按照封装进行解包
        
        BoxPicture(inputPic,5,[inputPic count]-1);
    }
    return 0;
}
//算法函数
void BoxPicture (NSMutableArray * input,NSUInteger m,NSUInteger picsize){
    static NSUInteger now=1;
    if(now == m) BoxPicShow(input);//盒子维度到达最后 输出
    else{
        int add;//存储 下个点要相加的长度量
        if(now>1){// 一开始 没有第二个比较量 所以要排除
            add=( [ ( NSValue *) input [[input count]-picsize-1] pointValue].x - [(NSValue *)input[0] pointValue].x)*2;//这个图的右上角1号点与左下角1号点的差的2倍
        }
        else add=2;//默认的单位距离 2就好
        NSUInteger pCount=[input count];
        for (NSUInteger i=0;i<pCount ; i++) {
            //添加 4个位置
            NSPoint p1=NSMakePoint( [ ( NSValue *)input[i] pointValue].x+add, [ ( NSValue *) input [i] pointValue].y);
            NSPoint p2=NSMakePoint( [ ( NSValue *)input[i] pointValue].x+(add/2), [ ( NSValue *) input [i] pointValue].y+(add/2));
            NSPoint p3=NSMakePoint( [ ( NSValue *)input[i] pointValue].x, [ ( NSValue *) input [i] pointValue].y+add);
            NSPoint p4=NSMakePoint( [ ( NSValue *)input[i] pointValue].x+add, [ ( NSValue *) input [i] pointValue].y+add);
            //存起来 注意封装问题（普通数据 用 [NSNumber NumberWith(type):]     结构体 用 [NSValue value:"&结构体名称" withObjCType:@encode(封装的结构体名称) ]）
            [input addObject:[NSValue value:&p1 withObjCType:@encode(NSPoint)]];
            [input addObject:[NSValue value:&p2 withObjCType:@encode(NSPoint)]];
            [input addObject:[NSValue value:&p3 withObjCType:@encode(NSPoint)]];
            [input addObject:[NSValue value:&p4 withObjCType:@encode(NSPoint)]];
        }
        ++now;//更新 now 的索引
        BoxPicture(input, m,picsize); //递归调用 以这一次的维度结果 为 下面的起始复制图形
    }
    
}
//盒算法的显示部分
void BoxPicShow(NSMutableArray *show){
    //构造比较器  对于两个点的比较 优先比较y的升序 其次是x的升序：作为下边点的排序准则
        NSComparator cmptr = ^(id obj1, id obj2){
        if ( [ ( NSValue *) obj1 pointValue].y < [ ( NSValue *) obj2 pointValue].y)
            return (NSComparisonResult)NSOrderedAscending;//这是 NSCompare的结果封装 注意 要先强制类型转换为 NSComparitionResult
        else if ( [ ( NSValue *) obj1 pointValue].y > [ ( NSValue *) obj2 pointValue].y )
            return (NSComparisonResult)NSOrderedDescending;
        else{
            if( [ (NSValue *) obj1 pointValue].x < [ ( NSValue *) obj2 pointValue].x)
                return (NSComparisonResult)NSOrderedAscending;
            else if( [ ( NSValue *) obj1 pointValue].x > [ ( NSValue *) obj2 pointValue].x)
                return (NSComparisonResult) NSOrderedDescending;
        }
        return NSOrderedSame;//最后返回个same 作为结束
    };
    /*NSSet *newShow=[ NSSet setWithArray:show];
    NSArray *sortDesc=@[ [ [ NSSortDescriptor alloc] initWithKey:nil ascending:YES] ];
    NSArray *sortedShow=[newShow sortedArrayUsingDescriptors:sortDesc];*/
    // Crash......... id 是OC 的动态绑定元素 不可以用Uinteger 强制封装转换！
    //去重排序
    //方法： 1.将 ArrayList->Set 由于Set特性去重。2.Set->ArrayList 方便排序操作(这个效率有点。。。 Hash方式再研究研究。。) 3.利用上面的排序构造器对 去重后的Array进行排序
    show=[[[[NSSet alloc]initWithArray:show]allObjects]sortedArrayUsingComparator:cmptr];
    
    //因为 排好序的点，所以可以轻松输出了 像C一样 这里选用printf 输出图形
    for (NSUInteger i=0; i<[show count]; i++) {
        if (i==0) printf("x");//输出起始位置
        else {
            if ( [(NSValue *) show[i] pointValue].y!= [ ( NSValue *) show[i-1] pointValue ].y){
                printf("\n");//y不一样 回车 然后 输出图形
                for (int j=0;j<[(NSValue *) show[i] pointValue].x; j++)
                    printf(" ");
                printf("x");
            }
            else{
                for (int j=0; j<[(NSValue *) show[i] pointValue].x-[(NSValue *) show[i-1] pointValue].x-1; j++) {
                    printf(" ");
                }
                printf("x");
            }
        }
    }
    printf("\n");
  //  NSLog(@"%@",show);
}
