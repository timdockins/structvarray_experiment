# structvarray_experiment

This is the C++ code that I used to do a run-time experiment for accessing data stored in structs vs accessing data stored in arrays.  The data is a set of particles having mass, radius, 3D position vector, and 3D velocity vector - all double values.  The question is whether it is faster, in terms of data access, to store this in an array of Particle structs having mass, radius, and two 3-element arrays, or to store in four arrays of doubles.

The assumption is that some function will need to access the data of all pairs of particles to calculate the gravitational forces.  

## Intuition

My intuition about computer architecture said the following:
 - There is little difference, in terms of compiled code, in addressing arrays vs structs.
 - There is a small difference in sizing on structs, given padding, but that's not an issue here.
 - Caching will cause a small difference in access speed

## Experiment

The idea is to test the access of data for use in a calculation.  So, the following steps are performed:

1) generate text files containing data with 100, 1000, 5000, 10000, 25000, 50000 elements respectively.
2) For each size, read in the data into the target data structures.
3) Start timing the procedure.
4) Provide the data from the structure as parameters to a function that performs some calculation using those parameters.
5) Record the time it takes to perform step through the 'lower-left triangle' of the cross-product of particles to particles.
6) Perform 3 - 5 for 35 episodes and take the average time.

## Compiling and running

I compiled this code with a GNU C++ compiler.  It's what I had on my Ubuntu 13.10 laptop.  Your mileage may vary.


The files in this experiment consist of:
 *   speedtest_struct.cpp 		 - runs the test using an array of structures
 *   speedtest_array.cpp  		 - runs the test using a set of arrays
 *   generateRandomParticles.cpp - generates random test data
 

If you have 'make', simply run that.

Otherwise:

g++ -std=gnu++11 generateRandomParticles.cpp -o generate
g++ -o speedtest_array speedtest_array.cpp
g++ -o speedtest_struct speedtest_struct.cpp
 
See the code for usage.