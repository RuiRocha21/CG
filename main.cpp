

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED         1.0, 0.0, 0.0, 1.0
#define YELLOW     1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define Castanho    0.43, 0.21, 0.1, 1.0
#define cinza    0.3,0.52,0.18,1.0
#define PI         3.14159

//-----------------------------Particulas

#define frand()            ((float)rand()/RAND_MAX)
#define MAX_PARTICULAS  3500


#include "materiais.h"
#include "RgbImage.h"


//falta afinar teclas de utilizador


//---------------------------------------- estrutura para particulas
typedef struct {
    bool    verificaParticula;
    float   size;        // tamanho
    float    life;        // vida
    float    fade;        // fade
    float    r, g, b;    // color
    GLfloat x, y, z;    // posicao
    GLfloat vx, vy, vz; // velocidade
    GLfloat ax, ay, az; // aceleracao
    float compunineteGravitacional;
} Particle;

Particle  particula1[MAX_PARTICULAS];
Particle  particula2[MAX_PARTICULAS];
Particle  particula3[MAX_PARTICULAS];
Particle  particula4[MAX_PARTICULAS];
Particle  particula5[MAX_PARTICULAS];

Particle particulaChuva[MAX_PARTICULAS];



char     ficheiroParticula[1][100] = {"/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/particula.bmp"};

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint        wScreen=1200, yC=1200.0, hScreen=1000;        //.. janela (pixeis)
GLfloat        xC=1400,  zC=1000;        //.. Mundo  (unidades mundo)
char     texto[50];
GLint    msec     = 1000;                    //.. definicao do timer (actualizacao)

//------------------------------------------------------------ Observador
GLfloat  rVisao=3.0, aVisao=0.5*PI, incVisao=1;
GLfloat  angPersp=109.0;
GLfloat  obsPini[] ={1, 10, static_cast<GLfloat>(-0.5*xC)};
GLfloat  obsPfin[] ={obsPini[0]-rVisao*cos(aVisao), obsPini[1], (obsPini[2]+rVisao*sin(aVisao))};

GLUquadricObj*  esfera1 = gluNewQuadric ();
GLUquadricObj*  esfera2 = gluNewQuadric ();

GLUquadricObj*  skyboxAmbiente  = gluNewQuadric ();
GLfloat         sizeSky  = 1400;
//=================================================================== TEXTURAS
GLuint   texture[10];
GLuint   texturasOutdoor[15];
GLuint   texturaParticula[1];

RgbImage imag;
int valorTextura = 0;
//--------------------------------------------------------------------ESCADA
static GLuint     poligono[]={0,0,0,0};

static GLfloat vertices[]={
    -400.000000, -0.000000, 96.000000, 400.000000, -0.000000, 96.000000, 400.000000, 0.000000, 0.000000, -400.000000, 0.000000, 0.000000, -400.000000, 0.000000, 96.000000, 400.000000, 0.000000, 96.000000, 400.000000, 16.000000, 96.000000, -400.000000, 16.000000, 96.000000, -400.000000, 16.000000, 128.000000, 400.000000, 16.000000, 128.000000, 400.000000, 16.000000, 96.000000, -400.000000, 16.000000, 96.000000, -400.000000, 16.000000, 128.000000, 400.000000, 16.000000, 128.000000, 400.000000, 32.000000, 128.000000, -400.000000, 32.000000, 128.000000, -400.000000, 32.000000, 160.000000, 400.000000, 32.000000, 160.000000, 400.000000, 32.000000, 128.000000, -400.000000, 32.000000, 128.000000, -400.000000, 32.000000, 160.000000, 400.000000, 32.000000, 160.000000, 400.000000, 48.000000, 160.000000, -400.000000, 48.000000, 160.000000, -400.000000, 48.000000, 192.000000, 400.000000, 48.000000, 192.000000, 400.000000, 48.000000, 160.000000, -400.000000, 48.000000, 160.000000, -400.000000, 48.000000, 192.000000, 400.000000, 48.000000, 192.000000, 400.000000, 64.000000, 192.000000, -400.000000, 64.000000, 192.000000, -400.000000, 64.000000, 224.000000, 400.000000, 64.000000, 224.000000, 400.000000, 64.000000, 192.000000, -400.000000, 64.000000, 192.000000, -400.000000, 64.000000, 224.000000, 400.000000, 64.000000, 224.000000, 400.000000, 80.000000, 224.000000, -400.000000, 80.000000, 224.000000, -400.000000, 80.000000, 320.000000, 400.000000, 80.000000, 320.000000, 400.000000, 80.000000, 224.000000, -400.000000, 80.000000, 224.000000, -400.000000, 80.000000, 320.000000, 400.000000, 80.000000, 320.000000, 400.000000, 96.000000, 320.000000, -400.000000, 96.000000, 320.000000, -400.000000, 96.000000, 352.000000, 400.000000, 96.000000, 352.000000, 400.000000, 96.000000, 320.000000, -400.000000, 96.000000, 320.000000, -400.000000, 96.000000, 352.000000, 400.000000, 96.000000, 352.000000, 400.000000, 112.000000, 352.000000, -400.000000, 112.000000, 352.000000, -400.000000, 112.000000, 384.000000, 400.000000, 112.000000, 384.000000, 400.000000, 112.000000, 352.000000, -400.000000, 112.000000, 352.000000, -400.000000, 112.000000, 384.000000, 400.000000, 112.000000, 384.000000, 400.000000, 128.000000, 384.000000, -400.000000, 128.000000, 384.000000, -400.000000, 128.000000, 416.000000, 400.000000, 128.000000, 416.000000, 400.000000, 128.000000, 384.000000, -400.000000, 128.000000, 384.000000, -400.000000, 128.000000, 416.000000, 400.000000, 128.000000, 416.000000, 400.000000, 144.000000, 416.000000, -400.000000, 144.000000, 416.000000, -400.000000, 144.000000, 448.000000, 400.000000, 144.000000, 448.000000, 400.000000, 144.000000, 416.000000, -400.000000, 144.000000, 416.000000, -400.000000, 144.000000, 448.000000, 400.000000, 144.000000, 448.000000, 400.000000, 160.000000, 448.000000, -400.000000, 160.000000, 448.000000, -400.000000, 160.000000, 544.000000, 400.000000, 160.000000, 544.000000, 400.000000, 160.000000, 448.000000, -400.000000, 160.000000, 448.000000
};


