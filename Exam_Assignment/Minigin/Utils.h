#pragma once
#include "Structs.h"

namespace dae
{
	inline bool IsRectOverlapping(Rectf ObjOne, Rectf ObjTwo)
	{	
		return (ObjOne.x < ObjTwo.x + ObjTwo.w  && ObjOne.x + ObjOne.w > ObjTwo.x &&
		ObjOne.y > ObjTwo.y - ObjTwo.h  && ObjOne.y - ObjOne.h < ObjTwo.y);
	}
	
	inline bool IsPointInSquare(Point2f point, Rectf rect)
	{
		return(point.x >= rect.x && point.x <= rect.x + rect.w) &&
			(point.y >= rect.y - rect.h && point.y <= rect.y);
	}

	inline Point2f GetDirectionToTarget(Point2f self, Point2f target)
	{
		Point2f delta = { target.x - self.x, target.y - self.y };
		float length = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
		return Point2f{ delta.x / length, -delta.y / length };
	}

	inline Point2f lerp(Point2f a, Point2f b, float f)
	{
		return Point2f{ (a.x * (1.0f - f)) + (b.x * f),(a.y * (1.0f - f)) + (b.y * f) };
	}
}