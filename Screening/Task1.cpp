/*

 */

#include "../Utils.hpp"

#include <set>

struct Point2D {
	int x;
	int y;
};

int solution( std::vector< Point2D > A )
{
	const int N = A.size();

	std::set< double > angles;

	for ( int i = 0; i < N; i++ ) {
		auto x = A[ i ].x;
		auto y = A[ i ].y;

		double angle = std::atan2( y, x );
		angles.insert( angle ); // << O(Nlog(N)) !!!!!
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
	return 0;
}

