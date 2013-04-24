// EGC
// Laborator 5
//-------------------------------------------------

#ifndef LIGHT_H
#define LIGHT_H

#include <glut.h>
#include <stdio.h>
#include "Object3D.h"

#define CUTOFF 10
#define EXPO 8

// tipul de iluminare
enum IlluminationType
{
	Ideal, // lumina omnidirectionala
	Spot   // lumina directionala
};

/*
	Light
	Clasa pentru desenarea si activarea unei lumini
*/

// derivata din object3D
class Light : public Object3D
{

// VARIABILE STATICE
//-------------------------------------------------
private:
	static int baseId;

// VARIABILE
//-------------------------------------------------
public:
	// tipul luminii - nu este folosit, inca
	IlluminationType LightType;
	GLfloat const_at;
	GLfloat lin_at;
	GLfloat quad_at;
	float cutoff;
	float expo;


public:
	// id-ul asignat. pleaca din 0 si este folosit pentru GL_LIGHT0 + id
	int id;
	// lumina difuza
	Vector4D diffuse;
	// lumina ambientala
	Vector4D ambient;
	// lumina speculara
	Vector4D specular;

	Vector3D direction;
	

	// pentru spot :

// FUNCTII
//-------------------------------------------------
public:
	// constructor fara parametri
	Light(IlluminationType);

	// plaseaza lumina in scena si o activeaza
	void Render();
	// dezactiveaza lumina
	void Disable();

	//functie de resetare de lumini
	static void RestartLights();

//Setteri
//--------------------------------------------------
public:
	// setare culoare lumina
	void SetLightColor(Vector4D);

	//setare tip de lumina
	inline void SetType(IlluminationType type){ LightType = type;};

	// setam vaorile default pentru atenuare
	//inline void SetDefaultAttenuation() {	const_at=1; lin_at=0; quad_at=1;};
};

#endif