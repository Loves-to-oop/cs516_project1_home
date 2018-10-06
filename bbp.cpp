#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <omp.h>
#include <chrono>
#include <thread>
#include <assert.h>

//auto start = std::chrono::high_resolution_clock::now();


// seed: seeds the random number generator
int * randNumArray( const int size, const int seed ) {
	srand( seed );
	int * array = new int[ size ];
	for( int i = 0; i < size; i ++ ) {
		array[i] = std::rand() % 1000000;
	}
	return array; }// end function

void swap(int *array, int a, int b)
{

	//std::cout << "swap: " << array[a] << " and " << array[b];

	int c = array[a];

	array[a] = array[b];

	array[b] = c;

	//std::cout << ", after: " << array[a] << ", " << array[b] << "\n";

}//end function

void print_out_array(int *array, int size);

int test_sort(int *array, int size)
{

	int fails = 0;

	for(int i = 1; i <= size - 1; i ++)
	{

		if(array[i] < array[i - 1])
		{

			fails ++;

		}//end if


	}//end for i


	return fails;

}//end function


int bubble_sort(int *array, omp_lock_t mutex,  int size)
{


	//omp_lock_t mutex;

	//	std::cout << "size of array: " << size << "\n";

	//	std::cout << "before, ";

	//	print_out_array(array, size);


	//int i = 0;

	//#pragma omp parallel for
	for(int i = 0; i <= size - 1; i ++)
	{
#pragma omp task
		{
			//std::cout << "i: " << i << "\n";

			//	std::cout << "fraction: " << fraction << "\n";
			//#pragma omp critical
			//			std::cout << "thread: " << omp_get_thread_num() << "\n";

			//#pragma omp parallel for
			for(int j = 1; j <= size - 1; j ++)
			{


				//#pragma omp task
				{
					//std::cout << "j: " << j << "\n";

					//	std::cout << "fraction: " << fraction << "\n";


#pragma omp critical	
					if(array[j - 1] > array[j])
					{

						//swap


						//#pragma omp critical
						{
							//omp_set_lock(&mutex);
							//
							//	#pragma omp critical
							swap(array, j - 1, j);


							//omp_unset_lock(&mutex);
						}//end critical

					}//end if

				}//end inner task
			}//end for j



		}//end task

	}//end for i



	//	std::cout << "after, ";
	int fails = 0;
	//fails = test_sort(array, size);

	//	print_out_array(array, size);

	//	std::cout << "fails: " << fails << "\n";

	return fails;

}//end function

void print_out_array(int *array, int size)
{


	int i = 0;

	//#pragma omp parallel for
	for(int i = 0; i <= size - 1; i ++)
	{

		std::cout << array[i] << ", ";

	}//end for i    

	std::cout << "\n";


}//end function


void test_openmp()
{



#pragma omp parallel for
	for(int i = 0; i <= 9; i ++)
	{

		std::cout << i;

	}//end for loop

	std::cout << "\n";



}//end function



int fails_in_sorts = 0;

