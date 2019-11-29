#include "mouseUtils.h"

void mouseUtils::convertToGL(int sWidth, int sHeight, int GLWidth, int GLHeight, float & mouseX, float & mouseY)
{
	float tempx = mouseX / sWidth; //percentage arcoss the screen in decimal
	float tempy = mouseY / sHeight; //percentage arcoss the screen in decimal

	//assume the GL origin is 0,0 and that this is at the center of the screen and that any conversion for movement is done out of function
	//because 0,0 is centered, it is acutally 0.5, 0.5 in the decimal used above, so we need to change the range of both temps to [-1.0, 1.0] 
	//because the current range is [0.0, 1.0] subtracting 0.5 will give us the range [-0.5, 0.5] then multiplying by 2 will give us the desired range 
	
	//subtract 0.5, to get [-0.5, 0.5] 
	tempx -= 0.5f; 
	tempy -= 0.5f; 

	//multiply by two to get [-1.0, 1.0] 
	tempx *= 2.f; 
	tempy *= 2.f; 

	//now GLWidth and GLHeight are factored in, however because the origin is centered we need to divide by two and save in mouseX and mouseY(+/- already held in temp)
	mouseX = tempx * (GLWidth / 2); 
	mouseY = tempy * (GLHeight / 2);
}
