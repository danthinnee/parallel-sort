/*	Merge sort, sequential
 *	Elisa Danthinne, under the direction of Dr. Kaeli
 *	17 December 2016
 *
 *	uses recursion and merge sort techniques to sort an array of 'dimension' elements
 *
 * */


#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

void split_merge(int[], int, int, int[]);
void merge(int[], int, int, int, int[]);
void populate_array(int[], int);
void duplicate_array(int[], int[], int);
int array_size(int[]);

int main() {
		int dimension = 1024;
		int marray [dimension]; 
		int warray [dimension]; 
		
		populate_array(marray, dimension);
	
		duplicate_array(marray, warray, dimension);
		
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
			cout << n << '\n';
			A[i] = n;//rand() % 100;
		}
	}

void duplicate_array(int A[], int B[], int dimension)
	{
		for(int i=0; i<dimension; i++)
			B[i] = A[i];	
	}

int array_size(int array[])
	{
		return sizeof((array));
	}
