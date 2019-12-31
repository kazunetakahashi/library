#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
using namespace std;

// ----- FFT -----

using Complex = complex<double>;

class FFT
{
  int N;
  vector<Complex> A;

public:
  FFT(FFT const &f) : N{f.N}, A(f.A) {}
  FFT(vector<Complex> const &A) : N{1}, A(A)
  {
    while (N < static_cast<int>(A.size()))
    {
      N <<= 1;
    }
    FFT::A.resize(N);
  }
  FFT(size_t x) : N{1}
  {
    while (N < static_cast<int>(x))
    {
      N <<= 1;
    }
    A.resize(N);
  }
  Complex &operator[](size_t i) { return A[i]; }
  Complex const &operator[](size_t i) const { return A[i]; }
  size_t size() const { return A.size(); }

  FFT fft(int sign = 1)
  {
    if (N == 1)
    {
      return *this;
    }
    Complex omega_N{exp(Complex(0, sign * 2 * M_PI / N))};
    Complex omega{1};
    vector<FFT> a(2, FFT(N / 2));
    for (auto i = 0; i < N; i++)
    {
      a[i % 2][i / 2] = A[i];
    }
    vector<FFT> y{FFT{a[0].fft(sign)}, FFT{a[1].fft(sign)}};
    FFT res(N);
    for (auto i = 0; i < N / 2; i++)
    {
      res[i] = y[0][i] + omega * y[1][i];
      res[i + N / 2] = y[0][i] - omega * y[1][i];
      omega *= omega_N;
    }
    return res;
  }

  FFT inv_fft()
  {
    FFT res{fft(-1)};
    for (auto &x : res.A)
    {
      x /= N;
    }
    return res;
  }
};

// ----- multiply_polynominal -----

template <typename T>
vector<T> operator*(vector<T> const &left, vector<T> const &right)
{
  int N = left.size() + right.size();
  FFT A(N), B(N);
  for (auto i = 0; i < static_cast<int>(left.size()); i++)
  {
    A[i] = left[i]; // cast
  }
  for (auto i = 0; i < static_cast<int>(right.size()); i++)
  {
    B[i] = right[i]; // cast
  }
  FFT FA{A.fft()}, FB{B.fft()};
  FFT C(N);
  for (auto i = 0; i < static_cast<int>(C.size()); i++)
  {
    C[i] = FA[i] * FB[i];
  }
  FFT IC{C.inv_fft()};
  vector<T> res(IC.size());
  for (auto i = 0; i < static_cast<int>(IC.size()); i++)
  {
    res[i] = real(IC[i]) + 0.5; // cast
  }
  return res;
}

int main()
{
  int N;
  cin >> N;
  vector<long long> A(N + 1), B(N + 1);
  for (auto i = 1; i <= N; i++)
  {
    cin >> A[i] >> B[i];
  }
  auto C{A * B};
  for (auto i = 1; i <= 2 * N; i++)
  {
    cout << C[i] << endl;
  }
}
