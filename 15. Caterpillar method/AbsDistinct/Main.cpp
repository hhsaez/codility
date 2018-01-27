/*

A non-empty zero-indexed array A consisting of N numbers is given. The array is sorted in 
non-decreasing order. The absolute distinct count of this array is the number of 
distinct absolute values among the elements of the array.

For example, consider array A such that:

  A[0] = -5
  A[1] = -3
  A[2] = -1
  A[3] =  0
  A[4] =  3
  A[5] =  6

The absolute distinct count of this array is 5, because there are 5 distinct absolute 
values among the elements of this array, namely 0, 1, 3, 5 and 6.

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A consisting of N numbers, returns absolute 
distinct count of array A.

For example, given array A such that:

  A[0] = -5
  A[1] = -3
  A[2] = -1
  A[3] =  0
  A[4] =  3
  A[5] =  6

the function should return 5, as explained above.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−2,147,483,648..2,147,483,647];
array A is sorted in non-decreasing order.
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

Results (100%):
https://app.codility.com/demo/results/training68Q388-2HM/

*/

#include "../../Utils.hpp"

#include <set>

int solution( std::vector< int > A )
{
	std::set< int > s;
	for ( auto a : A ) {
		s.insert( std::abs( a ) );
	}

	return s.size();
}

void test( std::vector< int > A, int expected )
{
	codility::compareResults( solution( A ), expected );
}

int main( int argc, char **argv )
{
	test( { -5, -3, -1, 0, 3, 6 }, 5 );
	test( {}, 0 );
	test( { 1, -1 }, 1 );
	test( { 0 }, 1 );
	test( { -5, -5, -5, -5, -5 }, 1 );
	test( { std::numeric_limits< int >::min(), std::numeric_limits< int >::max() }, 2 );
	test( { std::numeric_limits< int >::min() + 1, std::numeric_limits< int >::max() }, 1 );
	
	return 0;
}

