/*

A positive integer D is a factor of a positive integer N if there exists an integer M such 
that N = D * M.

For example, 6 is a factor of 24, because M = 4 satisfies the above condition (24 = 6 * 4).

Write a function:

int solution(int N);

that, given a positive integer N, returns the number of its factors.

For example, given N = 24, the function should return 8, because 24 has 8 factors, 
namely 1, 2, 3, 4, 6, 8, 12, 24. There are no other factors of 24.

Assume that:

N is an integer within the range [1..2,147,483,647].
Complexity:

expected worst-case time complexity is O(sqrt(N));
expected worst-case space complexity is O(1).

*/

#include <iostream>
#include <random>

int solution( int N )
{
    int count = 0;

	int i = 1;
	for ( ; i * i < N; i++ ) {
		if ( N % i == 0 ) {
			count += 2;
		}
	}

	if ( i * i == N ) {
		count++;
	}
	
	return count;
}

int brute( int N )
{
    int count = 0;

	for ( int i = 1; i <= N; i++ ) {
		if ( N % i == 0 ) {
			count++;
		}
	}
	
	return count;
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
	std::uniform_int_distribution<> dis( 1, std::numeric_limits< int >::max() );

	return dis( gen );
}

int main( int argc, char **argv )
{
	test( 24 );
	test( 1 );
	test( 1000 );
	test( generateRandom() );
	test( generateRandom() );
	test( generateRandom() );
	test( generateRandom() );
	test( std::numeric_limits< int >::max() );
	
	return 0;
}

