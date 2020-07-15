#include <fstream>
#include <vector>

int main()
{
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");

	int n, m;
	file_in >> n >> m;

	std::vector<std::vector<int>> list(n + 1);

	int first, second;
	for (auto i = 0; i < m; ++i)
	{
		file_in >> first >> second;
		list[first].push_back(second);
		list[second].push_back(first);
	}

	for (auto i = 1; i <= n; ++i)
	{
		file_out << list[i].size() << " ";
		for (auto j : list[i])
		{
			file_out << j << " ";
		}
		file_out << std::endl;
	}
}