static GLfloat normais[] = {
    0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000,
};
//------------------------------------------------------------ Cores
static GLfloat cores[]={
    0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000,
};

static GLfloat arrayTexture[]={
    0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1,  0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1
};


//------------------------------Iluminacao Ambiente
GLint noite = 0;
GLfloat intensidade = 10.0;
GLfloat luzGlobal[4] = {0.9, 0.9, 0.9, 1.0};

//…………………………………………………………………………………………………………………………………………… luz esfera1
GLint     ligaEsferaEsq=0;
GLint   ligaEsferaDir=0;
GLfloat rFocoEsfera=200.0, aFoco=aVisao;
GLfloat incH =0.0, incV=0.0;
GLfloat incMaxH =0.5, incMaxV=0.35;

GLfloat focoEsfera1_ini[]= { 800.0, 680.0, 750.0, 1.0 };
GLfloat focoEsfera1_fin[]=  { obsPini[0]-rFocoEsfera*cos(aFoco), obsPini[1], obsPini[2]+rFocoEsfera*sin(aFoco), 1.0};

GLfloat focoDir1[] = { focoEsfera1_fin[0]-focoEsfera1_ini[0], 0, focoEsfera1_fin[2]-focoEsfera1_ini[2]};
GLfloat focoExp   = 0.0;
GLfloat focoCut   = 180.0;

GLfloat focoCorDif[4] ={ 0.9, 0.9, 0.9, 1.0};
GLfloat focoCorEsp[4] ={ 1.0, 1.0, 1.0, 1.0};

//---------------------------------------------------lus esfera2
GLfloat focoEsfera2_ini[]= {-600.0, 680.0, 750.0, 1.0 };
GLfloat focoEsfera2_fin[]=  { obsPini[0]-rFocoEsfera*cos(aFoco), obsPini[1], obsPini[2]-rFocoEsfera*sin(aFoco), 1.0};
GLfloat focoDir2[] = { focoEsfera2_fin[0]-focoEsfera2_ini[0], 0, focoEsfera2_fin[2]+focoEsfera2_ini[2]};

//-----------------------------------------------------luz natural
//…………………………………………………………………………………………………………………………………………… BRANCA
GLfloat raioSol=1000.0;
GLfloat posInicio[] = {xC/2, 1000.0, xC/2, 0.0};   // no tecto
GLfloat posFim[] = { obsPini[0]-raioSol*cos(aFoco), obsPini[1], obsPini[2]-raioSol*sin(aFoco), 1.0};
GLfloat dirSol [] = { posFim[0]-posInicio[0], 0, posFim[2]-posInicio[2]};
GLint     ligaLuzNatural=0;

static GLfloat A1Dir[3]={600.0,120.0,96.0};
static GLfloat B1Dir[3]={400.0,120.0,96.0};
static GLfloat C1Dir[3]={400.0,0.0,96.0};
static GLfloat D1Dir[3]={600.0,0.0,96.0};
static GLfloat E1Dir[3]={600.0,120.0,300.0};
static GLfloat F1Dir[3]={400.0,120.0,300.0};
static GLfloat G1Dir[3]={400.0,0.0,300.0};
static GLfloat H1Dir[3]={600.0,0.0,300.0};

static GLfloat A2Dir[3]={600.0,200.0,300.0};
static GLfloat B2Dir[3]={400.0,200.0,300.0};
static GLfloat C2Dir[3]={400.0,0.0,300.0};
static GLfloat D2Dir[3]={600.0,0.0,300.0};
static GLfloat E2Dir[3]={600.0,200.0,600.0};
static GLfloat F2Dir[3]={400.0,200.0,600.0};
static GLfloat G2Dir[3]={400.0,0.0,600.0};
static GLfloat H2Dir[3]={600.0,0.0,600.0};

