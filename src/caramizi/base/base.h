#ifndef CZ_BASE
#define CZ_BASE

#include "dd.h"
#include "fold.h"
#include "norm.h"
#include "runmed.h"
#include "scrunch.h"

#include "nanobind/nanobind.h"
namespace nb = nanobind;

void initbase(nb::module_ m);

#endif
