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

	struct PipelineConfiguration
	{
		bool wireframeModeEnabled;
		BackFaceCullingMode backFaceCullingMode;
		DepthCheckMode depthCheckMode;

		PipelineConfiguration()
		{
			wireframeModeEnabled = false;
			backFaceCullingMode = BackFaceCullingMode::Clockwise;
			depthCheckMode = DepthCheckMode::DepthCheckGreaterThan;
		}

		PipelineConfiguration(
			bool wireframeModeEnabled,
			BackFaceCullingMode backFaceCullingMode,
			DepthCheckMode depthCheckMode)
		{
			this->wireframeModeEnabled = wireframeModeEnabled;
			this->backFaceCullingMode = backFaceCullingMode;
			this->depthCheckMode = depthCheckMode;
		}
	};
}