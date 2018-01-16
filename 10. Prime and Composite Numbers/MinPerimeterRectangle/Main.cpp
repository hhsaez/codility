/*

An integer N is given, representing the area of some rectangle.

The area of a rectangle whose sides are of length A and B is A * B, and the perimeter 
is 2 * (A + B).

The goal is to find the minimal perimeter of any rectangle whose area equals N. The sides 
of this rectangle should be only integers.

For example, given integer N = 30, rectangles of area 30 are:

 (1, 30), with a perimeter of 62,
 (2, 15), with a perimeter of 34,
 (3, 10), with a perimeter of 26,
 (5, 6), with a perimeter of 22.

Write a function:

int solution(int N);

that, given an integer N, returns the minimal perimeter of any rectangle whose area is
 exactly equal to N.

For example, given an integer N = 30, the function should return 22, as explained above.

Assume that:

N is an integer within the range [1..1,000,000,000].
Complexity:

expected worst-case time complexity is O(sqrt(N));
expected worst-case space complexity is O(1).

Results (100%):
https://app.codility.com/demo/results/trainingMUNZH5-PQW/

 */

#include <iostream>
#include <random>

int solution( int N )
{
	long i = 1;
	auto result = std::numeric_limits< long >::max();

	while ( i * i <= N ) {
		if ( N % i == 0 ) {
			auto A = i;
			auto B = ( long ) N / i;
			auto p = 2 * ( A + B );
			if ( p < result ) {
				result = p;
			}
		}
		i++;
	}

	return result;
}

int brute( int N )
{
	long result = std::numeric_limits< long >::max();
	
	for ( int i = 1; i <= N; i++ ) {
		if ( N % i != 0 ) {
			continue;
		}
		
		auto A = i;
		auto B = N / i;

		auto p = 2 * ( ( long ) A + ( long ) B );
		if ( p < result ) {
			result = p;
		}
	}

	return result;
}

void test( int N )
{
	static size_t test = 0;
	
	auto got = solution( N );
	auto expected = brute( N );

	if ( got != expected ) {
		std::cout << test++ << " ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << test++ << " OK\n";
	}
}

int generateRandom( void )
{
	std::random_device rd;
    std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis( 1, 1000000001 );

	return dis( gen );
}	

int main( int argc, char **argv )
{
	test( 30 );
	test( 1 );
	test( 101 );
	test( 1234 );
	test( 4564320 );
	test( 15486451 );
	test( 100000000 );
	test( generateRandom() );
	test( generateRandom() );
	test( generateRandom() );
	test( generateRandom() );

	return 0;
}

