#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <tuple>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ------------------------------------------------

#define SCREEN_WIDTH  glutGet( GLUT_SCREEN_WIDTH  )
#define SCREEN_HEIGHT glutGet( GLUT_SCREEN_HEIGHT )
#define PI 3.1415927
#define INIT_W 1200
#define INIT_H 800

int windowWidth = 1200, windowHeight = 800;
GLUquadric *sphere = NULL, *cylinder = NULL, *circleObj = NULL;

double orthoNum = 300;
double perspectiveEye = 90.0;
double perspectiveNear = 1.5, perspectiveFar = 400.0;

enum KEYBOARD
{
    ESC = 27, SPACE = 32
};

enum PERSPECTIVE
{
    OrthoX, OrthoY, OrthoZ,
    FIRST_VIEW, THIRD_VIEW, GOD_VIEW,
    EACH_VIEW, MY_VIEW
};

int viewing = MY_VIEW;