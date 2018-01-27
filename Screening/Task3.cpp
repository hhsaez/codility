/*

 */

#include "../Utils.hpp"

int solution( std::vector< int > A )
{
	const long N = A.size();

	std::vector< int > indices( N );
	for ( int i = 0; i < N; i++ ) {
		indices[ i ] = i;
	}
	std::sort( std::begin( indices ), std::end( indices ), [&A]( auto &left, auto &right ) {
		return A[ left ] < A[ right ];
	});

	int next = 0;
	int res = 0;

	while ( next < N ) {
		res++;
		next = indices[ next ] + 1;
	}
		
	return res;
}

int simple( std::vector< int > A )
{
	const int N = A.size();

	int start = 0;
	int end = 0;

	int res = 0;

	while ( start < N && end < N ) {
		int min = std::numeric_limits< int >::max();
		for ( int i = start; i < N; i++ ) {
			if ( A[ i ] <= min ) {
				min = A[ i ];
				end = i;
			}
		}

		res++;
		start = end + 1;
		end = start;
	}
	
	return res;
}

void test( std::vector< int > A )
{
	codility::compareResults( solution( A ), simple( A ) );
}

int main( int argc, char **argv )
{
	test( { 1, 5, 4, 9, 8, 7, 12, 13, 14 } );
	test( { 1, 5, 4, 9, 8, 7, 12, 13, 14, 2 } );
	test( { 4, 3, 2, 6, 1 } );
	test( { 1 } );
	return 0;
}

