#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulationmanager.h"
#include "vec3d.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern void printMatrix(char const *desc, int m, int n, double *a, int lda);
extern void print_int_vector(char const *desc, int n, int *a);

//int main( int argc, char* argv[] ) {
int main() {
    //Run Simulation
    SimulationManager sm = SimulationManager();
    sm.setReferenceVelocity( 100.0 );
    sm.setDt( 0.1 );
    sm.setReferenceSurface( ReferenceSurface( 10.0, 10.0, 1.0) );
    LiftingSurface ls = LiftingSurface(10,1,10,2);
    ls.setFreeWake( true );
    ls.setAspectRatio( 10.0 );
    ls.setPitch( 0.0 * M_PI / 180.0 );
    ls.getHorseshoeLattice().setHasTrailers(false); 
    ls.updateLattice( );
    sm.addSurface(&ls);
    sm.setGlobalLinearVelocity( Vec3D(-100.0, 0.0, 0.0).rotate(Vec3D(0.0, 0.0, 0.0), Vec3D(0.0, 1.0, 0.0), -10.0*M_PI/180.0 ) );
    int nStep = 0;
    while ( nStep < 500 ){
        sm.step();
        nStep++; 
    }
    sm.printState(); 
    return EXIT_SUCCESS;
} 

