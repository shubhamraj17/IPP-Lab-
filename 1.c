#include<omp.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

void generate_list(int * x, int n)
{
	int i,j,t;
	for (i = 0; i < n; i++)
		x[i]=n-i;
}

void print_list(int * x, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("%d ",x[i]);
	} 
}

void merge(int * X, int n, int * tmp)
{
	int i = 0;
	int j = n/2;
	int ti = 0;
	
	while (i<n/2 && j<n)
	{
		if (X[i] < X[j])
		{
			tmp[ti] = X[i];
			ti++;
			i++;
		}
		else
		{
			tmp[ti] = X[j];
			ti++;
			j++;
		}
	}
	while(i<n/2)
	{ /* finish up lower half */
		tmp[ti] = X[i];
		ti++;
		i++;
	}
	while(j<n)
	{ /* finish up upper half */
		tmp[ti] = X[j];
		ti++;
		j++;
	}
	memcpy(X, tmp, n*sizeof(int));
}

void mergesort(int * X, int n, int * tmp)
{
	if (n < 2)
		return;

	#pragma omp task firstprivate (X, n, tmp)
	mergesort(X, n/2, tmp);

	#pragma omp task firstprivate (X, n, tmp)
	mergesort(X+(n/2), n-(n/2), tmp);
 
	#pragma omp taskwait
	merge(X, n, tmp);
}

int main()
{
	int n,k,z;
	double s,t;
	int data[1000], tmp[1000];
	
	printf("Enter the number of elements : ");
	scanf("%d",&n);
	generate_list(data, n);
	
	z=0;
	for(k=1;k<=8;k=pow(2,z))
	{
		t=omp_get_wtime();
		#pragma omp parallel sections num_threads(k)
		{
			#pragma omp section
				mergesort(data, n, tmp);
		}
		s=omp_get_wtime()-t;
		
		z++;
		printf("\n");
		printf("numthreads:%d -------->time:%lf\n",k,s);
	}
}

