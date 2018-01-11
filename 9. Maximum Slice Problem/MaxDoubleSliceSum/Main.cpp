/*

A non-empty zero-indexed array A consisting of N integers is given.

A triplet (X, Y, Z), such that 0 ≤ X < Y < Z < N, is called a double slice.

The sum of double slice (X, Y, Z) is the total of 

A[X + 1] + A[X + 2] + ... + A[Y − 1] + A[Y + 1] + A[Y + 2] + ... + A[Z − 1].

For example, array A such that:

    A[0] = 3
    A[1] = 2
    A[2] = 6
    A[3] = -1
    A[4] = 4
    A[5] = 5
    A[6] = -1
    A[7] = 2

contains the following example double slices:

double slice (0, 3, 6), sum is 2 + 6 + 4 + 5 = 17,
double slice (0, 3, 7), sum is 2 + 6 + 4 + 5 − 1 = 16,
double slice (3, 4, 5), sum is 0.

The goal is to find the maximal sum of any double slice.

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A consisting of N integers, returns the 
maximal sum of any double slice.

For example, given:

    A[0] = 3
    A[1] = 2
    A[2] = 6
    A[3] = -1
    A[4] = 4
    A[5] = 5
    A[6] = -1
    A[7] = 2
the function should return 17, because no double slice of array A has a sum of greater 
than 17.

Assume that:

N is an integer within the range [3..100,000];
each element of array A is an integer within the range [−10,000..10,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the
 storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingQHSKUC-CJ7/

*/

#include <iostream>
#include <vector>
#include <random>

int solution( std::vector< int > &A )
{
	const auto N = A.size();
	if ( N <= 3 ) {
		return 0;
	}

	std::vector< long > leftSum( N );
	std::vector< long > rightSum( N );

	for ( size_t i = 1; i < N - 1; i++ ) {
		leftSum[ i ] = std::max( 0l, leftSum[ i - 1 ] + A[ i ] );
	}

	for ( size_t i = N - 2; i > 0; i-- ) {
		rightSum[ i ] = std::max( 0l, rightSum[ i + 1 ] + A[ i ] );
	}

	long result = 0;

	for ( size_t i = 1; i < N - 1; i++ ) {
		result = std::max( result, leftSum[ i - 1 ] + rightSum[ i + 1 ] );
	}

	return result;
}

int brute( std::vector< int > &A )
{
	const auto N = A.size();
	if ( N <= 3 ) {
		return 0;
	}
	
	long result = std::numeric_limits< long >::min();

	for ( size_t X = 0; X < N - 2; X++ ) {
		for ( size_t Y = X + 1; Y < N - 1; Y++ ) {
			for ( size_t Z = Y + 1; Z < N; Z++ ) {
				long sum = 0;
				for ( size_t i = X + 1; i <= Z - 1; i++ ) {
					if ( i == Y ) {
						continue;
					}
					sum += A[ i ];
				}
				result = std::max( result, sum );
			}
		}
	}

	return result;
}

void test( std::vector< int > A )
{
	auto got = solution( A );
	auto expected = brute( A );

	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << std::endl;
	}
	else {
		std::cout << "OK\n";
	}
}

std::vector< int > generateRandomVector( size_t size = 400000 )
{
	std::random_device rd;
    std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis( -10000, 10001 );

	std::vector< int > v1( size );
	for ( size_t i = 0; i < size; i++ ) {
		v1[ i ] = dis( gen );
	}

	return v1;
}	

int main( int argc, char **argv )
{
	test( { 3, 2, 6, -1, 4, 5, -1, 2 } );
	test( { 3, 2, 6, -1 } );
	test( { 1 } );
	test( { 1, 2 } );
	test( { 1, 2, 3 } );
	test( { 0, 0, 0 } );
	test( { -1, -2, -3 } );
	test( { -1, -2, -3, -4 } );
	test( { -10000, 0, 10000 } );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 20 ) );
	test( generateRandomVector( 30 ) );

	return 0;
}

