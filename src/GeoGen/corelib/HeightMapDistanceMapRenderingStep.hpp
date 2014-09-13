#pragma once

#include "../Number.hpp"
#include "../renderer/RenderingStep2D.hpp"

namespace geogen
{
	namespace corelib
	{
		class HeightMapDistanceMapRenderingStep : public renderer::RenderingStep2D
		{
		private:
			Size1D maxDistance;
		public:
			HeightMapDistanceMapRenderingStep(CodeLocation location, std::vector<unsigned> const& argumentSlots, unsigned returnSlot, Size1D maxDistance)
				: RenderingStep2D(location, argumentSlots, returnSlot), maxDistance(maxDistance) {};

			virtual String GetName() const { return GG_STR("HeightMap.DistanceMap"); };

			virtual void Step(renderer::Renderer* renderer) const;

			virtual void UpdateRenderingBounds(renderer::Renderer* renderer, std::vector<renderer::RenderingBounds*> argumentBounds) const;

			virtual void SerializeArguments(IOStream& stream) const;
		};
	}
}