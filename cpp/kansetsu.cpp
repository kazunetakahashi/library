// https://github.com/kazunetakahashi/icpc-challenge/blob/dd2b813997088a361e1e6d30ff6f8caa5bc39e5a/1201/1201_1.cpp を再構成してライブラリにした。

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
using namespace std;

const int MAX_SIZE = 100010;

// 入力先
int N;                            // 頂点の数
vector<int> graph_pass[MAX_SIZE]; // 隣接リストで連結グラフを入れておく。
int root = 0;                     // 根を指定する場合はここに書く。

/*
  辺には2種類ある。
  1. 親子関係を結ぶ辺
  2. その他(backedge)
  1.は、親へ向かう方向と、子に向かう方向を厳密に区別する。
  2.は、階層が上がる方向と、下がる方向を区別する。
 */

// 作業用
stack<int> S_lowest;
int visit[MAX_SIZE];  // 頂点を訪れた回数
int depth[MAX_SIZE];  // 深さ優先探索の階数
int parent[MAX_SIZE]; // 親
int lowest[MAX_SIZE]; // 子へ向かう方向とbackedgeで上がる方向を辿っていける最上階。つまり、親へ向かう方向は辿れない。

// 解答入力先
bool iskansetsu[MAX_SIZE];
vector<int> kansetsu_v;
vector<int> graph_tree[MAX_SIZE]; // backpassを削除したもの

void calc_lowest()
{
  S_lowest.push(root);
  parent[root] = -1;
  fill(visit, visit + N, 0);
  fill(lowest, lowest + N, -1);
  while (!S_lowest.empty())
  {
    int node = S_lowest.top();
    S_lowest.pop();
    if (visit[node] == 0)
    { // 普通に深さ優先探索をする。
      visit[node]++;
      depth[node] = ((parent[node] >= 0) ? depth[parent[node]] + 1 : 0);
      S_lowest.push(node);
      for (auto child : graph_pass[node])
      {
        if (visit[child] == 0)
        {
          S_lowest.push(child); // 実際は、後天的にbackedge先になる点も含まれる。
          parent[child] = node; // 最後に更新された親が本物の親。
        }
      }
    }
    else if (visit[node] == 1)
    { // 子を全部巡り終えた。
      visit[node]++;
      lowest[node] = depth[node];
      for (auto child : graph_pass[node])
      {
        if (child != parent[node])
        {
          if (lowest[child] == -1)
          { // 実は子でない。つまりbackedge先の点。
            lowest[node] = min(lowest[node], depth[child]);
          }
          else
          { // これは子。子はlowest確定済み。
            // (backedgeで下がる方向は辿れるが、その先は子孫なので、
            // 子のlowestに結果には影響を及ぼさない)
            lowest[node] = min(lowest[node], lowest[child]);
          }
        }
      }
    }
  }
}

int calc_kansetsu()
{ // calc_lowest(); を先に実行
  fill(iskansetsu, iskansetsu + N, false);
  kansetsu_v.clear();
  // root(つまり0)は関節点か
  int root_children = 0;
  for (auto i = 0; i < N; i++)
  {
    if (parent[i] == root)
      root_children++;
  }
  if (root_children >= 2)
  {
    // 子が2人以上いることが、rootが関節点であることの必要十分条件。
    // (rootは最祖先だから、backedgeを持たない)
    kansetsu_v.push_back(root);
    iskansetsu[root] = true;
  }
  // その他の辺は関節点か
  for (auto i = 0; i < N; i++)
  {
    if (parent[i] != -1 && parent[i] != root && depth[parent[i]] <= lowest[i])
    {
      // lowestで使った辺で親よりも上の階層に行けることが、
      // 親 が 関節点で な い ことの必要十分条件。
      kansetsu_v.push_back(parent[i]);
      iskansetsu[parent[i]] = true;
    }
    // 誰の親でもない点は関節点でない。
  }
  return (int)kansetsu_v.size();
}

void make_graph_tree()
{ // calc_lowest(); を先に実行
  for (auto i = 0; i < N; i++)
  {
    for (auto x : graph_pass[i])
    {
      if (parent[x] == i)
      {
        graph_tree[i].push_back(x);
        graph_tree[x].push_back(i);
      }
    }
  }
}

int main()
{
}
