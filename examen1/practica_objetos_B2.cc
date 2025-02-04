//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"


using namespace std;
// NECESARIO PARA CARGAR LAS IMÁGENES DE DISCO
#include "CImg.h"
using namespace cimg_library;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CONO, CILINDRO, ESFERA} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_cono cono(0.85,1.3,20);
_cilindro cilindro(0.85,1.3,20);
_esfera semiesfera(0.85,40,20);
_esfera esfera(0.85,40,20);
_esfera esfera2(0.85,40,20);
_objeto_ply  ply;
_rotacion rotacion;

// _objeto_ply *ply1;

luz *fuente_1 = NULL;
float lAlfa, lx, ly, lz;
float angulo_luz = 30.0;
//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funciodraw_objen que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{
	if(modo != MATERIAL1 && modo != MATERIAL2 ){
		switch (t_objeto){
			case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
			case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
			case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
			case ESFERA: modo=SOLID_ILLUMINATED_GOURAUD;
			esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
			glPushMatrix();

				glTranslatef(2,0,0);
				esfera2.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
			glPopMatrix();
				break;
			case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
		        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
			}
		}else{
			if(modo == MATERIAL1){

				switch (t_objeto){
					case CUBO:
					cubo.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
					cubo.especular = _vertex4f(0.5,0.5,0.5,1.0);
					cubo.brillo = 120;
					cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					break;

					case ESFERA:
					/*semiesfera.ambiente_difusa = _vertex4f(0.25,0.20725,0.20725,0.922);
					semiesfera.especular = _vertex4f(0.296648,0.296648,0.296648,0.922);
					semiesfera.brillo = 30;*/
					modo=SOLID_ILLUMINATED_GOURAUD;
					esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					glPushMatrix();

						glTranslatef(2,0,0);
						esfera2.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					glPopMatrix();
					;break;

					case PIRAMIDE:
					piramide.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
					piramide.especular = _vertex4f(0.5,0.5,0.5,1.0);
					piramide.brillo = 120;
					piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					;break;
				  case OBJETO_PLY:
					ply.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
					ply.especular = _vertex4f(0.5,0.5,0.5,1.0);
					ply.brillo = 120;
					ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);
					;break;

					}




			}else{
				switch (t_objeto){
					case CUBO:
					cubo.ambiente_difusa = _vertex4f(0.0,0.5,0.5,0.8);
					cubo.especular = _vertex4f(0.0,0.5,0.5,0.8);
					cubo.brillo = 0.8;

					cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					break;
					case ESFERA:
					modo=SOLID_ILLUMINATED_GOURAUD;
					esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					glPushMatrix();

						glTranslatef(2,0,0);
						esfera2.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					glPopMatrix();
					break;

					case PIRAMIDE:
					piramide.ambiente_difusa = _vertex4f(0.0,0.5,0.5,0.8);
					piramide.especular = _vertex4f(0.0,0.5,0.5,0.8);
					piramide.brillo = 0.8;
					piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
					break;
				  case OBJETO_PLY:
					ply.ambiente_difusa = _vertex4f(0.0,0.5,0.5,0.8);
					ply.especular = _vertex4f(0.0,0.5,0.5,0.8);
					ply.brillo = 0.8;
					ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);
					break;

					}

			}
		}


}

