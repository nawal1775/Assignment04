#include "Simulation.h"
using namespace std;

int main(int argc, const char * argv[])
{
    Simulation sim(argv[1]);
    sim.Simulate();
    sim.ComputeStatistics();
    return 0;
}