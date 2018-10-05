#include <iostream>
#include <sstream>
#include <cstdlib>
// create an array of length size of random numbers
// returns a pointer to the array

void swap(int * array, int index1, int index2)
{

	int c = array[index1];

	array[index1] = array[index2];

	array[index2] = c;


}//end function


int partition(int *array, int p, int r)
{

	int x = array[r];

	int i = p - 1;

	for(int j = p; j <= r - 1; j ++)
	{

		if(array[j] <= x)
		{

			i = i + 1;

			swap(array, i, j);



		}//end if


	}//end for

	swap(array, (i + 1), r);


	return i + 1;

}//end function

void quick_sort(int *array, int p, int r)
{

	int q = 0;

	if(p < r)
	{
		q = partition(array, p, r);

		quick_sort(array, p, q - 1);

		quick_sort(array, q + 1, r);

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

quick_sort(array, 0, size - 1);

for(int i = 0; i <= size - 1; i ++)
{

	std::cout << array[i] << ", ";

}//end for i

std::cout << "\n";


		// delete the heap memory
		delete [] array;
	}

