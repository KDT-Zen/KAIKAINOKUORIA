#include "CsvLoder.h"

#include <fstream>

#include <sstream>


std::vector<csvdata> LoadCSV(const std::string& path)
{
	std::vector<csvdata> list;


	std::ifstream file(path);

	if (!file.is_open())
	{

		return list;

	}


	std::string line;


	


}