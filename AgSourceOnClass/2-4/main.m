//
//  main.m
//  2-4
//
//  Created by 万能的仓鼠 on 3/14/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>

NSMutableArray * FindPath (NSMutableArray *,NSPoint * ,NSInteger);
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        //初始化一些需要的变量
        char sinput[1000];  // 作为 scanf的 buffer缓冲
        NSString *inputExpack = nil;    //这个作为处理输入宝塔每层数据时使用的媒介
        int len=0;//层数
        NSMutableArray *inputTower=[[NSMutableArray alloc]init]; //作为输入的二维 可变数组
        
        NSLog(@"请输入待输入的行数");
        scanf("%i",&len);
        getchar();  //获取回车符
        NSLog(@"请输入宝塔数据");
        
        for (int i=0; i<len; i++) {
            //[inputTower addObject:[[NSMutableArray alloc]init]];//新的一行
            gets(sinput);       //用于获取整行的数据
            inputExpack=[NSString stringWithUTF8String:sinput];     //数据封装为 NSString
            [inputTower addObject:[inputExpack componentsSeparatedByString:@" "]];   //  利用 NSString中的分割方法，按照“ ”将一行分成若干数字子串
        }
        NSInteger sum;// 定义 要查找的数
        NSLog(@"请输入待找路径和");
        scanf("%li",&sum);
        getchar();//吸收 scanf在OC 中不能吸收的回车符
        NSPoint firPoint=NSMakePoint(0, 0);//pos 参数是一个位置参数 故生成点
        NSMutableArray *output= FindPath(inputTower, &firPoint, sum);
        NSLog(@"ResultSet: %@",output);
        NSLog(@"Result count is %i",[output count]);
        
        
    }
    return 0;
}

NSMutableArray * FindPath (NSMutableArray * input,NSPoint * pos ,NSInteger getN){
    static NSUInteger size=0;//确定数字塔的深度
    int x,y;// 获取到 当前位置点的x y 坐标
    static NSMutableString * path;  //当前路径
    static NSMutableArray *pathArr;// 结果集
    //注意 在这里 深度 路径 和 结果集都应为静态常量

    if (pathArr==nil)
        pathArr=[[NSMutableArray alloc]init];
    if (path==nil)
        path=[[NSMutableString alloc]init];
    //判断静态量是否初始化，初始化在一次函数调用中只允许一次。
    if (size==0) size=[input count]-1;
    x=pos->x;
    y=pos->y;
    
    int now=[[[NSString alloc]initWithString:input[y][x]] intValue];//因为 获取输入时存入动态数组中是字符型量，这里为了方便将其转化为数字
    if (y==size){//策略 如果到了最深 才允许加入路径
        if(now==getN) {
            //构造 添加当前的路径
            [path appendFormat:@"%d ",now];
            [pathArr addObject:[[NSString alloc]initWithString: path]];
            //向上一层跳，由于path 是静态常量 所以，当前的路径要向上跳转，手动抹去最后一个数字
            int len=[(NSString *)input[y][x] length]+1;
            int laLoc=[path length]-len-1;
            if (laLoc>=0) [path deleteCharactersInRange:NSMakeRange(laLoc, len)];
            return pathArr;//该return 就大胆return
        }
    }else if(now<getN){// 如果路径加和未到目标，即可能存在结果集中有该点路径
         [path appendFormat:@"%d ",now];//加入该点
        NSPoint next=NSMakePoint(x, y+1);//深度优先遍历
        pathArr=FindPath(input,&next, getN-now);
        next=NSMakePoint(x+1, y+1);
        pathArr=FindPath(input, &next, getN-now);
        //如果 允许广度路径搜索，则添加下边的代码
        /*if (x+1<[input [y] count]){
        next=NSMakePoint(x+1, y);
        pathArr=FindPath(input, &next, getN-now);
        }*/
        //这里 路径的两个方向全部探索完毕，故向上一层跳转
        //手动删除路径中的最后一位路径
        int len=[(NSString *)input[y][x] length]+1;
        int laLoc=[path length]-len-1;
        if (laLoc>=0) [path deleteCharactersInRange:NSMakeRange(laLoc, len)];
        return pathArr;//回跳
    }
    //若此时不满足上面的结果，即该点一定不满足上面，故直接跳回上一层
    return pathArr;
}