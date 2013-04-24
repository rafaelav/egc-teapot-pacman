#include "Teapot.h"
#include<stdio.h>
#include<stdlib.h>

// constructor mostenit din Object3D
// tipul este Teapot
Teapot::Teapot() : Object3D(MyTeapot)
{
	//scalarea lui teapot se face in PacMan.cpp
	
	size = 1;
	teapotLight=new Light(Ideal);
	
	// setare scalare
	this->SetScale(new Vector3D(0.3,0.3,0.3));
	//scalam si raza sferei ce-l cuprinde
	this->R=0.3;	//cum R e 1 by default => 1*0.3

	//this->SetInitialNumberOfLightColors();	//setam numarul initial de lumini colorate ale ceainicului la 0
	listColors= new Vector4D[10];
	intensityOfLight=new float[10];
	numberOfLights=0;
	crtColorIndex=0;	//culoare alba implicita

	teapotLight->const_at=0;
	teapotLight->quad_at=0.4;
	teapotLight->lin_at=0;
}

void Teapot::SetPosition(Vector3D *poz)
{
	teapotLight->SetPosition(&(*poz+Vector3D(0,0.2,0)));
	Object3D::SetPosition(poz);
}

//creste diametrul luminii din jurul ceainicului
void Teapot::IncreaseLight()
{
	//if(this->teapotLight->const_at>0.6)
		//this->teapotLight->const_at=this->teapotLight->const_at-0.01;
	//this->teapotLight->lin_at=this->teapotLight->lin_at-0.1;
	if(this->teapotLight->quad_at>0.3)
	{
		this->teapotLight->quad_at=this->teapotLight->quad_at-0.01;
		//retinem cum a fost lasata lumina pe aceasta culoare ultima data
		this->intensityOfLight[crtColorIndex]=this->teapotLight->quad_at;
	}
}

//scade diametrul luminii din jurul ceainicului
void Teapot::DecreaseLight()
{
	//if(this->teapotLight->const_at<1.1)
		//this->teapotLight->const_at=this->teapotLight->const_at+0.01;
	//this->teapotLight->lin_at=this->teapotLight->lin_at+0.1;
	
	if(this->teapotLight->quad_at<2.5)
	{
		this->teapotLight->quad_at=this->teapotLight->quad_at+0.01;
		//retinem cum a fost lasata lumina pe aceasta culoare ultima data
		this->intensityOfLight[crtColorIndex]=this->teapotLight->quad_at;
	}
}

//adauga o noua culoare de lumina pentru ceainicului
void Teapot::addColor(Vector4D color)
{
	bool valid=true;
	int i;
	for(i=0;i<numberOfLights;i++)
		if(listColors[i]==color)
			valid=false;
	if(valid==true)	//daca aceasta culoare nu exista deja
	{
		listColors[numberOfLights]=color;
		intensityOfLight[numberOfLights]=this->teapotLight->quad_at;
		numberOfLights++;
	}
}

//ciclare prin culorile existente si schimbarea culorii luminii ceainicului
void Teapot::shiftColor(int dir)
{
	//printf("numar de cuori:%d\n",numberOfLights);
	if(dir==0)	//se merge ->
	{
		if(crtColorIndex<numberOfLights-1)	//daca indicele curent nu este cel al ultimei culori
			crtColorIndex++;
		else
			crtColorIndex=0;
	}
	else	//se merge <-
	{
		if(crtColorIndex>0)	//daca indicele curent nu este cel al primei culori
			crtColorIndex--;
		else
			crtColorIndex=numberOfLights-1;
	}

	//setam efectiv culoarea (exact asa cum era cand am modificat-o ultima data)
	SetTeapotLightColor(listColors[crtColorIndex]);
	teapotLight->quad_at=intensityOfLight[crtColorIndex];
	//printf("%d,%d,%d,%d, indice culoare %d:\n",listColors[crtColorIndex].x,listColors[crtColorIndex].y,listColors[crtColorIndex].z,listColors[crtColorIndex].a,crtColorIndex);
}

