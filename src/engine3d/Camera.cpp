#include "Camera.h"
#include "Rotation3D.h"
#include <cmath>

using namespace softengine;

Camera::Camera(
	double width,
	double height,
	double fov,
	double nearClip,
	double farClip)
	:
	width(width),
	height(height),
	fov(fov),
	nearClip(nearClip),
	farClip(farClip),
	projection(Matrix4::Identity()),
	view(Matrix4::Identity())
{
}

void Camera::CalculateProjection()
{
	projection = Matrix4::Zeros();
	projection.At(0, 0, (1.0 / std::tan(fov / 2.0)) / (width / height));
	projection.At(1, 1, (1.0 / std::tan(fov / 2.0)));
	projection.At(2, 2, (nearClip + farClip) / (nearClip - farClip));
	projection.At(2, 3, (2.0 * nearClip * farClip) / (nearClip - farClip));
	projection.At(3, 2, -1.0);
}

void Camera::CalculateView()
{
	view = position.Inverse().Matrix();
}
