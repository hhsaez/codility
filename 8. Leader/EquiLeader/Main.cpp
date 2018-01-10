/*

A non-empty zero-indexed array A consisting of N integers is given.

The leader of this array is the value that occurs in more than half of the elements of A.

An equi leader is an index S such that 0 ≤ S < N − 1 and two sequences A[0], A[1], ..., A[S] 
and A[S + 1], A[S + 2], ..., A[N − 1] have leaders of the same value.

For example, given array A such that:

    A[0] = 4
    A[1] = 3
    A[2] = 4
    A[3] = 4
    A[4] = 4
    A[5] = 2

we can find two equi leaders:

0, because sequences: (4) and (3, 4, 4, 4, 2) have the same leader, whose value is 4.
2, because sequences: (4, 3, 4) and (4, 4, 2) have the same leader, whose value is 4.

The goal is to count the number of equi leaders.

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A consisting of N integers, returns the 
number of equi leaders.

For example, given:

    A[0] = 4
    A[1] = 3
    A[2] = 4
    A[3] = 4
    A[4] = 4
    A[5] = 2
the function should return 2, as explained above.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000,000..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/training3EQU2E-BAJ/

*/

#include <iostream>
#include <vector>
#include <random>

int solution( std::vector< int > &A )
{
	const auto N = A.size();
	long size = 0;
	int value = -1;
	
	for ( size_t i = 0; i < N; i++ ) {
		if ( size == 0 ) {
			size++;
			value = A[ i ];
		}
		else if ( A[ i ] == value ) {
			size++;
		}
		else {
			size--;
		}
	}

	size = 0;
	
	for ( size_t i = 0; i < N; i++ ) {
		if ( A[ i ] == value ) {
			size++;
		}
	}

	if ( size <= N / 2 ) {
		return 0;
	}

	long equiLeader = 0;
	size_t count = 0;
	
	for ( size_t i = 0; i < N; i++ ) {
		if ( A[ i ] == value ) {
			count++;
		}
		
		if ( count > ( i + 1 ) / 2 && ( size - count ) > ( N - i - 1 ) / 2 ) {
			equiLeader++;
		}
	}

	return equiLeader;

}

long findLeader( std::vector< int > &A, size_t lo, size_t hi )
{
	for ( long i = lo; i <= hi; i++ ) {
		long count = 0;
		for ( long j = lo; j <= hi; j++ ) {
			if ( A[ j ] == A[ i ] ) {
				count++;
			}
		}
		if ( count > ( hi - lo + 1 ) / 2 ) {
			return i;
		}
	}

	return -1;	
}

int brute( std::vector< int > &A )
{
	const long N = A.size();

	auto leader = findLeader( A, 0, A.size() );
	if ( leader < 0 ) {
		return 0;
	}

	long equiLeader = 0;
	for ( long i = 0; i < N; i++ ) {
		auto l1 = findLeader( A, 0, i );
		auto l2 = findLeader( A, i + 1, N - 1 );

		if ( l1 >= 0 && A[ l1 ] == A[ l2 ] ) {
			equiLeader++;
		}
	}
	return equiLeader;
}

void test( std::vector< int > A )
{
	auto got = solution( A );
	auto expected = brute( A );

	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

std::vector< int > generateRandomVector( size_t size = 100000 )
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
	test( { 4, 3, 4, 4, 4, 2 } ),
	test( { 3, 4, 3, 2, 3, -1, 3, 3 } );
	test( { 3 } );
	test( { 3, 3 } );
	test( { 1, 3, 3 } );
	test( { 1, 3, 3, 2, 2, 2 } );
	test( { 1, 3 } );
	test( { 1, 2, 1, 2, 1 } );
	test( { 1, 1, 2, 2 } );
	test( { 1, 1, 3, 1, 1 } );
	test( generateRandomVector( 30 ) );
	test( generateRandomVector( 30 ) );
	test( generateRandomVector( 30 ) );
	test( generateRandomVector( 30 ) );
	test( generateRandomVector( 30 ) );
	
	return 0;
}

