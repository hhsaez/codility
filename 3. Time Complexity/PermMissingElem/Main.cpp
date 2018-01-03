/*

A zero-indexed array A consisting of N different integers is given. The array contains 
integers in the range [1..(N + 1)], which means that exactly one element is missing.

Your goal is to find that missing element.

Write a function:

int solution(vector<int> &A);

that, given a zero-indexed array A, returns the value of the missing element.

For example, given array A such that:

  A[0] = 2
  A[1] = 3
  A[2] = 1
  A[3] = 5
the function should return 4, as it is the missing element.

Assume that:

N is an integer within the range [0..100,000];
the elements of A are all distinct;
each element of array A is an integer within the range [1..(N + 1)].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(1), beyond input storage (not counting the 
storage required for input arguments).

*/

#include <iostream>
#include <vector>

int solution( std::vector< int > &A )
{
	const auto N = A.size();
	auto sum = ( ( N + 1 ) * ( N + 2 ) / 2 );

	for ( auto a : A ) {
		sum -= a;
	}

	return sum;
}

void test( std::vector< int > A, int expected )
{
	std::cout << "Input: A=[";
	bool first = true;
	for ( auto a : A ) {
		std::cout << ( first ? "" : ", " ) << a;
		first = false;
	}
	std::cout << "]\n";

	auto got = solution( A );

	if ( got != expected ) {
		std::cout << "ERROR got: " << got << " expected: " << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

int main( int argc, char** argv )
{
	test( { 2, 3, 1, 5 }, 4 );
	test( { 2 }, 1 );
	test( { 1, 2, 3, 4, 5 }, 6 );
	
	return 0;
}




