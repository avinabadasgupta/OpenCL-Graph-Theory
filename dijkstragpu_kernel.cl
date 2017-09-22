__kernel void dijkstragpu(__global float* Matrix,__global float* Visited,__global float* Min,__global int* Index,__global float* Array,__global int* Path,__local float* lmat,__local float* larr)
{
        #pragma OPENCL EXTENSION cl_khr_fp64 : enable        
        size_t id=get_global_id(0);       
        size_t lid=get_local_id(0);
        size_t ls=get_local_size(0);
        size_t gid=get_group_id(0);
        size_t gs=get_global_size(0);
        __private float min,mid;        
      	__private int i,j,index;     
	if(id==0)
	{	
		for(j=0;j<gs;j++)
        	{        
                	min=999999;                
                	for(i=0;i<gs;i++)
                	{
                        	if(Visited[i]==0)
                        	{                
                                	if(Matrix[0*gs+i]<min)
                                	{
                                        	min=Matrix[0*gs+i];
                                        	index=i;
                                	}
                        	}
                	}
                	Visited[index]=1;
                	for(i=0;i<gs;i++)
                	{
                        	if(Matrix[0*gs+i]>Matrix[0*gs+index]+Matrix[index*gs+i])
                        	{
                                	Matrix[0*gs+i]=Matrix[0*gs+index]+Matrix[index*gs+i];
                        	}
                	}
        	}
	}
}
        
