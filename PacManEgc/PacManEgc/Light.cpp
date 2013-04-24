// EGC
// Laborator 5
//-------------------------------------------------

#include "Light.h"

// id-ul de baza
int Light::baseId = 0;

// constructor fara parametri, mosteneste constructorul de Sfera din Object3D
// deoarece dorim ca lumina sa fie ilustrata printr-o sfera
Light::Light(IlluminationType type) : Object3D(Sphere)
{
	//setam valorile implicite de atenuare pentru lumina
	//this->SetDefaultAttenuation();

	LightType=type;

	// valori default
	diffuse = Vector4D(1,1,1,1);
	ambient = Vector4D(0,0,0,0);
	specular = Vector4D(1,1,1,1);
	color = Vector3D(1,1,1);
	scale = Vector3D(0.2,0.2,0.2);
	direction = Vector3D(0,-1,0);

	const_at=1;
	lin_at=0;
	quad_at=0;

	//daca lumina e de tip spot se fac niste modificari
	if (LightType == Spot)
	{
		lin_at=0.4;
		quad_at=0.1;
		direction=Vector3D(-1,-1,0);

		cutoff=CUTOFF;
		expo=EXPO;
		//printf("ok\n");
	}

	// id-ul este unic, id-ul de baza incrementat
	id = baseId++;
	
	// sfera plasata in locul luminii nu este wireframe
	Wireframe = false;
}

// functie care plaseaza efectivl umina in scena
void Light::Render()
{
	// atenuari standard
	//glLightf(GL_LIGHT0 + id,GL_CONSTANT_ATTENUATION,1);
	//glLightf(GL_LIGHT0 + id,GL_LINEAR_ATTENUATION,0.2f);

	// culoarea luminii 
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, Vector4D(diffuse.x, diffuse.y, diffuse.z, diffuse.a).Array());
	// culoarea ambientala 
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient.Array());

	// culoarea speculara
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular.Array());
	// pozitia luminii
	glLightfv(GL_LIGHT0 + id, GL_POSITION, Vector4D(translation.x,translation.y,translation.z,1).Array());

	//Se seteaza atenuarile
	glLightfv(GL_LIGHT0 + id, GL_CONSTANT_ATTENUATION, &const_at);
	glLightfv(GL_LIGHT0 + id, GL_LINEAR_ATTENUATION, &lin_at);
	glLightfv(GL_LIGHT0 + id, GL_QUADRATIC_ATTENUATION, &quad_at);


	//Pentru spot - se seteaza exponent, cutoff si direction
	if (LightType == Spot)
	{		
		glLightfv(GL_LIGHT0 + id, GL_SPOT_DIRECTION, direction.Array());
		glLightf(GL_LIGHT0 + id, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT0 + id, GL_SPOT_EXPONENT, expo);
	}


	// activam lumina
	glEnable(GL_LIGHT0 + id);
}

// functie care seteaza culoare luminii
void Light::SetLightColor(Vector4D _color)
{
	diffuse = _color;
	specular = _color;
}

// functie care dezactiveaza lumina
void Light::Disable()
{
	glDisable(GL_LIGHT0 + id);
}

void Light::RestartLights()
{
	Light::baseId=0;
}
