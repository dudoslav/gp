#include <pybind11/pybind11.h>
#include <gp.hh>

namespace py = pybind11;

float square(float x) { return x * x; }

PYBIND11_MODULE(gp_py, m) {
	m.def("generate", [](){
		return gp::gen(gp::selector::logo);
	});
}
