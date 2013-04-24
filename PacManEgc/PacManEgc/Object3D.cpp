// EGC
// Laborator 5
//-------------------------------------------------

#include "Object3D.h"

/*
Declaratiile clasei Object3D
Clasa pentru desenare si modificare a unui obiect 3d.
*/

// VARIABILE STATICE
//-------------------------------------------------
//float *Vector3D::arr = new float[3];
Vector3D Object3D::SelectedColor = Vector3D(1,0,1);		// culoarea obiectului selectat
Vector3D Object3D::ColorIncrement = Vector3D(0.04,0.04,0.04);	// valoarea cu care creste/scade in timp culoarea de mai sus


// CONSTRUCTORI
//-------------------------------------------------

// constructor de baza
Object3D::Object3D()
{
	defaultSettings();
}

// seteaza si tipul obiectului
Object3D::Object3D(ObjectType _Type)
{
	defaultSettings();
	Type = _Type;
}

// seteaza si pozitia
Object3D::Object3D(Vector3D *_translation)
{
	defaultSettings();
	this->SetPosition(_translation);
}

// seteaza pozitie, rotatie, translatie
Object3D::Object3D(Vector3D *_translation, Vector3D *_rotation, Vector3D *_scale)
{
	defaultSettings();
	this->SetPosition(_translation);
	this->SetRotation(_rotation);
	this->SetScale(_scale);	
}

// seteaza toti parametrii la valorile lor default
void Object3D::defaultSettings()
{
	translation = Vector3D(0.0,0.0,0.0);
	rotation = Vector3D(0.0,0.0,0.0);
	scale = Vector3D(1.0,1.0,1.0);

	Lighted = true;
	Wireframe = false;
	Visible = true;
	Type = Cube;

	levelOfDetail = 12;
	selected = false;

	//setam val default pt raza sferei ce inconjoara obiectul
/*	switch(Type)
	{
		case MyTeapot: this->R=1; break;
		case MyLamp: this->R=1.05; break;
		case MyEnemy: this->R=sqrtf(3); break;
	}*/

	//raza sferei ce contine cheia
	R=0.2;
}

// DRAW
//-------------------------------------------------
void Object3D::Draw ()
{
	// daca nu este vizibil, nu-l desenam
	if(!Visible)
	return;

	glPushMatrix();

	// translatie
	glTranslatef( translation.x , translation.y , translation.z );

	// rotatie
	glRotatef( rotation.x , 1.0 , 0.0 , 0.0 );
	glRotatef( rotation.y , 0.0 , 1.0 , 0.0 );
	glRotatef( rotation.z , 0.0 , 0.0 , 1.0 );

	// scalare
	glScalef( scale.x , scale.y , scale.z);

	// setari de material :
	// daca nu este selectat
	if( !selected )
	{
		// culoare normala
		glColor3f(color.x,color.y,color.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(color.x,color.y,color.z,1)).Array());
	}
	else
	{
		// culoarea atunci cand obiectul este selectat
		glColor3f(SelectedColor.x, SelectedColor.y, SelectedColor.z);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(Vector4D(SelectedColor.x,SelectedColor.y,SelectedColor.z,1)).Array());
	}
	// culoare speculara, default
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(Vector4D(0.1,0.1,0.1,1)).Array());

	//culoae emisiva
	if(emission==true)
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Vector4D(Vector4D(color.x,color.y,color.z,1)).Array());
	else
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Vector4D(0, 0, 0, 0).Array());


	// daca este wireframe
	if( Wireframe )
		switch( Type )
	{
		// cub wireframe
		case Cube :	glutWireCube(1.0); break;
		// sfera wireframe
		case Sphere : glutWireSphere(1.0, levelOfDetail, levelOfDetail); break;
		// ceainic wireframe
		case MyTeapot: glutWireTeapot(1); break;
		// lampa wireframe
		case MyLamp: glutWireCone(1.0,2.0,(int)levelOfDetail,(int)levelOfDetail); break;
		// inamic wireframe
		case MyEnemy: glutWireDodecahedron(); break;
		// extra inamic wireframe
		case ExtraEnemy: glutWireTetrahedron(); break;
		// orice alt obiect, specificat de programator
		case Custom : customDraw();
	}
	// daca nu este wireframe
	else
		switch( Type )
	{
		// cub solid
		case Cube :	glutSolidCube(1.0); break;
		// sfera solida
		case Sphere : glutSolidSphere(1.0, levelOfDetail, levelOfDetail); break;
		// ceainic solid
		case MyTeapot: glutSolidTeapot(1); break;
		// lampa solida
		case MyLamp: glutSolidCone(1.0,2.0,(int)levelOfDetail,(int)levelOfDetail); break;
		// inamic solid
		case MyEnemy: glutSolidDodecahedron();
		// extra inamic solid
		case ExtraEnemy: glutSolidTetrahedron(); break;
		// orice alt obiect, specificat de programator
		case Custom : customDraw();
	}

	glPopMatrix();
}

// functie proprie
// se presupune ca Wireframe este tratat inauntru
void Object3D::customDraw()
{
}

// SETTERS
//-------------------------------------------------

// selecteaza
void Object3D::Select()
{
	selected = true;
}

// deselecteaza
void Object3D::Deselect()
{
	selected = false;
}

// seteaza culoare
void Object3D::SetColor(Vector3D *_color)
{
	color = *_color;
}

// seteaza pozitie
void Object3D::SetPosition(Vector3D *_translation)
{
	translation = *_translation;
}

// seteaza rotatie
void Object3D::SetRotation(Vector3D *_rotation)
{
	rotation = *_rotation;
}

// seteaza scalare
void Object3D::SetScale(Vector3D *_scale)
{
	scale = *_scale;
}

// seteaza nivelul de detaliu
void Object3D::SetLevelOfDetail(float _levelOfDetail)
{
	if( _levelOfDetail > 0 && _levelOfDetail < MAXIMUM_LOD)
		levelOfDetail = _levelOfDetail;
}


// GETTERS
//-------------------------------------------------

// intoarce pozitia
Vector3D Object3D::GetPosition()
{
	return translation;
}

// intoarce rotatia
Vector3D Object3D::GetRotation()
{
	return rotation;
}

// intoarce scala
Vector3D Object3D::GetScale()
{
	return scale;
}

// intoarce nivelul de detaliu
float Object3D::GetLevelOfDetail()
{
	return levelOfDetail;
}

//Detectare de coliziuni
//------------------------------------------------
	bool Object3D::ColisionDetected(Object3D *object)
	{
		//centrele obiectelor
		Vector3D center1=this->GetPosition();
		Vector3D center2=object->GetPosition();

		//calculam distanta intre centrele obiectelor
		float x1,x2,y1,y2,z1,z2;
		x1=center1.x;
		x2=center2.x;
		y1=center1.y;
		y2=center2.y;
		z1=center1.z;
		z2=center2.z;

		//verificam daca distanta e mai mica decat suma razelor sferelor ce ar putea incapsula obiectele
		float distance=sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
		//printf("%f %f %f\n",this->R,object->R,distance);
		if(distance<this->R+object->R)
			return true;	//a aparut coliziune
		return false;		//nu a aparut coliziune
	}
