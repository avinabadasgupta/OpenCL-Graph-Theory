__kernel void gcgpu(__global int* Matrix,__global int* X)
{
        #pragma OPENCL EXTENSION cl_khr_fp64 : enable        
        size_t id=get_global_id(0);       
        //size_t lid=get_local_id(0);
        //size_t ls=get_local_size(0);
        //size_t gid=get_group_id(0);
        size_t gs=get_global_size(0);
     	__private int i,j,k;   
	if(id==0)
	{
		for(i=0;i<gs;i++)
		{
			X[i]=1;  
   			for(k=0;k<i;k++)
			{ 
     				if(Matrix[k*gs+i]!=0 && X[i]==X[k])  
       				X[i]=X[k]+1;
			} 
   		}
	}
}	    	
