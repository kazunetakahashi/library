---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: DataStructure/SegTree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/SegTree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-09 20:58:12+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/DataStructure/tests/RMQ_RUQ.test.cpp.html">DataStructure/tests/RMQ_RUQ.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/DataStructure/tests/RangeAddQuery.test.cpp.html">DataStructure/tests/RangeAddQuery.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/DataStructure/tests/RangeMinimumQuery.test.cpp.html">DataStructure/tests/RangeMinimumQuery.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/DataStructure/tests/RangeSumQuery.test.cpp.html">DataStructure/tests/RangeSumQuery.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/DataStructure/tests/RangeUpdateQuery.test.cpp.html">DataStructure/tests/RangeUpdateQuery.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>
using namespace std;
using ll = long long;

// ----- SegTree -----
// Referring to the following great materials.
//  - tsutaj-san's article: https://tsutaj.hatenablog.com/entry/2017/03/30/224339
//  - drken-san's article: https://drken1215.hatenablog.com/entry/2019/02/19/110200
//  - tsutaj-san's libary: https://tsutaj.github.io/cpp_library/library/structure/strc_021_dynamic_lazy_segtree.cpp.html
// Many thanks to them.

template <typename Monoid, typename Action>
class SegTree
{
  struct SegNode
  {
    bool need_update;
    unique_ptr<SegNode> left, right;
    Monoid value;
    Action lazy_value;

    SegNode() {}
    SegNode(Monoid value, Action lazy_value) : need_update{false}, left{nullptr}, right{nullptr}, value{value}, lazy_value{lazy_value} {}
  };

  using FuncAction = function<void(Monoid &, Action)>;
  using FuncMonoid = function<Monoid(Monoid, Monoid)>;
  using FuncLazy = function<void(Action &, Action)>;
  using FuncIndex = function<Action(Action, int)>;

  // fields
  int N;
  unique_ptr<SegNode> root;
  // unities
  Monoid unity_monoid;
  Action unity_action;
  // functions
  FuncAction func_update;
  FuncMonoid func_combine;
  FuncLazy func_lazy;
  FuncIndex func_accumulate;

public:
  SegTree() {}
  SegTree(int n, Monoid unity_monoid, Action unity_action, FuncAction func_update, FuncMonoid func_combine, FuncLazy func_lazy, FuncIndex func_accumulate) : N{1}, root{make_unique<SegNode>(unity_monoid, unity_action)}, unity_monoid(unity_monoid), unity_action(unity_action), func_update(func_update), func_combine(func_combine), func_lazy(func_lazy), func_accumulate(func_accumulate)
  {
    while (N < n)
    {
      N <<= 1;
    }
  }

  void update(int a, int b, Action const &x) { update(root.get(), a, b, x, 0, N); }
  void update(int a, Action const &x) { update(a, a + 1, x); }
  Monoid query(int a, int b) { return query(root.get(), a, b, 0, N); }
  Monoid query(int a) { return query(a, a + 1); }
  Monoid operator[](size_t i) { return query(static_cast<int>(i)); }

private:
  void node_maker(unique_ptr<SegNode> &pt) const
  {
    if (!pt)
    {
      pt = make_unique<SegNode>(unity_monoid, unity_action);
    }
  }

  void evaluate(SegNode *node, int l, int r)
  {
    if (!node->need_update)
    {
      return;
    }
    func_update(node->value, func_accumulate(node->lazy_value, r - l));
    if (r - l > 1)
    {
      node_maker(node->left);
      func_lazy(node->left->lazy_value, node->lazy_value);
      node->left->need_update = true;
      node_maker(node->right);
      func_lazy(node->right->lazy_value, node->lazy_value);
      node->right->need_update = true;
    }
    node->lazy_value = unity_action;
    node->need_update = false;
  }

  void update(SegNode *node, int a, int b, Action const &x, int l, int r)
  {
    evaluate(node, l, r);
    if (b <= l || r <= a)
    {
      return;
    }
    if (a <= l && r <= b)
    {
      func_lazy(node->lazy_value, x);
      node->need_update = true;
      evaluate(node, l, r);
    }
    else
    {
      auto mid{(l + r) >> 1};
      node_maker(node->left);
      update(node->left.get(), a, b, x, l, mid);
      node_maker(node->right);
      update(node->right.get(), a, b, x, mid, r);
      node->value = func_combine(node->left->value, node->right->value);
    }
  }

  Monoid query(SegNode *node, int a, int b, int l, int r)
  {
    if (b <= l || r <= a)
    {
      return unity_monoid;
    }
    evaluate(node, l, r);
    if (a <= l && r <= b)
    {
      return node->value;
    }
    auto mid{(l + r) >> 1};
    auto vl{(node->left ? query(node->left.get(), a, b, l, mid) : unity_monoid)};
    auto vr{(node->right ? query(node->right.get(), a, b, mid, r) : unity_monoid)};
    return func_combine(vl, vr);
  }
};

