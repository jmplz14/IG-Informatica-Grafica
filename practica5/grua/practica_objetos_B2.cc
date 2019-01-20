//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"
#include <iostream>


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CONO, CILINDRO, ESFERA, ARTICULADO} _tipo_objeto;
_tipo_objeto t_objeto=ARTICULADO;
_modo   modo=SOLID;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;
int estadoRaton[3], xc, yc, cambio=0;
bool cambioDraw = false, vistas_multiples = false, cambioModo = false;
//GLfloat Window_width,Window_height;
// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;
float factor = 1.0;

// objetos
_cubo cubo(0.8);
_piramide piramide(0.85,1.3);
_cono cono(0.85,1.3,20);
_cilindro cilindro(0.85,1.3,20);
_esfera esfera(0.85,12,6);
_objeto_ply  ply;
_rotacion rotacion;
_grua grua;


// _objeto_ply *ply1;


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
glViewport(0,0,Window_width,Window_high);
// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);


}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
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

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
				case ARTICULADO: grua.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	}

}


//**************************************************************************
//
//***************************************************************************

void draw_click(void)
{
	change_projection();
	change_observer();
	draw_axis();
	draw_objects();
	if(!cambioDraw)
		glutSwapBuffers();

	glDrawBuffer(GL_BACK);
	clean_window();
	change_observer();
		grua.draw_seleccion(modo,2);
		glDrawBuffer(GL_FRONT);

	glFlush();

	/*clean_window();
	change_observer();
	draw_axis();
	draw_objects();*/
	/*if(t_objeto == ARTICULADO){
		glDrawBuffer(GL_BACK);
		clean_window();
		change_observer();
		grua.draw_seleccion(modo,2);
		glDrawBuffer(GL_FRONT);
	}*/
	//glFlush();
}

void draw_sinclick(void)
{


	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
	glFlush();
	/*if(modo == ARTICULADO){
		cout << "dibujado fondo";
		glDrawBuffer(GL_BACK);
		clean_window();
		change_observer();
		grua.draw_seleccion(modo,2);
		glDrawBuffer(GL_FRONT);
	}*/
}

