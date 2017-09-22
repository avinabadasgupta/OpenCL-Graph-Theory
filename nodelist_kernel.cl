#define n 12000
__kernel void nlist(__global const int* x,__global const int* y,__global const int* rad,__global int* list)
{																		
	size_t i = get_global_id(0);														
        size_t l=get_local_id(0);        
        int k,j,count=0;
        int prad=rad[i];
        int px=x[i];
        int py=y[i];        
        int pn=n;        
        int pa,pb;
        int temp;                    
         for(j=0;j<pn;j++)
        {
                pa=px-x[j];
                pb=py-y[j];
                k=(pa*pa)+(pb*pb);
                if(k<=(prad*prad))
                {
                        list[i*n+count]=j;
                        count++;
                }
        }
}																																			