int run_bb(int * array, int *new_array, int size, int number_of_buckets)
{

	//print_out_array(array, size);


	auto start = std::chrono::high_resolution_clock::now();


	//int number_of_buckets = 5;

	int bucket_size = floor((double)size / (double)number_of_buckets);

	//std::cout << "bucket size: " << bucket_size << "\n";

	int buckets[number_of_buckets][size];

	int bucket_sizes[number_of_buckets];

	//bucket_sizes[0] = 0;

	//buckets[0][0] = 5;

	int current_bucket = 0;

	int max_value = 0;


	omp_lock_t mutex;

	omp_init_lock(&mutex);

	//https://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine

	//	int cores = sysconf(_SC_NPROCESSORS_ONLN);

	unsigned int cores = std::thread::hardware_concurrency();

	omp_set_num_threads(cores);

	//#pragma omp parallel for
	for(int i = 0; i <= size - 1; i ++)
	{

		//omp_set_lock(&mutex);
		#pragma omp critical
		if(array[i] > max_value)
		{max_value = array[i];}


		//omp_unset_lock(&mutex);


	}//end for i

	//#pragma omp parallel for
	for(int i = 0; i <= number_of_buckets - 1; i ++)
	{

		bucket_sizes[i] = 0;


	}//end for i



	//#pragma omp parallel
	for(int i = 0; i <= size - 1; i ++)
	{

		/*
		 *Sometimes one of the items is not getting added to a bucket in parellel mode: 
		 *
		 */
		//int assigned_bucket = floor((i / (double)size) * (double)number_of_buckets); 

		double fraction = (double)array[i] / ((double) max_value + 1);

		int assigned_bucket = floor((fraction) * ((double)number_of_buckets)); 

//#pragma omp critical
//	std::cout << array[i] << ", bucket: " << assigned_bucket << ", fraction: " << fraction << ", number of buckets: " << number_of_buckets << "\n";

		//#pragma omp critical
		{

			//omp_set_lock(&mutex);

	//for(int i = 0; i <= repetitions - 1; i ++)
	//{
//#pragma omp critical

#pragma omp critical
			{
			int size_of_bucket = bucket_sizes[assigned_bucket];

			//std::cout << "size of bucket: " << size_of_bucket << "\n";

			buckets[assigned_bucket][size_of_bucket] = array[i];

			bucket_sizes[assigned_bucket] ++;
			}//end critical
			//omp_unset_lock(&mutex);
		}//end critical

	}//end for i

//	std::cout << "after bucket assignment";

	//int new_array[size];

	int k = 0;

	int total_fails = 0;

	//#pragma omp parallel for
	for(int i = 0; i <= number_of_buckets - 1; i ++)
	{

		#pragma omp parallel
		total_fails += bubble_sort(buckets[i], mutex, bucket_sizes[i]);

#pragma omp critical
		if(bucket_sizes[i] > 0)
		{
			//adding current bucket
			for(int j = 0; j <= bucket_sizes[i] - 1; j ++)
			{
				//	std::cout << "adding buckets[" << i << "][" << j << "]: " << buckets[i][j] << "\n";
				new_array[k] = buckets[i][j];

				k++;

			}//end for j

		}//end if

	}//end for i

	fails_in_sorts += total_fails;

	//	std::cout << "total fails: " << total_fails << "\n";

	/*
	   for(int i = 0; i <= number_of_buckets - 1; i ++)
	   {
	   std::cout << "bucket " << i << ": ";

	   for(int j = 0; j <= bucket_sizes[i] - 1; j ++)
	   {

	   std::cout << buckets[i][j] << ", ";

	   }//end for j

	   std::cout << "\n\n";

	   }//end for i
	   */
	//std::cout << "\n";

	//bubble_sort(array, size);

	//https://stackoverflow.com/questions/12937963/get-local-time-in-nanoseconds

	auto finish = std::chrono::high_resolution_clock::now();

	//	std::cout << "finished sort: ";

	//	print_out_array(new_array, size);

	//	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << " ns\n";

	int duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

	return duration; 


}//end function

