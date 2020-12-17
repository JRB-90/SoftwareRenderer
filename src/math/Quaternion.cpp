#include "Quaternion.h"
#include "Rotation3D.h"
#include <cmath>

using namespace softengine;

Quaternion::Quaternion()
  :
    x(0.0),
    y(0.0),
    z(0.0),
    w(1.0)
{
}

Quaternion::Quaternion(
    double x, 
    double y, 
    double z, 
    double w)
  :
    x(x),
    y(y),
    z(z),
    w(w)
{
}

Quaternion::Quaternion(Rotation3D& rotation)
{
    double tr = rotation.At(0, 0) + rotation.At(1, 1) + rotation.At(2, 2);

    if (tr > 0)
    {
        double s = std::sqrt(tr + 1.0) * 2; // s=4*qw 
        w = 0.25 * s;
        x = (rotation.At(2, 1) - rotation.At(1, 2)) / s;
        y = (rotation.At(0, 2) - rotation.At(2, 0)) / s;
        z = (rotation.At(1, 0) - rotation.At(0, 1)) / s;
    }
    else if ((rotation.At(0, 0) > rotation.At(1, 1)) && (rotation.At(0, 0) > rotation.At(2, 2)))
    {
        double s = std::sqrt(1.0 + rotation.At(0, 0) - rotation.At(1, 1) - rotation.At(2, 2)) * 2; // s=4*qx 
        w = (rotation.At(2, 1) - rotation.At(1, 2)) / s;
        x = 0.25 * s;
        y = (rotation.At(0, 1) + rotation.At(1, 0)) / s;
        z = (rotation.At(0, 2) + rotation.At(2, 0)) / s;
    }
    else if (rotation.At(1, 1) > rotation.At(2, 2))
    {
        double s = std::sqrt(1.0 + rotation.At(1, 1) - rotation.At(0, 0) - rotation.At(2, 2)) * 2; // s=4*qy
        w = (rotation.At(0, 2) - rotation.At(2, 0)) / s;
        x = (rotation.At(0, 1) + rotation.At(1, 0)) / s;
        y = 0.25 * s;
        z = (rotation.At(1, 2) + rotation.At(2, 1)) / s;
    }
    else
    {
        double s = std::sqrt(1.0 + rotation.At(2, 2) - rotation.At(0, 0) - rotation.At(1, 1)) * 2; // s=4*qz
        w = (rotation.At(1, 0) - rotation.At(0, 1)) / s;
        x = (rotation.At(0, 2) + rotation.At(2, 0)) / s;
        y = (rotation.At(1, 2) + rotation.At(2, 1)) / s;
        z = 0.25 * s;
    }
}

double softengine::Quaternion::Length()
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

void Quaternion::Normalise()
{
    double length = Length();
    if (length < 1e-10)
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        w = 0.0;
    }
    double invLength = 1.0 / length;

    x *= invLength;
    y *= invLength;
    z *= invLength;
    w *= invLength;
}

Quaternion Quaternion::Normalised()
{
    double length = Length();
    if (length < 1e-10)
    {
        return Quaternion(0.0, 0.0, 0.0, 0.0);
    }
    double invLength = 1.0 / length;

    return Quaternion(
        x * invLength,
        y * invLength,
        z * invLength,
        w * invLength
    );
}

Rotation3D Quaternion::AsRotation3D()
{
    return Rotation3D(*this);
}
