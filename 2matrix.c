#include<omp.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int nthread,tid;
	int m,n,p,q,z,k=2;
	double t,s;
	printf("Enter the matrix size of matrix A : ");
	scanf("%d%d",&m,&n);
	printf("Enter the matrix size of matrix B : ");
	scanf("%d%d",&p,&q);
	if(n!=p)
	{
		printf("Wrong size\n");
		return 0;
	}
	int a[m][n],b[p][q],c[m][q];
	
	
	z=0;
	for(k=1;k<=8;k=pow(2,z))
	{
		t=omp_get_wtime();
	
		#pragma omp numthreads(k)
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{
				a[i][j]=i+j;
			}
		}


		#pragma omp numthreads(k)
		for(int i=0;i<p;i++)
		{
			for(int j=0;j<q;j++)
			{
				b[i][j]=i+j;
			}
		}
		#pragma omp numthreads(k)
		for(int i=0;i<m;i++)
			for(int j=0;j<q;j++)
				c[i][j]=0;
			

		#pragma omp numthreads(k)
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<q;j++)
			{
				for(int k=0;k<n;k++)
				{
					c[i][j]+=(a[i][k]*b[k][j]);
				}
			}
		}

		s=omp_get_wtime()-t;

		z++;
		printf("\n");
		printf("numthreads:%d -------->time:%lf\n",k,s);
	}

	return 0;
}
