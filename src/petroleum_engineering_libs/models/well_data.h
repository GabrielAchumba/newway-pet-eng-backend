#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <functional>
#include <map>
#include <math.h>
#include <cmath> 

using namespace std;

typedef struct _PerforationPosition
{
    int i;
    int j;
    int k;
} PerforationPosition;

typedef struct _WellData
{
   vector<PerforationPosition> perforationPositions;
   double bottomHolePressure;
   int wellType;
   int wellControlType;
   double wellboreRadius;   

   double AverageHorizontalPermeability(double Kx, double Ky) {
        double KH = sqrt(Kx * Ky);
        return KH;
    }

double WellDrainageRadius(double _Kx, double _Ky, double Dx, double Dy) {
	double Kx = _Kx / 1000;
	double Ky = _Ky / 1000;
	double KyKxSqr2 = sqrt(Ky / Kx);
	double KyKxSqr4 = pow(Ky/Kx, 0.25);
	double KxKySqr2 = sqrt(Kx / Ky);
	double KxKySqr4 = pow(Kx/Ky, 0.25);
	double DxPow2 = pow(Dx, 2);
	double DyPow2 = pow(Dy, 2);
	double numerator = sqrt(KyKxSqr2*DxPow2 + KxKySqr2*DyPow2);

	double re = 0.28 * numerator / (KyKxSqr4 + KxKySqr4);
	return re;
}


   double ComputeWellIndex(double k, double h, double re, double viscosity, double fvf) {

        double M_PI = 3.14159265358979323846;
        return (2.0 * M_PI * k * h) / (viscosity * fvf * log(re / wellboreRadius));
    }


    double calculateFlowRate(
        double dx, double dy, double kx, double ky, double h, 
        double viscosity, double fvf, double p_res)
    {
        double re = WellDrainageRadius(kx, ky, dx, dy);

        double horizontalPermeability = AverageHorizontalPermeability(kx, ky);

        double WI = ComputeWellIndex(horizontalPermeability, h, re, viscosity, fvf);
        double flowRate = WI * (p_res - bottomHolePressure) / viscosity;

        return flowRate;
    }


    double isPeforated(
        int wellI, int wellJ, int wellK, 
        int i, int j, int k) 
    {

        bool isOpen = (i == wellI && j == wellJ && k == wellK);
        
        return isOpen;

    }


} WellData;