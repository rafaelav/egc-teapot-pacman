#ifndef LAMP_H
#define LAMP_H

#include <glut.h>
#include "Object3D.h"
#include "Light.h"

/*
	Clasa Lamp:
		defineste o lampa
*/

// derivata din Object3D
class Lamp : public Object3D
{

// VARIABILE
//-------------------------------------------------
private:
	//Plane *plane;
	// orientare ceainic
	//int direction;	//0-up; 1-right; 2-down; 3-left
public:
	Light *lampLight;
	float angle;
	int status;		//spune daca lampa e pornita (1) sau oprita (0)
	int decrVal;	//val cu care descreste lumina lampii in intensitate

//Setteri
//-------------------------------------------------
public:
	//seteaza directia initiala a ceainicului pentru a stii cum este acesta pozitionat pe plan
//	inline void SetDirection(int dir){ direction=dir;}		
	// seteaza planul pe care se afla ceainicul
	//inline void SetPlane(Plane* p){ plane=p;};

	//culoarea luminii ampii
	inline void SetLampColor(Vector4D color){lampLight->SetLightColor(color); this->SetColor(new Vector3D(color.x,color.y,color.z));};
	//unghiul cu care se invarteste lumina lampii
	inline void SetAngle(float a){angle=a;};

// FUNCTII
//-------------------------------------------------
public:
	// constructor vid
	Lamp();
	// functie de setare a pozitiei lampii
	void SetPosition(Vector3D *poz);
	void RotateLight();
	void DecreaseLightIntensity();
	void Reset(float);
};

#endif