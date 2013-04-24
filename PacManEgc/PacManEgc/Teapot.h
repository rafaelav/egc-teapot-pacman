#ifndef TEAPOT_H
#define TEAPOT_H

#include <glut.h>
#include "Object3D.h"
#include "Plane.h"
#include "Light.h"
#include "Lamp.h"

#define minAttenuation 0.65	//val minima a atenuarii astfel incat sa s considere ca o lampa este in raza de actiune a ceainicului
#define step 0.2	//dimensiune pas facut de ceainic

/*
	Clasa Teapot:
		defineste un jucator
*/

// derivata din Object3D
class Teapot : public Object3D
{

// VARIABILE
//-------------------------------------------------
public:
	Light *teapotLight;
	Vector4D *listColors;	//culorile pe care le poate avea lumina ceainicului
	float *intensityOfLight;	//retine pentru fiecare lumina pe care o poate avea ceainicul caracteristicile ca atunci cand se face shift prin culori sa nu fie mereu valorile initiale
	int numberOfLights;	//numarul de culori pe care le poate avea lumina ceainicului
	int crtColorIndex;	//nr de ordine in listColors al culorii curente
	Vector3D prevPosition;	//retine unde se afla ceainicul inainte de a se face mutarea pentru a se putea reveni ulterior daca se descopera ca intra in coliziune
	Lamp **lamps;	//pointer catre lampi
	Object3D *myKey;
private:
	float size;	// dimensiune ceainic
	Plane *plane;//planul pe care sta ceainicul
	// orientare ceainic
	//int direction;	//0-up; 1-right; 2-down; 3-left

//Setteri
//-------------------------------------------------
public:
	//seteaza directia initiala a ceainicului pentru a stii cum este acesta pozitionat pe plan
//	inline void SetDirection(int dir){ direction=dir;}		
	//seteaza pozitia cluminii emise de ceainic
	void SetPosition(Vector3D*);
	// seteaza planul pe care se afla ceainicul
	inline void SetPlane(Plane* p){ plane=p;};
	//culoarea initiala a luminii emise de ceainic
	inline void SetTeapotLightColor(Vector4D color){teapotLight->SetLightColor(color);};
	//initial avem 0 culori ale lampilor in lista de culori a ceainicului
	//inline void SetInitialNumberOfLightColors(){ numberOfLightColors=0;};
	//initial avem o lumina pe care o emite ceainicul, lumina ce nu e necesar a unei lampi
	//inline void SetInitialListOfLightColors(int numberLamps){ listOfLightColors=new Vector4D*[numberLamps+1]; listOfLightColors[0]=new Vector4D(0,1,0,1);};
	//se adauga inca o culoare la lista de culori de lumina pe care le poate avea ceainicul
	//inline void AddColorToList(Vector4D v){ numberOfLightColors++; listOfLightColors[numberOfLightColors]=(&v);};

// FUNCTII
//-------------------------------------------------
public:
	// constructor vid
	Teapot();

	//miscare ceainic
	bool MoveTeapot(int);
	//creste diametrul luminii ceainicului
	void IncreaseLight();
	//scade diametrul luminii ceainicului
	void DecreaseLight();
	//adaugare culoare de lumina pe care o poate avea ceainicul
	void addColor(Vector4D);
	//schimbare culoare ceainic
	void shiftColor(int);	//primeste sensul in care se face schimbarea (inainte inapoi)

};

#endif