#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
// create an array of length size of random numbers
// returns a pointer to the array


void merge(int *array, int beginning, int middle, int end)
{

	int left_array_size = middle - (beginning - 1);
	int right_array_size = end - middle;

	int left_array[middle - (beginning - 1)];
	int right_array[end - middle];

	for(int i = 0; i <= left_array_size - 1; i++)
	{

		left_array[i] = array[beginning + i];

	}//end for i

	for(int i = 0; i <= right_array_size - 1; i ++)
	{

		right_array[i] = array[middle + 1 + i];

	}//end for i


	int i = 0;// left array index	
	int j = 0;// right array index

	int k;// main array index

	for(k = beginning; k <= end; k ++)
	{

		if(i <= left_array_size - 1 && j <= right_array_size - 1)
		{

			if(left_array[i] < right_array[j])
			{

				array[k] =  left_array[i];

				i++;

			}// end if
			else if(left_array[i] >= right_array[j])
			{

				array[k] = right_array[j];

				j++;

			}// end else

		}//end if
		else if(i <= left_array_size - 1)
		{

			array[k] =  left_array[i];
			i ++;

		}// end else if
		else if(j <= right_array_size - 1)
		{

			array[k] = right_array[j];
			j++;

		}// end else if
		else{

		}// end else


	}// end for k


}//end function


void mergesort(int * array, int beginning, int end)
{

	if(beginning < end)
	{

		int middle = (beginning + end) / 2;

		mergesort(array, beginning, middle);
		mergesort(array, middle + 1, end);
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


		//void mergesort(int * array, int beginning, int end)

		mergesort(array, 0, size - 1);

		for(int i = 0; i <= size - 1; i ++)
		{

			std::cout << array[i] << ", ";

		}//end for i

		std::cout << "\n";

		// delete the heap memory
		delete [] array;
	}//end main

