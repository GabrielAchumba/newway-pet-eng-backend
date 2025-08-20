#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const int NX = 10, NY = 10, NZ = 3;
const double DX = 10.0, DY = 10.0, DZ = 1.0;
const double DT = 0.001;
const int MAX_TIME_STEPS = 100;

// Rock and fluid properties
double porosity = 0.2;
double permeability = 100e-15; // m^2
double viscosityOil = 1e-3;
double viscosityWater = 0.5e-3;
double viscosityGas = 0.02e-3;

// 3D field represented as 1D vector
inline int index(int k, int j, int i) {
    return k * NY * NX + j * NX + i;
}

vector<double> pressureOil(NX * NY * NZ, 20e6);
vector<double> pressureWater(NX * NY * NZ, 20e6);
vector<double> pressureGas(NX * NY * NZ, 20e6);

vector<double> saturationOil(NX * NY * NZ, 0.7);
vector<double> saturationWater(NX * NY * NZ, 0.2);
vector<double> saturationGas(NX * NY * NZ, 0.1);

void InitializeReservoir() {
    // Already initialized via constructors above
}

void ApplyBoundaryConditions() {
    // Aquifer influx at bottom (k = 0)
    for (int j = 0; j < NY; ++j)
        for (int i = 0; i < NX; ++i)
            pressureWater[index(0, j, i)] = 22e6;
}

void ApplyWells() {
    // Injector: top-left corner at top layer
    pressureWater[index(NZ - 1, 0, 0)] = 25e6;
    saturationWater[index(NZ - 1, 0, 0)] = 1.0;
    saturationOil[index(NZ - 1, 0, 0)] = 0.0;
    saturationGas[index(NZ - 1, 0, 0)] = 0.0;

    // Producer: bottom-right corner at bottom layer
    pressureOil[index(0, NY - 1, NX - 1)] = 15e6;
    saturationOil[index(0, NY - 1, NX - 1)] = 0.0;
    saturationWater[index(0, NY - 1, NX - 1)] = 0.0;
    saturationGas[index(0, NY - 1, NX - 1)] = 1.0;
}

double ComputeDivergence(const vector<double>& pressure, double mu, int k, int j, int i) {
    double dPx = (pressure[index(k, j, i + 1)] - 2 * pressure[index(k, j, i)] + pressure[index(k, j, i - 1)]) / (DX * DX);
    double dPy = (pressure[index(k, j + 1, i)] - 2 * pressure[index(k, j, i)] + pressure[index(k, j - 1, i)]) / (DY * DY);
    double dPz = (pressure[index(k + 1, j, i)] - 2 * pressure[index(k, j, i)] + pressure[index(k - 1, j, i)]) / (DZ * DZ);

    return permeability / mu * (dPx + dPy + dPz);
}

void UpdatePressuresAndSaturations() {
    for (int k = 1; k < NZ - 1; ++k)
        for (int j = 1; j < NY - 1; ++j)
            for (int i = 1; i < NX - 1; ++i) {
                int idx = index(k, j, i);

                double divOil = ComputeDivergence(pressureOil, viscosityOil, k, j, i);
                double divWater = ComputeDivergence(pressureWater, viscosityWater, k, j, i);
                double divGas = ComputeDivergence(pressureGas, viscosityGas, k, j, i);

                pressureOil[idx] += DT * divOil;
                pressureWater[idx] += DT * divWater;
                pressureGas[idx] += DT * divGas;

                double so = saturationOil[idx] + 0.001 * divOil;
                double sw = saturationWater[idx] + 0.001 * divWater;
                double sg = saturationGas[idx] + 0.001 * divGas;

                double total = max(so + sw + sg, 1e-6);
                saturationOil[idx] = so / total;
                saturationWater[idx] = sw / total;
                saturationGas[idx] = sg / total;
            }
}

void PrintMidpointState(int timeStep) {
    int i = NX / 2, j = NY / 2, k = NZ / 2;
    int idx = index(k, j, i);
    cout << fixed << setprecision(2);
    cout << "Step " << timeStep
         << " | Po: " << pressureOil[idx] / 1e6 << " MPa"
         << " | So: " << saturationOil[idx] << endl;
}

int main() {
    InitializeReservoir();

    for (int t = 0; t < MAX_TIME_STEPS; ++t) {
        ApplyBoundaryConditions();
        ApplyWells();
        UpdatePressuresAndSaturations();
        if (t % 10 == 0)
            PrintMidpointState(t);
    }

    cout << "Simulation complete." << endl;
    return 0;
}
