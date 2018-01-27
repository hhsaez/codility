/*

You are given integers K, M and a non-empty zero-indexed array A consisting of N integers. 
Every element of the array is not greater than M.

You should divide this array into K blocks of consecutive elements. The size of the block 
is any integer between 0 and N. Every element of the array should belong to some block.

The sum of the block from X to Y equals A[X] + A[X + 1] + ... + A[Y]. The sum of empty 
block equals 0.

The large sum is the maximal sum of any block.

For example, you are given integers K = 3, M = 5 and array A such that:

  A[0] = 2
  A[1] = 1
  A[2] = 5
  A[3] = 1
  A[4] = 2
  A[5] = 2
  A[6] = 2
The array can be divided, for example, into the following blocks:

[2, 1, 5, 1, 2, 2, 2], [], [] with a large sum of 15;
[2], [1, 5, 1, 2], [2, 2] with a large sum of 9;
[2, 1, 5], [], [1, 2, 2, 2] with a large sum of 8;
[2, 1], [5, 1], [2, 2, 2] with a large sum of 6.
The goal is to minimize the large sum. In the above example, 6 is the minimal large sum.

Write a function:

int solution(int K, int M, vector<int> &A);

that, given integers K, M and a non-empty zero-indexed array A consisting of N integers, 
returns the minimal large sum.

For example, given K = 3, M = 5 and array A such that:

  A[0] = 2
  A[1] = 1
  A[2] = 5
  A[3] = 1
  A[4] = 2
  A[5] = 2
  A[6] = 2
the function should return 6, as explained above.

Assume that:

N and K are integers within the range [1..100,000];
M is an integer within the range [0..10,000];
each element of array A is an integer within the range [0..M].
Complexity:

expected worst-case time complexity is O(N*log(N+M));
expected worst-case space complexity is O(1), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingTXSFBS-CKZ/

 */

#include "../../Utils.hpp"

int check( std::vector< int > &A, int minSum )
{
	long sum = 0;
	int groups = 1;
	for ( auto a : A ) {
		if ( sum + a > minSum ) {
			sum = a;
			groups++;
		}
		else {
			sum += a;
		}
	}
	return groups;
}

int solution( int K, int M, std::vector< int > A )
{
	const long N = A.size();

	int beg = 0;
	long end = 0;

	for ( long i = 0; i < N; i++ ) {
		beg = std::max( beg, A[ i ] );
		end += A[ i ];
	}

	int result = 0;
	while ( beg <= end ) {
		long mid = ( beg + end ) / 2;
		if ( check( A, mid ) <= K ) {
			end = mid - 1;
			result = mid;
		}
		else {
			beg = mid + 1;
		}
	}
	
	return result;
}

void test( int K, int M, std::vector< int > A, int expected )
{
	codility::compareResults( solution( K, M, A ), expected );
}

int main( int argc, char **argv )
{
	test( 5, 20, { 1 }, 1 );
	test( 3, 5, { 2, 1, 5, 1, 2, 2, 2 }, 6 );
	test( 3, 1, { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }, 1 );
	
	return 0;
}

