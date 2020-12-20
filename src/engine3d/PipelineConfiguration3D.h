#pragma once

namespace softengine
{
	enum class BackFaceCullingMode
	{
		NoCulling,
		Clockwise,
		AntiClockwise
	};

	enum class DepthCheckMode
	{
		NoDepthCheck,
		DepthCheckLessThan,
		DepthCheckGreaterThan
	};
}