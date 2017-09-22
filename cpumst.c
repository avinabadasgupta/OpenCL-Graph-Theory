#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int main()
{

	int n=2048;	
	int a,b,u,v,i,j,ne=1;
	int min,mincost=0;	
	int *visited=malloc(sizeof(int)*n*n);	
	int *cost=malloc(sizeof(int)*n*n);
	for(i=0;i<n;i++)
	visited[i]=0;	
	FILE *fp = fopen("test.txt", "r");
	if (fp == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	while(!feof(fp))
	{
		i=0;
		for(;;)
		{		
			for(j=0;j<i-1;j++)
			{			
								
				fscanf(fp,"%d",&a);
				printf("%d ",a);
			}
			if(a==578)
			printf(" j %d\n",j);			
			if(a==9999)
			break;			
			i++;
		}
	}
	printf ("i %d\n",i);	
	/*for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		if(cost[i*n+j]==0)
		cost[i*n+j]=999999;
	}
	visited[0]=1;
	FILE *fq = fopen("answer2048.txt", "w");
	if (fq == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}	
	clock_t tic=clock();  	
	while(ne < n)
	{
		for(i=0,min=999999;i<n;i++)
		for(j=0;j<n;j++)
		if(cost[i*n+j]< min)
		if(visited[i]!=0)
		{
			min=cost[i*n+j];
			a=u=i;
			b=v=j;
		}
		if(visited[u]==0 || visited[v]==0)
		{
			fprintf(fq,"Edge %d:(%d %d) cost:%d\n",ne++,a,b,min);			
			mincost+=min;
			visited[b]=1;
		}
		cost[a*n+b]=cost[b*n+a]=999999;
	}
	fprintf(fq,"\n Minimun cost=%d",mincost);	
	clock_t toc=clock();
	printf("\n\nElasped time in milliseconds = %f\n",1000*(toc-tic)/(double)(CLOCKS_PER_SEC));*/	
	free(visited);
	free(cost);
	return 0;	
}
