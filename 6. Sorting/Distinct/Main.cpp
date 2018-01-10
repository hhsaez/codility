/*

Write a function

int solution(vector<int> &A);

that, given a zero-indexed array A consisting of N integers, returns the number of 
distinct values in array A.

Assume that:

N is an integer within the range [0..100,000];
each element of array A is an integer within the range [−1,000,000..1,000,000].
For example, given array A consisting of six elements such that:

 A[0] = 2    A[1] = 1    A[2] = 1
 A[3] = 2    A[4] = 3    A[5] = 1
the function should return 3, because there are 3 distinct values appearing in 
array A, namely 1, 2 and 3.

Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingDX8X4D-VAE/

*/

#include <iostream>
#include <vector>
#include <set>

int solution( std::vector< int > &A )
{
	std::set< int > distinct;
	for ( auto a : A ) {
		distinct.insert( a );
	}

	return distinct.size();
}

void test( std::vector< int > A, int expected )
{
	std::cout << "Input A=[";
	bool first = true;
	for ( auto a : A ) {
		std::cout << ( first ? "" : ", " ) << a;
		first = false;
	}
	std::cout << "]\n";

	auto got = solution( A );

	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

int main( int argc, char **argv )
{
	test( { 2, 1, 1, 2, 3, 1 }, 3 );
	test( { 1, 1, 1, 1, 1 }, 1 );
	test( {}, 0 );

	return 0;
}


