// По системе двусторонних дорог определить, есть ли в ней город, из которого можно добраться в любой другой, проехав меньше 100 км. Разрешается построить дополнительно три дороги.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<long long> solve(int start,
    vector<vector<pair<int, int>>>& g) {

    int n = g.size();

    vector<long long> dist(n, 9999);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

    dist[start] = 0;
    q.push({ 0, start });

    while (!q.empty()) {

        long long d = q.top().first;
        int v = q.top().second;
        q.pop();

        if (d != dist[v])
            continue;

        for (auto edge : g[v]) {

            int to = edge.first;
            int w = edge.second;

            if (dist[to] > dist[v] + w) {

                dist[to] = dist[v] + w;

                q.push({ dist[to], to });
            }
        }
    }

    return dist;
}

int main() {
    int n = 4;

    vector<vector<pair<int, int>>> g(n);

    g[0].push_back({ 1, 30 });
    g[1].push_back({ 0, 30 });

    g[0].push_back({ 2, 40 });
    g[2].push_back({ 0, 40 });

    g[1].push_back({ 3, 20 });
    g[3].push_back({ 1, 20 });

    g[2].push_back({ 3, 10 });
    g[3].push_back({ 2, 10 });
    
    bool ok = false;

    for (int i = 0; i < n; i++) {

        vector<long long> dist = solve(i, g);

        int newRoads = 0;

        for (int j = 0; j < n; j++) {

            if (j != i && dist[j] >= 100)
                newRoads++;
        }

        if (newRoads <= 3) {
            ok = true;
            break;
        }
    }
    cout << ok;
}