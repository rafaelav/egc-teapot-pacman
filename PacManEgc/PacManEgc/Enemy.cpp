#include "Enemy.h"

// constructor mostenit din Object3D
// tipul este Enemy
Enemy::Enemy(Vector3D poz) : Object3D(MyEnemy)
{
	//se seteaza pozitia unde apare pe plan, culoarea inamicului si se scaleaza
	this->SetPosition(&poz);
	this->SetColor(&Vector3D(0.4,0.4,0.4));
	this->SetScale(&Vector3D(0.1,0.1,0.1));
	//scalam si raza sferei care cuprinde obiectul
	this->R=(float)sqrtf(3)*0.1;
	
	timePassed=0;	//initializare de cat timp a inceput miscare
	moveTime=rand()%20+5;	//initializare timp in care isi va pastra traiectoria (daca nu apar coliziuni)
	stepMove=Vector3D(0,0,0.2);
}

bool Enemy::MoveEnemy()
{
	//aflam pozitia curenta a inamicului
	Vector3D crtPosition=this->GetPosition();

	//retinem pozitia curenta pentru a putea ulterior reveni daca se intampla sa apara ciocniri
	prevPosition=crtPosition;

	float speed=0.1;	//ajuta pentru a genera o mutare random in planul (x,z)
	float limit=0.2;
	float z,x;
	if(timePassed<moveTime)	//daca nu s-a depasit timpul in care trebuie sa se miste in acest mod
	{
		this->SetPosition(&(this->GetPosition()+stepMove));
		timePassed++;
	}
	else
	{
		//s-a terminat timpul alocat miscarii de acest fel
		timePassed=0;
		moveTime=rand()%20+5;

		//determinam un nou pas de muater (aleator)
		if(rand()%2==0)
		{

				z=(float)rand()/RAND_MAX*limit-speed;
				x=sqrt(speed*speed-z*z);
				stepMove=Vector3D(x,0,z);
		}
		else
		{
				z=(float)rand()/RAND_MAX*limit-speed;
				x=sqrt(speed*speed-z*z);
				stepMove=Vector3D(-x,0,z);
		}
		this->SetPosition(&(this->GetPosition()+stepMove));
	}

	//verificam daca a iesit din plan
	while(plane->PlaneContains(this->GetPosition())==false)	//daca a iesit din plan
	{
		this->SetPosition(&crtPosition);	//setam pozitia la pozitia anterioara

		//si incercam sa ii determinam o noua mutare
		timePassed=0;
		moveTime=rand()%20+5;

		//determinam un nou pas de muater (aleator)
		if(rand()%2==0)
		{

				z=(float)rand()/RAND_MAX*limit-speed;
				x=sqrt(speed*speed-z*z);
				stepMove=Vector3D(x,0,z);
		}
		else
		{
				z=(float)rand()/RAND_MAX*limit-speed;
				x=sqrt(speed*speed-z*z);
				stepMove=Vector3D(-x,0,z);
		}
		this->SetPosition(&(this->GetPosition()+stepMove));
	}

	int i;
	Vector3D posEn;
	Vector3D posMe;
	//verificam daca s-a ciocnit de un alt inamic
	//printf("Numar inamici: %d\n",numberOfEnemies);
	for(i=0;i<numberOfEnemies;i++)
	{
		posEn=enemies[i]->GetPosition();
		posMe=this->GetPosition();
		if(posEn.x!=posMe.x || posEn.z!=posMe.z)	//daca nu e vorba chiar de el insusi (coliziune cu sine n-are sens) 
			while(this->ColisionDetected(enemies[i])==true)	//coliziune intre doi inamici
			{
				this->SetPosition(&prevPosition);	//setam pozitia la pozitia anterioara

				//si incercam sa ii determinam o noua mutare
				timePassed=0;
				moveTime=rand()%20+5;

				//determinam un nou pas de muater (aleator)
				if(rand()%2==0)
				{

					z=(float)rand()/RAND_MAX*limit-speed;
					x=sqrt(speed*speed-z*z);
					stepMove=Vector3D(x,0,z);
				}
				else
				{
					z=(float)rand()/RAND_MAX*limit-speed;
					x=sqrt(speed*speed-z*z);
					stepMove=Vector3D(-x,0,z);
				}
				this->SetPosition(&(this->GetPosition()+stepMove));
			}
	}

	//verificam daca s-a ciocnit de o lampa
	for(i=0;i<4;i++)
	{
			while(this->ColisionDetected(lamps[i])==true)	//coliziune intre doi inamici
			{
				this->SetPosition(&prevPosition);	//setam pozitia la pozitia anterioara

				//si incercam sa ii determinam o noua mutare
				timePassed=0;
				moveTime=rand()%20+5;

				//determinam un nou pas de muater (aleator)
				if(rand()%2==0)
				{

					z=(float)rand()/RAND_MAX*limit-speed;
					x=sqrt(speed*speed-z*z);
					stepMove=Vector3D(x,0,z);
				}
				else
				{
					z=(float)rand()/RAND_MAX*limit-speed;
					x=sqrt(speed*speed-z*z);
					stepMove=Vector3D(-x,0,z);
				}
				this->SetPosition(&(this->GetPosition()+stepMove));
			}
	}

	//verificam daca s-a ciocnit de ceainic
	if(this->ColisionDetected(teapot)==true)
	{
			while(this->ColisionDetected(teapot)==true)	//coliziune cu ceainicul
			{
				this->SetPosition(&prevPosition);	//setam pozitia la pozitia anterioara

				//si incercam sa ii determinam o noua mutare
				timePassed=0;
				moveTime=rand()%20+5;

				//determinam un nou pas de muater (aleator)
				if(rand()%2==0)
				{

					z=(float)rand()/RAND_MAX*limit-speed;
					x=sqrt(speed*speed-z*z);
					stepMove=Vector3D(x,0,z);
				}
				else
				{
					z=(float)rand()/RAND_MAX*limit-speed;
					x=sqrt(speed*speed-z*z);
					stepMove=Vector3D(-x,0,z);
				}
				this->SetPosition(&(this->GetPosition()+stepMove));
			}
		return true;	//a murit ceainicul
	}
	return false;	//n-a murit ceainicu
}