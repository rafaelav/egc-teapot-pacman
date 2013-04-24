// Tema 3 -Egc
//-------------------------------------------------
#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

#include "Object3D.h"
#include "Plane.h"
#include "Teapot.h"
#include "Light.h"
#include "Lamp.h"
#include "Enemy.h"
#include "Teapot.h"
#include "Vector3D.h"
#include "Vector4D.h"

// tasta escape
#define ESC	27
#define TIMER 300

float *Vector3D::arr;
float *Vector4D::arr;

// VARIABILE
//-------------------------------------------------
//nivelul jocului
int level=1;
//vieti ramase
int lives=2;
// numarul de obiecte
int objectCount;
// numar de lampi
int lampCount;
// obiectul selectat
int selectedIndex = -1;

// ceainic
Teapot *myteapot;
// vector de obiecte 3D
Object3D *objects;
// vector de lampi
Lamp **lamps;
//vector de inamici
Enemy **enemies;
// planul de baza
Plane *ground;
// o lumina
Light *light;
// cheia
Object3D *myKey;
//unghi cu care se roteste lumina lampii
float a=3.1416/20;
//game over
bool gameover;
//game won
bool gamewon;
//extra inamici
int extraEnemies;
//timp scurs
int timer;


// FUNCTII
//-------------------------------------------------
//calculeaza distanta intre 2 puncte
float Distance(Vector3D center1,Vector3D center2)
{
		float x1,x2,y1,y2,z1,z2;
		x1=center1.x;
		x2=center2.x;
		y1=center1.y;
		y2=center2.y;
		z1=center1.z;
		z2=center2.z;

		//intoarcem distanta dintre cele 2 puncte
		return sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));	
}
//reseteaza pozitia unui obiect in caz ca aesta este suprapus cu un alt obiect
void ResetPosition(Object3D *obj, int objType, int index)
{
	int i,ok=0;
	//lampile se testeaza cu ceainicul si cu celelalte lampi
	//inamicii se testeaza cu lampile cu ceainicul si cu ceilalti inamici
	//cheia se testeaza cu toate celelalte obiecte
	
	//daca obiectul este lampa
	if(objType=1)
	{
		//testez sa nu se suprapuna cu ceainicul ->cat timp se suprapune se genereaza o noua pozitie
		while(Distance(myteapot->GetPosition(),obj->GetPosition())<myteapot->R+obj->R)
		{
			if(rand()%2==0) //dreapta x
			{
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0, -(rand()+0.0)/RAND_MAX*5));
			}
			else	//stanga x
			{	
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0, -(rand()+0.0)/RAND_MAX*5));
			}	
		}
		//verificam cu celelalte lampi
		while(ok==0)	//cat timp se suprapune cu o alat lampa (sau e prea aproape de alta lampa)
		{
			ok=1;	//consideram ca nu se suprapune cu nimeni
			for(i=0;i<4;i++)
				if(i!=index)	//nu e vb de aceeasi lampa cu cea pe care o testam
					if(Distance(lamps[i]->GetPosition(),obj->GetPosition())<lamps[i]->R+obj->R)	//sunt prea apropiate => se suprapun
					{
						if(rand()%2==0) //dreapta x
						{
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0, -(rand()+0.0)/RAND_MAX*5));
						}
						else	//stanga x
						{	
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0, -(rand()+0.0)/RAND_MAX*5));
						}	
						ok=0;	//a fost o lampa cu care s-a suprapus
					}
		}
	}

	//obiectul este de tip Enemy
	if(objType==2)	
	{
		//testam suprapunere cu ceainicul
		while(Distance(myteapot->GetPosition(),obj->GetPosition())<myteapot->R+obj->R)
		{
			if(rand()%2==0) //dreapta x
			{
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
			}
			else	//stanga x
			{	
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
			}	
		}

		//verificam cu ceilalti inamici
		while(ok==0)	//cat timp se suprapune cu o alat lampa (sau e prea aproape de alta lampa)
		{
			ok=1;	//consideram ca nu se suprapune cu nimeni
			for(i=0;i<level+1;i++)
				if(i!=index)	//nu e vb de aceeasi lampa cu cea pe care o testam
					if(Distance(enemies[i]->GetPosition(),obj->GetPosition())<enemies[i]->R+obj->R)	//sunt prea apropiate => se suprapun
					{
						if(rand()%2==0) //dreapta x
						{
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}
						else	//stanga x
						{	
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}	
						ok=0;	//a fost o lampa cu care s-a suprapus
					}
		}

		ok=0;
		//verificam cu lampile
		while(ok==0)	//cat timp se suprapune cu o alat lampa (sau e prea aproape de alta lampa)
		{
			ok=1;	//consideram ca nu se suprapune cu nimeni
			for(i=0;i<4;i++)
			{				
					if(Distance(lamps[i]->GetPosition(),obj->GetPosition())<lamps[i]->R+obj->R)	//sunt prea apropiate => se suprapun
					{
						if(rand()%2==0) //dreapta x
						{
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}
						else	//stanga x
						{	
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}	
						ok=0;	//a fost o lampa cu care s-a suprapus
					}
			}
		}
	}


	//obiectul este cheia
	if(objType==3)	
	{
		//testam suprapunere cu ceainicul
		while(Distance(myteapot->GetPosition(),obj->GetPosition())<myteapot->R+obj->R)
		{
			if(rand()%2==0) //dreapta x
			{
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
			}
			else	//stanga x
			{	
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
			}	
		}

		//verificam cu inamicii
		while(ok==0)	//cat timp se suprapune cu o alat lampa (sau e prea aproape de alta lampa)
		{
			ok=1;	//consideram ca nu se suprapune cu nimeni
			for(i=0;i<level+1;i++)
			{
					if(Distance(enemies[i]->GetPosition(),obj->GetPosition())<enemies[i]->R+obj->R)	//sunt prea apropiate => se suprapun
					{
						if(rand()%2==0) //dreapta x
						{
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}
						else	//stanga x
						{	
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}	
						ok=0;	//a fost o lampa cu care s-a suprapus
					}
			}
		}

		ok=0;
		//verificam cu lampile
		while(ok==0)	//cat timp se suprapune cu o alat lampa (sau e prea aproape de alta lampa)
		{
			ok=1;	//consideram ca nu se suprapune cu nimeni
			for(i=0;i<4;i++)
			{				
					if(Distance(lamps[i]->GetPosition(),obj->GetPosition())<lamps[i]->R+obj->R)	//sunt prea apropiate => se suprapun
					{
						if(rand()%2==0) //dreapta x
						{
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}
						else	//stanga x
						{	
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
						}	
						ok=0;	//a fost o lampa cu care s-a suprapus
					}
			}
		}
	}

	//obiectul este de tip extraEnemy
	if(objType==4)	
	{
		//testam suprapunere cu ceainicul
		while(Distance(myteapot->GetPosition(),obj->GetPosition())<myteapot->R+obj->R)
		{
			if(rand()%2==0) //dreapta x
			{
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
			}
			else	//stanga x
			{	
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
			}	
		}

		//verificam cu inamicii
		while(ok==0)	//cat timp se suprapune cu o alat lampa (sau e prea aproape de alta lampa)
		{
			ok=1;	//consideram ca nu se suprapune cu nimeni
			for(i=0;i<level+extraEnemies;i++)
			{
					if(Distance(enemies[i]->GetPosition(),obj->GetPosition())<enemies[i]->R+obj->R)	//sunt prea apropiate => se suprapun
					{
						if(rand()%2==0) //dreapta x
						{
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
						}
						else	//stanga x
						{	
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
						}	
						ok=0;	//a fost o lampa cu care s-a suprapus
					}
			}
		}

		ok=0;
		//verificam cu lampile
		while(ok==0)	//cat timp se suprapune cu o alat lampa (sau e prea aproape de alta lampa)
		{
			ok=1;	//consideram ca nu se suprapune cu nimeni
			for(i=0;i<4;i++)
			{				
					if(Distance(lamps[i]->GetPosition(),obj->GetPosition())<lamps[i]->R+obj->R)	//sunt prea apropiate => se suprapun
					{
						if(rand()%2==0) //dreapta x
						{
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
						}
						else	//stanga x
						{	
							if(rand()%2==0) // dreapta z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
							else	//stanga z
								obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
						}	
						ok=0;	//a fost o lampa cu care s-a suprapus
					}
			}
		}

		//verificam cu cheia
		while(Distance(myKey->GetPosition(),obj->GetPosition())<myKey->R+obj->R)	//sunt prea apropiate => se suprapun
		{
			if(rand()%2==0) //dreapta x
			{
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
			}
			else	//stanga x
			{	
				if(rand()%2==0) // dreapta z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, (rand()+0.0)/RAND_MAX*5));
				else	//stanga z
					obj->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.3, -(rand()+0.0)/RAND_MAX*5));
			}
		}
	}
}

