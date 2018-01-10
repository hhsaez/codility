/*

We draw N discs on a plane. The discs are numbered from 0 to N − 1. A zero-indexed array A 
of N non-negative integers, specifying the radiuses of the discs, is given. The J-th disc 
is drawn with its center at (J, 0) and radius A[J].

We say that the J-th disc and K-th disc intersect if J ≠ K and the J-th and K-th discs have 
at least one common point (assuming that the discs contain their borders).

The figure below shows discs drawn for N = 6 and A as follows:

  A[0] = 1
  A[1] = 5
  A[2] = 2
  A[3] = 1
  A[4] = 4
  A[5] = 0


There are eleven (unordered) pairs of discs that intersect, namely:

discs 1 and 4 intersect, and both intersect with all the other discs;
disc 2 also intersects with discs 0 and 3.
Write a function:

int solution(vector<int> &A);

that, given an array A describing N discs as explained above, returns the number 
of (unordered) pairs of intersecting discs. The function should return −1 if the number of 
intersecting pairs exceeds 10,000,000.

Given array A shown above, the function should return 11, as explained above.

Assume that:

N is an integer within the range [0..100,000];
each element of array A is an integer within the range [0..2,147,483,647].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/training92NDW2-BGF/

 */

#include <iostream>
#include <algorithm>
#include <random>

int solution( std::vector< int > &A )
{
	const auto N = A.size();
	
	struct Disk {
		long begin;
		long end;
		long center;
	};

	std::vector< Disk > disks( N );
	for ( long i = 0; i < N; i++ ) {
		disks[ i ].begin = i - A[ i ];
		disks[ i ].end = i + A[ i ];
		disks[ i ].center = i;
	}

	std::sort( std::begin( disks ), std::end( disks ), []( const Disk &a, const Disk &b ) -> bool {
		return a.begin < b.begin;
	});

	long i = 0;
	long j = i + 1;
	int count = 0;

	while ( i < N && j < N ) {
		if ( disks[ j ].begin <= disks[ i ].end ) {
			count++;
			if ( count > 10000000 ) {
				return -1;
			}
			j++;
			if ( j == N ) {
				i++;
				j = i + 1;
			}
		}
		else {
			i++;
			j = i + 1;
		}
	}

	return count;
}

int brute( std::vector< int > &A )
{
	auto N = A.size();

	int count = 0;
	for ( size_t i = 0; i < N; i++ ) {
		for ( size_t j = i + 1; j < N; j++ ) {
			if ( std::fabs( ( long ) i - ( long ) j ) <= ( ( long ) A[ i ] + ( long ) A[ j ] ) ) {
				count++;
				if ( count > 10000000 ) {
					return -1;
				}
			}
		}
	}
	
	return count;
}

void test( std::vector< int > A )
{

	std::cout << "Input A=[";
	bool first = true;
	for ( auto a : A ) {
		std::cout << ( first ? "" : ", " ) << a;
		first = false;
	}
	std::cout << "]\n";

	auto got = solution( A );
	auto expected = brute( A );

	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

std::vector< int > generateRandomVector( size_t size )
{
	std::random_device rd;
    std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis( 0, std::numeric_limits< int >::max() );

	std::vector< int > v1( size );
	for ( size_t i = 0; i < size; i++ ) {
		v1[ i ] = dis( gen );
	}

	return v1;
}

int main( int argc, char **argv )
{
	test( { 1, 5, 2, 1, 4, 0 } );
	return 0;
}

