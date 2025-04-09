#include "cz.h"

/* clang-format off */
NB_MODULE(base, m) {
  m.attr("kdm") = fb::kdm;
  m.def("dd", &fb::dd<float>);
  m.def("dd", &fb::dd<double>);
  m.def("rdd", &fb::rdd<float>);
  m.def("rdd", &fb::rdd<double>);
  m.def("dmt", &fb::dmt<float>);
  m.def("dmt", &fb::dmt<double>);
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
