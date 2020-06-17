#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <complex>
#include <vector>
using namespace std;
using ll = long long;
using ld = long double;
template <typename T>
constexpr T Infty() { return numeric_limits<T>::max(); }
template <typename T>
constexpr T mInfty() { return numeric_limits<T>::min(); }

// ----- Geometry Library -----
// Referring to the great source codes:
//   - Maehara-san's algorithm library: http://www.prefield.com/algorithm/index.html
// Many thanks.

// ----- Basic Classes -----

constexpr ld EPSILON{1e-12};

// ----- Point -----

using Point = complex<ld>;
bool operator<(Point const &p, Point const &q)
{
  return real(p) != real(q) ? real(p) < real(q) : imag(p) < imag(q);
}
istream &operator>>(istream &is, Point &p)
{
  ld x, y;
  is >> x >> y;
  p = Point{x, y};
  return is;
}

ld OuterProduct(Point const &p, Point const &q)
{
  return imag(conj(p) * q);
}
ld InnerProduct(Point const &p, Point const &q)
{
  return real(conj(p) * q);
}

Point Normalize(Point const &p)
{
  return p / abs(p);
}

// ---- ccw -----

int ccw(Point a, Point b, Point c)
{
  b -= a;
  c -= a;
  auto tmp{OuterProduct(b, c)};
  if (tmp > 0)
  {
    return +1; // counter clockwise
  }
  if (tmp < 0)
  {
    return -1; // clockwise
  }
  if (InnerProduct(b, c) < 0)
  {
    return +2; // c--a--b on line
  }
  if (norm(b) < norm(c))
  {
    return -2; // a--b--c on line
  }
  return 0;
}

// ----- Geom -----

using Geom = vector<Point>;

Geom &operator+=(Geom &g, Point const &p)
{
  for (auto &q : g)
  {
    q += p;
  }
  return g;
}
Geom operator+(Geom const &g, Point const &p)
{
  Geom h{g};
  return h += p;
}
Geom &operator-=(Geom &g, Point const &p)
{
  return g += (-p);
}
Geom operator-(Geom const &g, Point const &p)
{
  return g + (-p);
}

// ----- Line -----

struct Segment;

struct Line : public Geom
{
  Line(Point const &p, Point const &q)
  {
    push_back(p);
    push_back(q);
  }
};

// ----- Segment -----

struct Segment : public Line
{
};

// ----- Circle -----

struct Circle
{
  Point p;
  ld r;

  Circle(Point const &p, ld r) : p(p), r(r) {}
};

// ----- Functions -----

// ----- Rotate -----

Point Rotate(Point const &p, ld radian = M_PI / 2)
{
  return p * Point{cos(radian), sin(radian)};
}
Geom Rotate(Geom g, ld radian = M_PI / 2)
{
  for (auto &p : g)
  {
    p = Rotate(p, radian);
  }
  return g;
}

// ----- Projection and Reflection (Point and Line) -----

Point Projection(Line const &l, Point const &p)
{
  ld t{InnerProduct(p - l[0], l[0] - l[1]) / norm(l[0] - l[1])};
  return l[0] + t * (l[0] - l[1]);
}

Point Reflection(Line const &l, Point const &p)
{
  return p + ld{2} * (Projection(l, p) - p);
}

// ----- Intersect -----

bool Intersect(Line const &l, Line const &m)
{
  return abs(OuterProduct(l[1] - l[0], m[1] - m[0])) > EPSILON || // non-parallel
         abs(OuterProduct(l[1] - l[0], m[0] - l[0])) < EPSILON;   // same line
}
bool Intersect(Line const &l, Segment const &s)
{
  return OuterProduct(l[1] - l[0], s[0] - l[0]) * OuterProduct(l[1] - l[0], s[1] - l[0]) < EPSILON;
}
bool Intersect(Segment const &s, Line const &l)
{
  return Intersect(l, s);
}
bool Intersect(Line const &l, Point const &p)
{
  return abs(OuterProduct(l[1] - p, l[0] - p)) < EPSILON;
}
bool Intersect(Point const &p, Line const &l)
{
  return Intersect(l, p);
}
bool Intersect(Segment const &s, Segment const &t)
{
  return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 &&
         ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}
