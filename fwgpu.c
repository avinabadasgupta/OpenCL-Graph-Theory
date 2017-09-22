#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>
#include<time.h>
#include<math.h>
#define MAX_SOURCE_SIZE (0x100000)
int main()
{
	srand(time(NULL));        
        int n=1884;    
	int *matrix=malloc(sizeof(int)*n*n);
        int i,j,k,p,temp;
        FILE *fk = fopen("node1884.txt", "r");
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
       	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("kernel.cl", "r");
	if (!fp) 
        {
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
	if(clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_ALL,1,&device_id,&num_of_devices)!=CL_SUCCESS)
	{
		printf("Unable to get device\n");
		return 1;
	}
	cl_context context;
	cl_context_properties properties[3];
	cl_int err,event;
	properties[0]=CL_CONTEXT_PLATFORM;
	properties[1]=(cl_context_properties)platform_id;
	properties[2]=0;
	context=clCreateContext(properties,1,&device_id,NULL,NULL,&err);
	cl_command_queue command_queue;
	command_queue=clCreateCommandQueue(context,device_id,CL_QUEUE_PROFILING_ENABLE,&err);
        clFinish(command_queue);
	cl_program program;
	program = clCreateProgramWithSource(context, 1,(const char **)&source_str, (const size_t *)&source_size, &err);
	if(clBuildProgram(program,0,NULL,NULL,NULL,NULL)!=CL_SUCCESS)
	{
		printf("unable to build program\n");
		return 1;
	}
	cl_kernel kernel;
	kernel=clCreateKernel(program,"fwgpu",&err);
	cl_mem Matrix;
	Matrix=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(int)*n*n,NULL,&err);
        clEnqueueWriteBuffer(command_queue,Matrix,CL_TRUE,0,sizeof(int)*n*n,matrix,0,NULL,NULL);
        clSetKernelArg(kernel,0,sizeof(cl_mem),&Matrix);
        size_t globalsize[2];
	globalsize[0]=1884;
        globalsize[1]=1884;
        clock_t tic=clock();        
        clEnqueueNDRangeKernel(command_queue,kernel,2,NULL,globalsize,NULL,0,NULL,&event);
	clEnqueueReadBuffer(command_queue,Matrix,CL_TRUE,0,sizeof(int)*n*n,matrix,0,NULL,NULL);
        clWaitForEvents(1 , &event);
        clock_t toc=clock();        
        FILE *fq = fopen("gpuanswer1884.txt", "w");
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
	cl_ulong time_start, time_end;
        double total_time;
        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
        total_time = time_end - time_start;
        printf("\nExecution time in milliseconds = %0.3f ms\n", (total_time / 1000000.0) );        
        free(matrix);
        clReleaseMemObject(Matrix);
        clReleaseProgram(program);        
        clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	return 0;
}	
