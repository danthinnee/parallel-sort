/*	Merge Sort using pthreads
 *	Elisa Danthinne, under direction of Dr. Kaeli
 *	17 December 2016
 *
 * 	sorts a randomly populated (0-99) matrix of size 'dimension' using 'nthreads' pthreads and merge sort techniques
 * 	uses recursion
 * 	*please note: number of elements in the matrix must be divisible by both 2 and by the number of pthreads used
 *
 * */

#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

const int dimension = 1024;
int marray[dimension];
int warray[dimension];
int nthreads = 8;

void split_merge(int[], int, int, int[]);
void merge(int[], int, int, int, int[]);
void populate_array(int[], int);
void duplicate_array(int[], int[], int);
void parallel_sort();
void *parallel_sort_section(void *);
//void paralle_merge_section();

int main() {
		populate_array(marray, dimension);
		// consider immediately populating two arrays using populate_array
		duplicate_array(marray, warray, dimension);
		int x = 0;
                cout << '\n' << "MARRAY: " << '\n';
                while(x < dimension) {
                        cout << marray[x] << '\t';
                        x++;
                }
                cout << '\n' << "WARRAY:"<< '\n';
                x = 0;
                while(x < dimension) {
                        cout << warray[x] << '\t';
                        x++;
                }


		parallel_sort();
	
		x = 0;
		cout << '\n' << "MARRAY: " << '\n';
		while(x < dimension) {
			cout << marray[x] << '\t';
			x++;
		}
		cout << '\n' << "WARRAY:"<< '\n';	
		x = 0;
		while(x < dimension) {
                        cout << warray[x] << '\t';
                        x++;
                }
	}

void parallel_sort()
	{
		pthread_t sort_section[nthreads];

                for(int x=0; x<nthreads; x++){
                        pthread_create(&sort_section[x], NULL, parallel_sort_section, (void *) x);
                }

                for(int x=0; x<nthreads; x++){
                        pthread_join(sort_section[x], NULL);
                }
		
		
		int sections = nthreads;
		int size = dimension/nthreads;
		while(sections > 1){

			for(int i=0; i < (sections / 2); i++){
				int begin = i*(2*size);
				int middle = i*2*size + size;
				int end = middle + size;
				cout << begin << '\t' << middle << '\t' << end << '\n';
				merge(warray, begin, middle, end, marray);
			}
			for(int i=0; i<dimension; i++){
                                warray[i] = marray[i];
                        }


			size = 2*size;
			sections = sections / 2;
		}

	}

void *parallel_sort_section(void *x)
	{
		long n = (long) x;
		int size = dimension/nthreads;
		int begin = n * size;
		int section[size];//int *section = marray + begin;
		int end = begin + size;
		int wsection[size];
		
		int j=0;
		for(int i=begin; i<end; i++){
			section[j] = warray[i];
			j++;
		}

		duplicate_array(section, wsection, size);
		split_merge(section, 0, size, wsection);

		j=0;
		for(int i=begin; i<end; i++){
			warray[i] = wsection[j];
			j++;
		}
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

			A[i] = n;//rand() % 100;
		}
	}

void duplicate_array(int A[], int B[], int dimension)
	{
		for(int i=0; i<dimension; i++)
			B[i] = A[i];	
	}
