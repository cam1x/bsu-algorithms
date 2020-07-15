#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

class disjoint_set_union
{
	int components_;
	int* size_;
	int* parent_;

public:
	explicit disjoint_set_union(const int n)
	{
		components_ = n;
		size_ = new int[n + 1];
		parent_ = new int[n + 1];
		for (auto i = 1; i <= n; ++i)
		{
			size_[i] = 1;
			parent_[i] = i;
		}
	}

	int get_components() const
	{
		return components_;
	}

	int find(const int x) const
	{
		if (x == parent_[x])
		{
			return x;
		}

		parent_[x] = find(parent_[x]);
		return parent_[x];
	}

	void union_set(int x, int y)
	{
		x = find(x);
		y = find(y);

		if (x != y)
		{
			if (size_[x] < size_[y])
			{
				std::swap(x, y);
			}
			--components_;
			parent_[y] = x;
			size_[x] += size_[y];
		}
	}
};

int main()
{
	const auto read = fopen("input.txt", "r");
	const auto write = fopen("output.txt", "w");
	
	int number_of_roots, number_of_requests;

	fscanf(read,"%d %d", &number_of_roots, &number_of_requests);
	disjoint_set_union set_union(number_of_roots);

	int first, second;
	for (auto i = 0; i < number_of_requests; ++i)
	{
		fscanf(read, "%d %d", &first, &second);
		set_union.union_set(first, second);
		fprintf(write,"%d\n", set_union.get_components());
	}

	return 0;
}