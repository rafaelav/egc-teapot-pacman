#ifndef ENEMY_H
#define ENEMY_H

#include <glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Object3D.h"
#include "Plane.h"
#include "Lamp.h"
#include "Teapot.h"
//#include "Light.h"

/*
	Clasa Lamp:
		defineste o lampa
*/

// derivata din Object3D
class Enemy : public Object3D
{

// VARIABILE
//-------------------------------------------------
private:
	int moveTime;	//timpul in care isi va mentine un anumit tip de miscare
	int timePassed;	//cat timp a trecut de cand a inceput sa se miste intr-un anume mod
	Vector3D stepMove;	//cu cat se deplaseaza
	Plane *plane;

public:
	Vector3D prevPosition;	//retine unde se afla ceainicul inainte de a se face mutarea pentru a se putea reveni ulterior daca se descopera ca intra in coliziune
	Lamp **lamps;	//pointer catre lampi
	Teapot *teapot;	//pointer catre teapot
	Enemy **enemies;	//pointer catre inamici
	int numberOfEnemies;			//retine cati inamici st pe plansa

//Setteri
//-------------------------------------------------
public:
	//retinem planul pe care se afla inamicul
	inline void SetPlane(Plane* p){ plane=p;};
	inline void SetNumberOfEnemies(int n){numberOfEnemies=n;};
	

// FUNCTII
//-------------------------------------------------
public:
	// constructor - primeste pozitia initiala
	Enemy(Vector3D);
	bool MoveEnemy();	//returneaza true daca inamicul s-a ciocnit de ceainic
	
};

#endif