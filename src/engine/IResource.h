#pragma once

namespace softengine
{
	class IResource
	{
	public:
		virtual void CleanupResource() = 0;
	};
}