/*

A non-empty zero-indexed array A consisting of N integers is given.

A peak is an array element which is larger than its neighbors. More precisely, it is an index P such that 0 < P < N − 1,  A[P − 1] < A[P] and A[P] > A[P + 1].

For example, the following array A:

    A[0] = 1
    A[1] = 2
    A[2] = 3
    A[3] = 4
    A[4] = 3
    A[5] = 4
    A[6] = 1
    A[7] = 2
    A[8] = 3
    A[9] = 4
    A[10] = 6
    A[11] = 2
has exactly three peaks: 3, 5, 10.

We want to divide this array into blocks containing the same number of elements. More precisely, we want to choose a number K that will yield the following blocks:

A[0], A[1], ..., A[K − 1],
A[K], A[K + 1], ..., A[2K − 1],
...
A[N − K], A[N − K + 1], ..., A[N − 1].
What's more, every block should contain at least one peak. Notice that extreme elements of the blocks (for example A[K − 1] or A[K]) can also be peaks, but only if they have both neighbors (including one in an adjacent blocks).

The goal is to find the maximum number of blocks into which the array A can be divided.

Array A can be divided into blocks as follows:

one block (1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2). This block contains three peaks.
two blocks (1, 2, 3, 4, 3, 4) and (1, 2, 3, 4, 6, 2). Every block has a peak.
three blocks (1, 2, 3, 4), (3, 4, 1, 2), (3, 4, 6, 2). Every block has a peak. Notice in particular that the first block (1, 2, 3, 4) has a peak at A[3], because A[2] < A[3] > A[4], even though A[4] is in the adjacent block.
However, array A cannot be divided into four blocks, (1, 2, 3), (4, 3, 4), (1, 2, 3) and (4, 6, 2), because the (1, 2, 3) blocks do not contain a peak. Notice in particular that the (4, 3, 4) block contains two peaks: A[3] and A[5].

The maximum number of blocks that array A can be divided into is three.

Write a function:

class Solution { public int solution(int[] A); }

that, given a non-empty zero-indexed array A consisting of N integers, returns the maximum number of blocks into which A can be divided.

If A cannot be divided into some number of blocks, the function should return 0.

For example, given:

    A[0] = 1
    A[1] = 2
    A[2] = 3
    A[3] = 4
    A[4] = 3
    A[5] = 4
    A[6] = 1
    A[7] = 2
    A[8] = 3
    A[9] = 4
    A[10] = 6
    A[11] = 2
the function should return 3, as explained above.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [0..1,000,000,000].

*/

#include <iostream>
#include <vector>
#include <random>

int solution( std::vector< int > &A )
{
	const long N = A.size();
	if ( N < 3 ) {
		return 0;
	}
	
	std::vector< int > peaks( N );

	int nextPeak = -1;
	peaks[ N - 1 ] = nextPeak;

	for ( long i = N - 2; i > 0; i-- ) {
		if ( A[ i ] > std::max( A[ i - 1 ], A[ i + 1 ] ) ) {
			nextPeak = i;
		}

		peaks[ i ] = nextPeak;
	}

	peaks[ 0 ] = nextPeak;

	long maxPart = 0;

	for ( long i = 1; i * i <= N + i; i++ ) {
		if ( N % i != 0 ) {
			continue;
		}
		
		long partSize = N / i;

		for ( long j = 0; j < N; j += partSize ) {
			if ( peaks[ j ] < 0 || peaks[ j ] > j + partSize ) {
				return maxPart;
			}
		}

		maxPart = std::max( maxPart, i );
	}
	
	return maxPart;
}

int brute( std::vector< int > &A )
{
	const long N = A.size();
	if ( N < 3 ) {
		return 0;
	}
	
	std::vector< int > peaks( N );

	int nextPeak = -1;
	peaks[ N - 1 ] = nextPeak;

	for ( long i = N - 2; i > 0; i-- ) {
		if ( A[ i ] > std::max( A[ i - 1 ], A[ i + 1 ] ) ) {
			nextPeak = i;
		}

		peaks[ i ] = nextPeak;
	}

	peaks[ 0 ] = nextPeak;

	long maxPart = 0;

	//for ( long i = 1; i * i <= N + i; i++ ) {
	for ( long i = 1; i <= N; i++ ) {
		if ( N % i != 0 ) {
			continue;
		}
		
		long partSize = N / i;

		for ( long j = 0; j < N; j += partSize ) {
			if ( peaks[ j ] < 0 || peaks[ j ] > j + partSize ) {
				return maxPart;
			}
		}

		maxPart = std::max( maxPart, i );
	}
	
	return maxPart;
}

void test( std::vector< int > A )
{
	static int testCount = 0;
	
	auto got = solution( A );
	auto expected = brute( A );

	std::cout << "Test " << ++testCount << " - ";

	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "got=" << got << " PASSED\n";
	}
}

std::vector< int > generateRandom( size_t N )
{
	std::random_device rd;
    std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis( 0, 1000000001 );

	std::vector< int > result( N );
	for ( size_t i = 0; i < N; i++ ) {
		result[ i ] = dis( gen );
	}

	return result;
}

int main( int argc, char **argv )
{
	test( generateRandom( 50000 ) );
	test( { 1, 9, 2, 9, 3, 9, 4, 9, 5, 9, 6, 9 } );
	test( { 1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2 } );
	test( {} );
	test( { 1, 2, 3 } );
	test( { 1, 3, 2 } );
	test( { 1, 3, 4, 2 } );
	test( { 1, 3, 2, 5, 2 } );
	test( { 1, 9, 2, 9, 3, 9 } );
	test( { 1, 9, 2, 9, 3, 9, 4, 9, 5, 9 } );
	test( { 1, 9, 2, 9, 3, 9, 4, 9, 5, 9, 1 } );
	test( { 1, 9, 2, 9, 3, 9, 4, 9, 5, 9, 1, 2 } );
	test( { 9, 1, 9 } );
	test( generateRandom( 10 ) );
	test( { 1000000000 - 1, 1000000000, 1000000000 - 1 } );
	
	return 0;
}

