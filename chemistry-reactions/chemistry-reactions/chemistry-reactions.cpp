#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>

int main()
{
    std::ifstream file_in("in.txt");
    std::ofstream file_out("out.txt");
    int matrix_size, experiment_size;
    file_in >> matrix_size;
    file_in >> experiment_size;

    auto matrix = new int* [matrix_size];
    for (auto i = 0; i < matrix_size; ++i)
    {
        matrix[i] = new int[matrix_size];
        for (auto j = 0; j < matrix_size; ++j)
        {
            file_in >> matrix[i][j];
        }
    }

    auto experiments = new int[experiment_size];
    for (auto i = 0; i < experiment_size; ++i)
    {
        file_in >> experiments[i];
    }

    std::stack<int> stack;
    stack.push(experiments[0]);

    for (auto i = 1; i < experiment_size; ++i)
    {
        auto reaction = matrix[stack.top() - 1][experiments[i] - 1];
        if (reaction == 0) {
            stack.push(experiments[i]);
            continue;
        }

        stack.pop();
        stack.push(reaction);

        while (stack.size() != 1)
        {
            auto first = stack.top();
            stack.pop();
            const auto second = stack.top();

            auto react = matrix[first - 1][second - 1];
            if (react == 0) {
                stack.push(first);
                break;
            }
            stack.pop();
            stack.push(react);
        }
    }

    std::string result;

    while (!stack.empty())
    {
        file_out << stack.top();
        if (stack.size() != 1)
        {
            file_out << " ";
        }
        stack.pop();
    }

    delete[] experiments;
    for (auto i = 0; i < matrix_size; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}
