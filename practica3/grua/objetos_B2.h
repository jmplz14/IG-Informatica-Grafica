//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float btecla1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};
//*************************************************************************
// clase cono
//*************************************************************************
class _cilindro: public _triangulos3D
{
private:
  void parametros(vector<_vertex3f> perfil1, int num1);
public:

	_cilindro(float radio=0.5, float al=1,int lados = 10);
};

//*************************************************************************
// clase cono
//*************************************************************************

class _cono: public _triangulos3D
{
private:
  void parametros(vector<_vertex3f> perfil1, int num1);
public:

	_cono(float radio=0.5, float al=1,int lados = 10);
};

//*************************************************************************
// clase esfera
//*************************************************************************

class _esfera: public _triangulos3D
{
private:
  void parametros(vector<_vertex3f> perfil1, int num1);
public:

	_esfera(float radio=0.5, int puntos=40,int lados = 20);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1);

vector<_vertex3f> perfil;
int num;
};

class _grua: public _triangulos3D
{

public:
	_cubo base;
	_cono cabeza_giratoria;
	_cilindro brazo_inferior;
	_cubo brazo_superior;
	_grua();
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float giro_base;
	float giro_brazo_inferior;
	float giro_brazo_superior;
	float rotar_brazo_superior;
	float mover_mano;
	float girar_suelo;
};
