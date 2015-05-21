/*
 * This program was developed as part of an experiment to test the speed of 
 * accessing data stored in a set of arrays vs stored in an array of structures.  
 * 
 * The files in this experiement consist of:
 *   speedtest_struct.cpp 		 - runs the test using an array of structures
 *   speedtest_array.cpp  		 - runs the test using a set of arrays
 *   generateRandomParticles.cpp - generates random test data
 *
 * by Tim Dockins 2015-05-20
 * timdockins@gmail.com
 */


#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

const double G = 6.67384e-11; // 6.67384 × 10-11 m3 kg-1 s-2

struct Particle {
	double mass;
	double radius;
	double position[3];
	double velocity[3];
};

/*
 * calculates force
 * this version takes in double primitives and 
 * returns a pointer to an array of doubles
 * 
 */
double* force( double aMass,
			   double aPosX,
			   double aPosY,
			   double aPosZ,
			   double bMass,
			   double bPosX,
			   double bPosY,
			   double bPosZ) {
	static double forces[3];
	double diffX = aPosX - bPosX;
	double diffY = aPosY - bPosY;
	double diffZ = aPosZ - bPosZ;
 	double distance = sqrt(pow(diffX, 2.0) + pow(diffY, 2.0) + pow(diffZ, 2.0));
 	double unitX = diffX / distance;
 	double unitY = diffY / distance;
 	double unitZ = diffZ / distance;
 	double force = -1 * (G * aMass * bMass) / pow(distance, 2.0);
	forces[0] = force * unitX;
	forces[1] = force * unitY;
	forces[2] = force * unitZ;
	return forces;
}

int main(int argc, char **argv) {
	cout.precision(16);

	if (argc < 2) {
		cout << "Usage: speedtest_array <input filename> " << endl;
		return -1;
	} 

	ifstream inputFile(argv[1]);
	int numParticles;
	inputFile >> numParticles;
	
	cout << "Pulling " << numParticles << " particles from " << argv[1] << endl;

	double mass[numParticles];
	double radius[numParticles];
	double position[3 * numParticles];
	double velocity[3 * numParticles];


	for (int i = 0; i < numParticles; i++) {
		inputFile >> mass[i];
		inputFile >> radius[i];
		for (int j = 0; j < 3; j++) {
			inputFile >> position[3*i+j];
		}
		for (int j = 0; j < 3; j++) {
			inputFile >> velocity[3*i+j];
		}
	}

	inputFile.close();
	printf ("File closed...\n");

	// the forces function will return a pointer to an array of three doubles
	double *forces;
	float sum = 0.0;

	printf ("Running experiment for 35 epochs.\n");
	for (int epoch = 0; epoch < 35; epoch++) {

		clock_t t;
		int f;
		t = clock();  // we're going to count the clock ticks

		// this loop calls the forces function for each permutation of particle pairs
		// skipping same particle comparisons, and only doing them in one direction.
		// i.e. particle 1 to particle 2, but not particle 2 to particle 1 because
		// that's just the same force only inverse (* -1).

		for (int i = 1; i < numParticles; i++ ) {
			for (int j = 0; j < i; j++) {
				forces = force(mass[i], position[i], position[i+1], position[i+2],
							   mass[j], position[j], position[j+1], position[j+2]);
				// cout << "(" << i << "," << j << ").x = " << forces[0] 
				// 							 << "  y = " << forces[1]
				// 							 << "  z = " << forces[2] << endl;;
			}
		}

		t = clock() - t;
		cout << "Epoch " << epoch << " took " << t 
			 << " clicks ( " << (((float) t)/CLOCKS_PER_SEC) << " seconds)" << endl;
		sum += ((float) t)/CLOCKS_PER_SEC;
	}

	cout << "Average run time: " << (sum/35.0) << " seconds." << endl;

	return 0;

}
