__kernel void fwgpu(__global int* Matrix)
{
       	size_t idx=get_global_id(0);
        size_t idy=get_global_id(1);
	size_t gs=get_global_size(0);        
	int k,i,j;
	if(idx==0 && idy==0)
	{        
	for(k=0;k<gs;k++)
        {
                for(i=0;i<gs;i++)
                {
                        for(j=0;j<gs;j++)
                        {
                                if(Matrix[i*gs+k]+Matrix[k*gs+j]<Matrix[i*gs+j])
                                Matrix[i*gs+j]=Matrix[i*gs+k]+Matrix[k*gs+j];
                        }
                }
        }
	}
}
      
        
