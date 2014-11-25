#pragma once

// Basics 

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <time.h>

// STL

#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>

// OpenGL

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>

// Eigen

#include <Eigen\Dense> 

// Namespaces

using namespace std;
using namespace Eigen;

// ----
// Common math definitions

typedef Vector4d Plane; 

// ----
// infrastructure 

#include "graphics/Exception.h"
#include "graphics/Color.h"
#include "graphics/Math.h"
