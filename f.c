#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
int main()
{
	int n=2048;	
	int *matrix=malloc(sizeof(int)*n*n);
	int i,j,p;
	for(i=0;i<n;i++)
        {
                for(j=0;j<n;j++)
                {
                        if(i==j)
                        matrix[i*n+j]=0;
                        else
                        matrix[i*n+j]=999999;
                }
        }
	for(i=0;i<n;i++)
        {
                for(j=0;j<n;j++)
                {
                        if(i!=j)
                        {                                
                                if(matrix[i*n+j]==999999)
				{
					p=rand()%(2048)+1;                                
                                	matrix[i*n+j]=p;
					matrix[j*n+i]=p;
				}
                        }
                }
        }	
	FILE *fp = fopen("node2048.txt", "w");
	if (fp == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fprintf(fp,"%d\n",matrix[i*n+j]);
		}
	}			
	fclose(fp);
	free(matrix);
	return 0;
}
