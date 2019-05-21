#pragma once
#include "Structs.h"

namespace dae
{
	inline bool IsRectOverlapping(Rectf ObjOne, Rectf ObjTwo)
	{
		return (ObjOne.x < ObjTwo.x + ObjTwo.w  && ObjOne.x + ObjOne.w > ObjTwo.x &&
			ObjOne.y > ObjTwo.y - ObjTwo.h  && ObjOne.y - ObjOne.h < ObjTwo.y);
	}
	inline Point2f GetDirectionToTarget(Point2f self, Point2f target)
	{
		Point2f delta = { target.x - self.x, target.y - self.y };
		float length = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
		return Point2f{ delta.x / length, -delta.y / length };
	}
}