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

	int value;
	for (auto i = 0; i < n; ++i)
	{
		for (auto j = 0; j < n; ++j)
		{
			file_in >> value;
			if (value == 1)
			{
				array[j + 1] = i + 1;
			}
		}
	}
	file_in.close();

	for (auto i = 1; i <= n; ++i)
	{
		file_out << array[i] << " ";
	}
	file_out.close();
}