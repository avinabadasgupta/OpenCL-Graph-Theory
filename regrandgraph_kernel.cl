__kernel void regrandgraph(__global const int* List,__global int* Count,__global int* Matrix,__local int *temp)
{																		
	size_t i=get_global_id(0);														
        size_t j=get_local_id(0);
        size_t bx=get_local_size(0);        
        size_t gx=get_group_id(0);        
        temp[i]=List[i];
        barrier(CLK_GLOBAL_MEM_FENCE);       
        int p,m,t,x,y,a,b;
        int k=256;        
        if(j==0)
        {        
                m=bx*gx;                 
                for(p=m;p<m+k-1;p++)
                {
                        for(t=p+1;t<m+k;t++)
                        {
                                x=temp[p]*k+Count[temp[p]];
                                y=temp[t]*k+Count[temp[t]];
                                Matrix[x]=temp[t];
                                Matrix[y]=temp[p];
                                Count[temp[p]]++;
                                Count[temp[t]]++;
                        }
                }
       }
}       
      
        
