//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
	b_normales_caras = false;
	b_normales_vertices = false;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}


void _triangulos3D::draw_iluminacion_plana(){
  int i;
  GLfloat ambient_component[4] = {1,1,1,1};

  if (b_normales_caras == false)
    calcular_normales_caras();

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);

  //Añadir más luces
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  //Dibujar
  for (i=0; i<caras.size();i++){
    glNormal3fv((GLfloat *) &normales_caras[i]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }

  glEnd();

  //Deshabilitamos las luces
  glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_caras(){
  normales_caras.resize(caras.size());
  for(unsigned long i=0; i<caras.size(); i++){
    //obtener dos vectores en el triángulo y calcular el producto vectorial
    _vertex3f
          a1 = vertices[caras[i]._1]-vertices[caras[i]._0],
          a2 = vertices[caras[i]._2]-vertices[caras[i]._0],
          n = a1.cross_product(a2);
    //módulo
    float m = sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
    //normalización
    normales_caras[i] = _vertex3f(n.x/m, n.y/m, n.z/m);
    b_normales_caras = true;
  }
}

void _triangulos3D::calcular_normales_vertices(){
  int i,j;
  //initgauss();
  if (b_normales_vertices == false){
    if (b_normales_caras == false)
      calcular_normales_caras();

    normales_vertices.resize(vertices.size());
    for (i=0; i<vertices.size();i++){
      normales_vertices[i].x = 0.0;
      normales_vertices[i].y = 0.0;
      normales_vertices[i].z = 0.0;
    }
    for (i=0; i<caras.size(); i++){
      //Se suma la normal de la cara a las normales de los tres vértices de la cara
      normales_vertices[caras[i]._0] += normales_caras[i];
      normales_vertices[caras[i]._1] += normales_caras[i];
      normales_vertices[caras[i]._2] += normales_caras[i];
    }
    //normalización
    for (i=0; i<vertices.size(); i++)
      normales_vertices[i].normalize();
    //Aplicar ruido
    /*
    for (i=0;i<vertices.size();i++){
      normales_vertices[i].x *= gauss();
      normales_vertices[i].y *= gauss();
      normales_vertices[i].z *= gauss();
    }
    for (i=0; i<vertices.size();i++) normales_vertices[i].normalize();*/
    b_normales_vertices = true;
  }
}


// Hacer la iluminacion suave
void _triangulos3D::draw_iluminacion_suave(){
	GLfloat ambient_component[4] = {1,1,1,1};

  	if(b_normales_vertices == false)
  		calcular_normales_vertices();

  	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  	glShadeModel(GL_SMOOTH);
  	glEnable(GL_LIGHTING);
  	//glEnable(GL_LIGHT0);
  	//glEnable(GL_LIGHT1);
  	glEnable(GL_NORMALIZE);

  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  	glBegin(GL_TRIANGLES);

  	for(int i=0; i<caras.size(); ++i){
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}

  	glEnd();

  	// deshabilitamos las luces
  	glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);

	glBegin(GL_TRIANGLES);
	for(i = 0; i < caras.size(); i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();


}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBegin(GL_TRIANGLES);
	for(i = 0; i < caras.size(); i++){
		if(i%2 == 0)
			glColor3f(r1,g1,b1);
		else
			glColor3f(r2,g2,b2);


		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();break;
	case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
	case MATERIAL1:draw_iluminacion_plana();break;
	case MATERIAL2:draw_iluminacion_plana();break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	//vertices
		vertices.resize(8);
	//vertices cara inferiror
		vertices[0].x=tam;vertices[0].y=0;vertices[0].z=tam;
		vertices[1].x=tam;vertices[1].y=0;vertices[1].z=0;
		vertices[2].x=0;vertices[2].y=0;vertices[2].z=0;
		vertices[3].x=0;vertices[3].y=0;vertices[3].z=tam;
		vertices[4].x=tam;vertices[4].y=tam;vertices[4].z=tam;
		vertices[5].x=tam;vertices[5].y=tam;vertices[5].z=0;
		vertices[6].x=0;vertices[6].y=tam;vertices[6].z=0;
		vertices[7].x=0;vertices[7].y=tam;vertices[7].z=tam;
	// triangulos
		caras.resize(12);
		caras[0]._0=3;caras[0]._1=0;caras[0]._2=4;
		caras[1]._0=3;caras[1]._1=4;caras[1]._2=7;
		caras[2]._0=7;caras[2]._1=4;caras[2]._2=5;
		caras[3]._0=5;caras[3]._1=4;caras[3]._2=1;
		caras[4]._0=4;caras[4]._1=0;caras[4]._2=1;
		caras[5]._0=1;caras[5]._1=0;caras[5]._2=2;
		caras[6]._0=0;caras[6]._1=3;caras[6]._2=2;
		caras[7]._0=2;caras[7]._1=3;caras[7]._2=6;
		caras[8]._0=3;caras[8]._1=7;caras[8]._2=6;
		caras[9]._0=7;caras[9]._1=5;caras[9]._2=6;
		caras[10]._0=6;caras[10]._1=5;caras[10]._2=2;
		caras[11]._0=5;caras[11]._1=1;caras[11]._2=2;

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase cono
//*************************************************************************

_cono::_cono(float radio, float al, int lados)
{
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	vertice_aux.x=-radio;vertice_aux.y=0;vertice_aux.z=0;
	vertices.push_back(vertice_aux);
	parametros(vertices,lados);

	vertice_aux.x=0;vertice_aux.y=al;vertice_aux.z=0;
	vertices.push_back(vertice_aux);

	vertice_aux.x=0;vertice_aux.y=0;vertice_aux.z=0;
	vertices.push_back(vertice_aux);

	int i;
	cara_aux._0 = lados;
	for(i = 0; i < lados; i++){
		cara_aux._1 = i;
		cara_aux._2 = (i + 1)%lados;
		caras.push_back(cara_aux);
	}

	cara_aux._0 = lados + 1;
	for(i = 0; i < lados; i++){
		cara_aux._1 = i;
		cara_aux._2 = (i + 1)%lados;
		caras.push_back(cara_aux);
	}
}

void _cono::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }

 // tapa inferior
if (fabs(perfil[0].x)>0.0)
  {
  }

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
  }
}

