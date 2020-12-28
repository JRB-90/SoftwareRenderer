#define _USE_MATH_DEFINES

#include "Camera.h"
#include "Rotation3D.h"
#include "MathUtils.h"
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

void Camera::LookAt(
	Vector3D lookAtPoint, 
	Vector3D up)
{
	Vector3D zAxis = (position.Translation() - lookAtPoint).Normalised();
	Vector3D xAxis = up.Cross(zAxis * -1).Normalised();
	Vector3D yAxis = zAxis.Cross(xAxis).Normalised();

	position.Rotation(
		Rotation3D(
			xAxis,
			yAxis,
			zAxis
		)
	);
}

void Camera::CalculateProjection()
{
	double a = width / height;
	double t = 1.0 / std::tan(MathUtils::ToRad(fov) / 2.0);
	projection = Matrix4::Zeros();
	projection.At(0, 0, t / a);
	projection.At(1, 1, t);
	projection.At(2, 2, -(farClip + nearClip) / (farClip - nearClip));
	projection.At(2, 3, -2.0 * (nearClip * farClip) / (farClip - nearClip));
	projection.At(3, 2, -1.0);
}

void Camera::CalculateView()
{
	view = position.Inverse().Matrix();
}
