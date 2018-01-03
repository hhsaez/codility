/*

A non-empty zero-indexed array A consisting of N integers is given. Array A represents 
numbers on a tape.

Any integer P, such that 0 < P < N, splits this tape into two non-empty parts: 
A[0], A[1], ..., A[P − 1] and A[P], A[P + 1], ..., A[N − 1].

The difference between the two parts is the value of: 
|(A[0] + A[1] + ... + A[P − 1]) − (A[P] + A[P + 1] + ... + A[N − 1])|

In other words, it is the absolute difference between the sum of the first part and the 
sum of the second part.

For example, consider array A such that:

  A[0] = 3
  A[1] = 1
  A[2] = 2
  A[3] = 4
  A[4] = 3
We can split this tape in four places:

P = 1, difference = |3 − 10| = 7 
P = 2, difference = |4 − 9| = 5 
P = 3, difference = |6 − 7| = 1 
P = 4, difference = |10 − 3| = 7 

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A of N integers, returns the minimal difference 
that can be achieved.

For example, given:

  A[0] = 3
  A[1] = 1
  A[2] = 2
  A[3] = 4
  A[4] = 3
the function should return 1, as explained above.

Assume that:

N is an integer within the range [2..100,000];
each element of array A is an integer within the range [−1,000..1,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

*/

#include <iostream>
#include <vector>
#include <limits>

int solution( std::vector< int > &A )
{
	const auto N = A.size();

	if ( N < 2 ) {
		return -1;
	}

	long sumRight = 0;
	for ( auto a : A ) {
		sumRight += a;
	}

	long sumLeft = 0;

	long result = 0;
	for ( size_t i = 1; i < N; i++ ) {
		sumLeft += A[ i - 1 ];
		sumRight -= A[ i - 1 ];
		auto diff = std::abs( sumLeft - sumRight );
		if ( i == 1 || diff < result ) {
			result = diff;
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
	std::cout << "]\n";

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
	test( { 1 }, -1 );
	test( { 3, 1, 2, 4, 3 }, 1 );
	test( { 1, 2, 3, 4, 5, 6, 7 }, 2 );

	return 0;
}

