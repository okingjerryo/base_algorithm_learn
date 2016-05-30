//
//  main.cpp
//  3-3
//
//  Created by 万能的仓鼠 on 3/23/16.
//  Copyright © 2016 UryuoHamusta. All rights reserved.
//
#include<iostream>
#define N 70
void f(char a[][N], int rank, int row, int col)
{
    if(rank==1)
    {
        a[row][col] = '*';
        return; }
    int w = 1;
    int i;
    for(i=0; i<rank-1; i++) w *= 2;
    //补充部分============
    f(a,rank-1 ,row,col+w/2);
    //===================
    f(a, rank-1, row+w/2, col);
    f(a, rank-1, row+w/2, col+w);
}
int main() {
    char a[N][N];
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            a[i][j] = ' ';
    f(a,6,0,0);
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
            printf("%c",a[i][j]);
        printf("\n");
    }
    return 0; }
