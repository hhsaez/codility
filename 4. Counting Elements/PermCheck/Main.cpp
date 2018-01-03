/*

A non-empty zero-indexed array A consisting of N integers is given.

A permutation is a sequence containing each element from 1 to N once, and only once.

For example, array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
    A[3] = 2
is a permutation, but array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
is not a permutation, because value 2 is missing.

The goal is to check whether array A is a permutation.

Write a function:

int solution(vector<int> &A);

that, given a zero-indexed array A, returns 1 if array A is a permutation and 0 if it is not.

For example, given array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
    A[3] = 2
the function should return 1.

Given array A such that:

    A[0] = 4
    A[1] = 1
    A[2] = 3
the function should return 0.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [1..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage 
(not counting the storage required for input arguments).

*/

#include <iostream>
#include <vector>

int solution( std::vector< int > &A )
{
	const int N = A.size();
	std::vector< int > counters( N + 1 );
	for ( auto a : A ) {
		if ( a > N ) {
			return 0;
		}
		
		counters[ a ]++;
	}

	for ( int i = 1; i < N + 1; i++ ) {
		if ( counters[ i ] != 1 ) {
			return 0;
		}
	}
	
	return 1;
}

void test( std::vector< int > A, int expected )
{
	std::cout << "Input: A=[";
	bool first = true;
	for ( auto a : A ) {
		std::cout << ( first ? "" : ", " ) << a;
		first = false;
	}
	std::cout << "]\n";

	auto got = solution( A );

	if ( got != expected ) {
		std::cout << "ERROR got=" << got << " expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

int main( int argc, char **argv )
{
	test( { 4, 1, 3, 2 }, 1 );
	test( { 4, 1, 3 }, 0 );
	test( { 1 }, 1 );
	test( { 5, 2 }, 0 );
	test( { 2, 1, 3 }, 1 );
	
	return 0;
}

