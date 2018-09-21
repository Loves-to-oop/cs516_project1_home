#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
// create an array of length size of random numbers
// returns a pointer to the array


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

void print_out_array(int *array, int size);;

void bubble_sort(int *array, int size)
{

	std::cout << "size of array: " << size << "\n";

	std::cout << "before, ";

	print_out_array(array, size);


	//int i = 0;

	for(int i = 0; i <= size - 1; i ++)
	{

		//std::cout << "i: " << i << "\n";

		for(int j = 1; j <= size - 1; j ++)
		{

			//std::cout << "j: " << j << "\n";

			if(array[j - 1] > array[j])
			{

				//swap

				swap(array, j - 1, j);


			}//end if


		}//end for j





	}//end for i



	std::cout << "after, ";

	print_out_array(array, size);

}//end function

void print_out_array(int *array, int size)
{


	int i = 0;

	for(int i = 0; i <= size - 1; i ++)
	{

		std::cout << array[i] << ", ";

	}//end for i    

	std::cout << "\n";


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

	print_out_array(array, size);

	int number_of_buckets = 5;

	int bucket_size = floor((double)size / (double)number_of_buckets);

	std::cout << "bucket size: " << bucket_size << "\n";

	int buckets[number_of_buckets + 1][100];

	int bucket_sizes[number_of_buckets];

	//bucket_sizes[0] = 0;

	//buckets[0][0] = 5;

	int current_bucket = 0;

	int max_value = 0;

	for(int i = 0; i <= size - 1; i ++)
	{

		if(array[i] > max_value)
		{max_value = array[i];}


	}//end for i

	for(int i = 0; i <= number_of_buckets - 1; i ++)
	{

		bucket_sizes[i] = 0;


	}//end for i


	for(int i = 0; i <= size - 1; i ++)
	{

		//int assigned_bucket = floor((i / (double)size) * (double)number_of_buckets); 

		double fraction = (double)array[i] / ((double) max_value + 1);

		std::cout << "fraction: " << fraction << "\n";

		int assigned_bucket = floor((fraction) * (double)number_of_buckets); 

		std::cout << array[i] << " / " << max_value << " * " << number_of_buckets << " = assigned bucket: " << assigned_bucket << "\n";

		int size_of_bucket = bucket_sizes[assigned_bucket];

		//std::cout << "size of bucket: " << size_of_bucket << "\n";

		buckets[assigned_bucket][size_of_bucket] = array[i];

		bucket_sizes[assigned_bucket] ++;

	}//end for i

	int new_array[size];

	int k = 0;

	for(int i = 0; i <= number_of_buckets - 1; i ++)
	{

		bubble_sort(buckets[i], bucket_sizes[i]);

		if(bucket_sizes[i] > 0)
		{

			for(int j = 0; j <= bucket_sizes[i] - 1; j ++)
			{

				array[k] = buckets[i][j];

				k++;

			}//end for j

		}//end if

	}//end for i

	std::cout << "\n";

	//bubble_sort(array, size);

	print_out_array(array, size);


	// delete the heap memory
	delete [] array;
}

