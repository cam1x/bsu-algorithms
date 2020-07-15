#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

const long no_solution = INT16_MAX;
long size;

class pair {
    long first_;
    long second_;

    pair(const long first, const long second)
    {
        this->first_ = first;
        this->second_ = second;
    }

public:
    static pair of(const long first, const long second)
    {
        return pair(first, second);
    }

    long get_first() const
    {
        return first_;
    }

    long get_second() const
    {
        return second_;
    }
};

class coins_collector
{
    std::vector<pair> pairs_;

public:
    explicit coins_collector(const std::vector<pair>& pairs)
    {
        this->pairs_ = pairs;
    }

    long collect_coins() const
    {
        const auto min_time = new long* [size];

        for (auto i = 0; i < size; ++i)
        {
            min_time[i] = new long[size];
            std::memset(min_time[i], 0, sizeof(long) * size);
        }

        for (auto step = 1; step < size; ++step)
        {
            for (auto i = 0; i + step < size; ++i)
            {
                const auto last_index = i + step;
                auto inc_in_order = min_time[i + 1][last_index] +
                    pairs_[i + 1].get_first() - pairs_[i].get_first();
                auto inc_post_order = min_time[last_index][i + 1] +
                    pairs_[last_index].get_first() - pairs_[i].get_first();
                const auto inc_min = std::min(inc_post_order, inc_in_order);
                min_time[i][last_index] = (pairs_[i].get_second() >= inc_min) ? inc_min : no_solution;

                auto desc_in_order = min_time[last_index - 1][i] +
                    pairs_[last_index].get_first() - pairs_[last_index - 1].get_first();
                auto desc_post_order = min_time[i][last_index - 1] +
                    pairs_[last_index].get_first() - pairs_[i].get_first();
                const auto desc_min = std::min(desc_post_order, desc_in_order);
                min_time[last_index][i] = (pairs_[last_index].get_second() >= desc_min) ? desc_min : no_solution;

                if (std::abs(min_time[i][last_index]) == no_solution &&
                    std::abs(min_time[last_index][i]) == no_solution)
                {
                    return no_solution;
                }

                auto cant_reach_coin_before = false;
                if (std::abs(min_time[i + step][i]) != no_solution)
                {
                    for (auto before_i = 0; before_i < i; ++before_i)
                    {
                        if (pairs_[before_i].get_second() - min_time[i + step][i] < pairs_[i].get_first() - pairs_[before_i].get_first())
                        {
                            cant_reach_coin_before = true;
                            break;
                        }
                    }
                }

                auto cant_reach_coin_after = false;
                if (std::abs(min_time[i][i + step]) != no_solution)
                {
					for (auto after_k = i + 2 * step + 1; after_k < size; ++after_k)
                    {
                        if (pairs_[after_k].get_second() - min_time[i][last_index] < pairs_[after_k].get_first() - pairs_[i + 2 * step].get_first())
                        {
                            cant_reach_coin_after = true;
                            break;
                        }
                    }
                }

                if (cant_reach_coin_before && cant_reach_coin_after) return no_solution;
            }
        }

        return std::min(min_time[0][size - 1], min_time[size - 1][0]);
    }
};

int main()
{
    std::ifstream file_in("input.txt");
    std::ofstream file_out("output.txt");
    file_in >> size;

    std::vector<pair> pairs;

    long first, second;

    for (auto i = 0; i < size; ++i)
    {
        file_in >> first >> second;
        pairs.push_back(pair::of(first, second));
    }

    const coins_collector collector(pairs);
    const auto result = collector.collect_coins();

    file_out << (std::abs(result) == no_solution ? "No solution" : std::to_string(result));

    return 0;
}