#ifndef FB_DD
#define FB_DD

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

namespace fb {

constexpr double kdm = 1 / 2.41e-4;

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<1>>
dd(nb::ndarray<nb::numpy, T, nb::ndim<2>> X, double fh, double bw, double dt,
   double dm) {
  auto x = X.view();
  const size_t nf = x.shape(0);
  const size_t nt = x.shape(1);
  T *Y = (T *)calloc(nt, sizeof(T));

  int jj;
  int xi;
  double f, shift;
  double df = bw / nf;

  for (size_t i = 0; i < nf; ++i) {
    xi = (int)std::round(
        kdm * dm * (std::pow(fh - (i * df), -2.0) - std::pow(fh, -2.0)) / dt);
    for (size_t j = 0; j < nt; ++j) {
      jj = j + xi;
      if (jj < nt) Y[j] += x(i, jj);
    }
  }
  return nb::ndarray<nb::numpy, T, nb::ndim<1>>(Y, {nt}, nb::handle());
}

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<2>>
rolldd(nb::ndarray<nb::numpy, T, nb::ndim<2>> X, double fh, double bw,
       double dt, double dm) {
  size_t nf = X.shape(0);
  size_t nt = X.shape(1);
  T *Y = (T *)calloc(nf * nt, sizeof(T));

  int jj;
  int xi;
  double f, shift;
  double df = bw / nf;
  for (size_t i = 0; i < nf; ++i) {
    xi = (int)std::round(
        kdm * dm * (std::pow(fh - (i * df), -2.0) - std::pow(fh, -2.0)) / dt);
    for (size_t j = 0; j < nt; ++j) {
      jj = j + xi;
      if (jj >= nt) jj = jj % nt;
      Y[i * nt + j] = X(i, jj);
    }
  }
  return nb::ndarray<nb::numpy, T, nb::ndim<2>>(Y, {nf, nt}, nb::handle());
}

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<2>>
dmt(nb::ndarray<nb::numpy, T, nb::ndim<2>> X, double fh, double bw, double dt,
    double lodm, double hidm, size_t ndms) {
  size_t nf = X.shape(0);
  size_t nt = X.shape(1);
  T *Y = (T *)calloc(ndms * nt, sizeof(T));

  int kk;
  int xi;
  double f, shift;
  double df = bw / nf;
  double ddm = (hidm - lodm) / (ndms - 1);
  for (size_t i = 0; i < ndms; ++i) {
    for (size_t j = 0; j < nf; ++j) {
      xi = (int)std::round(
          kdm * (lodm + i * ddm) *
          (std::pow(fh - (j * df), -2.0) - std::pow(fh, -2.0)) / dt);
      for (size_t k = 0; k < nt; ++k) {
        kk = k + xi;
        if (kk < nt) Y[i * nt + k] += X(j, kk);
      }
    }
  }
  return nb::ndarray<nb::numpy, T, nb::ndim<2>>(Y, {ndms, nt}, nb::handle());
}

} // namespace fb

#endif
