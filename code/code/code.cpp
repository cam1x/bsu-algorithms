#include <iostream>
#include <vector>
#include <fstream>

class square_counter
{
    int counter_;
    int* square_collection_;
	
public:
    explicit square_counter(const int number_of_primes)
    {
        counter_ = 0;
        square_collection_ = new int[number_of_primes + 1];
        std::memset(square_collection_, -1, sizeof(int) * (number_of_primes + 1));
    }

	int get_counter() const
	{
        return counter_;
    }

	void update(const int first, const int second)
    {
        const auto first_root = find(first);
        const auto second_root = find(second);

        if (first_root == second_root)
        {
            ++counter_;
            return;
        }

        if (square_collection_[first_root] >= square_collection_[second_root])
        {
            square_collection_[second_root] = square_collection_[first_root] + square_collection_[second_root];
            square_collection_[first_root] = second_root;
        }
        else
        {
            square_collection_[first_root] = square_collection_[first_root] + square_collection_[second_root];
            square_collection_[second_root] = first_root;
        }
    }

private:
    int find(int value) const
    {
        int position;
        do {
            position = value;
            value = square_collection_[position];
        } while (value > 0);
        return position;
    }
};

int main()
{
    std::ifstream file_in("input.txt");
    std::ofstream file_out("output.txt");

    int number_of_primes, number_of_pairs;

    file_in >> number_of_primes >> number_of_pairs;
    square_counter counter(number_of_primes);

    int first, second;
	for (auto i = 0; i < number_of_pairs; ++i)
	{
        file_in >> first >> second;
        counter.update(first, second);
        
	}
    file_in.close();

    file_out << counter.get_counter();
    file_out.close();
}