// ----- RangePlusQuery -----
//  - update(i, x) : a[i] += x;,
//  - update(s, t, x) : a[i] += x; for all i \in [s, t),
//  - query(i) : return a[i];,
//  - query(s, t) : return the sum a[i] where i runs on [s, t).

// ----- RangeSumQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=ja
//  - update(i, x) : a[i] += x;,
//  - query(s, t) : return the sum a[i] where i runs on [s, t).

// ----- RangeAddQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja
//  - update(s, t, x) : a[i] += x; for all i \in [s, t),
//  - query(i) : return a[i].

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangePlusQuery(int N, Monoid const &unity_monoid, Action const &unity_action)
{
  return SegTree<Monoid, Action>{N, unity_monoid, unity_action, [](Monoid &x, Monoid y) { x += y; }, [](Monoid x, Monoid y) { return x + y; }, [](Action &x, Action y) { return x += y; }, [](Action x, int y) { return x * y; }};
}

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangePlusQuery(int N)
{
  return RangePlusQuery<Monoid, Action>(N, 0, 0);
}

// ----- RangeMinQuery -----
//  - update(i, x) : a[i] = x;,
//  - update(s, t, x) : a[i] = x; for all i \in [s, t),
//  - query(i) : return a[i];,
//  - query(s, t) : return the minimum of a[i] where i runs on [s, t).

// ----- RangeMinimumQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=ja
//  - update(i, x) : a[i] = x;,
//  - query(s, t) : return the minimum of a[i] where i runs on [s, t).

// ----- RangeUpdateQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
//  - update(s, t, x) : a[i] = x; for all i \in [s, t),
//  - query(i) : return a[i].

