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
        int n=452;        
        float *matrix=malloc(sizeof(float)*n*n);
        float *visited=malloc(sizeof(float)*n);
        float *minimum=malloc(sizeof(float)*n);
        int *index=malloc(sizeof(int)*n);        
        int *path=malloc(sizeof(int)*n);        
        float *array=malloc(sizeof(float)*n);        
        int i,j,k,p,temp;
        int count=0;        
        FILE *fk = fopen("node452.txt", "r");
	if (fk == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fk,"%f",&matrix[i*n+j]);
		}
	}		
        for(i=0;i<n;i++)
        {
                visited[i]=0;
                minimum[i]=999999;
                index[i]=-1;
        }
        visited[0]=1;
       
	for(i=0;i<n;i++)
        array[i]=matrix[0*n+i];        
	FILE *fp;
      	char *source_str;
	size_t source_size;
	fp = fopen("dijkstragpu_kernel.cl", "r");
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
	if(clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_CPU,1,&device_id,&num_of_devices)!=CL_SUCCESS)
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
	kernel=clCreateKernel(program,"dijkstragpu",&err);
	cl_mem Matrix,Visited,Min,Index,Array,Path;
	Matrix=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(float)*n*n,NULL,&err);
        Visited=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(float)*n,NULL,&err);        
        Min=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(float)*n,NULL,&err);
        Index=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(int)*n,NULL,&err);
        Array=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(float)*n,NULL,&err);      
        Path=clCreateBuffer(context,CL_MEM_READ_WRITE,sizeof(int)*n,NULL,&err);      
        clEnqueueWriteBuffer(command_queue,Matrix,CL_TRUE,0,sizeof(float)*n*n,matrix,0,NULL,NULL);
        clEnqueueWriteBuffer(command_queue,Visited,CL_TRUE,0,sizeof(float)*n,visited,0,NULL,NULL);
        clEnqueueWriteBuffer(command_queue,Min,CL_TRUE,0,sizeof(float)*n,minimum,0,NULL,NULL);       
        clEnqueueWriteBuffer(command_queue,Index,CL_TRUE,0,sizeof(int)*n,index,0,NULL,NULL);        
        clEnqueueWriteBuffer(command_queue,Array,CL_TRUE,0,sizeof(float)*n,array,0,NULL,NULL);        
        clEnqueueWriteBuffer(command_queue,Path,CL_TRUE,0,sizeof(int)*n,path,0,NULL,NULL);        
        size_t globalsize[1];
	globalsize[0]=452;
        size_t localsize[1];
        localsize[0]=113;        
        clSetKernelArg(kernel,0,sizeof(cl_mem),&Matrix);
        clSetKernelArg(kernel,1,sizeof(cl_mem),&Visited);
        clSetKernelArg(kernel,2,sizeof(cl_mem),&Min);
        clSetKernelArg(kernel,3,sizeof(cl_mem),&Index);
        clSetKernelArg(kernel,4,sizeof(cl_mem),&Array);
        clSetKernelArg(kernel,5,sizeof(cl_mem),&Path);  
        clSetKernelArg(kernel,6,sizeof(float)*113,NULL);
        clSetKernelArg(kernel,7,sizeof(float)*113,NULL);       
        clock_t tic=clock();        
        clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,globalsize,localsize,0,NULL,&event);
	clock_t toc=clock();        
	clEnqueueReadBuffer(command_queue,Matrix,CL_TRUE,0,sizeof(float)*n*n,matrix,0,NULL,NULL);
        FILE *fq = fopen("gpuanswer452.txt", "w");
	if (fq == NULL)
	{
    		printf("Error opening file!\n");
    		return 0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fprintf(fq,"%f\n",matrix[i*n+j]);
		}
	}			          
	cl_ulong time_start, time_end;
        double total_time;
        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
        clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
        total_time = time_end - time_start;
        printf("\nExecution time in milliseconds = %0.3f ms\n", (total_time / 1000000.0) );                
        free(matrix);
        free(visited);
        free(minimum);        
        free(index);        
        free(array);        
        clReleaseMemObject(Matrix);
        clReleaseMemObject(Visited);  
        clReleaseMemObject(Min);      
        clReleaseMemObject(Index);        
        clReleaseMemObject(Array);        
        clReleaseProgram(program);        
        clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	return 0;
}	
