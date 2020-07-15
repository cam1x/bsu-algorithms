#include <iostream>
#include <fstream>
#include <queue>

#define ll long long

int main()
{
    std::ifstream file_in("input.txt");
    std::ofstream file_out("output.txt");

    ll n, m;
    file_in >> n >> m;

    std::vector<std::vector<std::pair<ll, ll>>> ribs(n);
    ll first_tmp, second_tmp, third_tmp;
    for (ll i = 0; i < m; ++i) {
        file_in >> first_tmp >> second_tmp >> third_tmp;
        ribs[first_tmp - 1].push_back(std::make_pair(second_tmp - 1, third_tmp));
        ribs[second_tmp - 1].push_back(std::make_pair(first_tmp - 1, third_tmp));
    }
    file_in.close();

    ll* ways = new ll[n];
    for (ll i = 0; i < n; ++i)
    {
        ways[i] = INT64_MAX;
    }

    std::priority_queue<std::pair<ll, ll>, std::vector<std::pair<ll, ll>>, std::greater<std::pair<ll, ll>>> queue;
    queue.push(std::make_pair(0l, 0l));
    ways[0] = 0l;

    while (!queue.empty())
    {
        std::pair<ll, ll> curr = queue.top();
        queue.pop();

        ll first = curr.first;
        ll second = curr.second;

        if (ways[second] < first) continue;

        for (std::pair<ll, ll> rib : ribs[second])
        {
            ll f = rib.first;
            ll s = rib.second;

            ll dst = first + s;
            if (dst < ways[f])
            {
                ways[f] = dst;
                queue.push(std::make_pair(dst, f));
            }
        }
    }

    std::cout << ways[n - 1] << std::endl;
    file_out << ways[n - 1];
    file_out.close();
}
