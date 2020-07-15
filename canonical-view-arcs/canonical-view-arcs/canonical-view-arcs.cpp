#include <fstream>

int main()
{
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");

	int n;
	file_in >> n;

	auto array = new int[n + 1];
	for (auto i = 0; i <= n; ++i)
	{
		array[i] = 0;
	}

	int first, second;
	for (auto i = 1; i < n; ++i)
	{
		file_in >> first >> second;
		array[second] = first;
	}
	file_in.close();

	for (auto i = 1; i<=n; ++i)
	{
		file_out << array[i] << " ";
	}
	file_out.close();
}

