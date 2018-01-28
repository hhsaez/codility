/*

 */

#include "../Utils.hpp"

#include <unordered_set>

struct Point2D {
	int x;
	int y;
};

int solution( std::vector< Point2D > A )
{
	const int N = A.size();

	std::unordered_set< double > angles;

	for ( int i = 0; i < N; i++ ) {
		auto x = A[ i ].x;
		auto y = A[ i ].y;

		double angle = std::atan2( y, x );
		angles.insert( angle );
	}
	
	return angles.size();
}

void test( std::vector< Point2D> A, int expected )
{
	codility::compareResults( solution( A ), expected );
}

int main( int argc, char **argv )
{
	test( { { -1, -2 }, { 1, 2 }, { 2, 4 }, { -3, 2 }, { 2, -2 } }, 4 );
	test( { { -1000000000, -1000000000 }, { 1000000000, -1000000000 } }, 2 );
	test( { { 1, 1 } }, 1 );
	test( { { 1, 0 } }, 1 );
	test( { { 0, 1 } }, 1 );
	test( { { 1, 1 }, { -1, -1 } }, 2 );
	test( { { 1, 0 }, { -1, 0 } }, 2 );
	test( { { 0, 1 }, { 0, -1 } }, 2 );
	test( { { 1, 1 }, { 1, 1, } }, 1 );
	
	return 0;
}

