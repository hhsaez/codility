/*

A zero-indexed array A consisting of N integers is given. A triplet (P, Q, R) is 
triangular if it is possible to build a triangle with sides of lengths A[P], A[Q] and A[R]. 
In other words, triplet (P, Q, R) is triangular if 0 ≤ P < Q < R < N and:

A[P] + A[Q] > A[R],
A[Q] + A[R] > A[P],
A[R] + A[P] > A[Q].

For example, consider array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 12

There are four triangular triplets that can be constructed from elements of this array, 
namely (0, 2, 4), (0, 2, 5), (0, 4, 5), and (2, 4, 5).

Write a function:

int solution(vector<int> &A);

that, given a zero-indexed array A consisting of N integers, returns the number of 
triangular triplets in this array.

For example, given array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 12

the function should return 4, as explained above.

Assume that:

N is an integer within the range [0..1,000];
each element of array A is an integer within the range [1..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N2);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingDMZBKU-26U/

*/

#include "../../Utils.hpp"

int solution( std::vector< int > A )
{
	const long N = A.size();
	if ( N < 3 ) {
		return 0;
	}
	
	std::sort( A.begin(), A.end() );

	long result = 0;

	for ( long x = 0; x < N; x++ ) {
		long z = x + 2;
		for ( long y = x + 1; y < N; y++ ) {
			while ( z < N && A[ x ] + A[ y ] > A[ z ] ) {
				z++;
			}
			result += z - y - 1;
		}
	}
	
	return result;
}

void test( std::vector< int > A, int expected )
{
	codility::compareResults( solution( A ), expected );
}

int main( int argc, char **argv )
{
	test( { 10, 2, 5, 1, 8, 12 }, 4 );
	
	return 0;
}

