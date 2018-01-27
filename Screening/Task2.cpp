/*

 */

#include "../Utils.hpp"

int solution( std::vector< int > A )
{
	std::vector< int > sorted( A );
	std::sort( std::begin( sorted ), std::end( sorted ) );

	const int N = sorted.size();

	int front = 0;
	int res = 0;

	for ( int back = 0; back < N; back++ ) {
		while ( front < N && ( long( sorted[ front ] ) - long( sorted[ back ] ) <= 1 ) ) {
			front++;
		}
		res = std::max( res, front - back );
	}
	
	return res;
}

int simple( std::vector< int > A )
{
	const int N = A.size();

	int res = 0;
	
	for ( int i = 0; i < N; i++ ) {
		long maxAmplitude = 0;
		for ( int j = i; j < N; j++ ) {
			auto max = std::max( A[ i ], A[ j ] );
			auto min = std::min( A[ i ], A[ j ] );
			long amplitude = max - min;
			if ( amplitude <= 1 ) {
				res = std::max( res, j - i + 1 );
			}
		}
	}

	return res;
}

void test( std::vector< int > A )
{
	codility::compareResults( solution( A ), simple( A ) );
}

int main( int argc, char **argv )
{
	test( { 6, 10, 6, 9, 7, 8 } );
	test( { 6 } );
	test( { std::numeric_limits< int >::min(), std::numeric_limits< int >::min() + 1 } );
	test( { std::numeric_limits< int >::min(), std::numeric_limits< int >::max() } );
	test( {} );
	return 0;
}

