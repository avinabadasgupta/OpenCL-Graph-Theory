#define n 1024
#define source 0
__kernel void bfsgpu(__global const int* Matrix,__global int* Head,__global int* Visited)
{
	#pragma OPENCL EXTENSION cl_khr_fp64 : enable        
        size_t id=get_global_id(0);       
        size_t lid=get_local_id(0);
        size_t ls=get_local_size(0);
        size_t gid=get_group_id(0);
        size_t gs=get_global_size(0);
	__private int i,j,s=0,k=0,count=0,sum=0;
	__private int queue[1024];	
	if(id==0)
	{
		for(i=0;i<n;i++)
		queue[i]=0;		
		while(count<1024)
        	{
			for(i=0;i<n;i++)
                	{
                        	if(Matrix[s*n+i]==1)
                        	{
                                	if(Visited[i]==0)
                                	{
                                        	queue[k]=i;
						k++;                                        
						Visited[i]=1;
                                        	Head[count]=i;
                                        	count++;
                                	}
                        	}
                	}
                	s=queue[0];
			for(j=1;j<=n;j++)
			queue[j-1]=queue[j];
			k--;
               	}
	}
}
