#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main()
{
	int n=10000;
	int *g=malloc(sizeof(int)*n*n);
	int *x=malloc(sizeof(int)*n);  	
	int e= 990000,i,j,z,a,b;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	g[i*n+j]=0;	
	FILE *fp = fopen("qgordr100.col", "r");
	if (fp == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	if(fp!=NULL)
	{	
		for(i=0;i<e;i++)
		{
			fscanf(fp,"%d",&a);
			//printf("%d ",a);
			fscanf(fp,"%d",&b);
			//printf("%d",b);
			//printf("\n");
			a--,b--;
			g[a*n+b]=g[b*n+a]=1;
			
		}
	}
	clock_t tic=clock();	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(g[i*n+j]==1)
			e++;
		}
	}
	e=e/2;
	for(i=0;i<n;i++)
	{
		int k,j;
   		x[i]=1;  
   		for(k=0;k<i;k++)
		{ 
     			if(g[k*n+i]!=0 && x[i]==x[k])  
       			x[i]=x[k]+1;
		} 
   	}	    	
	FILE *fq = fopen("ale450_15c.col.txt", "w");
	if (fq == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}	
	for(i=0;i<n;i++)  
    	fprintf(fq,"Vertex[%d] : %d\n",i,x[i]);	
	int max=0;
	for(i=0;i<n;i++)
	{
		if(x[i]>max)
		max=x[i];
	}
	printf("\n max color %d\n",max);	
	clock_t toc=clock();	
	printf("\n\nElasped time in milliseconds = %f\n",1000*(toc-tic)/(double)(CLOCKS_PER_SEC));	
	free(x);
	free(g);	
	return 0;
}
