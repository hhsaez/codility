/*

A zero-indexed array A consisting of N integers is given. It contains daily prices of a
 stock share for a period of N consecutive days. If a single share was bought on day P 
and sold on day Q, where 0 ≤ P ≤ Q < N, then the profit of such transaction is equal 
to A[Q] − A[P], provided that A[Q] ≥ A[P]. Otherwise, the transaction brings loss 
of A[P] − A[Q].

For example, consider the following array A consisting of six elements such that:

  A[0] = 23171
  A[1] = 21011
  A[2] = 21123
  A[3] = 21366
  A[4] = 21013
  A[5] = 21367
If a share was bought on day 0 and sold on day 2, a loss of 2048 would occur 
because A[2] − A[0] = 21123 − 23171 = −2048. If a share was bought on day 4 and sold on 
day 5, a profit of 354 would occur because A[5] − A[4] = 21367 − 21013 = 354. Maximum 
possible profit was 356. It would occur if a share was bought on day 1 and sold on day 5.

Write a function,

int solution(vector<int> &A);

that, given a zero-indexed array A consisting of N integers containing daily prices of a 
stock share for a period of N consecutive days, returns the maximum possible profit 
from one transaction during this period. The function should return 0 if it was 
impossible to gain any profit.

For example, given array A consisting of six elements such that:

  A[0] = 23171
  A[1] = 21011
  A[2] = 21123
  A[3] = 21366
  A[4] = 21013
  A[5] = 21367
the function should return 356, as explained above.

Assume that:

N is an integer within the range [0..400,000];
each element of array A is an integer within the range [0..200,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(1), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingGJVVSD-RZG/
*/

#include <iostream>
#include <vector>
#include <random>

int solution( std::vector< int > &A )
{
	const auto N = A.size();
	if ( N < 2 ) {
		return 0;
	}

	long buy = A[ 0 ];
	long maxProfit = 0;
	
	for ( size_t i = 1; i < N; i++ ) {
		auto gain = ( long ) A[ i ] - buy;
		buy = std::min( buy, ( long ) A[ i ] );
		maxProfit = std::max( maxProfit, gain );
	}

	return maxProfit;
}

int brute( std::vector< int > &A )
{
	const auto N = A.size();
	long result = 0;

	for ( size_t i = 0; i < N; i++ ) {
		for ( size_t j = i + 1; j < N; j++ ) {
			auto gain = ( long ) A[ j ] - ( long ) A[ i ];
			result = std::max( gain, result );
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
	std::uniform_int_distribution<> dis( 0, 200001 );

	std::vector< int > v1( size );
	for ( size_t i = 0; i < size; i++ ) {
		v1[ i ] = dis( gen );
	}

	return v1;
}	

int main( int argc, char **argv )
{
	test( { 23171, 21011, 21123, 21366, 21013, 21367 } );
	test( { } );
	test( { 1000 } );
	test( { 1000, 500 } );
	test( { 0, 200000 } );
	test( generateRandomVector( 10 ) );
	test( generateRandomVector( 20 ) );
	test( generateRandomVector( 30 ) );
	test( generateRandomVector( 100 ) );
	test( generateRandomVector( 1000 ) );

	return 0;
}

