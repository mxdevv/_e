#ifndef _E_ALG_CPP
#define _E_ALG_CPP

namespace _e {
namespace alg {

constexpr auto pow(auto a, auto n)
{
	auto r = 1;
	while(n)
		if (n & 1) {
			r *= a;
			--n;
		} else {
			a *= a;
			n >>= 1;
		}
	return r;
}

constexpr unsigned int hash(const char chs[])
{
	unsigned int hash = 0;
	for(int i = 0; chs[i] != '\0'; i++)
		hash += (unsigned int)chs[i] * pow(31, i);
	return hash;
}

/*int substr(std::string sampl, std::string str)
{
	;
}*/

} // alg
} // _e

#endif // _E_ALG_CPP
