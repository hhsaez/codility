/*

A zero-indexed array A consisting of N integers is given. The dominator of array A is the 
value that occurs in more than half of the elements of A.

For example, consider array A such that

 A[0] = 3    A[1] = 4    A[2] =  3
 A[3] = 2    A[4] = 3    A[5] = -1
 A[6] = 3    A[7] = 3

The dominator of A is 3 because it occurs in 5 out of 8 elements of A (namely in those 
with indices 0, 2, 4, 6 and 7) and 5 is more than a half of 8.

Write a function

int solution(vector<int> &A);

that, given a zero-indexed array A consisting of N integers, returns index of any element 
of array A in which the dominator of A occurs. The function should return −1 if array A 
does not have a dominator.

Assume that:

N is an integer within the range [0..100,000];
each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].
For example, given array A such that

 A[0] = 3    A[1] = 4    A[2] =  3
 A[3] = 2    A[4] = 3    A[5] = -1
 A[6] = 3    A[7] = 3
the function may return 0, 2, 4, 6 or 7, as explained above.

Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(1), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingN7TZ7D-RCB/

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
	size_t first = N;
	
	for ( size_t i = 0; i < N; i++ ) {
		if ( A[ i ] == value ) {
			size++;
			if ( i < first ) {
				first = i;
			}
		}
	}

	return ( size > N / 2 ? first : -1 );
}

int brute( std::vector< int > &A )
{
	const auto N = A.size();

	size_t maxCount = 0;
	size_t candidate = -1;
	
	for ( size_t i = 0; i < N; i++ ) {
		size_t count = 0;
		for ( size_t j = 0; j < N; j++ ) {
			if ( A[ j ] == A[ i ] ) {
				count++;
			}
		}
		if ( count > N / 2 ) {
			return i;
		}
	}

	return -1;
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
	test( { 3, 4, 3, 2, 3, -1, 3, 3 } );
	test( { 3 } );
	test( { 3, 3 } );
	test( { 1, 3, 3 } );
	test( { 1, 3, 3, 2, 2, 2 } );
	test( { 1, 3 } );
	test( { 1, 2, 1, 2, 1 } );
	test( generateRandomVector( 30 ) );
	
	return 0;
}

