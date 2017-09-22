#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
int main()
{
        int n=8192,k=2048;        
        clock_t tic=clock();
        srand(time(NULL));        
        int *matrix=(int *)malloc(sizeof(int)*(n*k));
        int *list=(int *)malloc(sizeof(int)*n);
        int *count=(int *)malloc(sizeof(int)*n);        
        int i,j,p,m,t,temp,x,y,block=n/k;
        for(i=0;i<n;i++)
        {
                list[i]=i;
                count[i]=0;
        }
        for(i=0;i<n;i++)
        for(j=0;j<k;j++)
        matrix[i*k+j]=-1;
        for (j=n-1;j>0;j--)
        {
                p=rand()%(j+1);
                temp=list[j];
                list[j]=list[p];
                list[p]=temp;
        }
        for(p=0;p<block;p++)
        {
                m=p*k;                
                for(i=m;i<m+k-1;i++)
                {
                        for(t=i+1;t<m+k;t++)
                        {
                                x=list[i]*k+count[list[i]];
                                y=list[t]*k+count[list[t]];
                                matrix[x]=list[t];
                                matrix[y]=list[i];
                                count[list[i]]++;
                                count[list[t]]++;
                        }
                }
        }
        j=n/2;        
        for(i=0;i<j;i++)
        {
                usleep(10000);                
                x=list[i]*k+count[list[i]];
                y=list[i+j]*k+count[list[i+j]];              
                matrix[x]=list[i+j];
                matrix[y]=list[i];
                count[list[i]]++;
                count[list[i+j]]++;
        }        
        for(i=0;i<n;i++)
        printf("%d ",count[i]);     
        clock_t toc=clock();
        printf("elasped time = %f\n",(toc-tic)/(double)(CLOCKS_PER_SEC));	        
        /*for(i=0;i<n;i++)
        {
                printf("%d->",i);
                for(j=0;j<k;j++)
                printf("%d ",j);
                printf("\n\n");
        }*/
        free(matrix);
        free(list);
        free(count);
        return 0;
}
                                
                        
                        
        
