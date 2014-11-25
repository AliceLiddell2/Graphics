
#pragma once

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <Eigen\Dense> 

#define RAND_GRANULATION (10000)

namespace MyGL
{
	class Math // abstract, static 
	{
		Math() // never instantiate 
		{
			srand(time(0)); 
		}

		inline static Math& Instance()   
		{
			static Math s_Instance; 
			return s_Instance;
		}

		inline void Touch() const 
		{
			/*
			static int n = 0;
			n++;
			n = n % 100;
			*/
		}

	public:
		// -----------------------------------------------------------------------------
		// Eigen linear algebra manipulations 

		inline static Matrix4d TranslationMatrix(double dx, double dy, double dz) 
		{
			Matrix4d m = Matrix4d::Identity(); 
			m(0,3) = dx;
			m(1,3) = dy;
			m(2,3) = dz;
			// std::cout << "Here is the matrix m:\n" << m << std::endl;
			return m;
		}

		inline static Matrix4d TranslationMatrix(const Vector3d& t) 
		{
			Matrix4d m = Matrix4d::Identity(); 
			m(0,3) = t[0];
			m(1,3) = t[1];
			m(2,3) = t[2];
			return m;
		}

		inline static Matrix4d RotationMatrixX(double alphaDgr) 
		{
			double alpha = (alphaDgr * M_PI) / 180; 
			// 
			double cos_a = cos(alpha); 
			double sin_a = sin(alpha); 
			// 
			Matrix4d m = Matrix4d::Identity(); 
			m(1,1) = cos_a;
			m(1,2) = -sin_a;
			m(2,1) = sin_a;
			m(2,2) = cos_a;
			return m;
		}

		inline static Matrix4d RotationMatrixY(double alphaDgr) 
		{
			double alpha = (alphaDgr * M_PI) / 180; 
			// 
			double cos_a = cos(alpha); 
			double sin_a = sin(alpha); 
			// 
			Matrix4d m = Matrix4d::Identity(); 
			m(0,0) = cos_a;
			m(0,2) = -sin_a;
			m(2,0) = sin_a;
			m(2,2) = cos_a;
			return m;
		}

		inline static Matrix4d RotationMatrixZ(double alphaDgr) 
		{
			double alpha = (alphaDgr * M_PI) / 180; 
			// 
			double cos_a = cos(alpha); 
			double sin_a = sin(alpha); 
			// 
			Matrix4d m = Matrix4d::Identity(); 
			m(0,0) = cos_a;
			m(0,1) = -sin_a;
			m(1,0) = sin_a;
			m(1,1) = cos_a;
			return m;
		}

		// -----------------------------------------------------------------------------
		// Random values 

		inline static int RandomInt(int M)
		{
			Instance().Touch();
			//
			return rand() % M;
		}

		inline static double Random01()
		{
			double x = double(RandomInt(RAND_GRANULATION)) / RAND_GRANULATION; 
			double y = double(RandomInt(RAND_GRANULATION)) / RAND_GRANULATION; 
			x += .33 * sin(-M_PI + 2*M_PI*y);
			while (x < 0) x += 1;
			while (x >= 1) x -= 1;
			return x; 
		}

		inline static double RandomAngleDgr()
		{
			double a = Random01() * 2 * M_PI; 
			return a; 
		}

		inline static double RandomAngle()
		{
			return RandomAngleDgr(); 
		}

		inline static Vector3d RandomCircleVector(double r) 
		{
			Vector3d v;
			double a = RandomAngleDgr(); 
			v[0] = r * cos(a); 
			v[1] = r * sin(a); 
			v[2] = 0; 
			return v; 
		}

		inline static Vector3d RandomDiskVector(double r) 
		{
			Vector3d v;
			double a = RandomAngleDgr(); 
			double t = Random01();
			double R = sqrt(t) * r;
			v[0] = R * cos(a); 
			v[1] = R * sin(a); 
			v[2] = 0; 
			return v; 
		}

		inline static Vector3d RandomSphericalVector(double r) 
		{
			Vector3d v;
			double a = RandomAngleDgr(); 
			double z = -1 + 2 * Random01();
			double R = r * sqrt(1 - z*z);
			v[0] = R * cos(a); 
			v[1] = R * sin(a); 
			v[2] = r * z; 
			return v; 
		}
	};

} // namespace MyGL

