#include <iostream>
#include <fstream>

long n, m, q;

class disjoint_set_union {
    int components_;
    int *size_;
    int *parent_;

public:
    explicit disjoint_set_union(const int n) {
        components_ = n;
        size_ = new int[n + 1];
        parent_ = new int[n + 1];
        for (auto i = 1; i <= n; ++i) {
            size_[i] = 1;
            parent_[i] = i;
        }
    }

    int get_components() const {
        return components_;
    }

    int find(const int x) const {
        if (x == parent_[x]) {
            return x;
        }

        parent_[x] = find(parent_[x]);
        return parent_[x];
    }

    void union_set(int x, int y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            if (size_[x] < size_[y]) {
                std::swap(x, y);
            }
            --components_;
            parent_[y] = x;
            size_[x] += size_[y];
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fileIn("input.txt");
    fileIn.tie(nullptr);

    fileIn >> n >> m >> q;

    disjoint_set_union set_union(n);
    auto *roads = new std::pair<long, long>[m];
    bool *destroy = new bool[m];
    long *destroyReq = new long[q];

    long first, second;
    for (int i = 0; i < m; ++i) {
        fileIn >> first >> second;
        roads[i] = {first, second};
        destroy[i] = false;
    }

    for (int i = 0; i < q; ++i) {
        fileIn >> first;
        --first;
        destroyReq[q - 1 - i] = first;
        destroy[first] = true;
    }

    for (int i = 0; i < m; ++i) {
        if (!destroy[i]) {
            set_union.union_set(roads[i].first, roads[i].second);
        }
    }

    std::string res;
    for (int i = 0; i < q; ++i) {
        std::pair<long, long> &pair = roads[destroyReq[i]];
        res.insert(0, std::to_string(set_union.get_components() > 1 ? 0 : 1));
        set_union.union_set(pair.first, pair.second);
    }

    fileIn.close();

    std::ofstream fileOut("output.txt");
    fileOut.tie(nullptr);

    fileOut << res;

    fileOut.close();
    return 0;
}
