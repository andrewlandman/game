#include "Quaternion.hpp"

#include <math.h>

Quaternion::Quaternion(double w, double x, double y, double z)
    :
    mW(w),
    mX(x),
    mY(y),
    mZ(z)
{}

std::shared_ptr<Quaternion> Quaternion::fromAxisAngle(
    double angle,
    double x_axis,
    double y_axis,
    double z_axis)
{
    auto w = cos(angle / 2.0);
    auto x = sin(angle / 2.0) * x_axis;
    auto y = sin(angle / 2.0) * y_axis;
    auto z = sin(angle / 2.0) * z_axis;
    return std::make_shared<Quaternion>(w, x, y, z);
}

std::shared_ptr<Quaternion> Quaternion::multiply(std::shared_ptr<Quaternion> other) {
    double w1 = mW;
    double x1 = mX;
    double y1 = mY;
    double z1 = mZ;

    double w2 = other->mW;
    double x2 = other->mX;
    double y2 = other->mY;
    double z2 = other->mZ;

    double w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
    double x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
    double y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;
    double z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;

    return std::make_shared<Quaternion>(w, x, y, z);
}

std::shared_ptr<Quaternion> Quaternion::conjugate() {
    return std::make_shared<Quaternion>(mW, -mX, -mY, -mZ);
}

std::shared_ptr<Quaternion> Quaternion::rotate(double x, double y, double z) {
    auto q  = std::make_shared<Quaternion>(0.0, x, y, z);
         q  = this->multiply(q);
    auto qc = this->conjugate();
    q = q->multiply(qc);
    return q;
}
