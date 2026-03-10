#include"OLS.h"
namespace OLS{
std::vector<std::function<double(double)>> fs {
	[](double z) { return 1.0; },
	[](double z) { return z; },
	[](double z) { return z * z; }
	};
}