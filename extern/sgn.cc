//https://www.c-plusplus.net/forum/topic/168766/gibt-es-sgn-funktion-in-c/8

#include <memory>

class Sgn {
	private:
		template<class T>
		static std::auto_ptr<Sgn> createSignObjectByNr( T n );

	public:
		virtual int getSign() const = 0;

		template<class T>
		static T sign( T n );
};

class SgnPositiv : public Sgn {
	public:
		int getSign() const {
			return( 1 );
		}
};

class SgnNegativ : public Sgn {
	public:
		int getSign() const {
			return( -1 );
		}
};

class SgnNull : public Sgn {
	public:
		int getSign() const {
			return( 0 );
		}
};

template<class T> std::auto_ptr<Sgn> Sgn::createSignObjectByNr( T n ) {
	std::auto_ptr<Sgn> ret( new SgnNull() );

	if( n < T(0) )
		ret = std::auto_ptr<Sgn>( new SgnNegativ() );

	if( n > T(0) )
		ret = std::auto_ptr<Sgn>( new SgnPositiv() );

	return( ret );
}

template<class T> T Sgn::sign( T n ) {
	std::auto_ptr<Sgn> sobj = Sgn::createSignObjectByNr<T>( n );
	return( T( sobj.get()->getSign() ) );
}

// test
#include <iostream>

int main() {
	std::cout << "-5 -> " << Sgn::sign( -5 ) << std::endl;
	std::cout << "+6 -> " << Sgn::sign( 6 ) << std::endl;
	std::cout << " 0 -> " << Sgn::sign( 0 ) << std::endl;
}

