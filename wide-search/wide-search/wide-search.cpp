#include <fstream>
#include <queue>
#include <iostream>

int n;
int* nodes;
int count = 1;
int** matrix;
std::vector<bool> used;

void bfs(const int v)
{
	std::queue<int> queue;
	queue.push(v);
	used[v] = true;

	while (!queue.empty())
	{
		const auto curr = queue.front();
		queue.pop();

		nodes[curr] = count++;
		
		for (auto i = 0; i < n; ++i)
		{
			if (!used[i] && matrix[curr][i] == 1)
			{
				queue.push(i);
				used[i] = true;
			}
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
			bfs(i);
		}
	}

	for (auto i = 0; i < n; ++i)
	{
		file_out << nodes[i] << " ";
	}
	
	file_out.close();
}