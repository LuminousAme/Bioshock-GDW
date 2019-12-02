#include "HudAspect.h"

HudAspect::HudAspect()
{
	hudadjust = vec2(0.f, 0.f);
}

HudAspect::~HudAspect()
{
}

vec2 HudAspect::getHudAdjust() const
{
	return hudadjust;
}

void HudAspect::setHudAdjust(vec2 adjust)
{
	hudadjust = adjust; 
}
