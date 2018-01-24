/*

The Fibonacci sequence is defined using the following recursive formula:

    F(0) = 0
    F(1) = 1
    F(M) = F(M - 1) + F(M - 2) if M >= 2

A small frog wants to get to the other side of a river. The frog is initially located at 
one bank of the river (position −1) and wants to get to the other bank (position N). The 
frog can jump over any distance F(K), where F(K) is the K-th Fibonacci number. Luckily, 
there are many leaves on the river, and the frog can jump between the leaves, but only in 
the direction of the bank at position N.

The leaves on the river are represented in a zero-indexed array A consisting of N integers. 
Consecutive elements of array A represent consecutive positions from 0 to N − 1 on the river. 
Array A contains only 0s and/or 1s:

0 represents a position without a leaf;
1 represents a position containing a leaf.
The goal is to count the minimum number of jumps in which the frog can get to the other side 
of the river (from position −1 to position N). The frog can jump between positions −1 and 
N (the banks of the river) and every position containing a leaf.

For example, consider array A such that:

    A[0] = 0
    A[1] = 0
    A[2] = 0
    A[3] = 1
    A[4] = 1
    A[5] = 0
    A[6] = 1
    A[7] = 0
    A[8] = 0
    A[9] = 0
    A[10] = 0
The frog can make three jumps of length F(5) = 5, F(3) = 2 and F(5) = 5.

Write a function:

int solution(vector<int> &A);

that, given a zero-indexed array A consisting of N integers, returns the minimum number 
of jumps by which the frog can get to the other side of the river. If the frog cannot 
reach the other side of the river, the function should return −1.

For example, given:

    A[0] = 0
    A[1] = 0
    A[2] = 0
    A[3] = 1
    A[4] = 1
    A[5] = 0
    A[6] = 1
    A[7] = 0
    A[8] = 0
    A[9] = 0
    A[10] = 0
the function should return 3, as explained above.

Assume that:

N is an integer within the range [0..100,000];
each element of array A is an integer that can have one of the following values: 0, 1.
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/training22BN7F-RRP/

 */

#include "../../Utils.hpp"

std::vector< long > fib( long N )
{
	std::vector< long > res;
	res.push_back( 1 );
	res.push_back( 2 );
	long next = res[ 0 ] + res[ 1 ];
	while ( next <= N ) {
		res.push_back( next );
		next = res[ long( res.size() ) - 1 ] + res[ long( res.size() ) - 2 ];
	}
	return res;
}

int solution( std::vector<int> A )
{
	// simplify algorithm
	A.insert( A.begin(), 1 );
	A.push_back( 1 );

	const long N = A.size();

	auto f = fib( N + 1 );

	std::vector< int > minJumps( N, -1 );
	minJumps[ 0 ] = 0;
	
	for ( long i = 0; i < N; i++ ) {
		if ( A[ i ] == 1 ) {
			for ( long k = 0; k < f.size() && f[ k ] <= i; k++ ) {
				if ( A[ i - f[ k ] ] == 1 && minJumps[ i - f[ k ] ] >= 0 ) {
					if ( minJumps[ i ] == -1 ) {
						minJumps[ i ] = minJumps[ i - f[ k ] ] + 1;
					}
					else {
						minJumps[ i ] = std::min( minJumps[ i ], minJumps[ i - f[ k ] ] + 1 );
					}
				}
			}
		}
	}

	return minJumps[ N - 1 ];
}

int brute( std::vector< int > A )
{
	const long N = A.size();
	
	auto f = fib( N + 1 );

	std::vector< int > leaves;
	for ( size_t i = 0; i < N; i++ ) {
		if ( A[ i ] == 1 ) {
			leaves.push_back( i + 1 );
		}
	}
	leaves.push_back( N + 1 );

	int count = 0;

	long distance = 0;
	while ( distance <= N ) {
		long next = 0;
		for ( long j = 0; j < f.size(); j++ ) {
			for ( long k = 0; k < leaves.size(); k++ ) {
				if ( f[ j ] == leaves[ k ] - distance ) {
					next = std::max( next, f[ j ] );
				}
			}
		}

		if ( next == 0 ) {
			return -1;
		}

		count++;
	    distance += next;
	}

	return distance == N + 1 ? count : -1;
}

void test( std::vector< int > A )
{
	codility::compareResults( solution( A ), brute( A ) );
}

int main( int argc, char **argv )
{
	test( { 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0 } );

	for ( int i = 0; i < 10; i++ ) {
		std::vector< int > A( i );
		std::vector< int > B( i );
		for ( int j = 0; j < i; j++ ) {
			A[ j ] = 1;
			B[ j ] = 0;
		}
		test( A );
		test( B );
	}
	
	test( { 0 } );
	test( { 0, 1, 0, 1, 0, 1, 1 } );
	test( { 0, 0, 0, 0, 0, 0, 0 } );
	test( { 1, 1, 1, 1, 1, 1, 1 } );
	test( { 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 } );

	return 0;
}

