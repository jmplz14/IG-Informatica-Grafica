//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
using namespace std;
const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD, TEXTURE, TEXTURE_ILLUMINATED_FLAT,
						 TEXTURE_ILLUMINATED_GOURAUD} _modo;

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

//********modo*****************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );
void draw_textura(GLuint ident_textura);
void draw_textura_iluminacion_plana(GLuint ident_textura);
void draw_textura_iluminacion_suabe(GLuint ident_textura);

void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;
vector<_vertex2f> textura_coord;

bool b_normales_caras;
bool b_normales_vertices;
bool b_textura_coord;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;

bool modo_text;
GLfloat plano_s[4], plano_t[4];


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

class _semiesfera: public _triangulos3D
{
private:
  void parametros(vector<_vertex3f> perfil1, int num1);
public:

	_semiesfera(float radio=0.5, int puntos=40,int lados = 20);
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

class luz{
public:
	luz(GLenum p_luz_ind, _vertex4f p_luz_punto, _vertex4f p_luz_ambiente, _vertex4f p_luz_difusa, _vertex4f p_luz_especular);
	void activar();
	void transformar(GLenum p_luz_ind,float ang, float x, float y, float z);
protected:
	GLenum luz_ind;
	_vertex4f luz_punto;
	_vertex4f luz_ambiente;
	_vertex4f luz_especular;
	_vertex4f luz_difusa;
};
