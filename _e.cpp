#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <vector>
#include <array>

#include "src/lang.cpp"
#include "src/data.cpp"
#include "src/func.cpp"
#include "src/alg.cpp"

using namespace _e;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "_e: " << lang::no_arguments << '\n';
		return -1;
	}

	for(int i = 1; i < argc; i++)
	if (argv[i][0] == '-') {
		for(size_t j = 1, len = strlen(argv[i]); j < len; j++)
		switch(argv[i][j])
		{
			case 'h': func::help(); break;
			default:
				data::file_name = argv[i];
				func::open();
				break;
		}
	} else
		switch(alg::hash(argv[i]))
		{
			case alg::hash("help"): func::help(); break;
			default:
				data::file_name = argv[i];
				func::open();
				break;
		}

	data::ofs.close();
	data::ifs.close();
}
