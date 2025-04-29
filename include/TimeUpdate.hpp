#ifndef TIMEUPDATE_HPP
#define TIMEUPDATE_HPP

#include "../include/matrix.hpp"

Matrix TimeUpdate(Matrix& P, Matrix& Phi, double Qdt = 0.0);

#endif 
