#include <iostream>
#include <fstream>


int main()
{
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");

	int n, m;
	file_in >> n >> m;

	const auto matrix = new int*[n];
	for (auto i = 0; i < n; ++i)
	{
		matrix[i] = new int[n];
		for (auto j = 0; j < n; ++j)
		{
			matrix[i][j] = 0;
		}
	}

	int first, second;
	for (auto i = 0; i < m; ++i)
	{
		file_in >> first >> second;
		matrix[first - 1][second - 1] = 1;
		matrix[second - 1][first - 1] = 1;
	}

	for (auto i = 0; i < n; ++i)
	{
		for (auto j = 0; j < n; ++j)
		{
			file_out << matrix[i][j] << " ";
		}
		file_out << std::endl;
	}
}
