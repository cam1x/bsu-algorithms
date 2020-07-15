#include <iostream>
#include <fstream>

int main()
{
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");

	long long size;
	file_in >> size;
	file_in.close();

	auto power = 0;
	while (size > 0)
	{
		if (size % 2 == 1)
		{
			file_out << power << std::endl;
		}
		size /= 2;
		power++;
	}
	
	file_out.close();
	return 0;
}