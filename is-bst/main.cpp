#include <iostream>
#include <fstream>

#define ll long long

const ll INF = LONG_LONG_MAX;

int main() {
    std::ifstream file_in("bst.in");
    std::ios_base::sync_with_stdio(false);
    file_in.tie(nullptr);

    long n;
    long root;
    file_in >> n >> root;

    long *vertexes = new long[n + 1];
    auto *pairs = new std::pair<ll, ll>[n + 1];

    for (ll i = 0; i <= n; ++i) {
        vertexes[i] = 0;
        pairs[i] = {0, 0};
    }

    vertexes[1] = root;
    pairs[1] = {-INF, INF};

    bool is_bst = true;
    long value, parent;
    char way[15];
    for (auto i = 2; i <= n; ++i) {
        file_in >> value >> parent >> way;

        auto min = pairs[parent].first;
        auto max = pairs[parent].second;
        long parent_val = vertexes[parent];

        if (way[0] == 'L') {
            if (value >= parent_val || value < min) {
                is_bst = false;
                break;
            } else {
                vertexes[i] = value;
                pairs[i] = {min, parent_val};
            }
        } else {
            if (value < parent_val || value >= max) {
                is_bst = false;
                break;
            } else {
                vertexes[i] = value;
                pairs[i] = {parent_val, max};
            }
        }
    }
    file_in.close();

    std::ofstream file_out("bst.out");
    file_out.tie(nullptr);
    file_out << ((is_bst) ? "YES" : "NO");
    file_out.close();

    return 0;
}