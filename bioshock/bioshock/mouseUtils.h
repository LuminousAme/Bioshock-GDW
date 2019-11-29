#pragma once

class mouseUtils abstract {
public:
	static void convertToGL(int sWidth, int sHeight, int GLWidth, int GLHeight, float &mouseX, float &mouseY);
};