static GLfloat A3Dir[3]={600.0,500.0,600.0};
static GLfloat B3Dir[3]={400.0,500.0,600.0};
static GLfloat C3Dir[3]={400.0,0.0,600.0};
static GLfloat D3Dir[3]={600.0,0.0,600.0};
static GLfloat E3Dir[3]={600.0,500.0,900.0};
static GLfloat F3Dir[3]={400.0,500.0,900.0};
static GLfloat G3Dir[3]={400.0,0.0,900.0};
static GLfloat H3Dir[3]={600.0,0.0,900.0};

/*LADO DIREITO*/

static GLfloat A1Esq[3]={-600.0,120.0,96.0};
static GLfloat B1Esq[3]={-400.0,120.0,96.0};
static GLfloat C1Esq[3]={-400.0,0.0,96.0};
static GLfloat D1Esq[3]={-600.0,0.0,96.0};
static GLfloat E1Esq[3]={-600.0,120.0,300.0};
static GLfloat F1Esq[3]={-400.0,120.0,300.0};
static GLfloat G1Esq[3]={-400.0,0.0,300.0};
static GLfloat H1Esq[3]={-600.0,0.0,300.0};

static GLfloat A2Esq[3]={-600.0,200.0,300.0};
static GLfloat B2Esq[3]={-400.0,200.0,300.0};
static GLfloat C2Esq[3]={-400.0,0.0,300.0};
static GLfloat D2Esq[3]={-600.0,0.0,300.0};
static GLfloat E2Esq[3]={-600.0,200.0,600.0};
static GLfloat F2Esq[3]={-400.0,200.0,600.0};
static GLfloat G2Esq[3]={-400.0,0.0,600.0};
static GLfloat H2Esq[3]={-600.0,0.0,600.0};

static GLfloat A3Esq[3]={-600.0,500.0,600.0};
static GLfloat B3Esq[3]={-400.0,500.0,600.0};
static GLfloat C3Esq[3]={-400.0,0.0,600.0};
static GLfloat D3Esq[3]={-600.0,0.0,600.0};
static GLfloat E3Esq[3]={-600.0,500.0,900.0};
static GLfloat F3Esq[3]={-400.0,500.0,900.0};
static GLfloat G3Esq[3]={-400.0,0.0,900.0};
static GLfloat H3Esq[3]={-600.0,0.0,900.0};

static GLfloat SupTopoA[3]={-400,160,544};
static GLfloat SupTopoB[3]={400,160,544};
static GLfloat SupTopoC[3]={400.0,0.0,544.0};
static GLfloat SupTopoD[3]={-400.0,0.0,544.0};
static GLfloat SupTopoE[3]={-400.0,200.0,600.0};
static GLfloat SupTopoF[3]={400.0,200.0,600.0};
static GLfloat SupTopoG[3]={400.0,0.0,600.0};
static GLfloat SupTopoH[3]={-400.0,0.0,600.0};

static GLfloat cartasA[3]={-400,480,900};
static GLfloat cartasB[3]={400,480,900};
static GLfloat cartasC[3]={400,400,900};
static GLfloat cartasD[3]={-400,400,900};

static GLfloat passeioA[3] = {1400.0,0.0,-50.0};
static GLfloat passeioB[3] = {-1400.0,0.0,-50.0};
static GLfloat passeioC[3] = {-1400.0,-40.0,-50.0};
static GLfloat passeioD[3] = {1400.0,-40.0,-50.0};
static GLfloat passeioE[3] = {1400.0,0.0,96};
static GLfloat passeioF[3] = {-1400.0,0.0,96};
static GLfloat passeioG[3] = {-1400.0,-40.0,96};
static GLfloat passeioH[3] = {1400.0,-40.0,96};

static GLfloat EstradaA[3] = {-1400.0,-40.0,-50.0};
static GLfloat EstradaB[3] = {1400.0,-40.0,-50.0};
static GLfloat EstradaC[3] = {1400.0,-40.0,-1400.0};
static GLfloat EstradaD[3] = {-1400.0,-40.0,-1400.0};

static GLfloat PilarOutDoorEsqA[3] = {-800,300,300};
static GLfloat PilarOutDoorEsqB[3] = {-850,300,300};
static GLfloat PilarOutDoorEsqC[3] = {-850,0,300};
static GLfloat PilarOutDoorEsqD[3] = {-800,0,300};
static GLfloat PilarOutDoorEsqE[3] = {-800,300,350};
static GLfloat PilarOutDoorEsqF[3] = {-850,300,350};
static GLfloat PilarOutDoorEsqG[3] = {-850,0,350};
static GLfloat PilarOutDoorEsqH[3] = {-800,0,350};