//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, int puntos, int lados)
{
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int i;
	/*vertice_aux.x=-radio;vertice_aux.y=0;vertice_aux.z=0;
	vertices.push_back(vertice_aux);*/

	//se empieza desde el punto (r,0) y va aumentadon haca las x positivas
	vertice_aux.z = 0;
	for (i=puntos/4 + 1;i<(puntos/4+puntos/2);i++){
		vertice_aux.x =radio*cos(2.0*M_PI*i/puntos);
		vertice_aux.y =radio*sin(2.0*M_PI*i/puntos);
		vertices.push_back(vertice_aux);
	}
	parametros(vertices,lados);
	//x = 0 e y = radio
	vertice_aux.x =radio*cos(2.0*M_PI*(puntos/4)/puntos);
	vertice_aux.y =radio*sin(2.0*M_PI*(puntos/4)/puntos);
	vertices.push_back(vertice_aux);
	//x = 0 e y = -radio
	vertice_aux.x =radio*cos(2.0*M_PI*(puntos/4+puntos/2)/puntos);
	vertice_aux.y =radio*sin(2.0*M_PI*(puntos/4+puntos/2)/puntos);
	vertices.push_back(vertice_aux);

	int puntos_laterales = (puntos/2)-1;
	cara_aux._0 = vertices.size()-2;
	cara_aux._1 = 0;
	cara_aux._2 = puntos_laterales;
	caras.push_back(cara_aux);
	for(i = 1; i < lados; i++){
		cara_aux._1 = cara_aux._2;
		cara_aux._2 = (cara_aux._2+puntos_laterales)%(vertices.size()-2);
		cout << cara_aux._1<<":"<<cara_aux._2<<endl;
		caras.push_back(cara_aux);
	}

	cara_aux._0 = vertices.size()-1;
	cara_aux._1 = puntos_laterales-1;
	cara_aux._2 = cara_aux._1 + puntos_laterales;
	caras.push_back(cara_aux);
	for(i = 1; i < lados; i++){
		cara_aux._1 = cara_aux._2;
		cara_aux._2 = (cara_aux._2+puntos_laterales)%(vertices.size()-2);
		cout << cara_aux._1<<":"<<cara_aux._2<<endl;
		caras.push_back(cara_aux);
	}

}

