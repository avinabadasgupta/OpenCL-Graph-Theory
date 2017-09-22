#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>
#include<time.h>
#include<math.h>
#define MAX_SOURCE_SIZE (0x100000)
int main()
{
        int n=12000;	
        int i,j,q;
	int *xdata=malloc(sizeof(int)*n);
	int *ydata=malloc(sizeof(int)*n);
        int *radii=malloc(sizeof(int)*n);
        int *lister=malloc(sizeof(int)*n*n);
        srand(time(NULL));
        for(i=0;i<n;i++)
        {
                xdata[i]=rand()%100;
                ydata[i]=rand()%100;
                radii[i]=rand()%10;
        }	
        for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        lister[i*n+j]=-1;
        FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("nodelist_kernel.cl", "r");
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
	cl_kernel kernel;
	kernel=clCreateKernel(program,"nlist",&err);
	cl_mem x,y,rad,list;
	x=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int)*n,NULL,&err);
	y=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int)*n,NULL,&err);	
        list=clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(int)*n*n,NULL,&err);
        rad=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int)*n,NULL,&err);	
        clEnqueueWriteBuffer(command_queue,x,CL_TRUE,0,sizeof(int)*n,xdata,0,NULL,NULL);
        clEnqueueWriteBuffer(command_queue,y,CL_TRUE,0,sizeof(int)*n,ydata,0,NULL,NULL);
        clEnqueueWriteBuffer(command_queue,rad,CL_TRUE,0,sizeof(int)*n,radii,0,NULL,NULL);
        clEnqueueWriteBuffer(command_queue,list,CL_TRUE,0,sizeof(int)*n*n,lister,0,NULL,NULL);
	clSetKernelArg(kernel,0,sizeof(cl_mem),&x);
	clSetKernelArg(kernel,1,sizeof(cl_mem),&y);
        clSetKernelArg(kernel,2,sizeof(cl_mem),&rad);
        clSetKernelArg(kernel,3,sizeof(cl_mem),&list);
        size_t globalsize[1];
	globalsize[0]=n;
        size_t localsize[1];
        localsize[0]=3000;
        clock_t tic=clock();		
        clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,globalsize,localsize,0,NULL,NULL);
	clFinish(command_queue);	
        clEnqueueReadBuffer(command_queue,list,CL_TRUE,0,sizeof(int)*n*n,lister,0,NULL,NULL);
	clock_t toc=clock();	
	/*for(i=0;i<n;i++)
	{
                printf("\n%d -> ",i);		
                for(j=0;j<n;j++)
		{
                        if(lister[i*n+j]==-1)
                        break;
                        else
                        printf(" %d ",lister[i*n+j]);
                }
        }*/
        printf("elasped time = %f\n",(toc-tic)/(double)(CLOCKS_PER_SEC));		
        free(xdata);
        free(ydata);
        free(radii);
        free(lister);
	clReleaseMemObject(x);
	clReleaseMemObject(y);
        clReleaseMemObject(rad);
        clReleaseMemObject(list);			
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	return 0;
}	
