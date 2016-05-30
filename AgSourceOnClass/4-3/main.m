//
//  main.m
//  4-3
//
//  Created by 万能的仓鼠 on 4/7/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//

#import <Foundation/Foundation.h>
//承载传出的Path 和数量
@interface Output:NSObject
@property NSMutableString* path;
@property NSInteger amount;
-(id)initWithAmount:(NSInteger )amount andPath:(NSMutableString *)bestPath;
@end

@implementation Output
@synthesize path,amount;
-(id) initWithAmount:(NSInteger )inAmount andPath:(NSMutableString *)bestPath{
    self=[self init];
    [self setAmount:inAmount];
    [self setPath:bestPath];
    return self;
}
@end

Output* multiplePath(NSMutableArray *,NSPoint );
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        char buffer[100];
        NSUInteger inMass=0;
        NSMutableArray *input=[[NSMutableArray alloc]init];
        
        NSLog(@"please input your input number");
        scanf("%lu",&inMass);
        getchar();
        NSLog(@"please input your mutipal-squers scale");
        
        for (NSUInteger i=0;i<inMass;i++){
            [input addObject:[[NSMutableArray alloc]init]];
           
            gets(buffer);
            NSArray * inputT=[[[NSString alloc]initWithUTF8String:buffer] componentsSeparatedByString:@" "];
            //每项从integer 强制转换；
            for (NSString *elem in inputT)
                [input[i] addObject:[NSNumber numberWithUnsignedInteger:(NSUInteger)[elem integerValue]]];
        }
        Output *result=multiplePath(input, NSMakePoint(0, inMass-1));
        NSString *pathT=[result path];
        
        for (int j=0;j<[pathT length]-1;j++) {
            if ([pathT characterAtIndex:j]==')'&&[pathT characterAtIndex:j+1]=='('){
                pathT=[NSMutableString stringWithFormat:@"%@%@",[pathT substringToIndex:j],[pathT substringFromIndex:j+2]];
            j=j-1;
            }
        }
        NSLog(@"最佳的乘法结果: %@",pathT );
        NSLog(@"需要做: %lu 次乘法",[result amount]);
    }
    return 0;
}

Output* multiplePath(NSMutableArray *input,NSPoint now){
    static NSMutableArray *bei;
    NSMutableArray *tmpcom=[[NSMutableArray alloc]init];
    //位置从 a->b
    int a=now.x;
    int b=now.y;
    if (!bei){
        bei=[[NSMutableArray alloc]init];
        for(int i=0;i<=b-a;i++){
            [bei addObject: [[NSMutableArray alloc]init]];
            for (int j=0 ; j<=b-a; j++) {
                [bei[i] addObject:[[Output alloc]initWithAmount:-1 andPath:[[NSMutableString alloc]init] ]];
            }
        }
    }
    if ([bei[a] [b] amount] !=-1) return bei[a][b];//算过了就不再算了
    
    if(a==b) { //到了最底层 返回0 和 A本身
        bei[a][b]=[[Output alloc]initWithAmount:0 andPath:[[NSMutableString alloc] initWithFormat:@"A%i",a+1]];
        return bei[a][b] ;
    }
    
    for (int i=a; i<b; i++) {
        Output *ra=multiplePath(input,NSMakePoint(a, i) );
        Output *rb=multiplePath(input, NSMakePoint(i+1, b));
        NSUInteger adding=[input[a][0] unsignedIntegerValue]*[input[i+1][0] unsignedIntegerValue]*[input[b][1] unsignedIntegerValue];
        NSUInteger amoutR=[ra amount]+[rb amount]+adding;
        [tmpcom addObject:[[Output alloc]initWithAmount:amoutR andPath:[NSMutableString stringWithFormat:@"(%@)(%@)",[ra path],[rb path]] ] ];
    }
    //构建一个特殊的比较器，在这个数组的开头元素 就是需要amount数最小的那个
    [tmpcom sortUsingComparator:^(id obj1,id obj2){
        if ([(Output *)obj1 amount]< [(Output *)obj2 amount] )
            return (NSComparisonResult)NSOrderedAscending;
        else if ([(Output *) obj1 amount]>[(Output *) obj2 amount])
            return (NSComparisonResult)NSOrderedDescending;
        else return (NSComparisonResult)NSOrderedSame;
    }];
    bei[a][b]=tmpcom[0];
    return [tmpcom objectAtIndex:0];
}