void _esfera::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }

 // tapa inferior
if (fabs(perfil[0].x)>0.0)
  {
  }

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
  }
}
//*************************************************************************
// clase semiesfera
//*************************************************************************
_semiesfera::_semiesfera(float radio, int puntos, int lados)
{
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int i;
	/*vertice_aux.x=-radio;vertice_aux.y=0;vertice_aux.z=0;
	vertices.push_back(vertice_aux);*/

	//se empieza desde el punto (r,0) y va aumentadon haca las x positivas
	vertice_aux.z = 0;
	for (i=puntos/4 + 1;i<(puntos/4+puntos/2);i++){
		vertice_aux.x =radio*cos(2.0*M_PI*i/puntos);
		vertice_aux.y =radio*sin(2.0*M_PI*i/puntos);
		vertices.push_back(vertice_aux);
	}
	parametros(vertices,lados);
	//x = 0 e y = radio
	vertice_aux.x =0;
	vertice_aux.y =radio;
	vertices.push_back(vertice_aux);
	//x = 0 e y = -radio
	vertice_aux.x =0;
	vertice_aux.y =0;
	vertices.push_back(vertice_aux);

	int puntos_laterales = (puntos/2)-1;
	cara_aux._0 = vertices.size()-2;
	cara_aux._1 = 0;
	cara_aux._2 = puntos_laterales;
	caras.push_back(cara_aux);
	for(i = 1; i < lados; i++){
		cara_aux._1 = cara_aux._2;
		cara_aux._2 = (cara_aux._2+puntos_laterales)%(vertices.size()-2);
		cout << cara_aux._1<<":"<<cara_aux._2<<endl;
		caras.push_back(cara_aux);
	}

	cara_aux._0 = vertices.size()-1;
	cara_aux._1 = puntos_laterales-1;
	cara_aux._2 = cara_aux._1 + puntos_laterales;
	caras.push_back(cara_aux);
	for(i = 1; i < lados; i++){
		cara_aux._1 = cara_aux._2;
		cara_aux._2 = (cara_aux._2+puntos_laterales)%(vertices.size()-2);
		cout << cara_aux._1<<":"<<cara_aux._2<<endl;
		caras.push_back(cara_aux);
	}

}

void _semiesfera::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }

 // tapa inferior
if (fabs(perfil[0].x)>0.0)
  {
  }

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
  }
}
//*************************************************************************
// clase cilindro
//*************************************************************************

_cilindro::_cilindro(float radio, float al, int lados)
{
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	vertice_aux.x=-radio;vertice_aux.y=0;vertice_aux.z=0;
	vertices.push_back(vertice_aux);
	vertice_aux.x=-radio;vertice_aux.y=al;vertice_aux.z=0;
	vertices.push_back(vertice_aux);
	parametros(vertices,lados);

	vertice_aux.x=0;vertice_aux.y=0;vertice_aux.z=0;
	vertices.push_back(vertice_aux);

	vertice_aux.x=0;vertice_aux.y=al;vertice_aux.z=0;
	vertices.push_back(vertice_aux);

	int i;
	cara_aux._0 = lados * 2 ;
	for(i = 0; i < lados * 2; i= i + 2){
		cara_aux._1 = i;
		cara_aux._2 = (i + 2)%(lados * 2);
		caras.push_back(cara_aux);
	}

	cara_aux._0 = lados * 2 + 1;
	for(i = 1; i < lados * 2; i= i + 2){
		cara_aux._1 = i;
		cara_aux._2 = (i + 2)%(lados * 2);
		caras.push_back(cara_aux);
	}
}

void _cilindro::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }

 // tapa inferior
if (fabs(perfil[0].x)>0.0)
  {
  }

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
  }
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices

}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;

_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }

 // tapa inferior
if (fabs(perfil[0].x)>0.0)
  {
  }

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
  }
}

luz::luz(GLenum p_luz_ind, _vertex4f p_luz_punto, _vertex4f p_luz_ambiente, _vertex4f p_luz_difusa, _vertex4f p_luz_especular){
	luz_ind = p_luz_ind;

	luz_punto = luz_punto;
	luz_ambiente = p_luz_ambiente;
	luz_difusa = p_luz_difusa;
	luz_especular = p_luz_difusa;
}
