/*

You have to climb up a ladder. The ladder has exactly N rungs, numbered from 1 to N. With 
each step, you can ascend by one or two rungs. More precisely:

with your first step you can stand on rung 1 or 2,
if you are on rung K, you can move to rungs K + 1 or K + 2,
finally you have to stand on rung N.
Your task is to count the number of different ways of climbing to the top of the ladder.

For example, given N = 4, you have five different ways of climbing, ascending by:

1, 1, 1 and 1 rung,
1, 1 and 2 rungs,
1, 2 and 1 rung,
2, 1 and 1 rungs, and
2 and 2 rungs.
Given N = 5, you have eight different ways of climbing, ascending by:

1, 1, 1, 1 and 1 rung,
1, 1, 1 and 2 rungs,
1, 1, 2 and 1 rung,
1, 2, 1 and 1 rung,
1, 2 and 2 rungs,
2, 1, 1 and 1 rungs,
2, 1 and 2 rungs, and
2, 2 and 1 rung.
The number of different ways can be very large, so it is sufficient to return the result 
modulo 2P, for a given integer P.

Write a function:

vector<int> solution(vector<int> &A, vector<int> &B);

that, given two non-empty zero-indexed arrays A and B of L integers, returns an array 
consisting of L integers specifying the consecutive answers; position I should 
contain the number of different ways of climbing the ladder with A[I] rungs modulo 2B[I].

For example, given L = 5 and:

    A[0] = 4   B[0] = 3
    A[1] = 4   B[1] = 2
    A[2] = 5   B[2] = 4
    A[3] = 5   B[3] = 3
    A[4] = 1   B[4] = 1
the function should return the sequence [5, 1, 8, 0, 1], as explained above.

Assume that:

L is an integer within the range [1..50,000];
each element of array A is an integer within the range [1..L];
each element of array B is an integer within the range [1..30].
Complexity:

expected worst-case time complexity is O(L);
expected worst-case space complexity is O(L), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingQ67MQC-PMB/

 */

#include "../../Utils.hpp"

std::vector< int > solution( std::vector< int > &A, std::vector< int > &B )
{
	std::vector< size_t > f( 50000 + 2, 0 );
	f[ 0 ] = 0;
	f[ 1 ] = 1;
	for ( size_t i = 2; i < f.size(); i++ ) {
		f[ i ] = f[ i - 1 ] + f[ i - 2 ];
	}

	const auto N = A.size();
	
	std::vector< int > result( N );
	
	for ( size_t i = 0; i < N; i++ ) {
		result[ i ] = f[ A[ i ] + 1 ] % ( size_t ) std::pow( 2, B[ i ] );
	}
	
	return result;
}

int bruteFib( long count, int max )
{
	if ( count == max ) {
		return 1;
	}
	if ( count > max ) {
		return 0;
	}

	return bruteFib( count + 1, max ) + bruteFib( count + 2, max );
}

std::vector< int > brute( std::vector< int > &A, std::vector< int > &B )
{
	const auto N = A.size();
	
	std::vector< int > result( N );
	
	for ( size_t i = 0; i < N; i++ ) {
		result[ i ] = bruteFib( 0, A[ i ] ) % ( long ) std::pow( 2, B[ i ] );
	}
	
	return result;
}

void test( std::vector< int > A, std::vector< int > B )
{
	codility::compareResults( solution( A, B ), brute( A, B ) );
}

void generateRandomTest( void )
{
	const size_t L = codility::generateRandom( 1, 50000 + 1 );
	std::vector< int > A( L );
	std::vector< int > B( L );
	for ( size_t i = 0; i < L; i++ ) {
		A[ i ] = codility::generateRandom( 1, L + 1 );
		B[ i ] = codility::generateRandom( 1, 30 + 1 );
	}

	test( A, B );
}

int main( int argc, char **argv )
{
	test( { 4, 4, 5, 5, 1 }, { 3, 2, 4, 3, 1 } );
	test( {}, {} );
	test( { 1, 10 }, { 1, 30 } );

	//generateRandomTest();
	
	return 0;
}

