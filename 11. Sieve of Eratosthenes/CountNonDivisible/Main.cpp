/*

You are given an array A consisting of N integers.

For each number A[i] such that 0 ≤ i < N, we want to count the number of elements of the 
array that are not the divisors of A[i]. We say that these elements are non-divisors.

For example, consider integer N = 5 and array A such that:

    A[0] = 3
    A[1] = 1
    A[2] = 2
    A[3] = 3
    A[4] = 6

For the following elements:

A[0] = 3, the non-divisors are: 2, 6,
A[1] = 1, the non-divisors are: 3, 2, 3, 6,
A[2] = 2, the non-divisors are: 3, 3, 6,
A[3] = 3, the non-divisors are: 2, 6,
A[4] = 6, there aren't any non-divisors.
Write a function:

vector<int> solution(vector<int> &A);

that, given an array A consisting of N integers, returns a sequence of integers 
representing the amount of non-divisors.

The sequence should be returned as:

a structure Results (in C), or
a vector of integers (in C++), or
a record Results (in Pascal), or
an array of integers (in any other programming language).
For example, given:

    A[0] = 3
    A[1] = 1
    A[2] = 2
    A[3] = 3
    A[4] = 6
the function should return [2, 4, 3, 2, 0], as explained above.

Assume that:

N is an integer within the range [1..50,000];
each element of array A is an integer within the range [1..2 * N].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting 
the storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingVDF7FS-NUJ/

 */

#include "../../Utils.hpp"

std::vector< int > solution( std::vector< int > &A )
{
	long N = A.size();
	long M = 2 * N + 1;
	
	std::vector< int > counts( M, 0 );
	std::vector< int > divisors( M, 0 );
	std::vector< int > result( N );

	for ( auto a : A ) {
		counts[ a ]++;
	}
	
	for ( long i = 0; i < M; i++ ) {
		if ( counts[ i ] > 0 ) { 
			for ( long j = i; j < M; j += i ) { 
				divisors[ j ] += counts[ i ];
			}
		}
	}

	for ( long i = 0; i < N; i++ ) {
		result[ i ] = N - divisors[ A[ i ] ];
	}
	
	return result;
}

std::vector< int > brute( std::vector< int > &A )
{
	const long N = A.size();
	std::vector< int > result( N, 0 );

	for ( long i = 0; i < N; i++ ) {
		for ( long j = 0; j < N; j++ ) {
			if ( i == j ) {
				continue;
			}

			if ( ( A[ i ] % A[ j ] ) != 0 ) {
				result[ i ]++;
			}
		}
	}
	
	return result;
}

void test( std::vector< int > A )
{
	codility::compareResults( solution( A ), brute( A ) );
}

int main( int argc, char **argv )
{
	test( { 3, 1, 2, 3, 6 } );
	test( {} );
	test( { 1 } );
	test( { 1, 2 } );
	test( { 7, 5, 4, 2 } );
	test( { 1, 2, 3, 4, 5, 6 } );
	test( codility::generateRandomVector( 1, 10, 5 ) );
	test( codility::generateRandomVector( 1, 10, 5 ) );
	test( codility::generateRandomVector( 1, 10, 5 ) );
	test( codility::generateRandomVector( 1, 10, 5 ) );
}




