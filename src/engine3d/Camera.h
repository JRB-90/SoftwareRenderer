#pragma once

#include "Frame3D.h"
#include "Matrix4.h"

namespace softengine
{
	class Camera
	{
	public:
		Camera(
			double width,
			double height,
			double fov,
			double nearClip,
			double farClip
		);

		Frame3D& Position() { return position; }
		void Position(Frame3D position) { this->position = position; }
		Matrix4 ProjectionMatrix() { CalculateProjection(); return projection; }
		Matrix4 ViewMatrix() { CalculateView(); return view; }
		void LookAt(
			Vector3D lookAtPoint, 
			Vector3D up
		);

		double Width() const { return width; }
		void Width(double width) { this->width = width; }
		double Height() const { return height; }
		void Height(double height) { this->height = height; }
		double FOV() const { return fov; }
		void FOV(double fov) { this->fov = fov; }
		double NearClip() const { return nearClip; }
		void NearClip(double nearClip) { this->nearClip = nearClip; }
		double FarClip() const { return farClip; }
		void FarClip(double farClip) { this->farClip = farClip; }

	private:
		Frame3D position;
		Matrix4 projection;
		Matrix4 view;
		double width;
		double height;
		double fov;
		double nearClip;
		double farClip;

		void CalculateProjection();
		void CalculateView();
	};
}