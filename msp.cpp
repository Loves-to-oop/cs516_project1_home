#include <omp.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <assert.h>
#include <thread>
#include <chrono>

// create an array of length size of random numbers
// returns a pointer to the array


void merge(int *array, int beginning, int middle, int end)
{

	//#pragma omp critical
	//	std::cout << "beginning: " << beginning << ", middle: " << middle << ", end: " << end << "\n";

	int left_array_size = middle - (beginning - 1);
	int right_array_size = end - middle;

	int left_array[left_array_size];
	int right_array[right_array_size];


	//std::cout << left_array_size << ", " << right_array_size << "\n"; 

	//#pragma omp critical
	
//#pragma omp parallel for
	for(int i = 0; i <= left_array_size - 1; i++)
	{
		//#pragma omp critical
		left_array[i] = array[beginning + i];

	}//end for i

//#pragma omp parallel for
	//#pragma omp critical
//#pragma omp parallel for
	for(int i = 0; i <= right_array_size - 1; i ++)
	{
		//#pragma omp critical
		right_array[i] = array[middle + 1 + i];

	}//end for i

	int j = 0;// right array index

	int k = 0;// left array index

	//int sub_array_size = (end - beginning);


//#pragma omp parallel for
	for(int i = beginning; i <= end; i ++)
	{

		//right and left array are sorted.

		if(j <= right_array_size - 1 && k <= left_array_size - 1)
		{

			if(right_array[j] < left_array[k])
			{


				array[i] = right_array[j];

				j ++;

			}//end if
			else
			{


				array[i] = left_array[k];

				k++;


			}//end else
		}//end if
		else if(j <= right_array_size - 1)
		{


			array[i] = right_array[j];

			j ++;

		}
		else if(k <= left_array_size - 1)
		{

			array[i] = left_array[k];

			k ++;


		}//end if



	}//end for i


}//end function


void print_out_array(int *array, int size)
{

	std::cout << array << ": ";

	for(int i = 0; i <= size - 1; i ++)
	{




		std::cout << array[i] << ", ";





	}//end for i

	std::cout << "\n";


}//end function

void mergesort(int * array, int beginning, int end)
{



	//#pragma omp critical
	//	std::cout << "thread: " << omp_get_thread_num() << "\n";


	//std::cout << "thread: " << omp_get_thread_num() << "\n";

	if(beginning < end)
	{

		int middle = (beginning + end) / 2;

		//#pragma omp parallel
		//		{

		//#pragma omp task
		//#pragma omp single			
		mergesort(array, beginning, middle);

		//#pragma omp task
		//#pragma omp single
		mergesort(array, middle + 1, end);

		//		}//end parallel

#pragma omp critical
		merge(array, beginning, middle, end);

	}//end if


}//end function



// seed: seeds the random number generator
int * randNumArray( const int size, const int seed ) {
	srand( seed );
	int * array = new int[ size ];
	for( int i = 0; i < size; i ++ ) {
		array[i] = std::rand() % 1000000;
	}
	return array; }




void unit_test_sort() 
{
	for(int i = 10; i <= 100; i ++)
	{

		std::cout << "i: " << i << "\n";

		for(int j = 0; j <= 1000; j ++)
		{
			std::cout << j << ", ";
			int * array = randNumArray( i, j );

			int array2[i];// = new int[i];

			for(int k = 0; k <= i - 1; k ++)
			{

				array2[k] = array[k];

			}//end for k



#pragma omp parallel
			mergesort(array, 0, i - 1);

			//print_out_array(array2, i);

			//print_out_array(array, i);

			//std::cout << "\n";

			for(int k = 0; k <= i - 1; k ++)
			{

				bool number_in_sorted_array = false;

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
				assert(array[k] >= array[k - 1]);

				//assert(array[k] != array[k - 1]);
				//	std::cout << "array[" << k << "] = " << array[k] << " > " << array[k - 1] << "\n"; 

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


	unsigned CPUs = std::thread::hardware_concurrency();

	int threads = 0;

	if(CPUs == 44)
	{

		threads = 2;

	}
	else
	{
		threads = CPUs;
	}
	omp_set_num_threads(threads);


	//std::cout << "threads: " << threads << ", CPUs: " << CPUs << "\n";

	//omp_set_num_threads(16);

//	unit_test_sort();

	//void mergesort(int * array, int beginning, int end)


	//unit_test_sort();


	//print_out_array(array, size);


	auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel
	mergesort(array, 0, size - 1);
	//		print_out_array(array, size);


	auto finish = std::chrono::high_resolution_clock::now();

	int duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

	
	   //std::cout << "merge sorted array\n";

	   for(int i = 0; i <= size - 1; i ++)
	   {

	   std::cout << array[i] << ", ";

	   }//end for i

	   std::cout << "\n";
	   
	   std::cout << duration << "ns\n";

	// delete the heap memory
	delete [] array;
}//end main

