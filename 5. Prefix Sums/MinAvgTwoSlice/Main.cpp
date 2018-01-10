/*

A non-empty zero-indexed array A consisting of N integers is given. A pair of 
integers (P, Q), such that 0 ≤ P < Q < N, is called a slice of array A (notice 
that the slice contains at least two elements). The average of a slice (P, Q) is the 
sum of A[P] + A[P + 1] + ... + A[Q] divided by the length of the slice. To be precise, 
the average equals (A[P] + A[P + 1] + ... + A[Q]) / (Q − P + 1).

For example, array A such that:

    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8
contains the following example slices:

slice (1, 2), whose average is (2 + 2) / 2 = 2;
slice (3, 4), whose average is (5 + 1) / 2 = 3;
slice (1, 4), whose average is (2 + 2 + 5 + 1) / 4 = 2.5.
The goal is to find the starting position of a slice whose average is minimal.

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A consisting of N integers, returns the 
starting position of the slice with the minimal average. If there is more than one 
slice with a minimal average, you should return the smallest starting position of
 such a slice.

For example, given array A such that:

    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8
the function should return 1, as explained above.

Assume that:

N is an integer within the range [2..100,000];
each element of array A is an integer within the range [−10,000..10,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%): 
https://app.codility.com/demo/results/training3K6RVS-PJ7/

 */

#include <iostream>
#include <vector>
#include <limits>

int solution( std::vector< int > &A )
{
	// assumes result is either a 2-slice or a 3-slice
	const auto N = A.size();
	if ( N < 2 ) {
		return -1;
	}

	if ( N == 2 ) {
		return 0;
	}
	
	double minAvg = ( A[ 0 ] + A[ 1 ] ) / 2.0;
	int result = 0;

	for ( size_t p = 0; p < N - 2; p++ ) {
		auto avg2 = ( A[ p ] + A[ p + 1 ] ) / 2.0;
		if ( avg2 < minAvg ) {
			minAvg = avg2;
			result = p;
		}

		auto avg3 = ( A[ p ] + A[ p + 1 ] + A[ p + 2 ] ) / 3.0;
		if ( avg3 < minAvg ) {
			minAvg = avg3;
			result = p;
		}
	}

	if ( ( A[ N - 2 ] + A[ N - 1 ] ) / 2.0 < minAvg ) {
		result = N - 2;
	}

	return result;
}

int brute( std::vector< int > &A )
{
	const auto N = A.size();
	std::vector< int > minP( N );
	std::vector< double > minAvg( N );

	for ( size_t p = 0; p < N; p++ ) {
		for ( size_t q = p + 1; q < N; q++ ) {
			double avg = 0.0;
			for ( size_t k = p; k <= q; k++ ) {
				avg += A[ k ];
			}
			avg /= ( double )( q - p + 1 );
			if ( q == p + 1 || avg < minAvg[ p ] ) {
				minAvg[ p ] = avg;
			}
		}
	}

	int result = -1;
	double resultAvg = std::numeric_limits< double >::max();

	for ( size_t p = 0; p < N - 1; p++ ) {
		if ( minAvg[ p ] < resultAvg ) {
			resultAvg = minAvg[ p ];
			result = p;
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
		std::cout << "ERROR got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

int main( int argc, char **argv )
{
	test( { 4, 2, 2, 5, 1, 5, 8 } );
	test( { 4, 2 } );
	test( { 1, 2, 3 } );
	test( { 3, 2, 1 } );
	test( { -3, -2, -1 } );
	test( { -1, -2, -3, -4, -5, -6, -7, -8 } );
	return 0;
}