//miscare ceainic
bool Teapot::MoveTeapot(int key)
{

	//aflam pozitia curenta a ceainicului
	Vector3D crtPosition=this->GetPosition();
	//retinem pozitia curenta pentru a putea ulterior reveni daca se intampla sa apara ciocniri
	prevPosition=crtPosition;

	//verificam tipul de mutare si in functie de tasta deplasam ceainicul
	switch(key)
	{
		case GLUT_KEY_RIGHT :			
		{
			this->SetRotation(new Vector3D(0,0,0));
			this->SetPosition(new Vector3D(crtPosition.x+step,crtPosition.y,crtPosition.z));
			break;
		}
		case GLUT_KEY_LEFT : 
		{
			this->SetRotation(new Vector3D(0,180,0));
			this->SetPosition(new Vector3D(crtPosition.x-step,crtPosition.y,crtPosition.z));
			break;
		}
		case GLUT_KEY_DOWN : 
		{
			this->SetRotation(new Vector3D(0,-90,0));
			this->SetPosition(new Vector3D(crtPosition.x,crtPosition.y,crtPosition.z+step));
			break;
		}
		case GLUT_KEY_UP : 
		{
			this->SetRotation(new Vector3D(0,90,0));
			this->SetPosition(new Vector3D(crtPosition.x,crtPosition.y,crtPosition.z-step));
			break;
		}
		case GLUT_KEY_PAGE_UP:
		{
			this->IncreaseLight(); break;
		}
		case GLUT_KEY_PAGE_DOWN:
		{
			this->DecreaseLight(); break;
		}
		case GLUT_KEY_HOME:
		{
			//schimba culoarea
			this->shiftColor(0);
			break;
		}
		case GLUT_KEY_END:
		{
			//schimba culoarea
			this->shiftColor(1);
			break;
		}
	}

	//verificam daca a ieist din plan
	if(plane->PlaneContains(this->GetPosition())==false)	//daca a iesit din plan
		this->SetPosition(&crtPosition);	//setam pozitia la pozitia anterioara

	int i;
	//verificam daca intra in coliziune cu o lampa
	for(i=0;i<4;i++)
	{
		if(this->ColisionDetected(lamps[i])==true)	//coliziune intre ceainic si una din lampi
		{
			//se muta ceainicul la loc
			this->SetPosition(&crtPosition);	//setam pozitia la pozitia anterioara
		}
	}

	float x1,x2,y1,y2,z1,z2;
	Vector3D center1;
	Vector3D center2;
	float distance;
	float attenuation;

	Vector4D lightColorNow=listColors[crtColorIndex];
	Vector3D lightColor3D(lightColorNow.x,lightColorNow.y,lightColorNow.z);

	//verificam daca aprinde o lampa
	for(i=0;i<4;i++)
		if( lightColor3D==lamps[i]->GetColor())	//lampa e stinsa
		{
			center1=this->GetPosition();
			center2=lamps[i]->GetPosition();

			x1=center1.x;
			x2=center2.x;
			y1=center1.y;
			y2=center2.y;
			z1=center1.z;
			z2=center2.z;

			//distanta dintre lampa si ceainic
			distance=sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));

			//intensitatea luminii date de ceainic in punctul in care e lampa
			attenuation=1.0/(lamps[i]->lampLight->const_at+lamps[i]->lampLight->lin_at*distance+lamps[i]->lampLight->quad_at*distance*distance);

			//printf("Lampa %d :%f\n",i,attenuation);

			//verificam daca lampa este in raza de actiune a ceainicului
			if(attenuation>minAttenuation)	//limina lampii se aprinde
			{
				lamps[i]->status=1;
				lamps[i]->emission=true;
				lamps[i]->Reset((attenuation-minAttenuation));
			}
		}

	//verificam daca a luat cheia si a castigat
	if(this->ColisionDetected(myKey)==true && myKey->Visible==true)
		return true;
	return false;
}