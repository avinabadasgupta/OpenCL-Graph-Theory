#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int main()
{
        srand(time(NULL));        
        int n=2048;
        int *matrix=malloc(sizeof(int)*n*n);
        int *visited=malloc(sizeof(int)*n);
	int *trav=malloc(sizeof(int)*n);         
	int *queue=malloc(sizeof(int)*n);	
	int i,j,s,count,k,sum;
	s=0;
	count=0;
	k=0;
	sum=0;
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
        for(i=0;i<n;i++)
	queue[i]=0;
        clock_t tic=clock();           
        for(;;)
        {
		                
		for(i=0;i<n;i++)
                {
                        if(matrix[s*n+i]==1)
                        {
                                if(visited[i]==0)
                                {
                                        queue[k]=i;
					k++;                                        
					visited[i]=1;
                                        trav[count]=i;
                                        count++;
                                }
                        }
                }
                s=queue[0];
		for(j=1;j<=n;j++)
		queue[j-1]=queue[j];
		k--;
               	for(j=0;j<n;j++)
		sum=sum+queue[j];
		if(sum==0)
		break;
		sum=0;
        }
	FILE *fq = fopen("answer2048.txt", "w");
	if (fq == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}	        
	for(i=0;i<n;i++)
        fprintf(fq,"%d\n",trav[i]);
        clock_t toc=clock();
        printf("\n\nElasped time in milliseconds = %f\n",1000*(toc-tic)/(double)(CLOCKS_PER_SEC));        
        free(matrix);
        free(trav);
        free(visited);
        return 0;
}
                
        