// ----- RMQ_RUQ -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja
//  - update(s, t, x) : a[i] = x; for all i \in [s, t),
//  - query(s, t) : return the minimum of a[i] where i runs on [s, t).

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangeMinQuery(int N, Monoid const &unity_monoid, Action const &unity_action)
{
  return SegTree<Monoid, Action>{N, unity_monoid, unity_action, [](Monoid &x, Monoid y) { x = y; }, [](Monoid x, Monoid y) { return min(x, y); }, [](Action &x, Action y) { return x = y; }, [](Action x, int) { return x; }};
}

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangeMinQuery(int N)
{
  return RangeMinQuery<Monoid, Action>(N, numeric_limits<Monoid>::max(), numeric_limits<Action>::max());
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/SegTree.cpp"
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>
using namespace std;
using ll = long long;

// ----- SegTree -----
// Referring to the following great materials.
//  - tsutaj-san's article: https://tsutaj.hatenablog.com/entry/2017/03/30/224339
//  - drken-san's article: https://drken1215.hatenablog.com/entry/2019/02/19/110200
//  - tsutaj-san's libary: https://tsutaj.github.io/cpp_library/library/structure/strc_021_dynamic_lazy_segtree.cpp.html
// Many thanks to them.

template <typename Monoid, typename Action>
class SegTree
{
  struct SegNode
  {
    bool need_update;
    unique_ptr<SegNode> left, right;
    Monoid value;
    Action lazy_value;

    SegNode() {}
    SegNode(Monoid value, Action lazy_value) : need_update{false}, left{nullptr}, right{nullptr}, value{value}, lazy_value{lazy_value} {}
  };

  using FuncAction = function<void(Monoid &, Action)>;
  using FuncMonoid = function<Monoid(Monoid, Monoid)>;
  using FuncLazy = function<void(Action &, Action)>;
  using FuncIndex = function<Action(Action, int)>;

  // fields
  int N;
  unique_ptr<SegNode> root;
  // unities
  Monoid unity_monoid;
  Action unity_action;
  // functions
  FuncAction func_update;
  FuncMonoid func_combine;
  FuncLazy func_lazy;
  FuncIndex func_accumulate;

public:
  SegTree() {}
  SegTree(int n, Monoid unity_monoid, Action unity_action, FuncAction func_update, FuncMonoid func_combine, FuncLazy func_lazy, FuncIndex func_accumulate) : N{1}, root{make_unique<SegNode>(unity_monoid, unity_action)}, unity_monoid(unity_monoid), unity_action(unity_action), func_update(func_update), func_combine(func_combine), func_lazy(func_lazy), func_accumulate(func_accumulate)
  {
    while (N < n)
    {
      N <<= 1;
    }
  }

  void update(int a, int b, Action const &x) { update(root.get(), a, b, x, 0, N); }
  void update(int a, Action const &x) { update(a, a + 1, x); }
  Monoid query(int a, int b) { return query(root.get(), a, b, 0, N); }
  Monoid query(int a) { return query(a, a + 1); }
  Monoid operator[](size_t i) { return query(static_cast<int>(i)); }

private:
  void node_maker(unique_ptr<SegNode> &pt) const
  {
    if (!pt)
    {
      pt = make_unique<SegNode>(unity_monoid, unity_action);
    }
  }

  void evaluate(SegNode *node, int l, int r)
  {
    if (!node->need_update)
    {
      return;
    }
    func_update(node->value, func_accumulate(node->lazy_value, r - l));
    if (r - l > 1)
    {
      node_maker(node->left);
      func_lazy(node->left->lazy_value, node->lazy_value);
      node->left->need_update = true;
      node_maker(node->right);
      func_lazy(node->right->lazy_value, node->lazy_value);
      node->right->need_update = true;
    }
    node->lazy_value = unity_action;
    node->need_update = false;
  }

  void update(SegNode *node, int a, int b, Action const &x, int l, int r)
  {
    evaluate(node, l, r);
    if (b <= l || r <= a)
    {
      return;
    }
    if (a <= l && r <= b)
    {
      func_lazy(node->lazy_value, x);
      node->need_update = true;
      evaluate(node, l, r);
    }
    else
    {
      auto mid{(l + r) >> 1};
      node_maker(node->left);
      update(node->left.get(), a, b, x, l, mid);
      node_maker(node->right);
      update(node->right.get(), a, b, x, mid, r);
      node->value = func_combine(node->left->value, node->right->value);
    }
  }

  Monoid query(SegNode *node, int a, int b, int l, int r)
  {
    if (b <= l || r <= a)
    {
      return unity_monoid;
    }
    evaluate(node, l, r);
    if (a <= l && r <= b)
    {
      return node->value;
    }
    auto mid{(l + r) >> 1};
    auto vl{(node->left ? query(node->left.get(), a, b, l, mid) : unity_monoid)};
    auto vr{(node->right ? query(node->right.get(), a, b, mid, r) : unity_monoid)};
    return func_combine(vl, vr);
  }
};

// ----- RangePlusQuery -----
//  - update(i, x) : a[i] += x;,
//  - update(s, t, x) : a[i] += x; for all i \in [s, t),
//  - query(i) : return a[i];,
//  - query(s, t) : return the sum a[i] where i runs on [s, t).

// ----- RangeSumQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=ja
//  - update(i, x) : a[i] += x;,
//  - query(s, t) : return the sum a[i] where i runs on [s, t).

// ----- RangeAddQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja
//  - update(s, t, x) : a[i] += x; for all i \in [s, t),
//  - query(i) : return a[i].

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangePlusQuery(int N, Monoid const &unity_monoid, Action const &unity_action)
{
  return SegTree<Monoid, Action>{N, unity_monoid, unity_action, [](Monoid &x, Monoid y) { x += y; }, [](Monoid x, Monoid y) { return x + y; }, [](Action &x, Action y) { return x += y; }, [](Action x, int y) { return x * y; }};
}

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangePlusQuery(int N)
{
  return RangePlusQuery<Monoid, Action>(N, 0, 0);
}

// ----- RangeMinQuery -----
//  - update(i, x) : a[i] = x;,
//  - update(s, t, x) : a[i] = x; for all i \in [s, t),
//  - query(i) : return a[i];,
//  - query(s, t) : return the minimum of a[i] where i runs on [s, t).

// ----- RangeMinimumQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=ja
//  - update(i, x) : a[i] = x;,
//  - query(s, t) : return the minimum of a[i] where i runs on [s, t).

// ----- RangeUpdateQuery -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
//  - update(s, t, x) : a[i] = x; for all i \in [s, t),
//  - query(i) : return a[i].

// ----- RMQ_RUQ -----
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja
//  - update(s, t, x) : a[i] = x; for all i \in [s, t),
//  - query(s, t) : return the minimum of a[i] where i runs on [s, t).

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangeMinQuery(int N, Monoid const &unity_monoid, Action const &unity_action)
{
  return SegTree<Monoid, Action>{N, unity_monoid, unity_action, [](Monoid &x, Monoid y) { x = y; }, [](Monoid x, Monoid y) { return min(x, y); }, [](Action &x, Action y) { return x = y; }, [](Action x, int) { return x; }};
}

template <typename Monoid, typename Action>
SegTree<Monoid, Action> RangeMinQuery(int N)
{
  return RangeMinQuery<Monoid, Action>(N, numeric_limits<Monoid>::max(), numeric_limits<Action>::max());
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

