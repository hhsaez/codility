/*

A string S consisting of N characters is considered to be properly nested if any of 
the following conditions is true:

S is empty;
S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
S has the form "VW" where V and W are properly nested strings.
For example, the string "{[()()]}" is properly nested but "([)()]" is not.

Write a function:

int solution(string &S);

that, given a string S consisting of N characters, returns 1 if S is properly nested 
and 0 otherwise.

For example, given S = "{[()()]}", the function should return 1 and given S = "([)()]", 
the function should return 0, as explained above.

Assume that:

N is an integer within the range [0..200,000];
string S consists only of the following characters: "(", "{", "[", "]", "}" and/or ")".
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N) (not counting the storage required for 
input arguments).

Results (100%):
https://app.codility.com/demo/results/trainingFMVM59-VP4/

*/

#include <iostream>
#include <string>
#include <stack>

int solution( std::string &S )
{
	std::stack< char > brackets;

	for ( auto c : S ) {
		switch ( c ) {
		case '(':
		case '[':
		case '{':
			brackets.push( c );
			break;

		case ')':
			if ( brackets.top() != '(' ) {
				return 0;
			}
			brackets.pop();
			break;
			
		case ']':
			if ( brackets.top() != '[' ) {
				return 0;
			}
			brackets.pop();
			break;
			
		case '}':
			if ( brackets.top() != '{' ) {
				return 0;
			}
			brackets.pop();
			break;
		};
	}
	
	return ( brackets.empty() ? 1 : 0 );
}

void test( std::string S, int expected )
{
	std::cout << "Input S=" << S << "\n";

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
	test( "{[()()]}", 1 );
	test( "([)()]", 0 );
	test( "", 1 );
	test( "{{{{", 0 );
	test( "{({({){{", 0 );
	test( "{{{{(((())))}}}}", 1 );
	
	return 0;
}

