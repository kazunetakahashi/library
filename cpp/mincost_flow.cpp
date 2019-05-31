#define DEBUG 1

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

typedef long long ll;

// ------------------------------------------------------------

typedef tuple<ll, int> Info;

struct Edge
{
  int to;
  ll cap, cost;
  int rev;
};

class MinCostFlow
{
  int N;
  vector<Edge> *G;
  ll *h, *dist;
  int *prev_v, *prev_e;
  ll INFTY = 10000000000000010;

public:
  MinCostFlow() {}

  MinCostFlow(int n) : N(n)
  {
    G = new vector<Edge>[n];
    h = new ll[n];
    dist = new ll[n];
    prev_v = new int[n];
    prev_e = new int[n];
  }

  void add_edge(int from, int to, ll cap, ll cost)
  {
    G[from].push_back((Edge){to, cap, cost, (int)G[to].size()});
    G[to].push_back((Edge){from, 0, -cost, (int)G[from].size() - 1});
  }

  ll min_cost_flow(int s, int t, ll f)
  {
    ll res = 0;
    fill(h, h + N, 0);
    while (f > 0)
    {
      priority_queue<Info, vector<Info>, greater<Info>> Q;
      fill(dist, dist + N, INFTY);
      dist[s] = 0;
      Q.push(Info(0, s));
      while (!Q.empty())
      {
        Info p = Q.top();
        Q.pop();
        int v = get<1>(p);
        if (dist[v] < get<0>(p))
        {
          continue;
        }
        for (auto i = 0; i < (int)G[v].size(); i++)
        {
          Edge &e = G[v][i];
          ll tmp = dist[v] + e.cost + h[v] - h[e.to];
          if (e.cap > 0 && dist[e.to] > tmp)
          {
            dist[e.to] = tmp;
            prev_v[e.to] = v;
            prev_e[e.to] = i;
            Q.push(Info(dist[e.to], e.to));
          }
        }
      }
      if (dist[t] == INFTY)
      {
        return -1;
      }
      for (auto v = 0; v < N; v++)
      {
        h[v] += dist[v];
      }
      ll d = f;
      for (auto v = t; v != s; v = prev_v[v])
      {
        d = min(d, G[prev_v[v]][prev_e[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for (auto v = t; v != s; v = prev_v[v])
      {
        Edge &e = G[prev_v[v]][prev_e[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};

// ------------------------------------------------------------

int N, M;
ll F;
MinCostFlow flow;

int main()
{
  cin >> N >> M >> F;
  flow = MinCostFlow(N);
  for (auto i = 0; i < M; i++)
  {
    int u, v;
    ll c, d;
    cin >> u >> v >> c >> d;
    flow.add_edge(u, v, c, d);
  }
  cout << flow.min_cost_flow(0, N - 1, F) << endl;
}