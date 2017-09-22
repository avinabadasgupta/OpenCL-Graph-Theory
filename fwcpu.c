#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int main()
{
	clock_t tic=clock();        
	srand(time(NULL));        
        int n=2048;        
        int *matrix=malloc(sizeof(int)*n*n);
        int i,j,k,p,temp;
        FILE *fk = fopen("node2048.txt", "r");
	if (fk == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fk,"%d",&matrix[i*n+j]);
		}
	}		
      	for(k=0;k<n;k++)
        {
                for(i=0;i<n;i++)
                {
                        for(j=0;j<n;j++)
                        {
                                if(matrix[i*n+k]+matrix[k*n+j]<matrix[i*n+j])
                                matrix[i*n+j]=matrix[i*n+k]+matrix[k*n+j];
                        }
                }
        }
        clock_t toc=clock();
        FILE *fq = fopen("answer2048.txt", "w");
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
        printf("elasped time in milliseconds = %f\n",2048*(toc-tic)/(double)(CLOCKS_PER_SEC));		
        free(matrix);
        return 0;
}
        