void draw(void)
{
	clean_window();
	if(vistas_multiples){
			cout << "dentro" << endl;
			//vista perspectiva
	   /*glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	   glFrustum(-Window_width,Window_width,Window_high,
	             Window_high,Front_plane,Back_plane);
	   glViewport((GLint) Window_width/2.0,0,(GLint)Window_width/2.0,(GLint)Window_high/2.0);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   glTranslatef(0,0,-Observer_distance);
	   glRotatef(Observer_angle_x,1,0,0);
	  glRotatef(Observer_angle_y,0,1,0);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  draw_axis();
	  draw_objects();*/

		//vista alzado
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  glOrtho(-5.0,5.0,-5.0,5.0,-100.0,100.0);
	  glViewport((GLint) Window_width/2.0,0,(GLint)Window_width/2.0,(GLint)Window_high/2.0);
	  glRotatef(0,1,0,0);
	  glScalef(factor,factor,1.0);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  draw_axis();
	  draw_objects();

	  //vista alzado
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  glOrtho(-5.0,5.0,-5.0,5.0,-100.0,100.0);
	  glViewport(0,(GLint)Window_high/2.0,(GLint) Window_width/2.0,(GLint) Window_high/2.0);
	  glRotatef(90,1,0,0);
	  glScalef(factor,factor,1.0);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  draw_axis();
	  draw_objects();
		//vista perfil
		glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  glOrtho(-5.0,5.0,-5.0,5.0,-100.0,100.0);
	  glViewport((GLint) Window_width/2.0,(GLint)Window_high/2.0,(GLint)Window_width/2.0,(GLint)Window_high/2.0);
	  glRotatef(90,0,1,0);
	  glScalef(factor,factor,1.0);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  draw_axis();
	  draw_objects();
		//desde abajo
		glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  glOrtho(-5.0,5.0,-5.0,5.0,-100.0,100.0);
	  glViewport((GLint) 0,0,(GLint)Window_width/2.0,(GLint)Window_high/2.0);
	  glRotatef(270,1,0,0);
	  glScalef(factor,factor,1.0);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  draw_axis();
	  draw_objects();

		glutSwapBuffers();
		glFlush();
		cambioDraw = false;
	}else{
		cout << "fuera multibles" << endl;
		//if(t_objeto == ARTICULADO){
			draw_click();
			cambioDraw = true;
		/*}else{
			draw_sinclick();
			cambioDraw = false;
		}*/

	}
	if(cambioModo){
				glutPostRedisplay();
				cambioModo = false;
	}
}

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
// el evento manda a la funcion:
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
	case 'S':modo=SOLID;break;
	case 'A':modo=SOLID_CHESS;break;
	/*case '3':t_objeto=CONO;break;
	case '4':t_objeto=CILINDRO;break;
	case '5':t_objeto=ESFERA;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;
        case 'R':t_objeto=ROTACION;break;
				case 'G':t_objeto=ARTICULADO;break;*/
				case 'M':vistas_multiples = vistas_multiples ? false : true;
				cambioModo= true;
				break;
				case '+':factor*=0.9;break;
				case '-':factor*=1.1;break;
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
	case GLUT_KEY_F1:grua.giro_base+=1;break;
 case GLUT_KEY_F2:grua.giro_base-=1;break;
 case GLUT_KEY_F3:grua.giro_brazo_inferior+=1;break;
 case GLUT_KEY_F4:grua.giro_brazo_inferior-=1;break;
 case GLUT_KEY_F5:grua.giro_brazo_superior+=1; break;
 case GLUT_KEY_F6:grua.giro_brazo_superior-=1;break;
 case GLUT_KEY_F7:grua.rotar_brazo_superior+=1;break;
 case GLUT_KEY_F8:grua.rotar_brazo_superior-=1;
									break;
 case GLUT_KEY_F9:grua.mover_mano+=1;
								 	//if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_max
									break;
 case GLUT_KEY_F10:grua.mover_mano-=1;
								 	//if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_ma
								 	break;
	case GLUT_KEY_F11:grua.girar_suelo+=1;
								 	//if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_ma
								 	break;
	case GLUT_KEY_F12:grua.girar_suelo-=1;
								 	//if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_ma
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
Observer_distance=6*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}
void procesar_color(unsigned char color[3])
{
 int obj;
 bool encontrado = false;


 switch (color[0])
      {case 100: obj=0;encontrado = true;break;
        case 120: obj=1;encontrado = true;break;
        case 140: obj=2;encontrado = true;break;
        case 160: obj=3;encontrado = true;break;
        case 180: obj=4;encontrado = true;;break;}
				if(encontrado){
					grua.cambiarEstado(obj);
					//grua.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);
				}


 }

 void pick_color(int x, int y)
 {
 	GLint viewport[4];
 	unsigned char pixel[3];

 	glGetIntegerv(GL_VIEWPORT, viewport);
 	glReadBuffer(GL_BACK);
 	glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
 	printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

 	procesar_color(pixel);
 	glutPostRedisplay();
 }

void clickRaton( int boton, int estado, int x, int y )
{
if(boton == GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     }
   else estadoRaton[2] = 1;
 }
if(boton == GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick_color(xc, yc);
    }
  }
	if(boton == 3){
		cout << "dentro scroll" << endl;
		Observer_distance*=1.2;
		glutPostRedisplay();

	}
	if(boton == 4){
		Observer_distance/=1.2;
		glutPostRedisplay();
	}
}

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}
void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x+=y;
Observer_angle_y+=x;
}

void RatonMovido( int x, int y )
{

float x0, y0, xn, yn;
if(estadoRaton[2]==1)
    {
			 getCamara(&x0,&y0);
	     yn=y-yc;

	     xn=x-xc;
			 cout << "y:" << y << ":" << yc << endl;
			 cout << "x:" << x << ":" << xc << endl;
	     setCamara(xn,yn);
	     xc=x;
	     yc=y;
	     glutPostRedisplay();
    }
}

void setCamaraAntiguo (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}

/*verde = y, azul = z y rojo = x*/

/*************************************************************************/

void RatonMovidoAntiguo( int x, int y )
{
float x0, y0, xn, yn;
if(estadoRaton[2]==1)
    {getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************



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

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

glutMouseFunc( clickRaton );
glutMotionFunc( RatonMovido );
//glutMouseWheelFunc(mouseWheel);
//glutMousWheelFunc(mouseWheel)
// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