void luces(){
	GLfloat light_position[4] = {0,20,0,1},light1_position[4]={0,20,0,1},
															light1_ambient[4]={0.1,0.1,0.1,1},
															light1_intensity[4]={0.4,0.4,0.4,1};

	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_intensity);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_intensity);
	glPushMatrix();
	//glRotatef(alfa,0,1,0);
	glLightfv(GL_LIGHT1,GL_POSITION,light_position);
	glPopMatrix();

}
void luces2() {
  GLfloat luz_posicion[] = {2, 2, 0 ,1.0};
  GLfloat ambiente[] = {0.3, 0.3, 0.3 ,1};
	GLfloat difusa[] = {0.3, 0.3, 0.3, 1 };
	GLfloat especular[] = { 0.3, 0.3, 0.3, 1 };
	//desabiltar luces hay hasta la 7
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
	//habilitamos luces
  glEnable(GL_LIGHT2);

  glPushMatrix();
    glRotatef (lAlfa, lx, ly, lz);
		//cambia el color de la luz ambiente que le da a todo
    glLightfv(GL_LIGHT2, GL_AMBIENT, (GLfloat *) &ambiente);
		//Color real de la luz que enfoca desde la posicion en la que se encuentre
    glLightfv(GL_LIGHT2, GL_DIFFUSE, (GLfloat *) &difusa);
		//Luces que rebotan con el mismo angulo con el que llegaron
    glLightfv(GL_LIGHT2, GL_SPECULAR, (GLfloat *) &especular);
    glLightfv(GL_LIGHT2, GL_POSITION, (GLfloat *) &luz_posicion);
  glPopMatrix();
}
void luces3() {
  GLfloat luz_posicion[] = {-2, -2, 2 ,1.0};
  GLfloat ambiente[] = {0.3, 0.3, 0.3,1};
	GLfloat difusa[] = {1, 0, 0, 1 };
	GLfloat especular[] = { 1, 0, 0, 1 };
	//desabiltar luces hay hasta la 7
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
	//habilitamos luces
  glEnable(GL_LIGHT2);

  glPushMatrix();
    glRotatef (lAlfa, lx, ly, lz);
		//cambia el color de la luz ambiente que le da a todo
    glLightfv(GL_LIGHT2, GL_AMBIENT, (GLfloat *) &ambiente);
		//Color real de la luz que enfoca desde la posicion en la que se encuentre
    glLightfv(GL_LIGHT2, GL_DIFFUSE, (GLfloat *) &difusa);
		//Luces que rebotan con el mismo angulo con el que llegaron
    glLightfv(GL_LIGHT2, GL_SPECULAR, (GLfloat *) &especular);
    glLightfv(GL_LIGHT2, GL_POSITION, (GLfloat *) &luz_posicion);
  glPopMatrix();
}
//**************************************************************************
//
//***************************************************************************




//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:cubo.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
	case '5':modo=SOLID_ILLUMINATED_FLAT;break;
	case '6':modo=SOLID_ILLUMINATED_GOURAUD;break;

  case '7':modo=TEXTURE;break;
  case '8':modo=TEXTURE_ILLUMINATED_FLAT;break;
  case '9':modo=TEXTURE_ILLUMINATED_GOURAUD;break;
	case '0':modo=IMAGEN;break;
	case 'Z':modo=MATERIAL1;break;
	case 'X':modo=MATERIAL2;break;
  case 'P':t_objeto=PIRAMIDE;break;
	case 'C':t_objeto=CUBO;break;
	case 'O':t_objeto=OBJETO_PLY;break;
	case 'R':t_objeto=ROTACION;break;
	case 'E':t_objeto=ESFERA;break;
	case 'H':
		lAlfa = fmod(lAlfa + 5, 360.0);
		lz = 1;
		lx = ly = 0;;break;

	//case 'A';break;
	//case 'E':t_objeto=ESCENA;break;
	}

glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F10:
      lAlfa = fmod(lAlfa + 5, 360.0);
      lx = 1;
      ly = lz = 0;
      break;
    case GLUT_KEY_F11:
      lAlfa = fmod(lAlfa + 5, 360.0);
      lz = 1;
      lx = ly = 0;
      break;
    case GLUT_KEY_F12:
      lAlfa = fmod(lAlfa + 5, 360.0);
      lz = 1;
      lx = ly = 0;
break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);

cubo.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
cubo.especular = _vertex4f(0.5,0.5,0.5,1.0);
cubo.brillo = 120;

esfera.ambiente_difusa = _vertex4f(1,1,0.85,1);
esfera.especular = _vertex4f(0.3,0.3,0.25,0.95);
esfera.brillo = 97;

esfera2.ambiente_difusa = _vertex4f(0.29296875,0.2109375,0.12890625,1);
esfera2.especular = _vertex4f(0.3,0.3,0.25,0.95);
esfera2.brillo = 97;

ply.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
ply.especular = _vertex4f(0.5,0.5,0.5,1.0);
ply.brillo = 120;

piramide.ambiente_difusa = _vertex4f(0.5,0.5,0.5,1.0);
piramide.especular = _vertex4f(0.5,0.5,0.5,1.0);
piramide.brillo = 120;

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************




//texturas
//Functions declarations
void Init();
void OnDraw();

// FUNCIÓN QUE PREPARA LA TEXTURA
void prepara_textura(void);

// FUNCIÓN QUE DIBUJA
void dibuja(void);

// FUNCIÓN QUE LIBERA LA TEXTURA DE GPU
void libera_textura(void);


// IDENTIFICADOR DE TEXTURA
GLuint textura_id;
GLfloat vertices[] = {0, 0,
		      10, 0,
		      10, 5,
		      0, 5};
GLfloat texVertices[] = {0.0,1.0,
			 1.0,1.0,
			 1.0,0.0,
			 0.0,0.0};


