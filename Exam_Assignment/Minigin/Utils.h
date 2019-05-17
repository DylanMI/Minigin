#pragma once
#include "Structs.h"

namespace dae
{
	bool IsRectOverlapping(Rectf ObjOne, Rectf ObjTwo)
	{
		return (ObjOne.x < ObjTwo.x + ObjTwo.w  && ObjOne.x + ObjOne.w > ObjTwo.x &&
			    ObjOne.y > ObjTwo.y + ObjTwo.h  && ObjOne.y + ObjOne.h < ObjTwo.y);
	}

	


}