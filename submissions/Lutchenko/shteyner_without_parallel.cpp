#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <chrono>
using namespace std;

typedef vector<vector<pair<int, int>>> graph;
const int INF = 999999999;
std::chrono::time_point<std::chrono::system_clock> start;
struct edge
{
    int v, u, cost;
    edge(int v, int u, int cost) : v(v), u(u), cost(cost) {}
};
struct shteyner_tree
{
    vector<edge> edges;
    int weight;
};

void read_file(graph &g, vector<bool> &used_vertex, vector<int> &terminals, string str)
{
    ifstream fin(str);
    int v, cost, n;
    fin >> n;

    g.resize(n);

    for (auto &u : g)
    {
        fin >> n;
        for (int i = 0; i < n; ++i)
        {
            fin >> v;
            fin >> cost;
            u.push_back(make_pair(v, cost));
        }
    }

    fin >> n;
    terminals.resize(n);
    used_vertex.resize(g.size());

    for (auto &v : terminals)
    {
        fin >> v;
        used_vertex[v] = true;
    }
    sort(terminals.begin(), terminals.end());

    fin.close();
}

void read_file2(graph &g, vector<bool> &used_vertex, vector<int> &terminals, string str)
{
    ifstream fin(str);
    int u, v, cost, n, m;
    fin >> n;
    fin >> m;

    g.resize(n);

    for (int i = 0; i < m; ++i)
    {
        fin >> u;
        fin >> v;
        fin >> cost;
        g[u].push_back(make_pair(v, cost));
        g[v].push_back(make_pair(u, cost));
    }

    fin >> n;
    terminals.resize(n);
    used_vertex.resize(g.size());

    for (auto &v : terminals)
    {
        fin >> v;
        used_vertex[v] = true;
    }
    sort(terminals.begin(), terminals.end());

    fin.close();
}

void write_file(vector<edge> &edges, int weight, chrono::time_point<chrono::system_clock> &start, string str)
{
    auto end = chrono::system_clock::now();
    int elapsed_seconds = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    ofstream fout(str);
    fout << weight << endl;
    for (auto &v : edges)
        fout << v.v << " " << v.u << endl;
    fout << endl
         << (double)elapsed_seconds / 1000;

    fout.close();
}

void deykstra(graph &g, int s, int t, shteyner_tree &path)
{
    vector<int> d(g.size(), INF), p(g.size());
    d[s] = 0;
    set<pair<int, int>> q;
    q.insert(make_pair(d[s], s));
    while (!q.empty())
    {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (auto &u : g[v])
        {
            int to = u.first,
                len = u.second;
            if (d[v] + len < d[to])
            {
                q.erase(make_pair(d[to], to));
                d[to] = d[v] + len;
                p[to] = v;
                q.insert(make_pair(d[to], to));
            }
        }
    }

    path.weight = d[t];
    for (int v = t; v != s; v = p[v])
        path.edges.push_back(edge(v, p[v], 0));
}

void prim(graph &g, vector<bool> &used_vertex, vector<int> &terminals, int sz, shteyner_tree &record)
{
    shteyner_tree span;
    span.weight = 0;
    vector<int> min_e(g.size(), INF), sel_e(g.size(), -1);
    vector<bool> mst_used(g.size(), false);
    min_e[terminals[0]] = 0;
    set<pair<int, int>> q;
    q.insert(make_pair(0, terminals[0]));
    for (int i = 0; i < sz; ++i)
    {
        if (q.empty())
            return;

        int v = q.begin()->second;
        q.erase(q.begin());
        mst_used[v] = true;

        if (sel_e[v] != -1)
        {
            span.edges.push_back(edge(v, sel_e[v], min_e[v]));
            span.weight += min_e[v];
            if (span.weight > record.weight)
                return;
        }
        for (auto &u : g[v])
        {
            int to = u.first,
                cost = u.second;
            if (used_vertex[to] && !mst_used[to] && cost < min_e[to])
            {
                q.erase(make_pair(min_e[to], to));
                min_e[to] = cost;
                sel_e[to] = v;
                q.insert(make_pair(min_e[to], to));
            }
        }
    }

    if (record.weight > span.weight)
    {
        record.edges.swap(span.edges);
        record.weight = span.weight;
    }
}

void perebor(graph &g, vector<bool> &used_vertexs, vector<int> &terminals, int used_it, int term_it, int sz, shteyner_tree &record)
{
    while (term_it < terminals.size() && used_it == terminals[term_it])
    {
        used_it++;
        term_it++;
    }

    if (used_it != used_vertexs.size())
    {
        used_vertexs[used_it] = false;
        perebor(g, used_vertexs, terminals, used_it + 1, term_it, sz, record);

        used_vertexs[used_it] = true;
        perebor(g, used_vertexs, terminals, used_it + 1, term_it, sz + 1, record);
    }
    else
        prim(g, used_vertexs, terminals, sz, record);
}
#include <iostream>

void print_inf(graph &g, vector<bool> &used_vertex, vector<int> &terminals)
{
    int ii = 0;
    cout << g.size() << endl;
    for (auto &v : g)
    {
        cout << ii++ << " -> ";
        for (auto &u : v)
        {
            cout << u.first << " (" << u.second << ") ";
        }
        cout << endl;
    }

    for (auto &u : terminals)
        cout << u << " ";
    cout << endl;

    for (int i = 0; i < used_vertex.size(); cout << i++ << " ")
    {
    }
    cout << endl;
    for (int i = 0; i < used_vertex.size(); ++i)
        if (used_vertex[i])
            cout << "+ ";
        else
            cout << "- ";
    cout << endl;
    cout << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        return 0;

    auto start = std::chrono::system_clock::now();

    vector<vector<pair<int, int>>> graph;
    vector<int> terminals;
    vector<bool> used_vertexs;
    shteyner_tree record_shteyner_tree;
    record_shteyner_tree.weight = INF;

    read_file2(graph, used_vertexs, terminals, argv[1]);
    //print_inf(graph, used_vertexs, terminals);
    if (terminals.size() == 1)
        return 1;
    else if (terminals.size() == 2)
        deykstra(graph, terminals[0], terminals[1], record_shteyner_tree);

    else if (terminals.size() == graph.size())
        prim(graph, used_vertexs, terminals, terminals.size(), record_shteyner_tree);
    else
        perebor(graph, used_vertexs, terminals, 0, 0, terminals.size(), record_shteyner_tree);

    write_file(record_shteyner_tree.edges, record_shteyner_tree.weight, start, argv[2]);

    return 0;
}