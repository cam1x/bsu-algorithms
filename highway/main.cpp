#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>

#define ll long long

static const auto YES = "YES";
static const auto NO = "NO";
static const ll NOT_VISITED = -111;
static const ll RIGHT = 1;

class HighwayChecker {
    std::vector<ll> status;
    std::vector<std::vector<ll>> graph;
    ll leftLobe{};
    ll rightLobe{};
    bool isDicotyledonous{};
    ll maxEven{};

public:
    void init(std::ifstream &fileIn) {
        ll n;
        fileIn >> n;

        graph.resize(n);
        status.resize(n, NOT_VISITED);

        ll tmpValue;
        std::string tmpString;
        std::stringstream tmpStream;
        std::getline(fileIn, tmpString);
        for (int i = 0; i < n; ++i) {
            std::getline(fileIn, tmpString);
            tmpStream = std::stringstream(tmpString);
            while (tmpStream) {
                tmpStream >> tmpValue;
                if (tmpStream && tmpValue != 0) {
                    graph[i].push_back(tmpValue - 1);
                }
            }
        }

        isDicotyledonous = true;
    }

    ll find(const ll v) {
        leftLobe = 1;
        rightLobe = 0;
        ll count = 1;
        status[v] = 0;

        std::queue<ll> queue;
        queue.push(v);
        while (!queue.empty()) {
            auto curr = queue.front();
            queue.pop();

            for (ll i = 0; i < graph[curr].size(); ++i) {
                if (isNotVisited(curr, i)) {
                    auto lobe = (status[curr] + 1) % 2;
                    status[graph[curr][i]] = lobe;
                    if (lobe == RIGHT) {
                        ++rightLobe;
                    } else {
                        ++leftLobe;
                    }
                    ++count;
                    queue.push(graph[curr][i]);
                    continue;
                }

                changeLobeStatus(curr, i);
            }
        }
        incMaxEven((isDicotyledonous) ? std::max(leftLobe, rightLobe) : 1);

        return count;
    }

    bool getDicotyledonous() const {
        return isDicotyledonous;
    }

    long long int getMaxEven() const {
        return maxEven;
    }

    ll getSize() const {
        return graph.size();
    }

    const std::vector<ll> &getStatus() const {
        return status;
    }

private:
    bool isNotVisited(ll curr, ll i) const {
        return status[graph[curr][i]] == NOT_VISITED;
    }

    void changeLobeStatus(ll curr, ll i) {
        if (isDicotyledonous && status[graph[curr][i]] == status[curr]) {
            isDicotyledonous = false;
        }
    }

    void incMaxEven(ll num) {
        maxEven += num;
    }
};

int main() {
    std::ifstream fileIn("input.txt");
    std::ios_base::sync_with_stdio(false);
    fileIn.tie(nullptr);
    HighwayChecker checker;
    checker.init(fileIn);
    fileIn.close();

    std::ofstream fileOut("output.txt");
    fileOut.tie(nullptr);
    auto size = checker.getSize();
    ll count = checker.find(0);
    bool isConnected = (count == size);
    bool isDicotyledonous = checker.getDicotyledonous();

    if (isConnected && !isDicotyledonous) {
        fileOut << YES;
        fileOut.close();
        return 0;
    }

    if (isConnected) {
        fileOut << NO << std::endl;
        fileOut << checker.getMaxEven();
        fileOut.close();
        return 0;
    }

    auto &status = checker.getStatus();
    for (ll i = 0; i < size; ++i) {
        if (status[i] == NOT_VISITED) {
            checker.find(i);
        }
    }
    fileOut << NO << std::endl;
    fileOut << checker.getMaxEven();
    fileOut.close();
    return 0;
}