static GLfloat PilarOutDoorDirA[3] = {-1400,300,0};
static GLfloat PilarOutDoorDirB[3] = {-1350,300,0};
static GLfloat PilarOutDoorDirC[3] = {-1350,0,0};
static GLfloat PilarOutDoorDirD[3] = {-1400,0,0};
static GLfloat PilarOutDoorDirE[3] = {-1400,300,50};
static GLfloat PilarOutDoorDirF[3] = {-1350,300,50};
static GLfloat PilarOutDoorDirG[3] = {-1350,0,50};
static GLfloat PilarOutDoorDirH[3] = {-1400,0,50};

static GLfloat PainelOutDoorA[3] = {-1350,300,25};
static GLfloat PainelOutDoorB[3] = {-850,300,300};
static GLfloat PainelOutDoorC[3] = {-850,100,300};
static GLfloat PainelOutDoorD[3] = {-1350,100,25};

void iniciaMateriais(int material){
    switch (material){
       
        case 0: //material preto
            glMaterialfv(GL_FRONT,GL_AMBIENT,  blackRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, blackRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,blackRubberCoef);
            break;

        case 1: //latao
            glMaterialfv(GL_FRONT,GL_AMBIENT,  brassAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  brassDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, brassSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,brassCoef);
            break;
        case 2:    //……………………………………………………………………………………………greenRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  greenRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, greenRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,greenRubberCoef);
            break;
        case 3:    //……………………………………………………………………………………………chrome
            glMaterialfv(GL_FRONT,GL_AMBIENT,  chromeAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  chromeDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, chromeSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,chromeCoef);
            break;
        case 4://……………………………………………………………………………………………ruby
            glMaterialfv(GL_FRONT,GL_AMBIENT,  redRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  redRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, redRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,redRubberCoef);
            break;
            
        case 5:
            glMaterialfv(GL_FRONT,GL_AMBIENT,  whitePlasticAmb);
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  whitePlasticDif);
            glMaterialfv(GL_FRONT,GL_SPECULAR, whitePlasticSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,whitePlasticCoef);
            break;
        
        case 6:
            glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowRubberAmb);
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowRubberDif);
            glMaterialfv(GL_FRONT,GL_SPECULAR, yellowRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,yellowRubberCoef);
            break;
            
            
     
    }
}


//==========================================================================
//============================luzes==================================
void iniciaLuz(void){
    //…………………………………………………………………………………………………………………………………………… Ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobal);
    
    //…………………………………………………………………………………………………………………………………………… Foco (esfera esquerda)
    glLightfv(GL_LIGHT0, GL_POSITION,      focoEsfera1_ini );
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,focoDir1 );
    glLightf (GL_LIGHT0, GL_SPOT_EXPONENT ,focoExp);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,   focoCut);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,       focoCorDif );
    glLightfv(GL_LIGHT0, GL_SPECULAR,      focoCorEsp  );
    
    //…………………………………………………………………………………………………………………………………………… Foco (esfera direita)
    glLightfv(GL_LIGHT1, GL_POSITION,      focoEsfera2_ini );
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,focoDir2 );
    glLightf (GL_LIGHT1, GL_SPOT_EXPONENT ,focoExp);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF,   focoCut);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,       focoCorDif );
    glLightfv(GL_LIGHT1, GL_SPECULAR,      focoCorEsp  );
    
    
    
    if (ligaEsferaEsq)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
    
    if (ligaEsferaDir)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    
    
}

//=================================================================================================
//================================INICIA PARTICULAS
void iniParticulas(Particle *particula, GLfloat posX, GLfloat posy){
    GLfloat v, theta, phi;
    int i;
    GLfloat px, py, pz;
    GLfloat ps;
    
    px = posX;
    py = posy;
    pz = -200.0;
    ps = 4.5;
    
    
    
    for(i=0; i<MAX_PARTICULAS; i++)  {
        
        //---------------------------------
        v     = 1*frand()+0.02;
        theta = 2.0*frand()*M_PI;   // [0..2pi]
        phi   = frand()*M_PI;        // [0.. pi]
        
        particula[i].size = ps ;        // tamanh de cada particula
        particula[i].x      = px + 0.1*frand()*px;    // [-200 200]
        particula[i].y      = py + 0.1*frand()*py;    // [-200 200]
        particula[i].z      = pz + 0.1*frand()*pz;    // [-200 200]
        
        particula[i].vx = v * cos(theta) * sin(phi);    // esferico
        particula[i].vy = v * cos(phi);
        particula[i].vz = v * sin(theta) * sin(phi);
        particula[i].ax = 0.01f;
        particula[i].ay = -0.01f;
        particula[i].az = 0.015f;
        
        particula[i].r = 1.0f;
        particula[i].g = 1.0f;
        particula[i].b = 1.0f;
        particula[i].life = 1.0f;
        particula[i].fade = 0.001f;    // Em 100=1/0.01 iteracoes desaparece
    }
}

