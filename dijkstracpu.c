#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define n 2048
int main()
{
       
        srand(time(NULL));        
        int *matrix=malloc(sizeof(int)*n*n);
        int *visited=malloc(sizeof(int)*n);
        int i,j,p;        
        FILE *fp = fopen("node2048.txt", "r");
	if (fp == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d",&matrix[i*n+j]);
		}
	}		
        for(i=0;i<n;i++)
        visited[i]=0;
        visited[0]=1;
        int min,index;       
        clock_t tic=clock();         
        for(j=0;j<n;j++)
        {        
                min=999999;                
                for(i=0;i<n;i++)
                {
                        if(visited[i]==0)
                        {                
                                if(matrix[0*n+i]<min)
                                {
                                        min=matrix[0*n+i];
                                        index=i;
                                }
                        }
                }
                visited[index]=1;
                for(i=0;i<n;i++)
                {
                        if(matrix[0*n+i]>matrix[0*n+index]+matrix[index*n+i])
                        {
                                matrix[0*n+i]=matrix[0*n+index]+matrix[index*n+i];
                        }
                }
        }
        clock_t toc=clock();
	FILE *fq = fopen("cpuanswer2048.txt", "w");
	if (fq == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fprintf(fq,"%d\n",matrix[i*n+j]);
		}
	}			        
	printf("\n\nElasped time in milliseconds = %f\n",1000*(toc-tic)/(double)(CLOCKS_PER_SEC));	
        free(matrix);
        free(visited);
	fclose(fp);
	fclose(fq);
      	return 0;
}
        
                               
