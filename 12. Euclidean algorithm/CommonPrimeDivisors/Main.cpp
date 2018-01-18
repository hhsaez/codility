/*

A prime is a positive integer X that has exactly two distinct divisors: 1 and X. The first 
few prime integers are 2, 3, 5, 7, 11 and 13.

A prime D is called a prime divisor of a positive integer P if there exists a positive 
integer K such that D * K = P. For example, 2 and 5 are prime divisors of 20.

You are given two positive integers N and M. The goal is to check whether the sets of 
prime divisors of integers N and M are exactly the same.

For example, given:

N = 15 and M = 75, the prime divisors are the same: {3, 5};
N = 10 and M = 30, the prime divisors aren't the same: {2, 5} is not equal to {2, 3, 5};
N = 9 and M = 5, the prime divisors aren't the same: {3} is not equal to {5}.

Write a function:

int solution(vector<int> &A, vector<int> &B);

that, given two non-empty zero-indexed arrays A and B of Z integers, returns the number 
of positions K for which the prime divisors of A[K] and B[K] are exactly the same.

For example, given:

    A[0] = 15   B[0] = 75
    A[1] = 10   B[1] = 30
    A[2] = 3    B[2] = 5

the function should return 1, because only one pair (15, 75) has the same set of prime 
divisors.

Assume that:

Z is an integer within the range [1..6,000];
each element of arrays A, B is an integer within the range [1..2,147,483,647].
Complexity:

expected worst-case time complexity is O(Z*log(max(A)+max(B))2);
expected worst-case space complexity is O(1), beyond input storage (not counting the 
storage required for input arguments).

Result (100%):
https://app.codility.com/demo/results/training82XSDX-MQT/

 */

#include "../../Utils.hpp"

#include <set>

int gcd( int a, int b, int res )
{
	if ( a == b ) {
		return a * res;
	}
	else if ( a % 2 == 0 && b % 2 == 0 ) {
		return gcd( a / 2, b / 2, 2 * res );
	}
	else if ( a % 2 == 0 ) {
		return gcd( a / 2, b, res );
	}
	else if ( b % 2 == 0 ) {
		return gcd( a, b / 2, res );
	}
	else if ( a > b ) {
		return gcd( a - b, b, res );
	}
	else {
		return gcd( b - a, a, res );
	}
}

bool hasSameFactors( int a, int b )
{
	auto x = gcd( a, b, 1 );

	while ( a != 1 ) {
		auto y = gcd( a, x, 1 );
		if ( y == 1 ) {
			return false;
		}
		a /= y;
	}

	while ( b != 1 ) {
		auto y = gcd( b, x, 1 );
		if ( y == 1 ) {
			return false;
		}
		b /= y;
	}

	return true;
}

int solution( std::vector< int > &A, std::vector< int > &B )
{
	const long Z = std::min( A.size(), B.size() );

	int count = 0;
	
	for ( int z = 0; z < Z; z++ ) {

		auto a = A[ z ];
		auto b = B[ z ];

		if ( hasSameFactors( a, b ) ) {
			count++;
		}
	}
	
	return count;
}

bool isPrime( int N )
{
	if ( N < 2 ) {
		return false;
	}
	
	int i = 2;
	while ( i * i <= N ) {
		if ( N % i == 0 ) {
			return false;
		}
	    i++;
	}
	
	return true;
}

std::set< int > primeDivisors( int N )
{
	int i = 1;
	std::set< int > result;

	while ( i * i < N ) {
		if ( N % i == 0 ) {
			if ( isPrime( i ) ) {
				result.insert( i );
			}
			if ( isPrime( N / i ) ) {
				result.insert( N / i );
			}
		}
		i++;
	}

	if ( i * i == N ) {
		if ( isPrime( i ) ) {
			result.insert( i );
		}
	}

	return result;
}

int brute( std::vector< int > &A, std::vector< int > &B )
{
	const long Z = std::min( A.size(), B.size() );

	int count = 0;
	
	for ( int z = 0; z < Z; z++ ) {
		auto divA = primeDivisors( A[ z ] );
		auto divB = primeDivisors( B[ z ] );

		if ( divA == divB ) {
			count++;
		}
	}
	
	return count;
}

void test( std::vector< int > A, std::vector< int > B )
{
	codility::compareResults( solution( A, B ), brute( A, B ) );
}

void generateRandomTest( void )
{
	auto Z = codility::generateRandom( 1, 6001 );

	std::vector< int > A( Z );
	std::vector< int > B( Z );
	
	for ( int z = 0; z < Z; z++ ) {
		A[ z ] = codility::generateRandom( 1, std::numeric_limits< int >::max() );

		auto divA = primeDivisors( A[ z ] );
		int b = 1;
		for ( auto a : divA ) {
			b *= a;
		}
		B[ z ] = b;
	}

	test( A, B );
}

int main( int argc, char **argv )
{
	test( { 15, 10, 3 }, { 75, 30, 5 } );
	test( { 8, 15, 10, 3 }, { 5, 75, 30, 5 } );
	test( { 8 }, { 4 } );
	test( { 15, 8 }, { 75, 4 } );
	test( { 50 }, { 100 } );
	test( { 6 }, { 9 } );

	generateRandomTest();
	generateRandomTest();
	generateRandomTest();
	generateRandomTest();
	
	return 0;
}

