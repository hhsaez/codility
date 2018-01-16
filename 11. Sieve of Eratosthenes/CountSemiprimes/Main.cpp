/*

A prime is a positive integer X that has exactly two distinct divisors: 1 and X. The first 
few prime integers are 2, 3, 5, 7, 11 and 13.

A semiprime is a natural number that is the product of two (not necessarily distinct) prime 
numbers. The first few semiprimes are 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.

You are given two non-empty zero-indexed arrays P and Q, each consisting of M integers. 
These arrays represent queries about the number of semiprimes within specified ranges.

Query K requires you to find the number of semiprimes within the range (P[K], Q[K]), 
where 1 ≤ P[K] ≤ Q[K] ≤ N.

For example, consider an integer N = 26 and arrays P, Q such that:

    P[0] = 1    Q[0] = 26
    P[1] = 4    Q[1] = 10
    P[2] = 16   Q[2] = 20
The number of semiprimes within each of these ranges is as follows:

 (1, 26) is 10,
 (4, 10) is 4,
 (16, 20) is 0.
Write a function:

vector<int> solution(int N, vector<int> &P, vector<int> &Q);

that, given an integer N and two non-empty zero-indexed arrays P and Q consisting of M 
integers, returns an array consisting of M elements specifying the consecutive answers to 
all the queries.

For example, given an integer N = 26 and arrays P, Q such that:

    P[0] = 1    Q[0] = 26
    P[1] = 4    Q[1] = 10
    P[2] = 16   Q[2] = 20
the function should return the values [10, 4, 0], as explained above.

Assume that:

N is an integer within the range [1..50,000];
M is an integer within the range [1..30,000];
each element of arrays P, Q is an integer within the range [1..N];
P[i] ≤ Q[i].
Complexity:

expected worst-case time complexity is O(N*log(log(N))+M);
expected worst-case space complexity is O(N+M), beyond input storage (not counting the storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingBHNRTZ-F38/

*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>

std::string toString( std::vector< int > &A )
{
	std::stringstream ss;
	ss << "[";
	bool first = true;
	for ( auto v : A ) {
		ss << ( first ? "" : ", " ) << v;
		first = false;
	}
	ss << "]";

	return ss.str();
}

std::vector< int > solution( int N, std::vector< int > &P, std::vector< int > &Q )
{
	std::vector< int > factors( N + 1, 0 );
	long i = 2;
	while ( i * i <= N + 1 ) {
		if ( factors[ i ] == 0 ) {
			long k = i * i;
			while ( k <= N + 1 ) {
				if ( factors[ k ] == 0 ) {
					factors[ k ] = i;
				}
				k += i;
			}			
		}
		i++;
	}

	std::vector< int > primeFactors( N + 1 );

	for ( int i = 1; i <= N + 1; i++ ) {
		long count = 0;
		auto x = i;
		while ( factors[ x ] > 0 ) {
			count++;
			x /= factors[ x ];
		}
		
		if ( x > 0 ) {
			count++;
		}

		if ( count == 2 ) {
			primeFactors[ i ] = primeFactors[ i - 1 ] + 1;
		}
		else {
			primeFactors[ i ] = primeFactors[ i - 1 ];
		}
	}

	const auto M = P.size();

	std::vector< int > result( M, 0 );

	for ( size_t test = 0; test < M; test++ ) {
		result[ test ] = primeFactors[ Q[ test ] ] - primeFactors[ P[ test ] - 1 ];
	}

	return result;
}

std::vector< int > brute( int N, std::vector< int > &P, std::vector< int > &Q )
{
	std::vector< int > factors( N + 1, 0 );
	long i = 2;
	while ( i * i <= N + 1 ) {
		if ( factors[ i ] == 0 ) {
			long k = i * i;
			while ( k <= N + 1 ) {
				if ( factors[ k ] == 0 ) {
					factors[ k ] = i;
				}
				k += i;
			}			
		}
		i++;
	}

	const auto M = P.size();

	std::vector< int > result( M, 0 );

	for ( size_t test = 0; test < M; test++ ) {
		for ( int i = P[ test ]; i <= Q[ test ]; i++ ) {
			size_t primeFactors = 0;
			auto x = i;
			while ( factors[ x ] > 0 ) {
				primeFactors++;
				x /= factors[ x ];
			}

			if ( x > 0 ) {
				primeFactors++;
			}
			
			if ( primeFactors == 2 ) {
				result[ test ]++;
			}
		}
	}

	return result;
}

void test( int N, std::vector< int > P, std::vector< int > Q )
{
	static size_t name = 0;
	
	std::cout << name++ << ": ";

	auto got = solution( N, P, Q );
	auto expected = brute( N, P, Q );

	if ( got != expected ) {
		std::cout << "ERROR: got=" << toString( got ) << ", expected=" << toString( expected ) << "\n";
	}
	else {
		std::cout << "PASSED: got=" << toString( got ) << "\n";
	}
}

void generateRandomTest( void )
{
	std::random_device rd;
    std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis( 1, 50000 );

	const auto N = dis( gen );

	test( N, { 1 }, { N } );   
}

int main( int argc, char **argv )
{
	test( 26, { 1, 4, 16 }, { 26, 10, 20 } );
	test( 1, { 1 }, { 1 } );
	test( 25000, { 1, 50, 1000 }, { 800, 20000, 5000 } );

	generateRandomTest();
	generateRandomTest();
	generateRandomTest();
	generateRandomTest();
	
	return 0;
}