void iniciaParticulaChuva(int i){
    particulaChuva[i].size = 4.5 ;
    particulaChuva[i].verificaParticula = true;
    particulaChuva[i].life = 1.0;
    particulaChuva[i].fade = float(rand()%100)/1000.0f+0.003f;
    particulaChuva[i].x = (float) (rand() % 21) - 10;
    particulaChuva[i].y = 500.0;
    particulaChuva[i].z = (float) (rand() % 21) - 10;
    particulaChuva[i].vx = 0.0;
    particulaChuva[i].vy = 0.0;
    particulaChuva[i].vz = 0.0;
    particulaChuva[i].ax = 0.0;
    particulaChuva[i].ay = 0.0;
    particulaChuva[i].az = 0.0;
}

//================================================================================
//=========================== INICIAR TEXTURAS

void iniciaTexturas(){
    
    
    
    
    //-----------------------------------------------paines outdoor
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/images.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //----------------------------------------------------------escada
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/damascus_pattern.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //--------------------------------------------------pilares outdoor
    glGenTextures(1, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/pedra.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //---------------------------------------chao
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/pedra.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //---------------------------------------esferas
    glGenTextures(1, &texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/esfera.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //---------------------------------------paseio (lancil e calcada)
    glGenTextures(1, &texture[5]);
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/calcada2.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    glGenTextures(1, &texture[6]);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/lancil.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //-------------------------------guardas da escada
    
    glGenTextures(1, &texture[7]);
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/marmore.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //-----------------------------estrada
    
    glGenTextures(1, &texture[8]);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/estrada.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //-----------------------------skybox
    glGenTextures(1, &texture[9]);
    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/skybox.bmp");
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
    //-----------------------------------------------texturas outdoor
    glGenTextures(1, &texturasOutdoor[0]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[0]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/img1.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //---------
    glGenTextures(1, &texturasOutdoor[1]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[1]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/img2.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //---------
    glGenTextures(1, &texturasOutdoor[2]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[2]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/img3.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //---------
    glGenTextures(1, &texturasOutdoor[3]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[3]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2011.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //---------
    glGenTextures(1, &texturasOutdoor[4]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[4]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2012.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //---------
    glGenTextures(1, &texturasOutdoor[5]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[5]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2013.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //---------
    glGenTextures(1, &texturasOutdoor[6]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[6]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2014.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //--------------------------------------
    glGenTextures(1, &texturasOutdoor[7]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[7]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2015.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //------------------------------
    glGenTextures(1, &texturasOutdoor[8]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[8]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2016.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //------------------------------
    glGenTextures(1, &texturasOutdoor[9]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[9]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2017.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    //------------------------------
    glGenTextures(1, &texturasOutdoor[10]);
    glBindTexture(GL_TEXTURE_2D, texturasOutdoor[10]);
    imag.LoadBmpFile("/Users/ruirocha/Documents/uc/CG/projecto/ProjectoCG/ProjectoCG/img/outdoor/qf2018.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
}

void iniciaTexturaPaqrticula(){
    glGenTextures(1, texturaParticula);
    
    glBindTexture(GL_TEXTURE_2D, texturaParticula[0]);
    imag.LoadBmpFile(ficheiroParticula[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (int)imag.GetNumCols(),
                 (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imag.ImageData());
    
}


//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
    glClearColor(1,1,1,1);        //………………………………………………………………………………Apagar
    glShadeModel(GL_SMOOTH);    //………………………………………………………………………………Interpolacao de cores
    
    glEnable(GL_DEPTH_TEST);    //………………………………………………………………………………Profundidade
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    
    glEnable(GL_TEXTURE_2D);
    glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cores);
    glEnableClientState(GL_COLOR_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   
    //iluminacao
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    iniciaTexturas();            //------------------------------Texturas
    iniciaLuz();
    iniciaTexturaPaqrticula();
    iniParticulas(particula1,-400.0,500.0);
    iniParticulas(particula2,400.0,500.0);
    iniParticulas(particula3,-250.0,600.0);
    iniParticulas(particula4,250.0,600.0);
    iniParticulas(particula5,0.0,500.0);
    
    

    
    
}

GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    glViewport( 0, 0, wScreen,hScreen );
    glutPostRedisplay();
}

void drawOrientacao()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor4f(0,1,0,1);
    glTranslatef (obsPini[0],obsPini[1],obsPini[2]);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glColor4f(0,0,1,1);
    glTranslatef (obsPfin[0],obsPfin[1],obsPfin[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
    glColor4f(1,1,0,1);
    glBegin(GL_LINES);
    glVertex3i(0,0,-xC);
    glVertex3i(0,0, xC);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
    glColor4f(1,1,0,1);
    glBegin(GL_LINES);
    glVertex3i(0,-xC,0);
    glVertex3i(0, xC,0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
    glColor4f(1,1,0,1);
    glBegin(GL_LINES);
    glVertex3i(-xC,0,0);
    glVertex3i( xC,0,0);
    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    
}


/***************************************************************
 objectos
 ***************************************************************/
void drawSkySphere(){
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[9]);
    iniciaMateriais(5);
    glPushMatrix();
    
    glRotatef (       90, -1, 0, 0);
    gluQuadricDrawStyle ( skyboxAmbiente, GLU_FILL   );
    gluQuadricNormals   ( skyboxAmbiente, GLU_SMOOTH );
    gluQuadricTexture   ( skyboxAmbiente, GL_TRUE    );
    gluSphere ( skyboxAmbiente, sizeSky*1, 150, 150);
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
};

void actualizaTextura(int valor){
    valorTextura +=1;
    if(valorTextura >10){
        valorTextura = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(1000,actualizaTextura,valor);
}

void drawOutDoor(){
    iniciaMateriais(0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[2]);
   
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorEsqA);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorEsqB);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorEsqC);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorEsqD);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorEsqF);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorEsqE);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorEsqH);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorEsqG);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorEsqE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorEsqA);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorEsqD);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorEsqH);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorEsqB);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorEsqF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorEsqG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorEsqC);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorEsqE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorEsqF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorEsqB);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorEsqA);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorEsqD);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorEsqC);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorEsqG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorEsqH);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    iniciaMateriais(0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[2]);
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorDirA);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorDirB);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorDirC);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorDirD);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorDirF);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorDirE);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorDirH);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorDirG);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorDirE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorDirA);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorDirD);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorDirH);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorDirB);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorDirF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorDirG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorDirC);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorDirE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorDirF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorDirB);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorDirA);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PilarOutDoorDirD);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PilarOutDoorDirC);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PilarOutDoorDirG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PilarOutDoorDirH);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    iniciaMateriais(5);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texturasOutdoor[valorTextura]);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(PainelOutDoorA); //A
    glTexCoord2f(1.0f,0.0f);glVertex3fv(PainelOutDoorB);//B
    glTexCoord2f(1.0f,1.0f);glVertex3fv(PainelOutDoorC); //C
    glTexCoord2f(0.0f,1.0f);glVertex3fv(PainelOutDoorD); //D
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void drawChao(){
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=-5
    iniciaMateriais(5);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[3]);
    
    glPushMatrix();
    
    glTranslatef(0,-5,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);       glVertex3i( -xC,  -5, 96 );
    glTexCoord2f(1.0f, 0.0f);      glVertex3i( -xC,   -5,  xC );
    glTexCoord2f(1.0f, 1.0f);    glVertex3i(  xC,   -5,  xC);
    glTexCoord2f(0.0f, 1.0f);    glVertex3i(  xC,     -5,  96);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void DrawEsfera(){
    //------------------------------------------esfera 1
    iniciaMateriais(1);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    
    glPushMatrix();
    
    glTranslatef ( 500.0,680.0,750.0);
    gluQuadricDrawStyle ( esfera1, GLU_FILL   );
    gluQuadricNormals   ( esfera1, GLU_SMOOTH );
    gluQuadricTexture   ( esfera1, GL_TRUE    );
    glScaled(200.0,200.0,200.0);
    gluSphere ( esfera1, 1.0, 2000, 2000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //------------------------------------------esfera 2
    iniciaMateriais(1);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    
    glPushMatrix();
    
    glTranslatef ( -500.0,680.0,750.0);
    gluQuadricDrawStyle ( esfera2, GLU_FILL   );
    gluQuadricNormals   ( esfera2, GLU_SMOOTH );
    gluQuadricTexture   ( esfera2, GL_TRUE    );
    glScaled(200.0,200.0,200.0);
    gluSphere ( esfera2, 1.0, 2000, 2000);
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void DrawPasseio(){
     iniciaMateriais(5);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[6]);
   
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(passeioA);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(passeioB);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(passeioC);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(passeioD);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(passeioF);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(passeioE);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(passeioH);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(passeioG);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(passeioE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(passeioA);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(passeioD);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(passeioH);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(passeioB);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(passeioF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(passeioG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(passeioC);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(passeioD);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(passeioC);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(passeioG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(passeioH);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    iniciaMateriais(5);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(passeioE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(passeioF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(passeioB);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(passeioA);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void DrawEstrada(){
    iniciaMateriais(5);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[8]);//alterar imagem
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(EstradaA);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(EstradaB);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(EstradaC);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(EstradaD);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void DrawCartasTopo(){
    iniciaMateriais(5);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[0]);//alterar imagem
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(cartasA);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(cartasB);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(cartasC);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(cartasD);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void DrawSuperficieTopo(){
    iniciaMateriais(6);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(SupTopoA);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(SupTopoB);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(SupTopoC);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(SupTopoD);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(SupTopoF);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(SupTopoE);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(SupTopoH);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(SupTopoG);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(SupTopoE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(SupTopoA);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(SupTopoD);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(SupTopoH);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(SupTopoB);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(SupTopoF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(SupTopoG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(SupTopoC);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(SupTopoE);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(SupTopoF);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(SupTopoB);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(SupTopoA);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(SupTopoD);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(SupTopoC);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(SupTopoG);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(SupTopoH);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawCorrimaoEsquerdo(){
    iniciaMateriais(2);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[7]);
    
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(A1Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(B1Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(C1Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(D1Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(F1Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(E1Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(H1Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(G1Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E1Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(A1Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(D1Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H1Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(B1Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F1Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G1Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(C1Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E1Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F1Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(B1Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(A1Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(D1Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(C1Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G1Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H1Esq);
    glEnd();
    
    
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(A2Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(B2Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(C2Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(D2Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(F2Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(E2Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(H2Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(G2Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E2Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(A2Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(D2Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H2Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(B2Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F2Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G2Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(C2Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E2Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F2Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(B2Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(A2Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(D2Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(C2Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G2Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H2Esq);
    glEnd();
    
    
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(A3Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(B3Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(C3Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(D3Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(F3Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(E3Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(H3Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(G3Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E3Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(A3Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(D3Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H3Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(B3Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F3Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G3Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(C3Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E3Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F3Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(B3Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(A3Esq);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(D3Esq);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(C3Esq);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G3Esq);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H3Esq);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawCorrimaoDireito(){
    iniciaMateriais(4);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[7]);
    
    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(A1Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(B1Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(C1Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(D1Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(F1Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(E1Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(H1Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(G1Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E1Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(A1Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(D1Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H1Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(B1Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F1Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G1Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(C1Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E1Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F1Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(B1Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(A1Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(D1Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(C1Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G1Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H1Dir);
    glEnd();
    
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(A2Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(B2Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(C2Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(D2Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(F2Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(E2Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(H2Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(G2Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E2Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(A2Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(D2Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H2Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(B2Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F2Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G2Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(C2Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E2Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F2Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(B2Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(A2Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(D2Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(C2Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G2Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H2Dir);
    glEnd();
    
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(A3Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(B3Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(C3Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(D3Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(F3Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(E3Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(H3Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(G3Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E3Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(A3Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(D3Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H3Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(B3Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F3Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G3Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(C3Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(E3Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(F3Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(B3Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(A3Dir);
    glEnd();
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
    glTexCoord2f(0.0f,0.0f);glVertex3fv(D3Dir);
    glTexCoord2f(1.0f,0.0f);glVertex3fv(C3Dir);
    glTexCoord2f(1.0f,1.0f);glVertex3fv(G3Dir);
    glTexCoord2f(0.0f,1.0f);glVertex3fv(H3Dir);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
}


void drawScene(){
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    
    
    //---------------------------------------------Escada
    
    iniciaMateriais(6);
    glPushMatrix();
    
    
    for(int i=0;i<22;i++) {
        
        poligono[0] = i*4;
        poligono[1] = i*4+1;
        poligono[2] = i*4+2;
        poligono[3] = i*4+3;
        
        glDrawElements(GL_POLYGON, 4,   GL_UNSIGNED_INT, poligono);
    }
    
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    
    
}

void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
    glRasterPos3f(x,y,z);
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void showInformacao(){
    glDisable(GL_LIGHTING);
    glColor4f(0.0,1.0,0.0,1);
    desenhaTexto(texto,-1000,1000,-600);
    sprintf(texto, "%d - Luz esfera esquerda 'j' ou 'J'  ", ligaEsferaEsq);
    desenhaTexto(texto,-1000,1000,-750);
    sprintf(texto, "%d - Luz esfera direita  'k' ou 'K'  ", ligaEsferaDir);
    desenhaTexto(texto,-1000,1000,-900);
    sprintf(texto, "Luz natural(sol)    'h' ou 'H'  ");
    
    
    
    glEnable(GL_LIGHTING);
}

void showParticulas(Particle *particula, int sistema) {
    int i;
    int numero;
    
    numero=(int) (frand()*10.0);
    glEnable(GL_TEXTURE_2D);
    for (i=0; i<MAX_PARTICULAS; i++)
    {
        glBindTexture(GL_TEXTURE_2D,texturaParticula[0]);
        glColor4f(1,1,1, particula[i].life);
        glBegin(GL_QUADS);
        glTexCoord2d(0,0); glVertex3f(particula[i].x -particula[i].size, particula[i].y -particula[i].size, particula[i].z);
        glTexCoord2d(1,0); glVertex3f(particula[i].x +particula[i].size, particula[i].y -particula[i].size, particula[i].z);
        glTexCoord2d(1,1); glVertex3f(particula[i].x +particula[i].size, particula[i].y +particula[i].size, particula[i].z);
        glTexCoord2d(0,1); glVertex3f(particula[i].x -particula[i].size, particula[i].y +particula[i].size, particula[i].z);
        glEnd();
        particula[i].x += particula[i].vx;
        particula[i].y += particula[i].vy;
        particula[i].z += particula[i].vz;
        particula[i].vx += particula[i].ax;
        particula[i].vy += particula[i].ay;
        particula[i].vz += particula[i].az;
        particula[i].life -= particula[i].fade;
        
    }
    glDisable(GL_TEXTURE_2D);
}



void display(void){
    
    //================================================================= APaga ecran/profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    //**********************VIEW PORT1***********************************************
    //================================================================= NAO MOFIFICAR
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (0, hScreen/4, wScreen/6, hScreen/5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 5,0, 0,0,0, 0, 0, -1);
    //================================================================= NAO MOFIFICAR
    
    //…………………………………………………………………………………………………………………………………………………………Objectos/modelos
    drawChao();
    
    drawCorrimaoDireito();
    drawCorrimaoEsquerdo();
    DrawCartasTopo();
    DrawSuperficieTopo();
    DrawEsfera();
    drawOutDoor();
    DrawPasseio();
    DrawEstrada();
    drawScene();
    showInformacao();
    //**********************VIEW PORT2***********************************************
    glEnable(GL_LIGHTING);
    glViewport (wScreen/5, 0, 0.75*wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angPersp, (float)wScreen/hScreen, 0.1, 3*zC);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
    
    //…………………………………………………………………………………………………………………………………………………………Objectos/modelos
    iniciaLuz();
    showParticulas(particula1, 1);
    showParticulas(particula2, 1);
    showParticulas(particula3, 1);
    showParticulas(particula4, 1);
    showParticulas(particula5, 1);
    drawSkySphere();
    drawChao();
    
    DrawCartasTopo();
    DrawSuperficieTopo();
    DrawEsfera();
    drawOutDoor();
    DrawPasseio();
    DrawEstrada();
    drawCorrimaoDireito();
    drawCorrimaoEsquerdo();
    drawScene();
    
    if (ligaEsferaDir) glEnable(GL_LIGHT0);
    else glDisable(GL_LIGHT0);
    
    if (ligaEsferaEsq) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);
    
    
    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
    glutSwapBuffers();
}

void updateVisao(){
    
    obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
    obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
    glutPostRedisplay();
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
    switch (key) {
            
            //ligar luz
        case 'j':
        case 'J':
            ligaEsferaDir=!ligaEsferaDir;
            glutPostRedisplay();
            break;
            
        case 'k':
        case 'K':
            ligaEsferaEsq=!ligaEsferaEsq;
            glutPostRedisplay();
            break;
            
        case 'l':
        case 'L':
            ligaEsferaEsq=!ligaEsferaEsq;
            ligaEsferaDir=!ligaEsferaDir;
            glutPostRedisplay();
            break;
            
        case 'h':
        case 'H':
            noite = !noite;
            
            if (noite)
            {
                luzGlobal[0] = 0.9;
                luzGlobal[1] = 0.9;
                luzGlobal[2] = 0.9;
            }
            
            else
            {
                luzGlobal[0] = intensidade;
                luzGlobal[1] = intensidade;
                luzGlobal[2] = intensidade;
            }
            
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobal);
            glutPostRedisplay();
            break;
            //--------------------------- Angulo da perspectiva
        case 'z': case 'Z':
            angPersp=angPersp+3;
            if (angPersp>170) angPersp=170;
            glutPostRedisplay();
            break;
            
        case 'x': case 'X':
            angPersp=angPersp-3;
            if (angPersp<1) angPersp=1;
            glutPostRedisplay();
            break;
            
            //--------------------------- Altura observador
        case 'q': case 'Q':
            obsPini[1]=obsPini[1]+1;
            glutPostRedisplay();
            break;
            
        case 'a': case 'A':
            obsPini[1]=obsPini[1]-1;
            glutPostRedisplay();
            break;
          
        case 'E':  case 'e':
            iniParticulas(particula1,-400.0,500.0);
            iniParticulas(particula2,400.0,500.0);
            iniParticulas(particula3,-250.0,600.0);
            iniParticulas(particula4,250.0,600.0);
            iniParticulas(particula4,0.0,500.0);
            break;
            //--------------------------- Escape
        case 27:
            exit(0);
            break;
            
            
        
            
    }
}



void teclasNotAscii(int key, int x, int y)
{
    //----------------------------------- moivimento observador
    if(key == GLUT_KEY_UP) {
        obsPini[0]=obsPini[0]+ 40 *incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]- 40 *incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_DOWN) {
        obsPini[0]=obsPini[0]- 40 *incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]+ 40 *incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_LEFT) {
        aVisao = (aVisao + 0.1) ;
    }
    if(key == GLUT_KEY_RIGHT) {
        aVisao = (aVisao - 0.1) ;
    }
    updateVisao();
}

void idle(void){
    
    glutPostRedisplay();
    
}



void Timer(int value)
{
    iniParticulas(particula1,-400.0,500.0);
    iniParticulas(particula2,400.0,500.0);
    iniParticulas(particula3,-250.0,600.0);
    iniParticulas(particula4,250.0,600.0);
    iniParticulas(particula5,0.0,500.0);
    glutPostRedisplay();
    glutTimerFunc(msec,Timer, 1);
}


//======================================================= MAIN
int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (300, 100);
    glutCreateWindow ("Rui Rocha| Observador:'SETAS' esquerda-> roda esquerda| direita-> roda direita| 'a'->aumentar inclinacao|'q'->baixar inclinacao|'x'->avacar|'z'->recuar");
    
    inicializa();
    glutSpecialFunc(teclasNotAscii);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutTimerFunc(1000,actualizaTextura,1);
    glutTimerFunc(msec, Timer, 1);
    glutMainLoop();
    
    return 0;
}

