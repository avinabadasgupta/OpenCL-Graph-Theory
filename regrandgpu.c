#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>
#include<time.h>
#include<math.h>
#define MAX_SOURCE_SIZE (0x100000)
int main()
{
        int n=1024,d=256;	
        int i,j,k,p,temp;
	int *list=malloc(sizeof(int)*n);
	int *count=malloc(sizeof(int)*n);
        int *matrix=malloc(sizeof(int)*(n*d));
        srand(time(NULL));
        for(i=0;i<n;i++)
        for(j=0;j<d;j++)
        matrix[i*d+j]=-1;
        for(i=0;i<n;i++)
        {
                list[i]=i;
                count[i]=0;
        }
        for (j=n-1;j>0;j--)
        {
                p=rand()%(j+1);
                temp=list[j];
                list[j]=list[p];
                list[p]=temp;
        }        
        FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("regrandgraph_kernel.cl", "r");
	if (!fp) {
	fprintf(stderr, "Failed to load kernel.\n");
	exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp );
	cl_platform_id platform_id;
	cl_uint num_of_platforms;
	if(clGetPlatformIDs(1,&platform_id,&num_of_platforms)!=CL_SUCCESS)
	{	
		printf("Unable to get Platform\n");
		return 1;
	}
	cl_device_id device_id;
	cl_uint num_of_devices;
	if(clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_CPU,1,&device_id,&num_of_devices)!=CL_SUCCESS)
	{
		printf("Unable to get device\n");
		return 1;
	}
	cl_context context;
	cl_context_properties properties[3];
	cl_int err;
	properties[0]=CL_CONTEXT_PLATFORM;
	properties[1]=(cl_context_properties)platform_id;
	properties[2]=0;
	context=clCreateContext(properties,1,&device_id,NULL,NULL,&err);
	cl_command_queue command_queue;
	command_queue=clCreateCommandQueue(context,device_id,0,&err);
	cl_program program;
	program = clCreateProgramWithSource(context, 1,(const char **)&source_str, (const size_t *)&source_size, &err);
	if(clBuildProgram(program,0,NULL,NULL,NULL,NULL)!=CL_SUCCESS)
	{
		printf("unable to build program\n");
		return 1;
	}
        size_t globalsize[1];
	globalsize[0]=n;
        size_t localsize[1];
	localsize[0]=256; 	
        cl_kernel kernel;
	kernel=clCreateKernel(program,"regrandgraph",&err);
	cl_mem List,Matrix,Count;
	List=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int)*n,NULL,&err);
	Count=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(int)*n,NULL,&err);	
        Matrix=clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(int)*n*d,NULL,&err);
        clEnqueueWriteBuffer(command_queue,List,CL_TRUE,0,sizeof(int)*n,list,0,NULL,NULL);
        clEnqueueWriteBuffer(command_queue,Count,CL_TRUE,0,sizeof(int)*n,count,0,NULL,NULL);
        clEnqueueWriteBuffer(command_queue,Matrix,CL_TRUE,0,sizeof(int)*n*d,matrix,0,NULL,NULL);
	clSetKernelArg(kernel,0,sizeof(cl_mem),&List);
	clSetKernelArg(kernel,1,sizeof(cl_mem),&Count);
        clSetKernelArg(kernel,2,sizeof(cl_mem),&Matrix);
        clSetKernelArg(kernel,3,sizeof(cl_int)*localsize[0],NULL);
        clock_t tic=clock();	        
        clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,globalsize,localsize,0,NULL,NULL);
	clFinish(command_queue);	
        clock_t toc=clock();        
        clEnqueueReadBuffer(command_queue,Count,CL_TRUE,0,sizeof(int)*n,count,0,NULL,NULL);
	for(i=0;i<n;i++)
	{
                printf("\n%d -> ",i);		
                for(j=0;j<n;j++)
		{
                        if(matrix[i*n+j]==1)
                        printf("%d ",j);
                }
                printf("\n\n");
        }
        for(i=0;i<n;i++)
        printf("%d",count[i]);
        printf("elasped time = %f\n",(toc-tic)/(double)(CLOCKS_PER_SEC));		
        free(list);
        free(count);
        free(matrix);
        clReleaseMemObject(List);
	clReleaseMemObject(Count);
        clReleaseMemObject(Matrix);
        clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	return 0;
}	
