#include "Lamp.h"

// constructor mostenit din Object3D
// tipul este Lamp
Lamp::Lamp() : Object3D(MyLamp)
{
	lampLight=new Light(Spot);
	lampLight->emission=false;
	//lampLight->LightType=Spot;
	// facem scalare
	decrVal=0.1;
	this->SetScale(new Vector3D(0.3,0.3,0.3));
	//facem si scalarea razei sferei care contine lampa
	this->R=1.05*0.3;	//cum R e 1.05 by default => 1.05*0.3
	//setam cum este lampa
	status=0;	//oprita
}

void Lamp::SetPosition(Vector3D *poz)
{
	lampLight->SetPosition(&(*poz+Vector3D(0,2,0)));
	Object3D::SetPosition(poz);
}
void Lamp::RotateLight()
{
	float x,z,y;

	y=lampLight->direction.y;

	//facem rotirea vectorului direction
	x=lampLight->direction.x*cos(angle)-lampLight->direction.z*sin(angle);
	z=lampLight->direction.x*sin(angle)+lampLight->direction.z*cos(angle);

	//setam noua directie
	lampLight->direction=Vector3D(x,y,z);

	//scadem intensitatea
	this->DecreaseLightIntensity();
}

void Lamp::DecreaseLightIntensity()
{
	if(lampLight->cutoff>3)
	{
		lampLight->cutoff=lampLight->cutoff-0.02;
		//if(lampLight->expo>3)
			//lampLight->expo=lampLight->expo-0.01;
	}
	else
	{
		status=0;	//s-a stins lumina lampii
		this->emission=false;
	}
}

void Lamp::Reset(float extraIntensity)
{
	this->lampLight->cutoff=CUTOFF+extraIntensity;
	this->lampLight->expo=EXPO;
}