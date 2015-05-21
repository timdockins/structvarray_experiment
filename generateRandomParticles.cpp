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

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <random>

/*
 * compile: g++ -std=gnu++11 generateRandomParticles.cpp -o generate
 * 
 * this writes to standard out, so redirect to a file if you want it saved.
 */

using namespace std;



struct Particle {
	double mass;
	double radius;
	double position[3];
	double velocity[3];
};



int main(int argc, char **argv) {

	if (argc < 2) {
		cout << "Usage: generate <n> " << endl;
		cout << "This writes to standard out so redirect to a file if you want it saved." << endl;		
		return -1;
	} 

	int numParticles = atoi(argv[1]);

	cout << numParticles << endl;

	Particle particles[numParticles];
	default_random_engine generator;
	normal_distribution<double> massDistribution(5.0, 2.0);
	normal_distribution<double> radiusDistribution(5.0, 2.0);
	uniform_real_distribution<double> particleDistribution(0.0, 10.0);
	normal_distribution<double> velocityDistribution(0.0, 1.0);

	for (int i = 0; i < numParticles; i++) {
		//cout << "Particle: " << (i + 1) << endl;
		particles[i].mass = massDistribution(generator);
		//cout << "Mass: " << particles[i].mass << endl;
		cout << particles[i].mass << endl;
		particles[i].radius = radiusDistribution(generator);
		//cout << "Radius: " << particles[i].radius << endl;
		cout << particles[i].radius << endl;
		for (int j = 0; j < 3; j++) {
			particles[i].position[j] = particleDistribution(generator);
			//cout << "Position[ " << j << "] : " << particles[i].position[j] << endl;
			cout << particles[i].position[j] << endl;
		}
		for (int j = 0; j < 3; j++) {
			particles[i].velocity[j] = velocityDistribution(generator);
			//cout << "velocity[ " << j << "] : " <<  particles[i].velocity[j] << endl;
			cout << particles[i].velocity[j] << endl;
		}
	}

	return 0;

}
