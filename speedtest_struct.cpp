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
 * this version takes in two Particles
 * returns a pointer to an array of doubles
 */
double* force( Particle a, Particle b ) {
	static double forces[3];
	double diffX = a.position[0] - b.position[0];
	double diffY = a.position[1] - b.position[1];
	double diffZ = a.position[2] - b.position[2];
 	double distance = sqrt(pow(diffX, 2.0) + pow(diffY, 2.0) + pow(diffZ, 2.0));
 	double unitX = diffX / distance;
 	double unitY = diffY / distance;
 	double unitZ = diffZ / distance;
 	double force = -1 * (G * a.mass * b.mass) / pow(distance, 2.0);
	forces[0] = force * unitX;
	forces[1] = force * unitY;
	forces[2] = force * unitZ;
	return forces;
}

int main(int argc, char **argv) {
	cout.precision(16);

	if (argc < 2) {
		cout << "Usage: speedtest_struct <input filename> " << endl;
		return -1;
	} 

	ifstream inputFile(argv[1]);
	int numParticles;
	inputFile >> numParticles;

	cout << "Pulling " << numParticles << " particles from " << argv[1] << endl;


	/*
	 * This version stores data in an array of Particle structures
	 */
	Particle particles[numParticles];

	for (int i = 0; i < numParticles; i++) {
		inputFile >> particles[i].mass;
		inputFile >> particles[i].radius;
		for (int j = 0; j < 3; j++) {
			inputFile >> particles[i].position[j];
		}
		for (int j = 0; j < 3; j++) {
			inputFile >> particles[i].velocity[j];
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
				forces = force(particles[i], particles[j]);
				/*cout << "(" << i << "," << j << ").x = " << forces[0] << endl;
				cout << "(" << i << "," << j << ").y = " << forces[1] << endl;
				cout << "(" << i << "," << j << ").z = " << forces[2] << endl;*/
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
