/*

There are N giraffes in your zoo. The zoo is famous for the distinct heights of its
giraffes. This means that there are no two giraffes of equal height in the zoo.

The giraffes live in displays located along the main path. Every giraffe has its own display.
For aesthetic reasons, you want the giraffes to be arranged in ascending order of height. 
Reordering all the giraffes at once, however, would cause the animals a lot of stress, so you
want to split the displays into as many smaller groups as possible and reorder all the
groups separately. Agroup should contain one or more consecutive displays. After 
reordering all the groups, the giraffes should be arranged in ascending order of height.

Write a function: 

int solution( std::vector< int > &A );

that, given a zero-indexed array A containing N integer, where A[ i ] denotes the height
of the giraffe in the I-th display, returns the maxim number of groups that can be reordered
independently in order to sort all the giraffes in ascending order of height.

For example, given A = [1, 5, 4, 9, 8, 7, 12, 13, 14], the function should return 6. Displays
can be split into six groups: [1], [5, 4], [9, 8, 7], [12], [13], [14]. Then, after 
reordering each group, the whole sequence of giraffes will be sorted into ascending order.
Note that group [12, 13, 14] was already ordered correctly, so it could be split into three
groups, each containing one giraffe.

Given A = [4, 3, 2, 6, 1], the function should return 1. Displays cannot be split into smaller
groups; the giraffes have to be sorted all at once.

Assume that:

* N is an integer within the range [1..100000];
* each element of array A is an integer within the range [1..1000000000];
* the elements of A are all distinct.

Complexity:

* expected worst-case time complexity is O(N*log(N));
* expected worst-case space complexity is O(N), beyond input storage (not counting
the storage required for input arguments).

 */

#include "../Utils.hpp"

#include <stack>

int solution( std::vector< int > A )
{
	const long N = A.size();

	std::stack< int > groups;

	for ( int i = 0; i < N; i++ ) {
		if ( groups.empty() || A[ i ] > groups.top() ) {
			// new group
			groups.push( A[ i ] );
		}
		else {
			auto current = groups.top();
			groups.pop();
			while ( !groups.empty() && A[ i ] < groups.top() ) {
				groups.pop();
			}
			groups.push( current );
		}
	}

	return groups.size();
}

void test( std::vector< int > A, int expected )
{
	codility::compareResults( solution( A ), expected );
}

int main( int argc, char **argv )
{
	test( { 1, 5, 4, 9, 8, 7, 12, 13, 14 }, 6 );
	test( { 1, 5, 4, 9, 8, 7, 12, 13, 14, 2 }, 2 );
	test( { 4, 3, 2, 6, 1 }, 1 );
	test( { 1, 2, 3, 4, 5, 6 }, 6 );
	test( { 1 }, 1 );
	test( {}, 0 );
	test( { 1, 2, 3, 4 }, 4 );
	test( { 4, 3, 2, 1 }, 1 );
	test( { 5, 1, 2 }, 1 );
	test( { 4, 5, 6, 10, 9, 8, 11, 7 }, 4 );

	// should be 3, but input is invalid (different heights only)
	test( { 1, 5, 5, 4 }, 2 ); 
	
	return 0;
}

