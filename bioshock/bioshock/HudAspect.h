#pragma once

#include "JSON.h"
#include "Vector.h"

class HudAspect {
public:
	//creates the HudAspect
	HudAspect(); 
	//destroys the HudAspect 
	~HudAspect(); 

	//getter
	vec2 getHudAdjust() const;

	//setter
	void setHudAdjust(vec2 adjust); 

private:
	vec2 hudadjust; 
};

inline void to_json(nlohmann::json& j, const HudAspect& hud)
{
	//adjust
	j["Adjust"] = { hud.getHudAdjust().x, hud.getHudAdjust().y };
}

inline void from_json(const nlohmann::json& j, HudAspect& hud)
{
	//Sets adjust
	hud.setHudAdjust(vec2(j["Adjust"][0], j["Adjust"][1]));
}