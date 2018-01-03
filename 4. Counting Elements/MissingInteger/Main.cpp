/*

This is a demo task.

Write a function:

int solution(vector<int> &A);

that, given an array A of N integers, returns the smallest positive integer (greater 
than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000..1,000,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

*/

#include <iostream>
#include <vector>
#include <map>

int solution( std::vector< int > &A )
{
	std::map< int, bool > candidates;
	candidates[ 1 ] = true;

	for ( auto a : A ) {
		if ( a <= 0 ) {
			continue;
		}

		candidates[ a ] = false;
		if ( candidates.count( a + 1 ) == 0 ) {
			candidates[ a + 1 ] = true;
		}
	}

	int result = 1;
	bool first = true;
	for ( auto it : candidates ) {
		if ( it.second ) {
			if ( first || it.first < result ) {
				result = it.first;
				first = false;
			}
		}
	}
			
	return result;
}

void test( std::vector< int > A, int expected )
{
	std::cout << "Input: A=[";
	bool first = true;
	for ( auto a : A ) {
		std::cout << ( first ? "" : ", " ) << a;
		first = false;
	}
	std::cout << "] \n";

	auto got = solution( A );

	if ( got != expected ) {
		std::cout << "ERROR got=" << got << " expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}


int main( int argc, char **argv )
{
	test( { 1, 2, 3 }, 4 );
	test( { -1, -3 }, 1 );
	test( { -1, -2, -3 }, 1 );
	test( { 1000, 2000 }, 1 );
	test( { 1, 2, 3, 4, 5, 6, }, 7 );
	
	return 0;
}

