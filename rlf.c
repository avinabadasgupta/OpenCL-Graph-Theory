#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main()
{
	int n=436;
	int *g=malloc(sizeof(int)*n*n);
	int *col=malloc(sizeof(int)*n);  	
	int *L=malloc(sizeof(int)*n);	
	int *deg=malloc(sizeof(int)*n);	
	int *cno=malloc(sizeof(int)*n);	
	int i,j,k,a,max,sum=0,color=1,flag=1,flag2=1,count,top=1,v;
	FILE *fp;
	fp=fopen("node436.txt","r");	
	if(fp!=NULL)
	{	
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{		
				fscanf(fp,"%d",&a);
				g[i*n+j]=a;				
			}
		}
	}
	fclose(fp);
	for(i=0;i<n;i++)
	{
		col[i]=0;
		L[i]=0;
		deg[i]=0;
	}
	while(flag==1)
	{
		printf("flag\n");		
		count=0;		
		for(i=0;i<n;i++)
		{
			if(col[i]==0)
			{
				L[count]=i;
				count++;
			}
		}
		while(flag2==1)
		{
			printf("flag2\n");			
			sum=0;			
			for(j=0;j<count;j++)
			{
				top=1;				
				for(k=0;k<n;k++)
				{
					if(g[L[j]*n+k]==1)
					{
						if(col[k]==0)
						{
							deg[L[j]]=top;
							top++;
						}
					}
				}
			}
			max=0;
			for(j=0;j<count;j++)
			{
				if(deg[L[j]]>max)
				{
					max=deg[L[j]];
					v=L[j];
				}
			}
			cno[v]=color;
			col[v]=1;
			for(j=0;j<count;j++)
			if(L[j]==v)
			L[j]=0;
			for(j=0;j<count;j++)
			{
				if(g[v*n+L[j]]==1)
				L[j]=0;
			}
			k=0;			
			for(j=0;j<count;j++)
			{
				if(L[j]!=0)
				{
					L[k]=L[j];
					k++;
					L[j]=0;
				}
			}			
			count=k;			
			for(j=0;j<count;j++)
			sum=sum+L[j];
			if(sum==0)
			flag2=0;
		}
		color++;
		flag2=1;
		sum=0;		
		for(j=0;j<n;j++)
		{
			sum=sum+col[j];
		}
		if(sum==n)
		flag=0;
	}
	for(i=0;i<n;i++)
	printf(" %d ",cno[i]);
	printf("\nMax color %d\n",color--);
	free(g);
	free(L);
	free(col);
	free(deg);
	free(cno);
	return 0;
}
	
			
		
		
			
					
				
				
		
		
	
	
