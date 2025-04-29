#ifndef IERS_HPP
#define IERS_HPP

#include "../include/matrix.hpp"
#include "../include/global.hpp"
#include <string>
#include <tuple>

tuple<double, double, double, double, double, double, double, double, double> IERS(double Mjd_UTC, const string& interp = "n");

#endif
