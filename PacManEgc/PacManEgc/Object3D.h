// EGC
// Laborator 5
//-------------------------------------------------

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glut.h>
#include <math.h>
#include <stdio.h>
#include "Vector3D.h"
#include "Vector4D.h"

// nivelul maxim de detaliu
#define MAXIMUM_LOD 50 

enum ObjectType
{
	Cube,	// glut cube
	Sphere, // glut sphere
	MyTeapot,	//ceainic
	MyLamp,	// felinar
	MyEnemy,//inamic
	ExtraEnemy,//inamic suplimentar
	Custom  // obiect propriu
};

/*
	OBJECT3D
	Clasa pentru desenare si modificare a unui obiect 3d.
*/
class Object3D
{
// VARIABILE STATICE ::
//-------------------------------------------------
public:
	static Vector3D SelectedColor;
	static Vector3D ColorIncrement;

// VARIABILE
//-------------------------------------------------
// publice
public :
	// incep cu litera mare
	ObjectType Type;	// tipul obiectuliu
	bool Wireframe;		// daca va fi desenat wireframe
	bool Visible;		// daca va fi sau nu desenat
	bool Lighted;		// daca este sau nu luminat
	float R;	//raza sferei care contine obiectul
	bool emission;

// private
protected:
	// incep cu litera mica
	Vector3D translation;	// pozitie
	Vector3D rotation;		// rotatie
	Vector3D scale;			// scalare
	Vector3D color;			// culoare

	float levelOfDetail;	// nivelul de detaliu (pentru glutSphere)
	bool selected;			// daca este sau nu selectat


// FUNCTII ::
//-------------------------------------------------
public:
// constructor
	// fara parametri
	Object3D();		
	// doar cu tip
	Object3D(ObjectType);
	// doar cu pozitie
	Object3D(Vector3D *);			
	// cu pozitie, rotatie, scalare
	Object3D(Vector3D *,Vector3D *,Vector3D *);

	//functie care verifica daca apar coliziuni intre obiecte
	bool ColisionDetected(Object3D*);
	//setare tip obiect
	inline void SetObjectType(ObjectType t){Type=t;}

// functie de desenare
	void virtual Draw();

// setters 
	// pentru toate variabilele care nu sunt publice
	void Select();
	void Deselect();
	void virtual SetPosition(Vector3D *);
	void SetRotation(Vector3D *);
	void SetScale(Vector3D *);
	void SetColor(Vector3D *);
	void SetLevelOfDetail(float);
// getters
	// pentru toate variabilele care nu sunt publice, si pot fi modificate din exterior
	Vector3D GetRotation();
	Vector3D GetScale();
	Vector3D GetPosition();
	float GetLevelOfDetail();
	inline Vector3D GetColor() {return color;}

protected:
	// functie proprie de desenare. se apeleaza doar daca tipul este Custom
	void virtual customDraw();
	// seteaza valorile default 
	void defaultSettings();
	
};

#endif
