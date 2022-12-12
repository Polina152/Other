// Lab_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
#include <iostream>
using namespace std;

void f1(double* A, int N)
{
	for (int i = 0; i < N*N; i++)
		A[i] = 1;
}
void f(double* a, double* b, int N, int k, int myrank, int m, int start)
{
	for (int i = 0; i<m; i++)
	{
		int str = start+i;
		for (int j = 0; j < N; j++)
		{
			b[i*N+j] = 0;
			for (int k = 0; k < N; k++)
			{
				b[i*N+j] += a[str+k]*a[k*N+j];
			}
		b[i*N+j] *= k;
		}
	}
}
double f_p(double*a, int N, int myrank, int m, int start)
{
	double p = 1, s=0;

	for (int i = 0; i<m; i++)
	{
		int str = start+i*N;
		p=1;
		for (int j = 0; j < N; j++)
		{
			p*=a[str+j];
		}
		s+=p;
	}
	return s;
}
void f2(double* A, int N)
{
	for (int i = 0; i < N*N; i++)
	{
		if (i%N==0) cout << "\n";
		cout << A[i] << " ";
	}
}

int main(int argc,char *argv[])
{ 
  int myrank, size,m;
  int *sendcounts=0, *displs=0;
  double *A=0,*B=0;   // входной и выходной массив  
  int     N;          // размер массивовов
  double *a=0,*b=0;   // части массивов для каждого процесса  
  double *p, k=0;		  // произведения и сумма произведений
  double t1, t2;

   MPI_Init( &argc, &argv ); 
   MPI_Comm_rank( MPI_COMM_WORLD, &myrank ); 
   MPI_Comm_size( MPI_COMM_WORLD, &size ); 
   if (myrank == 0) 
     {cout<<"Vvedite N ";   cin>>N; t1 = MPI_Wtime();}
   MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);

	   A = new double[N*N];  // для входного 
	   p = new double[size];
	  if (myrank == 0)
	  {
		B = new double[N*N];  // и выходного массивов
	  }

       // определения количества строк для каждого процесса
//	if (N%size==0)
//{
	m = N/size+ (N%(size)>(myrank)?1:0); 
    sendcounts = new int[size];
	m *= N;
	MPI_Allgather(&m,1,MPI_INT,sendcounts,1,MPI_INT, MPI_COMM_WORLD);
	m /= N;
	displs =  new int[size];  // заполнение массива displs
    displs[0] = 0;
    for (int i = 1;i<size; ++i)
       displs[i] = displs[i-1] + sendcounts[i-1]; 

	b = new double[N*m];  
    if (myrank == 0)
	{
        f1(A,N);   // заполнение исходной матрицы А
	}
	MPI_Bcast(A,N*N,MPI_DOUBLE,0,MPI_COMM_WORLD); //Рассылка матрицы А
	double s = 0;
	s = f_p(A,N,myrank,m,displs[myrank]);
	MPI_Gather(&s, 1, MPI_DOUBLE, p, 1,  MPI_DOUBLE, 0, MPI_COMM_WORLD );
	if(myrank == 0)
		for (int i = 0; i < size; i++)
			k += p[i];
	MPI_Bcast(&k,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

   f(A,b,N,k,myrank, m, displs[myrank]);   // основная функция обработки
   MPI_Gatherv(b, N*m, MPI_DOUBLE, B, sendcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD );
                    // сбор результатов в корневой процесс
   if (myrank == 0) 
   {
       f2(B,N);// вывод результата
	   t2 = MPI_Wtime();
	   cout << "\n time is " << t2-t1;
   }
//} 
//	else cout << "N % size = " << N % size << " != 0\n"; 
    MPI_Finalize();
}

