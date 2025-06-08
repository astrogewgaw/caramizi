#include "base.h"

#include "nanobind/nanobind.h"
namespace nb = nanobind;

/* clang-format off */
void initbase(nb::module_ m) {
  m.attr("kdm") = fb::kdm;
  m.def("dd", &fb::dd<float>);
  m.def("dd", &fb::dd<double>);
  m.def("rdd", &fb::rdd<float>);
  m.def("rdd", &fb::rdd<double>);
  m.def("ddmt", &fb::ddmt<float>);
  m.def("ddmt", &fb::ddmt<double>);
  m.def("fold", &fb::fold<float>);
  m.def("fold", &fb::fold<double>);
  m.def("runmed", &fb::runmed<float>);
  m.def("runmed", &fb::runmed<double>);
  m.def("scrunch", &fb::scrunch<float>);
  m.def("scrunch", &fb::scrunch<double>);
  m.def("norm", nb::overload_cast<nb::ndarray<nb::numpy, float, nb::ndim<1>>>(&fb::norm<float>));
  m.def("norm", nb::overload_cast<nb::ndarray<nb::numpy, double, nb::ndim<1>>>(&fb::norm<double>));
  m.def("norm", nb::overload_cast<nb::ndarray<nb::numpy, float, nb::ndim<2>>>(&fb::norm<float>));
  m.def("norm", nb::overload_cast<nb::ndarray<nb::numpy, double, nb::ndim<2>>>(&fb::norm<double>));
  m.def("inorm", nb::overload_cast<nb::ndarray<nb::numpy, float, nb::ndim<1>>>(&fb::inorm<float>));
  m.def("inorm", nb::overload_cast<nb::ndarray<nb::numpy, double, nb::ndim<1>>>(&fb::inorm<double>));
  m.def("inorm", nb::overload_cast<nb::ndarray<nb::numpy, float, nb::ndim<2>>>(&fb::inorm<float>));
  m.def("inorm", nb::overload_cast<nb::ndarray<nb::numpy, double, nb::ndim<2>>>(&fb::inorm<double>));
}
/* clang-format on */
