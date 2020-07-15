#include <iostream>

class segment_tree
{
	long long* tree_;
	long long size_;

public:
	segment_tree(long long* array, const long long size) : size_(size)
	{
		tree_ = new long long[4 * size];
		build_helper(array, 0, 0, size);
	}

	void add(const long long i, const long long x) const
	{
		add_helper(0, 0, size_, i, x);
	}

	long long sum(const long long l_bound, const long long r_bound) const
	{
		return sum_helper(0, 0, size_, l_bound, r_bound);
	}

private:
	void build_helper(long long* array, const long long index, const long long left, const long long right) const
	{
		if (right - left == 1)
		{
			tree_[index] = array[left];
		}
		else
		{
			const auto middle = get_mid(left, right);
			build_helper(array, 2 * index + 1, left, middle);
			build_helper(array, 2 * index + 2, middle, right);
			tree_[index] = tree_[2 * index + 1] + tree_[2 * index + 2];
		}
	}

	void add_helper(const long long index, const long long left, const long long right, const long long i, const long long x) const
	{
		if (right - left == 1)
		{
			tree_[index] += x;
			return;
		}
		const auto middle = get_mid(left, right);
		if (i < middle) {
			add_helper(2 * index + 1, left, middle, i, x);
		}
		else
		{
			add_helper(2 * index + 2, middle, right, i, x);
		}
		tree_[index] = tree_[2 * index + 1] + tree_[2 * index + 2];
	}

	long long sum_helper(const long long index, const long long left, const long long right, const long long l_bound, const long long r_bound) const
	{
		if (left == l_bound && right == r_bound)
		{
			return tree_[index];
		}

		const auto middle = get_mid(left, right);
		if (r_bound <= middle)
		{
			return sum_helper(2 * index + 1, left, middle, l_bound, r_bound);
		}
		if (middle <= l_bound)
		{
			return sum_helper(2 * index + 2, middle, right, l_bound, r_bound);
		}

		return sum_helper(2 * index + 1, left, middle, l_bound, middle) +
			sum_helper(2 * index + 2, middle, right, middle, r_bound);
	}

	static long long get_mid(const long long a, const long long b)
	{
		return a + (b - a) / 2;
	}
};

int main()
{
	long long size;
	std::cin >> size;

	const auto array = new long long[size];
	for (auto i = 0; i < size; ++i)
	{
		std::cin >> array[i];
	}

	const segment_tree tree(array, size);

	long long number_of_requests;
	std::cin >> number_of_requests;

	char operation[15];
	long long first, second;
	for (auto i = 0; i < number_of_requests; ++i)
	{
		std::cin >> operation >> first >> second;
		if (operation[0] == 'F')
		{
			std::cout << tree.sum(first, second) << std::endl;
		}
		else
		{
			tree.add(first, second);
		}
	}
}