void Init(int argc, char **argv){
   //Initialize GLUT windows manager
   //Create the window
   glutInit(&argc, argv);
   glutInitWindowSize(800,600);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("My World");

   //enable lights and define perspective
   //glEnable(GL_LIGHT0);
   //glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_COLOR_MATERIAL);
   glMatrixMode(GL_PROJECTION);
   gluPerspective( 40.0, 800/600.0f, 0.1, 150);

   prepara_textura();
}

void OnDraw(void){
   //cleaning the screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //Define view
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // eye position -> (0.0, 10, 20)
   // target -> (0,0,0)
   // define positive Y axis  -> (0.0, 1.0, 0.0)
   gluLookAt(5.0, 10, 20,
	     0.0, 0, 0.0,
	     0.0, 1.0, 0.0);
   glTranslatef(-2,0,0);
   //Put your code here to draw objects
   dibuja();

   //no delete this line
   glutSwapBuffers();
}

/*int main(int argc, char** argv) {
   Init(argc, argv);
   //Enter the callbacks
   glutDisplayFunc(OnDraw);

   glutMainLoop(); // begin the loop

   // LIBERA LA TEXTURA
   libera_textura();
   return 0;
}*/
void draw(void)
{

	clean_window();
	change_observer();

		luces2();


	draw_axis();
	if(modo != IMAGEN){
		draw_objects();

	}else
		dibuja();
	glutSwapBuffers();
}

int main(int argc, char *argv[] )
{


// perfil

vector<_vertex3f> perfil2;
_vertex3f aux;

aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil2.push_back(aux);

rotacion.parametros(perfil2,6);
/*aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=0.5;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.8;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.55;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=1.4;aux.z=0.0;
perfil2.push_back(aux);
*/


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");
prepara_textura();
// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();

libera_textura();
return 0;
}


// ----------------------------------------------------------------------
void prepara_textura (void)
{
   vector<unsigned char> data;

   CImg<unsigned char> logo;
   logo.load("./abeto.jpg");

   // empaquetamos bien los datos
   for (long y = 0; y < logo.height(); y ++)
      for (long x = 0; x < logo.width(); x ++)
      {
	 unsigned char *r = logo.data(x, y, 0, 0);
	 unsigned char *g = logo.data(x, y, 0, 1);
	 unsigned char *b = logo.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }

   glGenTextures(1, &textura_id);
   glBindTexture(GL_TEXTURE_2D, textura_id);

   glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo.width(), logo.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}




 void dibujacubo (void)
 {
 	GLfloat vertices[] = {
 	 /*0, 0, 0,
 	 1, 1, 0,
 	 1, 0, 0,
 	 0, 1, 0,
 	 0, 0, 1,
 	 1, 0, 1,
 	 1, 1, 1,
 	 0, 1, 1,
 	 0, 1, 1,
 	 0, 0, 1,
 	 0, 1, 0,
 	 0, 0, 0,
 	 0, 1, 1,
 	 0, 0, 1*/
 	 -0.5, 0.0, 0.5,   0.5, 0.0, 0.5,   0.5, 1.0, 0.5,  -0.5, 1.0, 0.5,
 		 -0.5, 1.0, -0.5,  0.5, 1.0, -0.5,  0.5, 0.0, -0.5, -0.5, 0.0, -0.5,
 		 0.5, 0.0, 0.5,   0.5, 0.0, -0.5,  0.5, 1.0, -0.5,  0.5, 1.0, 0.5,
 		 -0.5, 0.0, -0.5,  -0.5, 0.0, 0.5,  -0.5, 1.0, 0.5, -0.5, 1.0, -0.5
  };
  GLfloat texVertices[] = {
 	 /*0.75,0.5,
 		0.5,0.5,
 		0.5,0.25,
 	 0.75,0.25,
 			0,0.5,
 	 0.25,0.5,
 	 0.25,0.25,
 	 0,0.25,
 	 0.25,0,
 	 0.75,0.25,
 	 0.5,0,
 	 0.5,0.75,
 	 1,0.25,
 	 1,0.5*/
 	 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
 																	0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
 																	0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
 																	0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0
  };

	 /*
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura_id);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texVertices);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	*/
	GLubyte cubeIndices[24] = {0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0,
																 8,9,10,11, 12,13,14,15};
	glEnable(GL_TEXTURE_2D);
		 glBindTexture(GL_TEXTURE_2D, textura_id);
		 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		 glColor3f(1.0f, 1.0f, 1.0f);

		 glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		 glEnableClientState(GL_VERTEX_ARRAY);

		 glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
		 glVertexPointer(3, GL_FLOAT, 0, vertices);

		 glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
		 glDisableClientState(GL_VERTEX_ARRAY);
	 glDisable(GL_TEXTURE_2D);

}