bool Intersect(Segment const &s, Point const &p)
{
  return abs(s[0] - p) + abs(s[1] - p) - abs(s[1] - s[0]) < EPSILON; // triangle inequality
}
bool Intersect(Point const &p, Segment const &s)
{
  return Intersect(s, p);
}
bool Intersect(Circle const &a, Circle const &b)
{
  return a.r + b.r + EPSILON < abs(a.p - b.p);
}

// ----- Dist -----

ld Dist(Point const &p, Point const &q)
{
  return abs(p - q);
}
ld Dist(Line const &l, Point const &p)
{
  return abs(p - Projection(l, p));
}
ld Dist(Point const &p, Line const &l)
{
  return Dist(l, p);
}
ld Dist(Line const &l, Line const &m)
{
  return Intersect(l, m) ? 0 : Dist(l, m[0]);
}
ld Dist(Line const &l, Segment const &s)
{
  if (Intersect(l, s))
  {
    return 0;
  }
  return min(Dist(l, s[0]), Dist(l, s[1]));
}
ld Dist(Segment const &s, Line const &l)
{
  return Dist(l, s);
}
ld Dist(Segment const &s, Point const &p)
{
  auto r{Projection(static_cast<Line>(s), p)};
  if (Intersect(s, r))
  {
    return abs(r - p);
  }
  return min(abs(s[0] - p), abs(s[1] - p));
}
ld Dist(Point const &p, Segment const &s)
{
  return Dist(s, p);
}
ld Dist(Segment const &s, Segment const &t)
{
  if (Intersect(s, t))
  {
    return 0;
  }
  return min({Dist(s, t[0]), Dist(s, t[1]), Dist(t, s[0]), Dist(t, s[1])});
}

// ----- IntersectionPoints ------

vector<Point> IntersectionPoints(Circle const &a, Circle const &b)
{
  auto d{Dist(a.p, b.p)};
  if (a.r + b.r + EPSILON < d)
  {
    return {};
  }
  auto l{(a.r * a.r - b.r * b.r + d * d) / (2 * d)};
  auto tmp{a.r * a.r - l * l};
  if (tmp <= 0)
  {
    return {};
  }
  auto h{sqrt(tmp)};
  vector<Point> res;
  auto v{Normalize(b.p - a.p)};
  auto w{Rotate(v)};
  res.push_back(a.p + v * l + w * h);
  res.push_back(a.p + v * l - w * h);
  return res;
}

vector<Point> IntersectionPoints(Line const &l, Line const &m)
{
  auto A{OuterProduct(l[1] - l[0], m[1] - m[0])};
  auto B{OuterProduct(l[1] - l[0], l[1] - m[0])};
  if (abs(A) < EPSILON && abs(B) < EPSILON)
  {
    return {m[0], m[1], l[0], l[1]}; // same line
  }
  if (abs(A) < EPSILON)
  {
    assert(false); // Precondition is not satisfied.
  }
  return {m[0] + B / A * (m[1] - m[0])};
}

// ----- Contains -----

enum class ContainState
{
  OUT,
  ON,
  IN
};

ContainState Contains(Geom const &g, Point const &p)
{
  bool in{false};
  for (auto i{size_t{0}}; i < g.size(); ++i)
  {
    auto a{g[i] - p};
    auto b{g[(i + 1) % g.size()] - p};
    if (imag(a) > imag(b))
    {
      swap(a, b);
    }
    if (imag(a) <= 0 && 0 < imag(b) && OuterProduct(a, b) < 0)
    {
      in = !in;
    }
    if (abs(OuterProduct(a, b)) < EPSILON && InnerProduct(a, b) < EPSILON)
    {
      return ContainState::ON;
    }
  }
  return in ? ContainState::IN : ContainState::OUT;
}

ContainState Contains(Circle const &c, Point const &p)
{
  auto d{Dist(c.p, p)};
  if (abs(d - c.r) < EPSILON)
  {
    return ContainState::ON;
  }
  if (d > c.r)
  {
    return ContainState::OUT;
  }
  return ContainState::IN;
}

bool ContainStateToBool(ContainState s)
{
  return s == ContainState::IN || s == ContainState::ON;
}

template <typename T, typename U>
bool DoesContain(T const &a, U const &b)
{
  return ContainStateToBool(Contains(a, b));
}