void unit_test_bubble_sort()
{


	for(int i = 10; i <= 50; i ++)
	{

		std::cout << "i: " << i << "\n";

		for(int j = 1; j <= 30; j ++)
		{
			//std::cout << j << ", ";
			int * array = randNumArray( i, j );

			int array2[i];// = new int[i];

			for(int k = 0; k <= i - 1; k ++)
			{

				array2[k] = array[k];

			}//end for k


			//		sum += run_bb(array, new_array, size, number_of_buckets);


//#pragma omp critical
			//std::cout << "buckets: " << (j % i) << ", ";


			int number_of_buckets = 5;
if(j % i != 0 && j % i != i)
number_of_buckets = (j % i);


int * new_array = new int[i];



	omp_lock_t mutex;

	omp_init_lock(&mutex);



#pragma omp parallel
			bubble_sort(array, mutex, i);


			std::cout << "\n\n";

			std::cout << array2 << ": qty: " << i << ", ";

			for(int k = 0; k <= i - 1; k ++)
			{
			
				std::cout << array2[k] << ", ";
			
			}//end for k


			std::cout << "\n";


			std::cout << array << ": ";


			for(int k = 0; k <= i - 1; k ++)
			{

				std::cout << array[k] << ", ";

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


			std::cout << "\n";

			for(int k = 1; k <= i - 1; k ++)
			{
				//array[k] = 0;
				assert(array[k] > array[k - 1]);

				//				std::cout << "array[" << k << "] = " << array[k] << " > " << array[k - 1]; 

				//				std::cout << "\n";

			}//end for k

			delete array;

			delete new_array;

		}//end for j




	}//end for i





}//end function

void unit_test_sort() 
{
	for(int i = 10; i <= 50; i ++)
	{

		std::cout << "i: " << i << "\n";

		for(int j = 1; j <= 30; j ++)
		{
			//std::cout << j << ", ";
			int * array = randNumArray( i, j );

			int array2[i];// = new int[i];

			for(int k = 0; k <= i - 1; k ++)
			{

				array2[k] = array[k];

			}//end for k


			//		sum += run_bb(array, new_array, size, number_of_buckets);


//#pragma omp critical
			//std::cout << "buckets: " << (j % i) << ", ";


			int number_of_buckets = 5;
if(j % i != 0 && j % i != i)
number_of_buckets = (j % i);


			int * new_array = new int[i];

//#pragma omp parallel
			run_bb(array, new_array,  i, number_of_buckets);


			std::cout << "\n\n";

			std::cout << array2 << ": qty: " << i << ", ";

			for(int k = 0; k <= i - 1; k ++)
			{
			
				std::cout << array2[k] << ", ";
			
			}//end for k


			std::cout << "\n";


			std::cout << array << ": ";


			for(int k = 0; k <= i - 1; k ++)
			{

				std::cout << new_array[k] << ", ";

				bool number_in_sorted_array = false;
				//array[3] = 0;
				for(int z = 0; z <= i - 1; z ++)
				{

					if(array2[k] == new_array[z])
					{

						number_in_sorted_array = true;

					}//end if


				}//end for z

				assert(number_in_sorted_array == true);

			}//end for k


			std::cout << "\n";

			for(int k = 1; k <= i - 1; k ++)
			{
				//array[k] = 0;
				assert(new_array[k] > new_array[k - 1]);

				//				std::cout << "array[" << k << "] = " << array[k] << " > " << array[k - 1]; 

				//				std::cout << "\n";

			}//end for k

			delete array;

			delete new_array;

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

	//print_out_array(array, size);

	//unit_test_bubble_sort();

	unit_test_sort();

	int differences = 0;

	int fails = 0;

	int total = 0;

	int repetitions = 10;

	int number_of_buckets = 5;

	double min_buckets = (double)size / 10.0;

	//std::cout << "min_buckets: " << min_buckets << "\n";

	//number_of_buckets = floor((double)size / 10.0);

	number_of_buckets = 5;

	std::cout << "number_of_buckets = " << number_of_buckets << "\n";

	//int number_of_buckets = 5;

	int sum = 0;


	int * new_array = new int[size];

//#pragma omp parallel
	run_bb(array, new_array, size, number_of_buckets);

	int in_order = 1;

	unsigned int cores = std::thread::hardware_concurrency();

	std::cout << "after sort: \n";

	for(int i = 0; i <= size - 1; i ++)
	{

		std::cout << new_array[i] << ", ";


	}//end for i

	std::cout << "\n";

	delete new_array;


	//std::cout << "cores: " << cores << "\n";

	//delete [] new_array;

	// delete the heap memory
	delete [] array;
}//end main

