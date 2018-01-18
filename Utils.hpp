#ifndef CODILITY_UTILS_
#define CODILITY_UTILS_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>

namespace codility {

	std::string toString( int N )
	{
		std::stringstream ss;
		ss << N;
		return ss.str();
	}

	std::string toString( bool b )
	{
		return ( b ? "T" : "F" );
	}

	template< typename T >
	std::string toString( std::vector< T > &A )
	{
		std::stringstream ss;
		ss << "[";
		bool first = true;
		for ( auto v : A ) {
			ss << ( first ? "" : ", " ) << toString( v );
			first = false;
		}
		ss << "]";
		
		return ss.str();
	}
	
	long generateRandom( long lo, long hi )
	{
		std::random_device rd;
		std::mt19937 gen( rd() );
		std::uniform_int_distribution<> dis( lo, hi );
		
		return dis( gen );
	}
	
	std::vector< int > generateRandomVector( long lo, long hi, long N )
	{
		std::random_device rd;
		std::mt19937 gen( rd() );
		std::uniform_int_distribution<> dis( lo, hi );

		std::vector< int > result( N );
		for ( size_t i = 0; i < N; i++ ) {
			result[ i ] = dis( gen );
		}
		return result;
	}

	template< typename T >
	void compareResults( T got, T expected )
	{
		static size_t testCount = 0;
		std::cout << testCount++ << ": ";
		
		if ( got != expected ) {
			std::cout << "ERROR: got=" << codility::toString( got ) << ", expected=" << codility::toString( expected ) << "\n";
		}
		else {
			std::cout << "PASSED: got=" << codility::toString( got ) << "\n";
		}
	}
}

#endif

