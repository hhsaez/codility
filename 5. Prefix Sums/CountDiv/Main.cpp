/*

Write a function:

int solution(int A, int B, int K);

that, given three integers A, B and K, returns the number of integers within the 
range [A..B] that are divisible by K, i.e.: { i : A ≤ i ≤ B, i mod K = 0 }

For example, for A = 6, B = 11 and K = 2, your function should return 3, because 
there are three numbers divisible by 2 within the range [6..11], namely 6, 8 and 10.

Assume that:

A and B are integers within the range [0..2,000,000,000];
K is an integer within the range [1..2,000,000,000];
A ≤ B.
Complexity:

expected worst-case time complexity is O(1);
expected worst-case space complexity is O(1).

 */

#include <iostream>
#include <cmath>

int solution( int A, int B, int K )
{
	if ( A > B ) {
		return 0;
	}
	
	int Amod = A % K;
	if ( Amod != 0 ) {
		A += K - Amod;
	}

	B -= B % K;
	
	return ( B - A ) / K + 1;
}

int brute( int A, int B, int K )
{
	if ( A > B ) {
		return 0;
	}
	
	size_t count = 0;
	for ( int i = A; i <= B; i++ ) {
		if ( i % K == 0 ) {
			count++;
		}		
	}

	return count;
}

void test( int A, int B, int K )
{
	std::cout << "Input: A=" << A << " B=" << B << " K=" << K << "\n";

	auto got = solution( A, B, K );
	auto expected = brute( A, B, K );

	if ( got != expected ) {
		std::cout << "ERROR got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

int main( int argc, char **argv )
{

	test( 6, 11, 2 );
	test( 6, 11, 3 );
	test( 20, 0, 4 );
	test( 0, 20, 4 );
	test( 11, 6, 2 );
	test( 6, 6, 2 );
	test( 6, 6, 3 );
	test( 6, 6, 6 );
	test( 6, 6, 7 );
	test( 0, 1, 11 );
	test( 200, 1000, 120 );
	
	return 0;
}

