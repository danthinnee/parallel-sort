#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

struct Section
        {
                int begin;
                int end;
                int dim;
                int numbers[];
        };
void split_merge(int[], int, int, int[]);
void merge(int[], int, int, int, int[]);
void populate_array(int[], int);
void duplicate_array(int[], int[], int);
void parallel_split(int, int, int[]);
void parallel_sort(struct Section);

int main() {
		int dimension = 16;
		int marray [dimension]; 
		int warray [dimension]; 
		
		populate_array(marray, dimension);
		// consider immediately populating two arrays using populate_array
		duplicate_array(marray, warray, dimension);
		
		parallel_split(2, dimension, marray);
		
		split_merge(marray, 0, dimension, warray);

		int x = 0;
		while(x < dimension) {
			cout << marray[x] << '\t';
			x++;
		}
		cout << '\n';	
		x = 0;
		while(x < dimension) {
                        cout << warray[x] << '\t';
                        x++;
                }
	}

void parallel_split(int nthreads, int dimension, int array[])
	{
		pthread_t sort_section[nthreads];
		
		struct Section *sections; 
		(*sections).dim = dimension;
		(*sections).numbers = array;
		for(int x=0; x<nthreads; x++){
			sections = malloc(sizeof(struct Section));
			(*sections).begin = dimension/nthreads * x;
			(*sections).end = dimension/nthreads *x + dimension/nthreads;
			pthread_create(&sort_section[x], NULL, parallel_sort, (void *) sections);
		}
		for(int x=0; x<nthreads; x++)
                        pthread_join(sort_section[x], NULL);

	}

void parallel_sort(struct Section sections)
	{
		cout << "PARALLEL SORT: " << sections.begin;
	}

void split_merge(int B[], int begin, int end, int A[]) 
	{
		if(end-begin < 2)
			return;
		int middle = (end + begin) / 2;

		split_merge(A, begin, middle, B);
		split_merge(A, middle, end, B);
		merge(B, begin, middle, end, A);
		
	}	

void merge(int A[], int begin, int middle, int end, int B[]) 
	{
		int i = begin, j = middle;

		for(int k = begin; k < end; k++){
			if(i < middle && (j >= end || A[i] <= A[j])) {
				B[k] = A[i];
				i = i+1;
			}
			else {
				B[k] = A[j];
				j = j+1;
			}
		}
	}

void populate_array(int A[], int dimension)
	{
	        // populate with random values
	        for(int i=0; i < dimension; i++){
			int n = rand() % 100;
			A[i] = n;
		}
	}

void duplicate_array(int A[], int B[], int dimension)
	{
		for(int i=0; i<dimension; i++)
			B[i] = A[i];	
	}
