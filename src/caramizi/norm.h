#ifndef FB_NORM
#define FB_NORM

#include <algorithm>
#include <numeric>
#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

namespace fb {

template <typename T> double median(nb::ndarray<nb::numpy, T, nb::ndim<1>> X) {
  std::vector<T> XX;
  const size_t n = X.size();
  const size_t nm = n / 2;
  XX.insert(XX.end(), X.data(), X.data() + n);
  std::nth_element(XX.begin(), XX.begin() + nm, XX.end());
  double m = XX[nm];
  if (!(n & 1)) m = (*std::max_element(XX.begin(), XX.begin() + nm) + m) / 2.0;
  return m;
}

template <typename T> double stdev(nb::ndarray<nb::numpy, T, nb::ndim<1>> X) {
  auto n = X.size();
  auto XX = X.view();
  const double mean = std::accumulate(XX.data(), XX.data() + n, 0.0) / n;
  return std::sqrt(std::accumulate(
      XX.data(), XX.data() + n, 0.0,
      [&mean, &n](double accumulator, const double &val) {
        return accumulator + ((val - mean) * (val - mean) / (n - 1));
      }));
}

template <typename T> void inorm(nb::ndarray<nb::numpy, T, nb::ndim<1>> X) {
  const size_t n = X.size();
  double mu = median<T>(X);
  double sigma = stdev<T>(X);
  for (size_t i = 0; i < n; ++i) X(i) = (X(i) - mu) / sigma;
}

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<1>>
norm(nb::ndarray<nb::numpy, T, nb::ndim<1>> X) {
  const size_t n = X.size();
  double mu = median<T>(X);
  double sigma = stdev<T>(X);
  T *Y = (T *)calloc(n, sizeof(T));
  for (size_t i = 0; i < n; ++i) Y[i] = (X(i) - mu) / sigma;
  return nb::ndarray<nb::numpy, T, nb::ndim<1>>(Y, {n}, nb::handle());
}

template <typename T> void inorm(nb::ndarray<nb::numpy, T, nb::ndim<2>> X) {
  size_t nrows = X.shape(0);
  size_t ncols = X.shape(1);
  for (size_t i = 0; i < nrows; ++i) {
    nb::ndarray xx = nb::ndarray<nb::numpy, T, nb::ndim<1>>(
        X.data() + i * ncols, {ncols}, nb::handle());
    inorm(xx);
  }
}

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<2>>
norm(nb::ndarray<nb::numpy, T, nb::ndim<2>> X) {
  double mu, sigma;
  size_t nrows = X.shape(0);
  size_t ncols = X.shape(1);
  T *Y = (T *)calloc(nrows * ncols, sizeof(T));
  for (size_t i = 0; i < nrows; ++i) {
    nb::ndarray xx = nb::ndarray<nb::numpy, T, nb::ndim<1>>(
        X.data() + i * ncols, {ncols}, nb::handle());
    mu = median<T>(xx);
    sigma = stdev<T>(xx);
    for (size_t j = 0; j < ncols; ++j) Y[i * ncols + j] = (xx(i) - mu) / sigma;
  }
  return nb::ndarray<nb::numpy, T, nb::ndim<2>>(Y, {nrows, ncols},
                                                nb::handle());
}

} // namespace fb

#endif