void dibujaportatil (void)
{
 GLfloat vertices[] = {
	/*0, 0, 0,
	1, 1, 0,
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	1, 0, 1,
	1, 1, 1,
	0, 1, 1,
	0, 1, 1,
	0, 0, 1,
	0, 1, 0,
	0, 0, 0,
	0, 1, 1,
	0, 0, 1*/
	-5,0,0, 0,0,0, 0,1,0, -5,1,0,
	-5,0,1, 0,0,1,

 };
 GLfloat texVertices[] = {
	/*0.75,0.5,
	 0.5,0.5,
	 0.5,0.25,
	0.75,0.25,
		 0,0.5,
	0.25,0.5,
	0.25,0.25,
	0,0.25,
	0.25,0,
	0.75,0.25,
	0.5,0,
	0.5,0.75,
	1,0.25,
	1,0.5*/
	0,0.5, 1,0.5, 1,0, 0,0,
	0,1, 1,1

 };

	/*
 glEnable(GL_TEXTURE_2D);
 glEnableClientState(GL_VERTEX_ARRAY);
 glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

 glActiveTexture(GL_TEXTURE0);
 glBindTexture(GL_TEXTURE_2D, textura_id);

 glVertexPointer(3, GL_FLOAT, 0, vertices);
 glTexCoordPointer(2, GL_FLOAT, 0, texVertices);

 glDrawArrays(GL_QUADS, 0, 4);

 glDisableClientState(GL_VERTEX_ARRAY);
 glBindTexture(GL_TEXTURE_2D, 0);
 glDisable(GL_TEXTURE_2D);
 */
 GLubyte cubeIndices[8] = {0,1,2,3, 4,5,1,0};
 glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura_id);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glColor3f(1.0f, 1.0f, 1.0f);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glDrawElements(GL_QUADS, 8, GL_UNSIGNED_BYTE, cubeIndices);
		glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

	void dibuja (void)
	{
	 GLfloat vertices[] = {
		/*0, 0, 0,
		1, 1, 0,
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
		0, 1, 1,
		0, 0, 1,
		0, 1, 0,
		0, 0, 0,
		0, 1, 1,
		0, 0, 1*/
		-1,0,-1, -1,0,1, 1,0,1, 1,0,-1, 0,1,0
		/*-1,0,-1, -1,0,1, 1,0,1, 1,0,-1*/
	 };
	 GLfloat texVertices[] = {
		/*0.75,0.5,
		 0.5,0.5,
		 0.5,0.25,
		0.75,0.25,
			 0,0.5,
		0.25,0.5,
		0.25,0.25,
		0,0.25,
		0.25,0,
		0.75,0.25,
		0.5,0,
		0.5,0.75,
		1,0.25,
		1,0.5*/
		0,1, 1,1, 0,1, 1,1, 0.5,0
	 };
	 GLfloat verticesCu[] = {
		/*0, 0, 0,
		1, 1, 0,
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
		0, 1, 1,
		0, 0, 1,
		0, 1, 0,
		0, 0, 0,
		0, 1, 1,
		0, 0, 1*/
		-1,0,-1, -1,0,1, 1,0,1, 1,0,-1
	 };
	 GLfloat texVerticesCu[] = {
		/*0.75,0.5,
		 0.5,0.5,
		 0.5,0.25,
		0.75,0.25,
			 0,0.5,
		0.25,0.5,
		0.25,0.25,
		0,0.25,
		0.25,0,
		0.75,0.25,
		0.5,0,
		0.5,0.75,
		1,0.25,
		1,0.5*/
		0,0, 0,1, 1,1, 1,0
	 };

		/*
	 glEnable(GL_TEXTURE_2D);
	 glEnableClientState(GL_VERTEX_ARRAY);
	 glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D, textura_id);

	 glVertexPointer(3, GL_FLOAT, 0, vertices);
	 glTexCoordPointer(2, GL_FLOAT, 0, texVertices);

	 glDrawArrays(GL_QUADS, 0, 4);

	 glDisableClientState(GL_VERTEX_ARRAY);
	 glBindTexture(GL_TEXTURE_2D, 0);
	 glDisable(GL_TEXTURE_2D);
	 */
	 GLubyte cubeIndices[12] = {0,1,4, 1,2,4, 2,3,4, 3,0,4};
	 glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_id);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(1.0f, 1.0f, 1.0f);

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);

			glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
			glVertexPointer(3, GL_FLOAT, 0, vertices);

			glDrawElements( GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, cubeIndices);
			glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_TEXTURE_2D);

		GLubyte baIndices[4] = {0,1,2,3};
 	 glEnable(GL_TEXTURE_2D);
 			glBindTexture(GL_TEXTURE_2D, textura_id);
 			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 			glColor3f(1.0f, 1.0f, 1.0f);

 			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 			glEnableClientState(GL_VERTEX_ARRAY);

 			glTexCoordPointer(2, GL_FLOAT, 0, texVerticesCu);
 			glVertexPointer(3, GL_FLOAT, 0, verticesCu);

 			glDrawElements( GL_QUADS, 4, GL_UNSIGNED_BYTE, baIndices);
 			glDisableClientState(GL_VERTEX_ARRAY);
 		glDisable(GL_TEXTURE_2D);
		int i = 0;
		for(i = 0; i < 4 ; i++){
			verticesCu[i*3 + 1] += 0.5;
		}

		for(i = 0; i < 5 ; i++){
			vertices[i*3 + 1] += 0.5;
		}
		glEnable(GL_TEXTURE_2D);
 			glBindTexture(GL_TEXTURE_2D, textura_id);
 			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 			glColor3f(1.0f, 1.0f, 1.0f);

 			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 			glEnableClientState(GL_VERTEX_ARRAY);

 			glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
 			glVertexPointer(3, GL_FLOAT, 0, vertices);

 			glDrawElements( GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, cubeIndices);
 			glDisableClientState(GL_VERTEX_ARRAY);
 		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
  			glBindTexture(GL_TEXTURE_2D, textura_id);
  			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  			glColor3f(1.0f, 1.0f, 1.0f);

  			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  			glEnableClientState(GL_VERTEX_ARRAY);

  			glTexCoordPointer(2, GL_FLOAT, 0, texVerticesCu);
  			glVertexPointer(3, GL_FLOAT, 0, verticesCu);

  			glDrawElements( GL_QUADS, 4, GL_UNSIGNED_BYTE, baIndices);
  			glDisableClientState(GL_VERTEX_ARRAY);
  		glDisable(GL_TEXTURE_2D);


	}

	void dibujaskybox(void)
	{
	 GLfloat vertices[] = {
		/*0, 0, 0,
		1, 1, 0,
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
		0, 1, 1,
		0, 0, 1,
		0, 1, 0,
		0, 0, 0,
		0, 1, 1,
		0, 0, 1*/
		//base del suelo
		-2,0,0, -2,0,2, 0,0,2, 0,0,0,
		//bsae del cielo
		-2,2,0, -2,2,2, 0,2,2, 0,2,0,
		//lado izquierdo
		-2,2,2, -2,0,2,
		//lado derecho
		0,2,2, 0,0,2,

		//ultima tapa
		-2,2,2, -2,0,2
	 };

	 GLfloat texVertices[] = {
		/*0.75,0.5,
		 0.5,0.5,
		 0.5,0.25,
		0.75,0.25,
			 0,0.5,
		0.25,0.5,
		0.25,0.25,
		0,0.25,
		0.25,0,
		0.75,0.25,
		0.5,0,
		0.5,0.75,
		1,0.25,
		1,0.5*/
		0.25,0.5, 0.25,0.75, 0.5,0.75, 0.5,0.5,

		0.25,0.25, 0.25,0, 0.5,0, 0.5,0.25,

		0,0.25, 0,0.50,

		0.75,0.25, 0.75,0.5,
		//Tapa del fondo no necesita nuevos punto
		//Tapa izquierdad
		1,0.25, 1,0.5
	 };

		/*
	 glEnable(GL_TEXTURE_2D);
	 glEnableClientState(GL_VERTEX_ARRAY);
	 glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D, textura_id);

	 glVertexPointer(3, GL_FLOAT, 0, vertices);
	 glTexCoordPointer(2, GL_FLOAT, 0, texVertices);

	 glDrawArrays(GL_QUADS, 0, 4);

	 glDisableClientState(GL_VERTEX_ARRAY);
	 glBindTexture(GL_TEXTURE_2D, 0);
	 glDisable(GL_TEXTURE_2D);
	 */
	 GLubyte cubeIndices[24] = {0,1,2,3, 4,5,6,7, 0,3,7,4, 4,0,9,8, 7,3,11,10, 10,11,13,12 };
	 glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura_id);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glColor3f(1.0f, 1.0f, 1.0f);

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);

			glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
			glVertexPointer(3, GL_FLOAT, 0, vertices);

			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
			glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_TEXTURE_2D);
	}

void libera_textura (void)
{
   glDeleteTextures(1, &textura_id);
}
