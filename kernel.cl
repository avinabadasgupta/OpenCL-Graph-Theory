__kernel void mstgpu(__global int* Matrix,__global int* Visited,__global int* X,__global int* Y,__global int* Z)
{
        #pragma OPENCL EXTENSION cl_khr_fp64 : enable        
        size_t id=get_global_id(0);       
        size_t lid=get_local_id(0);
        size_t ls=get_local_size(0);
        size_t gid=get_group_id(0);
        size_t gs=get_global_size(0);
     	__private int a,b,u,v,i,j,ne=1,min,mincost=0;   
	if(id==0)
	{	
		while(ne < gs)
		{
			for(i=0,min=999999;i<gs;i++)
			for(j=0;j<gs;j++)
			if(Matrix[i*gs+j]< min)
			if(Visited[i]!=0)
			{
				min=Matrix[i*gs+j];
				a=u=i;
				b=v=j;
			}
			if((Visited[u]==0) || (Visited[v]==0))
			{
				//printf("Edge %d:(%d %d) cost:%d\n",ne++,a,b,min);			
				X[ne]=a;
				Y[ne]=b;
				Z[ne]=min;				
				ne++;				
				mincost=mincost+min;
				Visited[b]=1;
			}
			Matrix[a*gs+b]=Matrix[b*gs+a]=999999;
			
		}			
		X[0]=mincost;
	}
}
