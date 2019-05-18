#pragma once
#include "Structs.h"

namespace dae
{
	bool IsRectOverlapping(Rectf ObjOne, Rectf ObjTwo)
	{
		// new
		return (ObjOne.x < ObjTwo.x + ObjTwo.w  && ObjOne.x + ObjOne.w > ObjTwo.x &&
			ObjOne.y > ObjTwo.y - ObjTwo.h  && ObjOne.y - ObjOne.h < ObjTwo.y);


		// old
		//return (ObjOne.x < ObjTwo.x + ObjTwo.w  && ObjOne.x + ObjOne.w > ObjTwo.x &&
		//	    ObjOne.y > ObjTwo.y + ObjTwo.h  && ObjOne.y + ObjOne.h < ObjTwo.y);
	}

	


}