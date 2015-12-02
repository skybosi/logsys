#include <cstdio>
namespace cov
{
	namespace ioctrl
	{
		inline void flush();
		inline void endl();
	}
	inline void print(const int &);
	inline void print(const char &);
	inline void print(const char *);
	inline void print(void (*)());
	template < typename Type > inline void print(const Type &);
	template < typename Type, typename ... Argt > inline void print(const Type &,
			const Argt & ...);
}


inline void cov::print(const int &i)
{
	printf("%i", i);
}


inline void cov::print(const char &c)
{
	printf("%c", c);
}


inline void cov::print(const char *s)
{
	printf("%s", s);
}


inline void cov::print(void (*func) ())
{
	func();
}


inline void cov::ioctrl::flush()
{
	fflush(stdout);
}


inline void cov::ioctrl::endl()
{
	printf("\n");
	fflush(stdout);
}


template < typename Type > inline void cov::print(const Type & obj)
{
	throw "Can't call overloaded function correctly.";
}


	template < typename Type, typename...Argt >
inline void cov::print(const Type & obj, const Argt & ... argv)
{
	print(obj);
	print(argv...);
}
