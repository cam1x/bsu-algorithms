#include <iostream>
#include <fstream>

int main()
{
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");

	int size;
	file_in >> size;

	const auto heap = new long[size];

	for (auto i=0;i<size; ++i)
	{
		file_in >> heap[i];
	}

	auto is_heap = true;
	for (auto i = 0; i < size; ++i)
	{
		if (2 * i + 1 < size && heap[i] > heap[2 * i + 1] || 2 * i + 2 < size && heap[i] > heap[2 * i + 2])
		{
			is_heap = false;
			break;
		}
	}

	file_out << (is_heap? "Yes": "No");
	return 0;
}