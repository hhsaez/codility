/*

Let A be a non-empty zero-indexed array consisting of N integers.

The abs sum of two for a pair of indices (P, Q) is the absolute value 

|A[P] + A[Q]|, for 0 ≤ P ≤ Q < N.

For example, the following array A:

  A[0] =  1
  A[1] =  4
  A[2] = -3

has pairs of indices (0, 0), (0, 1), (0, 2), (1, 1), (1, 2), (2, 2). 
The abs sum of two for the pair (0, 0) is A[0] + A[0] = |1 + 1| = 2. 
The abs sum of two for the pair (0, 1) is A[0] + A[1] = |1 + 4| = 5. 
The abs sum of two for the pair (0, 2) is A[0] + A[2] = |1 + (−3)| = 2. 
The abs sum of two for the pair (1, 1) is A[1] + A[1] = |4 + 4| = 8. 
The abs sum of two for the pair (1, 2) is A[1] + A[2] = |4 + (−3)| = 1. 
The abs sum of two for the pair (2, 2) is A[2] + A[2] = |(−3) + (−3)| = 6.
 
Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A consisting of N integers, returns the 
minimal abs sum of two for any pair of indices in this array.

For example, given the following array A:

  A[0] =  1
  A[1] =  4
  A[2] = -3

the function should return 1, as explained above.

Given array A:

  A[0] = -8
  A[1] =  4
  A[2] =  5
  A[3] =-10
  A[4] =  3

the function should return |(−8) + 5| = 3.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000,000..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingM6NZXA-ZHF/

 */

#include "../../Utils.hpp"

int solution( std::vector< int > A )
{
	const long N = A.size();

	std::sort( std::begin( A ), std::end( A ) );

	long front = N - 1;
	long back = 0;

	int res = std::abs( A[ front ] + A[ front ] );
	
	while ( back <= front ) {
		auto tmp = A[ front ] + A[ back ];

		res = std::min( res, std::abs( tmp ) );

		if ( tmp >= 0 ) {
			--front;
		}
		else {
			++back;
		}
	}

	return res;
}

int brute( std::vector< int > A )
{
	const long N = A.size();

	int res = std::numeric_limits< int >::max();
	for ( long i = 0; i < N; i++ ) {
		for ( long j = 0; j < N; j++ ) {
			res = std::min( res, std::abs( A[ i ] + A[ j ] ) );
		}
	}

	return res;
}

void test( std::vector< int > A )
{
	codility::compareResults( solution( A ), brute( A ) );
}

int main( int argc, char **argv )
{
	test( { 1, 4, -3 } );
	test( { -8, 4, 5, -10, 3 } );
	
	return 0;
}

