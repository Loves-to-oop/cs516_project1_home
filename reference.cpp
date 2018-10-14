#include <iostream>
#include <sstream>
#include <cstdlib>
#include <thread>

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
    
    // delete the heap memory
    delete [] array;
}

