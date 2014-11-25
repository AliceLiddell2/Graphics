// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>

#include <windows.h>

#include "graphics\Common.h"

#define EIGEN_DONT_ALIGN_STATICALLY
#define EIGEN_DONT_VECTORIZE 
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#include <Eigen/Dense>

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <map>
#include <fstream>

using namespace std;

#include <Eigen\Dense> 

using namespace Eigen;
