// Lab_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{   

	int summ=0, myid, i, j, root=0, *rbuff=0;
	const int n = 5, m = 5, k = 1;
	if (k >= m) cout << "Error";
	else
	{
		int gsize, msize, sendarray[m][n];
		MPI_Status status;
		MPI_Comm comm = MPI_COMM_WORLD;
		MPI_Init(&argc,&argv);
		MPI_Comm_size(comm, &gsize);
		MPI_Comm_rank(comm, &myid);
		    msize = gsize;
		if (myid == root) 
		{
			rbuff = new int[msize*m];
		}
		for (i = 0; i < n; ++i)
			for (j = 0; j < m; j++)
				sendarray[j][i] = myid + i;

//		MPI_Gather(sendarray[k],m,MPI_INT,rbuff,m,MPI_INT,root,comm);

		if (myid != root)
		{
			MPI_Send(&sendarray[k],n,MPI_INT,root,0,MPI_COMM_WORLD );
		}
		if (myid == root)
  		{	
			for (i = 0; i<msize; i++)
			{
				if (i != myid)
					MPI_Recv(&rbuff[n*i],n,MPI_INT,i,0, MPI_COMM_WORLD,&status);
				else
					for (int l = 0; l<n; l++)
						rbuff[n*i+l] = sendarray[k][l];
			}
			for (i = 0; i < msize*m; ++i)
			{
				if (i%m == 0) cout << "\n";
				cout<<rbuff[i] << " ";
			}

		}
    MPI_Finalize();
	}


}
