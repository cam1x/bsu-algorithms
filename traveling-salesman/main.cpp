#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

#define ll long long

double INF = LONG_MAX;

class City {
public:
    ll x;
    ll y;
    ll num;

    City() {
        x = y = num = 0;
    }

    City(ll x, ll y, ll num) : x(x), y(y), num(num) {}
};

double calcLen(City *fromCity, City *toCity) {
    return std::sqrt(std::pow(toCity->x - fromCity->x, 2) +
                     std::pow(toCity->y - fromCity->y, 2));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fileIn("input.txt");
    fileIn.tie(nullptr);

    ll n;
    fileIn >> n;
    City **cities = new City *[n];

    ll x, y;
    for (ll i = 0; i < n; ++i) {
        fileIn >> x >> y;
        cities[i] = new City(x, y, i + 1);
    }
    fileIn.close();

    auto **lengthArr = new double *[n];
    for (ll i = 0; i < n; ++i) {
        lengthArr[i] = new double[n];
        for (ll j = i; j < n; ++j) {
            lengthArr[i][j] = (i == j) ? INF : calcLen(cities[i], cities[j]);
        }
    }

    double length = INF;
    double currLength;
    bool *isVisited = new bool[n];
    std::vector<ll> minPath;
    std::vector<ll> currPath;


    ll start = 1;
    currPath.clear();
    currLength = 0;
    for (ll i = 0; i < n; ++i) {
        isVisited[i] = (i == start - 1);
    }

    ll curr = start;
    for (ll step = 1; step <= n; ++step) {
        ll next = curr;
        isVisited[curr - 1] = true;
        double min = INF;

        for (ll nxt = 1; nxt <= n; ++nxt) {
            if (nxt == curr) continue;

            double len = (nxt < curr) ?
                         lengthArr[nxt - 1][curr - 1] :
                         lengthArr[curr - 1][nxt - 1];

            if ((!isVisited[nxt - 1] || step == n) && len < min) {
                min = len;
                next = nxt;
            }
        }

        curr = next;
        currLength += min;
        currPath.push_back(curr);
    }

    if (currLength < length) {
        length = currLength;
        std::swap(minPath, currPath);
    }


    std::ofstream fileOut("output.txt");
    fileOut.tie(nullptr);

    fileOut << std::fixed << std::setprecision(3) << length << '\n';
    for (ll i = minPath.size() - 1; i >= 0; --i) {
        fileOut << minPath[i] << ((i != 0) ? " " : "");
    }
    fileOut.close();

    return 0;
}