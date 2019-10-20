#include "CollisionHelpers.h"

#include <utility>

using namespace DirectX::SimpleMath;

namespace CollisionHelpers
{

	bool IsRayIntersectingCube(const Vector3& rOrigin, const Vector3& rDir, const Vector3& rCubeMin, const Vector3& rCubeMax, float& rfOutDistance)
	{
		float tmin = (rCubeMin.x - rOrigin.x) / rDir.x;
		float tmax = (rCubeMax.x - rOrigin.x) / rDir.x;

		if (tmin > tmax)
			std::swap(tmin, tmax);
	
		float tymin = (rCubeMin.y - rOrigin.y) / rDir.y;
		float tymax = (rCubeMax.y - rOrigin.y) / rDir.y;

		if (tymin > tymax)
			std::swap(tymin, tymax);
		
		if ((tmin > tymax) || (tymin > tmax))
			return false;

		if (tymin > tmin)
			tmin = tymin;

		if (tymax < tmax)
			tmax = tymax;

		float tzmin = (rCubeMin.z - rOrigin.z) / rDir.z;
		float tzmax = (rCubeMax.z - rOrigin.z) / rDir.z;

		if (tzmin > tzmax) 
			std::swap(tzmin, tzmax);

		if ((tmin > tzmax) || (tzmin > tmax))
			return false;

		if (tzmin > tmin)
			tmin = tzmin;

		if (tzmax < tmax)
			tmax = tzmax;

		rfOutDistance = tmin;
		return true;
	}
}