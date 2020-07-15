#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

class competition_result
{
	int first_;
	int second_;
	int third_;
public:
	explicit competition_result(const int first = 0, const int second = 0, const int third = 0) :
		first_(first), second_(second), third_(third) {}

	int get_first() const { return  first_; }
	int get_second() const { return second_; }
	int get_third() const { return third_; }
};

struct competition_comparator
{
	bool operator() (const competition_result& o1, const competition_result& o2) const
	{
		return o1.get_first() < o2.get_first();
	}
};

class competition_resolver
{
	const int no_solution_ = INT32_MAX;
	std::vector<competition_result>* results_;
	std::vector<int>* tree_of_segments_;
	int size_;
	
public:
	explicit competition_resolver(std::set<competition_result, competition_comparator>& collection)
	{
		size_ = to_upper_bound_of_two(collection.size());
		results_ = new std::vector<competition_result>(collection.size());
		std::copy(collection.begin(), collection.end(), results_->begin());
		tree_of_segments_ =
			new std::vector<int>(2 * size_, no_solution_);
	}

	int resolve() const
	{
		int solution = results_->size();

		for (auto result : *results_)
		{
			modify(result.get_second(), result.get_third());
			if (result.get_third() > find_min(result.get_second() - 1))
			{
				--solution;
			}
		}

		return solution;
	}

private:
	void modify(unsigned int position, const int value) const
	{
		position += size_ - 1;
		(*tree_of_segments_)[position] = value;

		while (position /= 2)
		{
			(*tree_of_segments_)[position] = std::min(tree_of_segments_->at(2 * position), 
				tree_of_segments_->at(2 * position + 1));
		}
	}

	long find_min(int right) const
	{
		auto min_element = no_solution_;

		auto left = size_;
		right += size_ - 1;

		while (left <= right)
		{
			if (left % 2 == 1)
			{
				min_element = std::min(min_element, tree_of_segments_->at(left));
			}

			if (right % 2 == 0)
			{
				min_element = std::min(min_element, tree_of_segments_->at(right));
			}

			left = (left + 1) / 2;
			right = (right - 1) / 2;
		}
		
		return min_element;
	}

	static int to_upper_bound_of_two(int x) {
		--x;
		for (auto p = 1; p < 32; p <<= 1) 
		{
			x |= (x >> p);
		}
		return ++x;
	}
};

int main()
{
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");

	int size;
	file_in >> size;
	
	std::set<competition_result, competition_comparator> competition_results;

	for (auto i = 0; i < size; ++i)
	{
		int first, second, third;
		file_in >> first >> second >> third;
		competition_result result(first, second, third);
		competition_results.insert(result);
	}
	file_in.close();

	competition_resolver resolver(competition_results);
	file_out << resolver.resolve();
	file_out.close();

	return 0;
}