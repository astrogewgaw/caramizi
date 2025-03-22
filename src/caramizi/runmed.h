#ifndef FB_RUNMED
#define FB_RUNMED

#include <vector>

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

namespace fb {

template <typename T>
size_t partition(T *X, size_t start, size_t end, size_t ipiv) {
  const T pivot = X[ipiv];
  std::swap(X[ipiv], X[end]);
  size_t j = start;
  for (size_t i = start; i < end; ++i) {
    if (X[i] < pivot) {
      std::swap(X[i], X[j]);
      ++j;
    }
  }
  std::swap(X[j], X[end]);
  return j;
}

template <typename T>
float nth_element(T *X, size_t start, size_t end, size_t n) {
  if (start == end) return X[start];
  const size_t j = partition(X, start, end, end);
  if (j == n)
    return X[j];
  else if (j < n)
    return nth_element(X, j + 1, end, n);
  else
    return nth_element(X, start, j - 1, n);
}

template <typename T> class RunMed {
private:
  size_t writepos;
  const size_t width;
  std::vector<T> ring;
  std::vector<T> buffer;

  void ringpush(T value) {
    ring[writepos] = value;
    ++writepos;
    if (writepos >= width) writepos = 0;
  }

public:
  RunMed(size_t width)
      : width(width), ring(width), writepos(0), buffer(width) {}

  float push(float value) {
    ringpush(value);
    std::copy(ring.begin(), ring.end(), buffer.begin());
    return nth_element(buffer.data(), 0, width - 1, width / 2);
  }
};

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<1>>
runmed(nb::ndarray<nb::numpy, T, nb::ndim<1>> X, size_t width) {
  const size_t N = X.size();
  const size_t half = width / 2;
  auto rm = RunMed<T>(width);
  T *Y = (T *)calloc(N, sizeof(T));
  for (size_t i = 0; i < half + 1; ++i) rm.push(X(0));
  for (size_t i = 1; i < half; ++i) rm.push(X(i));
  for (size_t i = half; i < N; ++i) Y[i - half] = rm.push(X(i));
  for (size_t i = 0; i < half; ++i) Y[N - half + i] = rm.push(X(N - 1));
  return nb::ndarray<nb::numpy, T, nb::ndim<1>>(Y, {N}, nb::handle());
}

} // namespace fb

#endif
