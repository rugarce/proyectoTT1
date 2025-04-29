#include "../include/matrix.hpp"
#include "../include/TimeUpdate.hpp"

Matrix TimeUpdate(Matrix& P, Matrix& Phi, double Qdt) {
    Matrix result = Phi * P * transpose(Phi);
    if (Qdt != 0.0) {
        result = result + Qdt;
    }
    return result;
}
