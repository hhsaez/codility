/*

A non-empty zero-indexed array A consisting of N integers is given.

A peak is an array element which is larger than its neighbours. More precisely, it is an index P such that 0 < P < N − 1 and A[P − 1] < A[P] > A[P + 1].

For example, the following array A:

    A[0] = 1
    A[1] = 5
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
has exactly four peaks: elements 1, 3, 5 and 10.

You are going on a trip to a range of mountains whose relative heights are represented by
 array A, as shown in a figure below. You have to choose how many flags you should take 
with you. The goal is to set the maximum number of flags on the peaks, according to 
certain rules.



Flags can only be set on peaks. What's more, if you take K flags, then the distance 
between any two flags should be greater than or equal to K. The distance between 
indices P and Q is the absolute value |P − Q|.

For example, given the mountain range represented by array A, above, with N = 12, 
if you take:

two flags, you can set them on peaks 1 and 5;
three flags, you can set them on peaks 1, 5 and 10;
four flags, you can set only three flags, on peaks 1, 5 and 10.
You can therefore set a maximum of three flags in this case.

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A of N integers, returns the maximum number of flags that can be set on the peaks of the array.

For example, the following array A:

    A[0] = 1
    A[1] = 5
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

N is an integer within the range [1..400,000];
each element of array A is an integer within the range [0..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingVNN3KB-BBH/

*/

#include <iostream>
#include <vector>

int solution( std::vector< int > &A )
{
	const long N = A.size();
	if ( N < 3 ) {
		return 0;
	}

	std::vector< int > peaks( N );

	peaks[ N - 1 ] = -1;
	for ( long i = N - 2; i > 0; i-- ) {
		if ( A[ i ] > std::max( A[ i - 1 ], A[ i + 1 ] ) ) {
			peaks[ i ] = i;
		}
		else {
			peaks[ i ] = peaks[ i + 1 ];
		}
	}
	peaks[ 0 ] = peaks[ 1 ];

	int max = 0;

	for ( int i = 1; i * i <= N + i; i++ ) {
		int flags = 0;
		int next_peak = peaks[ 0 ];
		
		for ( int j = 0; j < i && next_peak != -1; j++, flags++ ) {
			if ( next_peak + i >= N ) {
				next_peak = -1;
			}
			else {
				next_peak = peaks[ next_peak + i ];
			}
		}

		max = std::max( max, flags );
	}
	
	return max;
}

void test( std::vector< int > A, int expected )
{
	static size_t test = 0;
	
	auto got = solution( A );

	if ( got != expected ) {
		std::cout << test++ << " ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << test++ << " OK\n";
	}
}

int main( int argc, char **argv )
{
	test( { 1, 5, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2 }, 3 );
	test( { 1 }, 0 );
	test( { 1, 3, 2 }, 1 );
	test( { 1, 1, 2 }, 0 );
	test( { 1, 1, 1 }, 0 );
	test( { 1, 5, 3, 5, 3, 5, 1, 5, 3, 5, 3, 5 }, 3 );
	
	return 0;
}
