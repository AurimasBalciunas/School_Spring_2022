/*
 * main.c
 *
 *  Created on: Feb 2, 2022
 *      Author: aurisb
 */

int modify_value(int z);

void main(void)
{
    int i,j,x,y,alpha,beta,finished;
    x=0;
    y=0;
    finished=0;
    alpha=10;
    beta=3;

    for(i=0;i<alpha;i++)
    {
        for(j=0;j<beta;j++)
        {
            y=modify_value(y);
        }

    }

    finished=1;
}

int modify_value(int z)
{
    int w;
    w=z+1;
    return(w);
}



