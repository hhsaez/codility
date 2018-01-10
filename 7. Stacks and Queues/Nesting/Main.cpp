/*

A string S consisting of N characters is called properly nested if:

S is empty;
S has the form "(U)" where U is a properly nested string;
S has the form "VW" where V and W are properly nested strings.
For example, string "(()(())())" is properly nested but string "())" isn't.

Write a function:

int solution(string &S);

that, given a string S consisting of N characters, returns 1 if string S is properly 
nested and 0 otherwise.

For example, given S = "(()(())())", the function should return 1 and given S = "())", 
the function should return 0, as explained above.

Assume that:

N is an integer within the range [0..1,000,000];
string S consists only of the characters "(" and/or ")".
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(1) (not counting the storage required for 
input arguments).

Results (100%):
https://app.codility.com/demo/results/training8EY2RV-SGC/

*/

#include <iostream>

int solution( std::string &S )
{
	long count = 0;

	for ( auto c : S ) {
		if ( c == '(' ) {
			count++;
		}
		else if ( c == ')' ) {
			count--;
			if ( count < 0 ) {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	return count == 0 ? 1 : 0;
}

void test( std::string S, int expected )
{
	auto got = solution( S );
	if ( got != expected ) {
		std::cout << "ERROR: got=" << got << ", expected=" << expected << "\n";
	}
	else {
		std::cout << "OK\n";
	}
}

int main( int argc, char **argv )
{
	test( "(()(())())", 1 );
	test( "(()", 0 );
	test( "", 1 );
	test( "(", 0 );
	test( ")", 0 );
	test( "((()))", 1 );
	test( ")))(((", 0 );
	
	return 0;
}

