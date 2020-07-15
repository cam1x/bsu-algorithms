#include <iostream>
#include <vector>
#include <fstream>

int n;
int* nodes;
int count = 1;
int** matrix;
std::vector<bool> used;

void dfs(const int v)
{
	used[v] = true;
	nodes[v] = count++;
	for (auto i = 0; i < n; ++i)
	{
		if (!used[i] && matrix[v][i] == 1)
		{
			dfs(i);
		}
	}
}

int main()
{
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");

	file_in >> n;

	nodes = new int[n];
	matrix = new int* [n];
	for (auto i = 0; i < n; ++i)
	{
		matrix[i] = new int[n];
		for (auto j = 0; j < n; ++j)
		{
			file_in >> matrix[i][j];
		}
	}
	file_in.close();

	used.assign(n, false);
	for (auto i = 0; i < n; ++i)
	{
		if (!used[i])
		{
			dfs(i);
		}
	}

	for (auto i = 0; i < n; ++i)
	{
		file_out << nodes[i] << " ";
	}

	file_out.close();
}
