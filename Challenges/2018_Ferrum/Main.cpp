/*

You are given an array A consisting of the integers −1, 0 and 1. A slice of that array 
is any pair of integers (P, Q) such that 0 ≤ P ≤ Q < N. Your task is to find the longest 
slice of A whose elements yield a non-negative sum.

Write a function:

int solution(vector<int> &A);

that, given an array A of length N, consisting only of the values −1, 0, 1, returns the 
length of the longest slice of A that yields a non-negative sum. If there's no such slice, 
your function should return 0.

For example, given A = [−1, −1, 1, −1, 1, 0, 1, −1, −1], your function should return 7, as 
the slice starting at the second position and ending at the eighth is the longest slice 
with a non-negative sum.

For another example, given A = [1, 1, −1, −1, −1, −1, −1, 1, 1] your function should 
return 4: both the first four elements and the last four elements of array A are 
longest valid slices.

Assume that:

N is an integer within the range [2..100,000];
each element of array A is an integer within the range [−1..1].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

 */

#include "../../Utils.hpp"

#include <queue>
#include <stack>

int solution( std::vector< int > A )
{
	std::vector< int > B( A );
	
	const long N = A.size();

#if 1
	std::stack< long > qNegative;
	std::stack< long > qPositive;

	std::cout << codility::toString( B ) << std::endl;
	
	for ( long i = 0; i < N; i++ ) {
		if ( B[ i ] < 0 ) {
			if ( qPositive.empty() ) {
				qNegative.push( i );
			}
			else {
				auto other = qPositive.top();
				qPositive.pop();
				B[ i ] = 0;
				B[ other ] = 0;
			}
		}
		else if ( B[ i ] > 0 ) {
			if ( qNegative.empty() ) {
				qPositive.push( i );
			}
			else {
				auto other = qNegative.top();
				qNegative.pop();
				B[ i ] = 0;
				B[ other ] = 0;
			}
		}
	}
#elif 0
	long i = 0;
	long j = 1;

	while ( i < N && j < N ) {
		if ( B[ i ] + B[ j ] == 0 ) {
			B[ i ] = 0;
			B[ j ] = 0;
			i++;
			j = i + 1;
		}
		else {
			j++;
		}
	}
#else
	std::stack< long > qNegative;
	std::stack< long > qPositive;

	std::cout << codility::toString( B ) << std::endl;
	
	for ( long i = 0; i < N; i++ ) {
		if ( B[ i ] < 0 ) {
			qNegative.push( i );
		}
		else if ( B[ i ] > 0 ) {
			qPositive.push( i );
		}
	}

	while ( !qNegative.empty() && !qPositive.empty() ) {
		auto i = qNegative.top();
		qNegative.pop();

		auto j = qPositive.top();
		qPositive.pop();

		B[ i ] = 0;
		B[ j ] = 0;
	std::cout << codility::toString( B ) << std::endl;
	
	}

#endif

	std::cout << codility::toString( B ) << std::endl;
	
	long count = 0;
	long result = 0;
	for ( long i = 0; i < N; i++ ) {
		if ( B[ i ] >= 0 ) {
			count++;
			result = std::max( result, count );
		}
		else {
			count = 0;
		}
	}
	
	return result;
}

int caterpillar( std::vector< int > A )
{
	const long N = A.size();

	long front = 0;
	long total = 0;
	long maxLength = -1;

	for ( long back = 0; back < N; back++ ) {
		while ( front < N && total + A[ front ] >= 0 ) {
			front++;
			maxLength = std::max( maxLength, front - back + 1 );
			total += A[ front ];
		}
		if ( front >= N ) {
			return maxLength;
		}
		total -= A[ back ];
	}

	return -1;
}

/**
   Silver Certificate: 
   https://app.codility.com/cert/view/certP52E6K-9HT63EKFPANW45VU/
 */
int silver( std::vector< int > A )
{
	const long N = A.size();
	
	long count = 0;
	for ( long i = 0; i < N; i++ ) {
		long sum = 0;
		for ( long j = i; j < N; j++ ) {
			sum += A[ j ];
			if ( sum >= 0 ) {
				count = std::max( count, j - i + 1 );
			}
		}
	}

	return count;
}

void test( std::vector< int > A )
{
	codility::compareResults( caterpillar( A ), silver( A ) );
}

int main( int argc, char **argv )
{
	test( { -1, -1, 1, -1, 1, 0, 1, -1, -1 } );
	test( { 1, 1, -1, -1, -1, -1, -1, 1, 1 } );
	test( { -1, -1, -1, -1, -1 } );
	test( { -1, -1, 1, -1, -1 } );
	test( { -1, -1, 1, -1, -1, 1 } );
	test( { 1, 1 } );
	test( { 1 } );
	test( { -1 } );
	test( { -1, -1, -1, 1, 1, 1 } );
	test( { -1, 1, -1, -1, 0, 0, 1, -1, 1 } );
	return 0;
}

