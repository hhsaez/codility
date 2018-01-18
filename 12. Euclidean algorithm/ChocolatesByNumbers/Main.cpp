/*

Two positive integers N and M are given. Integer N represents the number of chocolates 
arranged in a circle, numbered from 0 to N − 1.

You start to eat the chocolates. After eating a chocolate you leave only a wrapper.

You begin with eating chocolate number 0. Then you omit the next M − 1 chocolates or 
wrappers on the circle, and eat the following one.

More precisely, if you ate chocolate number X, then you will next eat the chocolate 
with number (X + M) modulo N (remainder of division).

You stop eating when you encounter an empty wrapper.

For example, given integers N = 10 and M = 4. You will eat the following 
chocolates: 0, 4, 8, 2, 6.

The goal is to count the number of chocolates that you will eat, following the above rules.

Write a function:

int solution(int N, int M);

that, given two positive integers N and M, returns the number of chocolates that you will eat.

For example, given integers N = 10 and M = 4. the function should return 5, as 
explained above.

Assume that:

N and M are integers within the range [1..1,000,000,000].
Complexity:

expected worst-case time complexity is O(log(N+M));
expected worst-case space complexity is O(log(N+M)).

Result (100%):
https://app.codility.com/demo/results/trainingCDJK8J-63G/

 */

#include "../../Utils.hpp"

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

int solution( int N, int M )
{
	int x = gcd( N, M, 1 );
	return N / x;
}

int brute( int N, int M )
{
	std::vector< bool > eaten( N, false );

	int i = 0;
	long count = 0;
	while ( !eaten[ i ] ) {
		eaten[ i ] = true;
		i = ( i + M ) % N;
		count++;
	}
	
	return count;
}

void test( int N, int M )
{
	codility::compareResults( solution( N, M ), brute( N, M ) );
}

void generateRandomTest( int limit )
{
	auto N = codility::generateRandom( 1, limit );
	auto M = codility::generateRandom( 1, limit );
	test( N, M );
}

int main( int argc, char **argv )
{
	test( 10, 4 );
	test( 4, 2 );
	test( 1, 10 );
	test( 1000000000, 8 );

	generateRandomTest( 1000 );
	generateRandomTest( 10000);
	generateRandomTest( 100000 );
	generateRandomTest( 1000000 );
	
	return 0;
}
