#ifndef FB_FOLD
#define FB_FOLD

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

namespace fb {

struct FoldStatistics {
  int n;
  int nprof;
  double var;
  double mean;
  double profvar;
  double profmean;
  double redchisqr;
};

inline int isone(int x) { return std::abs(x - 1.0) < 1e-12; }

template <typename T>
inline double sprinkle(T *profile, T *buffer, int nprof, double phzlow,
                       double delphz, T x, double phzadded) {
  int xi_i;
  double delxi = 1.0 / nprof;
  double valperphz = x / delphz;
  double xicurr = phzlow * nprof;
  double delphzcurr, phzleft, fracdelphz;
  while (delphz > 1e-12) {
    xi_i = (int)std::floor(xicurr + 1e-12);
    delphzcurr = ((xi_i + 1.0) - xicurr) * delxi;
    xi_i = xi_i % nprof;
    if (delphzcurr > delphz) delphzcurr = delphz;
    phzleft = 1 - phzadded;
    fracdelphz = (phzleft > delphzcurr) ? delphzcurr : phzleft;
    buffer[xi_i] += fracdelphz * valperphz;
    phzadded += fracdelphz;
    if (isone(phzadded)) {
      for (size_t j = 0; j < nprof; ++j) profile[j] += buffer[j];
      for (size_t j = 0; j < nprof; ++j) buffer[j] = 0.0;
      fracdelphz = delphzcurr - phzleft;
      buffer[xi_i] += fracdelphz * valperphz;
      phzadded = fracdelphz;
    }
    delphz -= delphzcurr;
    xicurr += delphzcurr * nprof;
  }
  return phzadded;
}

template <typename T>
void delta(T *profile, T *buffer, int nprof, double phzlow, double delphz,
           T x) {
  int xi = (int)(std::floor((phzlow + 0.5 * delphz) * nprof + 1e-12)) % nprof;
  buffer[xi] += 1.0;
  profile[xi] += x;
}

template <typename T>
nb::ndarray<nb::numpy, T, nb::ndim<1>>
fold(nb::ndarray<nb::numpy, T, nb::ndim<1>> data, double dt, double f0,
     int nprof, double t0, double phz0, double fd, double fdd, bool standard) {
  FoldStatistics stats;
  T *buffer = (T *)calloc(nprof, sizeof(T));
  T *profile = (T *)calloc(nprof, sizeof(T));

  double sigma, dtmp;
  long double tnext = 0.0, phz = 0.0, phzlow = 0.0, phzhigh = 0.0,
              phznext = 0.0, delphz = 0.0, phzadded = 0.0;

  fd /= 2.0;
  fdd /= 6.0;
  stats.nprof = nprof;
  stats.var *= (stats.n - 1.0);
  phz = t0 * (t0 * (t0 * fdd + fd) + f0) + phz0;
  phzlow = (phz < 0.0) ? 1.0 + std::modf(phz, &dtmp) : std::modf(phz, &dtmp);
  for (size_t i = 0; i < data.shape(0); ++i) {
    tnext = t0 + i * dt;
    phznext = tnext * (tnext * (tnext * fdd + fd) + f0) + phz0;
    delphz = phznext - phz;
    if (standard)
      phzadded = sprinkle<T>(profile, buffer, nprof, phzlow, delphz, data(i),
                             phzadded);
    else
      delta<T>(profile, buffer, nprof, phzlow, delphz, data(i));
    phzhigh = phzlow + delphz;
    phzlow = std::modf(phzhigh, &dtmp);
    phz = phznext;

    stats.n += 1;
    sigma = data(i) - stats.mean;
    stats.mean += sigma / stats.n;
    stats.var += std::pow(sigma, 2.0);
  }
  for (size_t i = 0; i < nprof; ++i) stats.profmean += profile[i];
  stats.profmean /= nprof;

  stats.redchisqr = 0.0;
  for (size_t i = 0; i < nprof; ++i)
    stats.redchisqr += std::pow(profile[i] - stats.profmean, 2.0);
  stats.var /= (stats.n - 1);
  stats.profvar = stats.var * stats.n * (1.0 / nprof);
  stats.redchisqr /= (stats.profvar * (nprof - 1));
  phznext = (phznext < 0.0) ? 1.0 + std::modf(phznext, &dtmp)
                            : std::modf(phznext, &dtmp);

  return nb::ndarray<nb::numpy, T, nb::ndim<1>>(profile, {(size_t)nprof},
                                                nb::handle());
}

} // namespace fb

#endif
