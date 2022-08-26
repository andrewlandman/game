#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <memory>

class Quaternion {
public:
    Quaternion(double w, double x, double y, double z);
    static std::shared_ptr<Quaternion> fromAxisAngle(
        double angle,
        double x_axis,
        double y_axis,
        double z_axis
    );
    std::shared_ptr<Quaternion> multiply(std::shared_ptr<Quaternion> other);
    std::shared_ptr<Quaternion> conjugate();
    std::shared_ptr<Quaternion> rotate(double x, double y, double z);

    double mW;
    double mX;
    double mY;
    double mZ;
};

#endif // QUATERNION_HPP
