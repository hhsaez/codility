/*

A non-empty zero-indexed array A consisting of N integers is given. The product of 
triplet (P, Q, R) equates to A[P] * A[Q] * A[R] (0 ≤ P < Q < R < N).

For example, array A such that:

  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6

contains the following example triplets:

 (0, 1, 2), product is −3 * 1 * 2 = −6
 (1, 2, 4), product is 1 * 2 * 5 = 10
 (2, 4, 5), product is 2 * 5 * 6 = 60
Your goal is to find the maximal product of any triplet.

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A, returns the value of the maximal product 
of any triplet.

For example, given array A such that:

  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6
the function should return 60, as the product of triplet (2, 4, 5) is maximal.

Assume that:

N is an integer within the range [3..100,000];
each element of array A is an integer within the range [−1,000..1,000].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(1), beyond input storage (not counting the 
storage required for input arguments).

Results (100%): 
https://app.codility.com/demo/results/training3REDMN-YAU/

 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int solution( std::vector< int > &A )
{
	const auto N = A.size();
	if ( N < 3 ) {
		return 0;
	}
	
	std::sort( A.begin(), A.end() );

	long r1 = ( long ) A[ 0 ] * ( long ) A[ 1 ] * ( long ) A[ N - 1 ];
	long r2 = ( long ) A[ N - 3 ] * ( long ) A[ N - 2 ] * ( long ) A[ N - 1 ];

	return std::max( r1, r2 );
}

int brute( std::vector< int > &A )
{
	const auto N = A.size();

	long result = std::numeric_limits< long >::min();
	
	for ( size_t p = 0; p < N; p++ ) {
		for ( size_t q = p + 1; q < N; q++ ) {
			for ( size_t r = q + 1; r < N; r++ ) {
				if ( p < q && q < r ) {
					long AP = A[ p ];
					long AQ = A[ q ];
					long AR = A[ r ];
					auto prod = AP * AQ * AR;
					if ( prod > result ) {
						result = prod;
					}
				}
			}
		}
	}
	
	return result;
}

void test( std::vector< int > A )
{
	std::cout << "Input A=[";
	bool first = true;
	for ( auto a : A ) {
		std::cout << ( first ? "" : ", " ) << a;
		first = false;
	}
	std::cout << "]\n";

	auto got = solution( A );
	auto expected = brute( A );

	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

std::vector< int > generateRandomVector( size_t size )
{
	std::random_device rd;
    std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis( -1000, 1000 );

	std::vector< int > v1( size );
	for ( size_t i = 0; i < size; i++ ) {
		v1[ i ] = dis( gen );
	}

	return v1;
}	

int main( int argc, char **argv )
{
	test( { 1, 2, 3, 4, 5 } );
	test( { -3, 1, 2, -2, 5, 6 } );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 10 ) );
	return 0;
}



	
