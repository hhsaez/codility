/*

A DNA sequence can be represented as a string consisting of the letters A, C, G and T, 
which correspond to the types of successive nucleotides in the sequence. Each nucleotide 
has an impact factor, which is an integer. Nucleotides of types A, C, G and T have impact 
factors of 1, 2, 3 and 4, respectively. You are going to answer several queries of the 
form: What is the minimal impact factor of nucleotides contained in a particular part of 
the given DNA sequence?

The DNA sequence is given as a non-empty string S = S[0]S[1]...S[N-1] consisting of N 
characters. There are M queries, which are given in non-empty arrays P and Q, each 
consisting of M integers. The K-th query (0 ≤ K < M) requires you to find the minimal 
impact factor of nucleotides contained in the DNA sequence between positions P[K] 
and Q[K] (inclusive).

For example, consider string S = CAGCCTA and arrays P, Q such that:

    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6
The answers to these M = 3 queries are as follows:

The part of the DNA between positions 2 and 4 contains nucleotides G and C (twice), whose 
impact factors are 3 and 2 respectively, so the answer is 2.
The part between positions 5 and 5 contains a single nucleotide T, whose impact factor 
is 4, so the answer is 4.
The part between positions 0 and 6 (the whole string) contains all nucleotides, in 
particular nucleotide A whose impact factor is 1, so the answer is 1.
Write a function:

vector<int> solution(string &S, vector<int> &P, vector<int> &Q);

that, given a non-empty zero-indexed string S consisting of N characters and two 
non-empty zero-indexed arrays P and Q consisting of M integers, returns an array 
consisting of M integers specifying the consecutive answers to all queries.

The sequence should be returned as:

a Results structure (in C), or
a vector of integers (in C++), or
a Results record (in Pascal), or
an array of integers (in any other programming language).
For example, given the string S = CAGCCTA and arrays P, Q such that:

    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6
the function should return the values [2, 4, 1], as explained above.

Assume that:

N is an integer within the range [1..100,000];
M is an integer within the range [1..50,000];
each element of arrays P, Q is an integer within the range [0..N − 1];
P[K] ≤ Q[K], where 0 ≤ K < M;
string S consists only of upper-case English letters A, C, G, T.
Complexity:

expected worst-case time complexity is O(N+M);
expected worst-case space complexity is O(N), beyond input storage (not counting the 
storage required for input arguments).

*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector< int > solution( std::string &S, std::vector< int > &P, std::vector< int > &Q )
{
	const auto N = S.length();
	const auto M = P.size();

	std::vector< std::map< char, int >> counters( N );

	std::map< char, int > impacts = {
		{ 'A', 1 },
		{ 'C', 2 },
		{ 'G', 3 },
		{ 'T', 4 }
	};
	
	std::map< char, int > cs = {
		{ 'A', 0 },
		{ 'C', 0 },
		{ 'G', 0 },
		{ 'T', 0 }
	};

	for ( size_t i = 0; i < N; i++ ) {
		counters[ i ] = cs;
		cs[ S[ i ] ]++;
	}

	std::vector< int > results( M );

	for ( size_t i = 0; i < M; i++ ) {
		auto p = P[ i ];
		auto q = Q[ i ];

		auto r = impacts[ S[ q ] ];

		std::map< char, int > diffs;
		for ( auto it : impacts ) {
			diffs[ it.first ] = counters[ q ][ it.first ] - counters[ p ][ it.first ];
		}

		for ( auto it : diffs ) {
			if ( it.second > 0 ) {
				r = std::min( r, impacts[ it.first ] );
			}
		}

		results[ i ] = r;
	}

	return results;
}

std::vector< int > brute( std::string &S, std::vector< int > &P, std::vector< int > &Q )
{
	const auto M = P.size();
	std::vector< int > results( M );

	std::map< char, int > impacts = {
		{ 'A', 1 },
		{ 'C', 2 },
		{ 'G', 3 },
		{ 'T', 4 }
	};
	
	for ( size_t k = 0; k < M; k++ ) {
		auto p = P[ k ];
		auto q = Q[ k ];
		int minImpact = 4;
		for ( size_t i = p; i <= q; i++ ) {
			int impact = impacts[ S[ i ] ];
			minImpact = std::min( impact, minImpact );
		}
		results[ k ] = minImpact;
	}
	
	return results;
}

void test( std::string S, std::vector< int > P, std::vector< int > Q )
{
	std::cout << "TEST \"" << S << "\": ";

	auto got = solution( S, P, Q );
	auto expected = brute( S, P, Q );

	if ( got != expected ) {
		std::cout << "ERROR";
		std::cout << "\ngot: [";
		bool first = true;
		for ( auto a : got ) {
			std::cout << ( first ? "" : ", " ) << a;
			first = false;
		}
		std::cout << "], expected: [";
		first = true;
		for ( auto a : expected ) {
			std::cout << ( first ? "" : ", " ) << a;
			first = false;
		}
		std::cout << "]\n";
	}
	else {
		std::cout << "OK\n";
	}
}

int main( int argc, char **argv )
{
	test( "CAGCCTA", { 2, 5, 0 }, { 4, 5, 6 } );
	test( "AAATCCA", { 2, 5, 0 }, { 4, 5, 6 } );
	test( "A", { 0 }, { 0 } );
	test( "GTGT", { 0, 0, 1 }, { 0, 1, 3 } );
	return 0;
}

