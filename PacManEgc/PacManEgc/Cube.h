#ifndef CUBE_H
#define CUBE_H

#include <glut.h>
#include "Vector3D.h"

class Cube
{
public:

	Cube();
	// Draw
	void Draw();

public:
	Vector3D Translation;
	Vector3D Rotation;
	Vector3D Scale;
	Vector3D Color;
};


#endif
