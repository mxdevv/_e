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

constexpr unsigned int hash(const char* chs)
{
	unsigned int hash = 0;
	for(int i = 0; chs[i] != '\0'; i++)
		hash += (unsigned int)chs[i] * pow(31, i);
	return hash;
}

unsigned int hash(std::string str)
{
	unsigned int hash = 0;
	for(int i = 0; i < str.size(); i++)
		hash += (unsigned int)str[i] * pow(31, i);
	return hash;
}

std::vector<int> substr(const char* sampl, std::vector<struc::Color_ch>& sourc)
{
	int i = 0, j = 0;
	std::vector<int> v;
	for(; sourc.size() > j; j++)
	{
		if (sampl[i] == sourc[j].ch) {
			i++;
			if (sampl[i] == '\0') {
				v.push_back(j);
				i = 0;
			}
		} else i = 0;
	}
	return v;
}

} // alg
} // _e

#endif // _E_ALG_CPP
