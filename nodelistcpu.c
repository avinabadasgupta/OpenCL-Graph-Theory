#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main()
{
        int nodes=12000;
        int i,j,count=0;
        double k;
        int *xdata=malloc(sizeof(int)*nodes);
        int *ydata=malloc(sizeof(int)*nodes);
        int *radius=malloc(sizeof(int)*nodes);
        int *nlist=malloc(sizeof(int)*nodes*nodes);
        srand(time(NULL));
        for(i=0;i<nodes;i++)
        {
                xdata[i]=rand()%100;
                ydata[i]=rand()%100;
                radius[i]=rand()%10;
                for(j=0;j<nodes;j++)
                nlist[i*nodes+j]=-1;
        }        
        clock_t tic=clock();	        
        for(i=0;i<nodes;i++)
        {        
                count=0;                
                for(j=0;j<nodes;j++)
                if(j!=i)                
                {
                        k=((xdata[i]-xdata[j])*(xdata[i]-xdata[j])) + ((ydata[i]-ydata[j])*(ydata[i]-ydata[j]));
                        k=sqrt(k);
                        if(k<=radius[i])
                        {
                                nlist[i*nodes+count]=j;
                                count++;
                        }
                }
        }
        clock_t toc=clock();	        
        /*for(i=0;i<nodes;i++)
        {
                printf("\n%d->",i);
                for(j=0;j<nodes;j++)
                {
                        if(nlist[i*nodes+j]==-1)
                        break;
                        else
                        printf("%d ",nlist[i*nodes+j]);
                }
        } */      
        free(xdata);
        free(ydata);
        free(radius);
        printf("elasped time = %f\n",(toc-tic)/(double)(CLOCKS_PER_SEC));	
        return 0;
}        
        
