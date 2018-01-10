/*

A zero-indexed array A consisting of N integers is given. A triplet (P, Q, R) is 
triangular if 0 ≤ P < Q < R < N and:

A[P] + A[Q] > A[R],
A[Q] + A[R] > A[P],
A[R] + A[P] > A[Q].

For example, consider array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20
Triplet (0, 2, 4) is triangular.

Write a function:

int solution(vector<int> &A);

that, given a zero-indexed array A consisting of N integers, returns 1 if there 
exists a triangular triplet for this array and returns 0 otherwise.

For example, given array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 20

the function should return 1, as explained above. Given array A such that:

  A[0] = 10    A[1] = 50    A[2] = 5
  A[3] = 1

the function should return 0.

Assume that:

N is an integer within the range [0..100,000];
each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingMSME4J-ERJ/

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

	for ( size_t p = 0; p < N - 2; p++ ) {
		auto q = p + 1;
		auto r = p + 2;
		long AP = A[ p ];
		long AQ = A[ q ];
		long AR = A[ r ];
		if ( AP + AQ > AR && AQ + AR > AP && AP + AR > AQ ) {
			return 1;
		}
	}
	
	return 0;
}

int brute( std::vector< int > &A )
{
	const auto N = A.size();
	for ( size_t p = 0; p < N; p++ ) {
		for ( size_t q = p + 1; q < N; q++ ) {
			for ( size_t r = q + 1; r < N; r++ ) {
				if ( p < q && q < r ) {
					long AP = A[ p ];
					long AQ = A[ q ];
					long AR = A[ r ];
					if ( AP + AQ > AR && AQ + AR > AP && AP + AR > AQ ) {
						return 1;
					}
				}
			}
		}
	}
	
	return 0;
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
	std::uniform_int_distribution<> dis( std::numeric_limits< int >::min(), std::numeric_limits< int >::max() );

	std::vector< int > v1( size );
	for ( size_t i = 0; i < size; i++ ) {
		v1[ i ] = dis( gen );
	}

	return v1;
}	

int main( int argc, char **argv )
{
	test( { 10, 2, 5, 1, 8, 20 } );
	test( { 1, 2, 3, 4, 5, 6, 7 } );
	test( { 1 } );
	test( { 1, 1, 1, 1, 1, 1 } );
	test( { -1, -1, -1, -1, -1, -1 } );
	test( { 2, 5, 1 } );
	test( { 10, 50, 5, 1 } );
	test( {} );
	test( { std::numeric_limits< int >::min(), std::numeric_limits< int >::max(), 0 } );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 10 ) );

	return 0;
}


