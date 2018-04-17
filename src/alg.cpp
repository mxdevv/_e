#ifndef _E_ALG_CPP
#define _E_ALG_CPP

namespace _e {
namespace alg {

constexpr size_t utf8_strlen(const char* cstr)
{
	size_t c = 0, q = 0;
	for(const char* p = cstr; *p != '\0'; p++)
	{
		if           ((*p & 0b1'0000000) == 0b0'0000000) { c++; continue; }
		else if (q && (*p & 0b11'000000) == 0b10'000000) { q--; continue; }
		else if      ((*p & 0b111'00000) == 0b110'00000) { c++; q = 1; continue; }
		else if      ((*p & 0b1111'0000) == 0b1110'0000) { c++; q = 2; continue; }
		else if      ((*p & 0b11111'000) == 0b11110'000) { c++; q = 3; continue; }
	}
	return (q != 0 ? 0 : c);
}

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

constexpr unsigned int hash(const char* chs)
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