// functie de initializare
void init(void)
{
	extraEnemies=0;
	timer=0;
	gameover=false;
	gamewon=false;

	int i;
	float c1,c2,c3,c4;

	srand((unsigned)time(0));

	// initialize vector arrays
	Vector3D::arr = new float[3];
	Vector4D::arr = new float[4];

	// initializam un plan de latura 5.0f
	ground = new Plane(5.0f);
	// culoare
	ground->SetColor(new Vector3D(0.04,0,0.0));
	// setam o grila de 5
	ground->SetLevelOfDetail(1.5);
	// sub nivelul obiectelor
	ground->SetPosition(new Vector3D(0,0,0));
	// si wireframe
	ground->Wireframe = false;

	// initializare ceainic
	myteapot=new Teapot();
	// setare culoare
	myteapot->SetColor(new Vector3D(0.3,0.2,0.5));	
	// setare scalare
	//myteapot->SetScale(new Vector3D(0.3,0.3,0.3));
	//scalam si raza sferei ce-l cuprinde
	//myteapot->R=myteapot->R*0.3;
	// setare pozitie initiala
	myteapot->SetPosition(new Vector3D(0,0.22,0));
	// setare plan pe care e ceainicul
	myteapot->SetPlane(ground);
	//setam culoarea luminii initiale a ceainicui
	myteapot->SetTeapotLightColor(Vector4D(1,1,1,1));
	myteapot->addColor(Vector4D(1,1,1,1));	//adaugam lumina alba la lista de culori pe care o poate avea lumina ceainicului
	//setam valorileimplicite pentru atenuarea luminii din jurul ceainicului
	//myteapot->teapotLight->SetDefaultAttenuation();
	//seteaza directia initiala a ceainicului
	//myteapot->SetDirection(1);	//dreapta initial


	// initializare felinare
	// numar de felinare
	lampCount=4;
	// initializam vectorul de felinare
	lamps = new Lamp*[lampCount];
	// pentru fiecare felinar
	float offset = -4.0f;
	for(i = 0; i < lampCount; i++ )
	{		
		lamps[i]=new Lamp();
		//setam tipul de lumina ca fiind Spot
		lamps[i]->lampLight->LightType=Spot;
		//setam unghiul cu care se roteste lumina
		lamps[i]->SetAngle(a+(float)i/20);
		//setam valorile implicite pentru atenuarea luminii din jurul lampii
		//lamps[i]->lampLight->SetDefaultAttenuation();
		// setam culoarea
		c1=0.1+(i%10)/2;
		c2=(rand()+0.0)/RAND_MAX;
		c3=(rand()+0.0)/RAND_MAX;
		c4=1;
		//TODO - sa nu se suprapuna cu pozitia altor lampi respectiv a ceainicului
		lamps[i]->SetLampColor(Vector4D(c1,c2,c3,c4));
		//retinem si in teapot ca poate lua aceasta culoare
		myteapot->addColor(Vector4D(c1,c2,c3,c4));
		//lamps[i]->SetLampColor(Vector4D(0,1,0,1));
		// facem scalare
		//lamps[i]->SetScale(new Vector3D(0.3,0.3,0.3));
		//facem si scalarea razei sferei care contine lampa
		
		//generam pozitia relativa la centru astfel incat sa se afle in ambele jumatati ale terenului (- stanga + dreapta)
		if(rand()%2==0) //dreapta x
		{
			if(rand()%2==0) // dreapta z
				lamps[i]->SetPosition(new Vector3D((rand()+0.0)/RAND_MAX*5, 0, (rand()+0.0)/RAND_MAX*5));
			else	//stanga z
				lamps[i]->SetPosition(new Vector3D((rand()+0.0)/RAND_MAX*5, 0, -(rand()+0.0)/RAND_MAX*5));
		}
		else	//stanga x
		{	
			if(rand()%2==0) // dreapta z
				lamps[i]->SetPosition(new Vector3D(-(rand()+0.0)/RAND_MAX*5, 0, (rand()+0.0)/RAND_MAX*5));
			else	//stanga z
				lamps[i]->SetPosition(new Vector3D(-(rand()+0.0)/RAND_MAX*5, 0, -(rand()+0.0)/RAND_MAX*5));
		}		
		// rotatie cu 90 de grade pe Y
		lamps[i]->SetRotation(new Vector3D(-90,0,0));
	}

	//initializare inamici
	enemies=new Enemy*[level+3];
	for(i=0;i<level+1;i++)
	{
		//level+2==nr de inamici de la un anumit nivel
		//generam pozitia relativa la centru astfel incat sa se afle in ambele jumatati ale terenului (- stanga + dreapta)		
		if(rand()%2==0) //dreapta x
		{
			if(rand()%2==0) // dreapta z
				enemies[i]=new Enemy(Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
			else	//stanga z
				enemies[i]=new Enemy(Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
		}
		else	//stanga x
		{	
			if(rand()%2==0) // dreapta z
				enemies[i]=new Enemy(Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
			else	//stanga z
				enemies[i]=new Enemy(Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
		}	
		enemies[i]->SetPlane(ground);
		enemies[i]->SetNumberOfEnemies(level+1);
	}



	//initializare cheie
	myKey=new Object3D();
	myKey->Type=Sphere;
	myKey->SetScale(&Vector3D(0.2,0.2,0.2));
	myKey->SetColor(&Vector3D(0.4,0.4,0.4));
	myKey->Visible=false;
	if(rand()%2==0) //dreapta x
	{
			if(rand()%2==0) // dreapta z
				myKey->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
			else	//stanga z
				myKey->SetPosition(&Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
	}
	else	//stanga x
	{	
			if(rand()%2==0) // dreapta z
				myKey->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
			else	//stanga z
				myKey->SetPosition(&Vector3D(-(rand()+0.0)/RAND_MAX*5, 0.2, -(rand()+0.0)/RAND_MAX*5));
	}

	//legaturi pentru a putea verifica coliziunile
	myteapot->lamps=lamps;
	myteapot->myKey=myKey;
	for(i=0;i<level+1;i++)
	{
		enemies[i]->lamps=lamps;
		enemies[i]->enemies=enemies;
		enemies[i]->teapot=myteapot;
	}
	
	//testam existenta de suprapuneri
	//lampi
	for(i=0;i<4;i++)
		ResetPosition(lamps[i], 1, i);
	//inamici
	for(i=0;i<level+1;i++)
		ResetPosition(enemies[i], 2, i);
	//cheie
	ResetPosition(myKey, 3, 0);

	// initializam o noua lumina
	//light = new Light();
	// setam pozitia
	//light->SetPosition(new Vector3D(0, 1, 0));

	// pregatim o scena noua in opengl
	glClearColor(0.0, 0.0, 0.0, 0.0);	// stergem tot
	glEnable(GL_DEPTH_TEST);			// activam verificarea distantei fata de camera (a adancimii)
	glShadeModel(GL_SMOOTH);			// mod de desenare SMOOTH
	glEnable(GL_LIGHTING);				// activam iluminarea
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);	//lumina ambientala
	glEnable(GL_NORMALIZE);				// activam normalizarea normalelor
}


// functie de desenare (se apeleaza cat de repede poate placa video)
void display(void)
{
	if(gameover==true)
		return;
	int i;
	// stergere ecran
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// plasare observator
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,12.5,0,0,0,0,0,0,-1);
	//gluLookAt(0,0.1,10,0,0,0,0,1,0);

	// activare lumina
	//light->Render();

	//activare lumina ceainic
	myteapot->teapotLight->Render();

	// activare lumina felinare
	for (i = 0 ; i < lampCount ; i ++ )
	{
		if(lamps[i]->status==1)	//daca lampa e pornita
			lamps[i]->lampLight->Render();
	}

	// desenare lampi
	for (i = 0 ; i < lampCount ; i ++ )
	{
		lamps[i]->Draw();
	}

	//desenare inamici
	for(i=0;i<level+1+extraEnemies;i++)
	{
		enemies[i]->Draw();
	}

	// desenare plan
	ground->Draw();

	// desenare ceainic
	myteapot->Draw();

	//desenare cheie
	if(myKey->Visible==true)
		myKey->Draw();

	// desenare lumina (deseneaza o sfera acolo unde se afla lumina, nu face nimic altceva)
	//light->Draw();

	// dezactivare lumina felinare
	for ( int i = 0 ; i < lampCount ; i ++ )
	{
		lamps[i]->lampLight->Disable();
	}

	//dezactivare lumina ceainic
	myteapot->teapotLight->Disable();

	// dezactivare lumina
	//light->Disable();

	// double buffering
	glutSwapBuffers();

	// redeseneaza scena
	glutPostRedisplay();
}


// functie de update (se realizeaza animatia)
void update(void)
{
	
	Sleep(15);
	if(gameover==true)
		return;

	int lightsOn=0;
	int i;
	for(i=0;i<level+1+extraEnemies;i++)
	{
		if(enemies[i]->MoveEnemy()==true)	//a mai pierdut o viata
		{
			lives--;
			printf("You have %d lives left!\n",lives);
		}
	}
	for(i=0;i<lampCount;i++)
		if(lamps[i]->status==1)
		{
			lightsOn++;
			lamps[i]->RotateLight();	//se roteste lumina daca e aprinsa 
		}
		if(lightsOn==4)	//daca toate lampile sunt aprinse		
			myKey->Visible=true;		
		else
			myKey->Visible=false;
	//daca nu mai are vieti se retine acest lucru
	if(lives==0)
	{
		gameover=true;
		printf("Game over! Press <ESC> to exit.\n");
	}

	if(extraEnemies<2)
	{
		timer++;
		if(timer>(extraEnemies+1)*TIMER)	//daca a trecut un anumit timp de cand suntem in acest nivel
		{
			extraEnemies++;
			//AICI functia care testeaza coliziuni
			enemies[level+extraEnemies]=new Enemy(Vector3D((rand()+0.0)/RAND_MAX*5, 0.2, (rand()+0.0)/RAND_MAX*5));
			ResetPosition(enemies[level+extraEnemies], 4, level+extraEnemies);
			enemies[level+extraEnemies]->SetPlane(ground);
			
			//fiecare inamic stie ca acum sunt mai multi inamici
			for(i=0;i<level+1+extraEnemies;i++)
				enemies[i]->SetNumberOfEnemies(level+1+extraEnemies);
			//facem legaturile catre ceilalti inamici, lampi si ceainic
			enemies[level+extraEnemies]->lamps=lamps;
			enemies[level+extraEnemies]->enemies=enemies;
			enemies[level+extraEnemies]->teapot=myteapot;
			//setam tipul la tetraedru
			enemies[level+extraEnemies]->SetObjectType(ExtraEnemy);

			//scalam noul inamic
			enemies[level+extraEnemies]->SetScale(&Vector3D(0.3,0.3,0.3));
			//setam raza sferei ce-l cuprinde
			enemies[level+extraEnemies]->R=0.3*sqrtf(3);
		}
	}
	// redeseneaza scena
	glutPostRedisplay();
}

// functie de proiectie
void reshape(int w, int h)
{
	// viewport de dimensiuni date
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	// calculare aspect ratio ( Width/ Height )
	GLfloat aspect = (GLfloat) w / (GLfloat) h;

	// intram in modul proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// incarcam matrice de perspectiva 
	gluPerspective(45, aspect, 1.0, 60);

	// redeseneaza scena
	glutPostRedisplay();
}

// handler pentru tastatura
void keyboard(unsigned char key , int x, int y)
{
	switch (key)
	{
		// la escape se iese din program
	case ESC : exit(0);
	default: break;
	}

	// redeseneaza scena
	glutPostRedisplay();
}

// handler taste speciale
void keyboard(int key , int x, int y)
{
	// mutam ceainicul
	if(myteapot->MoveTeapot(key)==true)
	{
		gamewon=true;
		gameover=true;
		printf("You have won! Moving on to next leve now (level %d)! Good luck!",level+1);
		level++;
		timer=0;
		extraEnemies=0;
		Light::RestartLights();
		init();
	}

	// redeseneaza scena
	glutPostRedisplay();
}

void mouse(int buton, int stare, int x, int y)
{
	switch(buton)
	{
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	}
	// redeseneaza scena
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1000,800);
	glutInitWindowPosition(300,100);
	glutCreateWindow("PacMan");

	init();
	glutIdleFunc(update);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}