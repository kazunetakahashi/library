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
<script type="text/javascript" src="assets/js/copy-button.js"></script>
<link rel="stylesheet" href="assets/css/copy-button.css" />


# {{ site.title }}

[![Actions Status]({{ site.github.repository_url }}/workflows/verify/badge.svg)]({{ site.github.repository_url }}/actions)
<a href="{{ site.github.repository_url }}"><img src="https://img.shields.io/github/last-commit/{{ site.github.owner_name }}/{{ site.github.repository_name }}" /></a>

{% if site.description %}{{ site.description }}{% else %}This documentation is automatically generated by <a href="https://github.com/kmyk/online-judge-verify-helper">online-judge-verify-helper</a>.{% endif %}

## Library Files

<div id="5058f1af8388633f609cadb75a75dc9d"></div>

### .

* :warning: <a href="library/Bipartite.cpp.html">Bipartite.cpp</a>
* :warning: <a href="library/Dinic.cpp.html">Dinic.cpp</a>
* :warning: <a href="library/EulerNums.cpp.html">EulerNums.cpp</a>
* :warning: <a href="library/FFT.cpp.html">FFT.cpp</a>
* :warning: <a href="library/KMP.cpp.html">KMP.cpp</a>
* :warning: <a href="library/LCA.cpp.html">LCA.cpp</a>
* :warning: <a href="library/LazySegTree.cpp.html">LazySegTree.cpp</a>
* :warning: <a href="library/LinearMod.cpp.html">LinearMod.cpp</a>
* :warning: <a href="library/Matrix.cpp.html">Matrix.cpp</a>
* :warning: <a href="library/MaxFlow.cpp.html">MaxFlow.cpp</a>
* :warning: <a href="library/MinCostFlow.cpp.html">MinCostFlow.cpp</a>
* :warning: <a href="library/RangeAddQuery.cpp.html">RangeAddQuery.cpp</a>
* :warning: <a href="library/SegTree.cpp.html">SegTree.cpp</a>
* :warning: <a href="library/Sieve.cpp.html">Sieve.cpp</a>
* :warning: <a href="library/SuffixArray.cpp.html">SuffixArray.cpp</a>
* :warning: <a href="library/UnionFind.cpp.html">UnionFind.cpp</a>
* :warning: <a href="library/ZAlgorithm.cpp.html">ZAlgorithm.cpp</a>


<div id="149603e6c03516362a8da23f624db945"></div>

### old

* :warning: <a href="library/old/fast_fourier_transform.cpp.html">old/fast_fourier_transform.cpp</a>
* :warning: <a href="library/old/kansetsu.cpp.html">old/kansetsu.cpp</a>
* :warning: <a href="library/old/under_count.cpp.html">old/under_count.cpp</a>


## Verify Files

* :heavy_check_mark: <a href="verify/example.test.cpp.html">example.test.cpp</a>

