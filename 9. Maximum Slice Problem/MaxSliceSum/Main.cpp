/*

A non-empty zero-indexed array A consisting of N integers is given. A pair of 
integers (P, Q), such that 0 ≤ P ≤ Q < N, is called a slice of array A. The sum of a 
slice (P, Q) is the total of A[P] + A[P+1] + ... + A[Q].

Write a function:

int solution(vector<int> &A);


that, given an array A consisting of N integers, returns the maximum sum of any slice of A.

For example, given array A such that:

A[0] = 3  A[1] = 2  A[2] = -6
A[3] = 4  A[4] = 0
the function should return 5 because:

 (3, 4) is a slice of A that has sum 4,
 (2, 2) is a slice of A that has sum −6,
 (0, 1) is a slice of A that has sum 5,

no other slice of A has sum greater than (0, 1).

Assume that:

N is an integer within the range [1..1,000,000];
each element of array A is an integer within the range [−1,000,000..1,000,000];
the result will be an integer within the range [−2,147,483,648..2,147,483,647].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingV9C6J2-U7H/

*/

#include <iostream>
#include <vector>
#include <random>

int solution( std::vector< int > &A )
{
	long max_slice = std::numeric_limits< long >::min();
	long max_ending = 0;

	for ( auto a : A ) {
		max_ending = std::max( ( long ) a, max_ending + a );
		max_slice = std::max( max_slice, max_ending );
	}
	
	return max_slice;
}

int brute( std::vector< int > &A )
{
	const auto N = A.size();
	long result = std::numeric_limits< long >::min();

	for ( size_t i = 0; i < N; i++ ) {
		long sum = 0;
		for ( size_t j = i; j < N; j++ ) {
			sum += A[ j ];
			result = std::max( result, sum );
		}
	}	
	
	return result;
}

void test( std::vector< int > A )
{
	auto got = solution( A );
	auto expected = brute( A );

	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << std::endl;
	}
	else {
		std::cout << "OK\n";
	}
}

std::vector< int > generateRandomVector( size_t size = 400000 )
{
	std::random_device rd;
    std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis( -1000000, 1000001 );

	std::vector< int > v1( size );
	for ( size_t i = 0; i < size; i++ ) {
		v1[ i ] = dis( gen );
	}

	return v1;
}	

int main( int argc, char **argv )
{
	test( { 3, 2, -6, 4, 0 } );
	test( { 3, 2, -6, 4, 0, -20 } );
	test( { -3, -2, -6, -4, 0, -20 } );
	test( { } );
	test( { 3 } );
	test( { 3, 2 } );
	test( { -3, -2, -1 } );
	test( { -3, -2, -4, -10 } );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 20 ) );
	test( generateRandomVector( 30 ) );
	test( generateRandomVector( 100 ) );

	return 0;
}

