#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <assert.h>
#include <omp.h>


// create an array of length size of random numbers
// returns a pointer to the array


// seed: seeds the random number generator
int * randNumArray( const int size, const int seed ) {
	srand( seed );
	int * array = new int[ size ];
	for( int i = 0; i < size; i ++ ) {
		array[i] = std::rand() % 1000000;
	}
	return array; }

void swap(int * array, int index1, int index2)
{

	int c = array[index1];

	array[index1] = array[index2];

	array[index2] = c;


}//end function


int partition(int *array, int p, int r)
{

	int i = 0;
	//int tid = omp_get_thread_num();
	//#pragma omp critical
	{



		//}//end critical



		//			long tid = omp_get_thread_num();


		//#pragma omp critical
		//	std::cout << p << " and " << r << ", tid: " << tid << "\n";


	/* 
	 *:
	 *Array is declared outside of scope of multithreaded area
	 so is shared between threads.

	 Array is declared outside of scope of multithreaded area shared between threads..
	 *
	 * */


	int x = 0;

	//#pragma omp critical
	{
		x = array[r];
	}//end critical

	i = p - 1;

	for(int j = p; j <= r - 1; j ++)
	{

		int less_than_or_equals = 0;

		//#pragma omp critical
		{


			if(array[j] <= x)
			{

				i = i + 1;


				//		#pragma omp critical
				{
					swap(array, i, j);

				}//end critical

			}//end if


		}//end critical

	}//end for j

	//#pragma omp critical
	{
		swap(array, (i + 1), r);
	}//end critical


}//end critical
return i + 1;



}//end function

void quick_sort(int *array, int p, int r)
{

//#pragma omp critical
//	std::cout << "thread: " << omp_get_thread_num() << "\n";

	int q = 0;


	if(p < r)
	{

		/* 
		 *
		 *Works if you make the entire partition section critical.
		 *
		 * */

		#pragma omp critical
		q = partition(array, p, r);

#pragma omp task
		{

			//			long tid = omp_get_thread_num();

			//		std::cout << "first quick sort, tid: " << tid << "\n";

			quick_sort(array, p, q - 1);
		}//end parallel

#pragma omp task
		{

			//			long tid = omp_get_thread_num();

			//		std::cout << "second quick sort, tid: " << tid << "\n";


			quick_sort(array, q + 1, r);
		}//end parallel

	}//end if
}//end function


void unit_test_quick_sort() 
{
	for(int i = 10; i <= 20; i ++)
	{

		std::cout << "i: " << i << "\n";

		for(int j = 0; j <= 1000; j ++)
		{
			std::cout << j << ", ";
			int * array = randNumArray( i, i );

			int array2[i];// = new int[i];

			for(int k = 0; k <= i - 1; k ++)
			{

				array2[k] = array[k];

			}//end for k

			quick_sort(array, 0, i - 1);

			for(int k = 0; k <= i - 1; k ++)
			{

				bool number_in_sorted_array = false;
//array[3] = 0;
				for(int z = 0; z <= i - 1; z ++)
				{

					if(array2[k] == array[z])
					{

						number_in_sorted_array = true;

					}//end if


				}//end for z

				assert(number_in_sorted_array == true);

			}//end for k


			for(int k = 1; k <= i - 1; k ++)
			{
				//array[k] = 0;
				assert(array[k] > array[k - 1]);

				//				std::cout << "array[" << k << "] = " << array[k] << " > " << array[k - 1]; 

				//				std::cout << "\n";

			}//end for k

		}//end for j




	}//end for i

}//end function



int main( int argc, char** argv ) {
	int * array; // the poitner to the array of rands
	int size, seed; // values for the size of the array
	// and the seed for generating
	// random numbers
	// check the command line args
	if( argc < 3 ){
		std::cerr << "usage: "
			<< argv[0]
			<< " [amount of random nums to generate] [seed value for rand]" << std::endl;
		exit( -1 ); }
	// convert cstrings to ints
	{
		std::stringstream ss1( argv[1] );
		ss1 >> size;
	} {
		std::stringstream ss1( argv[2] );
		ss1 >> seed; }
	// get the random numbers
	array = randNumArray( size, seed );
	// **************************
	// **************************
	// **************************
	//
	//  YOUR CODE HERE !!!
	//
	// **************************
	// **************************
	// **************************

	unit_test_quick_sort();

	auto start = std::chrono::high_resolution_clock::now();


	//	omp_set_num_threads( 2 );


	omp_set_num_threads(44);

#pragma omp parallel

	quick_sort(array, 0, size - 1);

	auto finish = std::chrono::high_resolution_clock::now();

	int duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

//	std::cout << "duration: " << duration << " nanoseconds\n";


	std:: cout << "sort results: \n";

	for(int i = 0; i <= size - 1; i ++)
	{

		std::cout << array[i] << ", ";

	}//end for i

	std::cout << "\n";


	// delete the heap memory
	delete [] array;
}

