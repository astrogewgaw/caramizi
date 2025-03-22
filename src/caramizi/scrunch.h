#ifndef FB_SCRUNCH
#define FB_SCRUNCH

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

namespace fb {

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<1>>
scrunch(nb::ndarray<nb::numpy, T, nb::ndim<1>> X, double factor) {
  size_t N = X.size();
  size_t n = std::floor(N / factor);
  T *Y = (T *)calloc(n, sizeof(T));

  if (factor < 1)
    throw std::runtime_error(
        "Downsampling factor must be greater than one! Exiting...");
  if (factor > N)
    throw std::runtime_error("Downsampling factor must be less than total "
                             "number of samples! Exiting...");

  for (size_t i = 0; i < n; ++i) {
    const double start = i * factor;
    const double end = start + factor;
    const size_t imin = std::floor(start);
    const size_t imax = std::min((size_t)std::floor(end), N - 1);
    const float wmin = (imin + 1) - start;
    const float wmax = end - imax;
    T acc = wmin * X(imin);
    for (size_t j = imin + 1; j < imax; ++j) acc += X(j);
    acc += wmax * X(imax);
    Y[i] = acc;
  }
  return nb::ndarray<nb::numpy, T, nb::ndim<1>>(Y, {n}, nb::handle());
}

} // namespace fb

#endif
