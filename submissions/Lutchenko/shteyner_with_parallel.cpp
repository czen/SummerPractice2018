#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <ParallelTree.hpp>
#include <chrono>
#include <iostream>
using namespace std;
typedef vector<vector<pair<int, int>>> graph;
const int INF = 999999999;
struct edge
{
    int v, u, cost;
    edge(int v, int u, int cost) : v(v), u(u), cost(cost) {}
};

struct shteyner_tree
{
    vector<edge> *edges;
    int weight = INF;
};

struct TreeNode : public Node
{
    TreeNode(int used_it, int term_it, int sz) : used_it(used_it), term_it(term_it), sz(sz) {}
    TreeNode(vector<bool> used_vertexs, int used_it, int term_it, int sz) : used_vertexs(used_vertexs), used_it(used_it), term_it(term_it), sz(sz) {}
    vector<bool> used_vertexs;
    int used_it, term_it, sz;
};

struct NumericResult : public Result
{
    NumericResult(int weight, vector<edge> *path)
    {
        record.edges = path;
        record.weight = weight;
    }

    bool betterThan(const Result &other) override
    {
        const NumericResult o = (NumericResult &)other;
        return record.weight < o.record.weight;
    }

    unique_ptr<Result> clone() override
    {
        return unique_ptr<Result>(new NumericResult(*this));
    }

    Result &operator=(const Result &other) override
    {
        const NumericResult o = (NumericResult &)other;
        record.edges = o.record.edges;
        record.weight = o.record.weight;
        return *this;
    }
    shteyner_tree record;
};

struct TreeParams : public Params
{
    TreeParams(graph &g, vector<int> &terminals)
    {
        this->g.swap(g);
        this->terminals.swap(terminals);
    }
    graph g;
    vector<int> terminals;
    shteyner_tree record;
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
        path.edges->push_back(edge(v, p[v], 0));
}

void prim(graph &g, vector<bool> &used_vertex, vector<int> &terminals, int sz, shteyner_tree &record)
{
    shteyner_tree span;
    span.weight = 0;
    vector<edge> path;
    span.edges = &path;

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
            span.edges->push_back(edge(v, sel_e[v], min_e[v]));
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
        record.edges->swap(*span.edges);
        record.weight = span.weight;
    }
}

vector<unique_ptr<Node>> processNode(unique_ptr<Node> node, Result &result, const Params *params)
{
    TreeNode *treeNode = (TreeNode *)node.get();
    NumericResult &numericResult = (NumericResult &)result;
    TreeParams *treeParams = (TreeParams *)params;

    while (treeNode->term_it < treeParams->terminals.size() && treeNode->used_it == treeParams->terminals[treeNode->term_it])
    {
        treeNode->used_it++;
        treeNode->term_it++;
    }

    if (treeNode->used_it != treeNode->used_vertexs.size())
    {
        vector<unique_ptr<Node>> children;
        treeNode->used_vertexs[treeNode->used_it] = false;
        children.emplace_back(new TreeNode(treeNode->used_vertexs, treeNode->used_it + 1, treeNode->term_it, treeNode->sz));

        treeNode->used_vertexs[treeNode->used_it] = true;
        children.emplace_back(new TreeNode(treeNode->used_vertexs, treeNode->used_it + 1, treeNode->term_it, treeNode->sz + 1));
        return children;
    }
    else
    {
        prim(treeParams->g, treeNode->used_vertexs, treeParams->terminals, treeNode->sz, numericResult.record);
        return vector<unique_ptr<Node>>();
    }
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
    vector<edge> path;
    record_shteyner_tree.edges = &path;

    read_file2(graph, used_vertexs, terminals, argv[1]);

    if (terminals.size() == 1)
        return 1;

    else if (terminals.size() == 2)
    {
        deykstra(graph, terminals[0], terminals[1], record_shteyner_tree);
        write_file(*record_shteyner_tree.edges, record_shteyner_tree.weight, start, argv[2]);
    }
    else if (terminals.size() == graph.size())
    {
        prim(graph, used_vertexs, terminals, terminals.size(), record_shteyner_tree);
        write_file(*record_shteyner_tree.edges, record_shteyner_tree.weight, start, argv[2]);
    }
    else
    {
        unique_ptr<Node> root(new TreeNode(used_vertexs, 0, 0, terminals.size()));
        TreeParams params(graph, terminals);
        NumericResult result(INF, &path);

        parallelTree(processNode, move(root), result, &params, nullptr);
        write_file(*result.record.edges, result.record.weight, start, argv[2]);
    }

    return 0;
}