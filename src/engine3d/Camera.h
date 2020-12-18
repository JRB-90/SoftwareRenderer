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

		Frame3D Position() { return position; }
		void Position(Frame3D position) { this->position = position; CalculateView(); }
		Matrix4 ProjectionMatrix() const { return projection; }
		Matrix4 ViewMatrix() const { return view; }

		double Width() const { return width; }
		void Width(double width) { this->width = width; CalculateProjection(); }
		double Height() const { return height; }
		void Height(double height) { this->height = height; CalculateProjection(); }
		double FOV() const { return fov; }
		void FOV(double fov) { this->fov = fov; CalculateProjection(); }
		double NearClip() const { return nearClip; }
		void NearClip(double nearClip) { this->nearClip = nearClip; CalculateProjection(); }
		double FarClip() const { return farClip; }
		void FarClip(double farClip) { this->farClip = farClip; CalculateProjection(); }

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