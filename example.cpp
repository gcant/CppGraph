#include <iostream>
#include <random>
#include "Graph.h"
#include "RandomGraphs.h"

// set the seed for random number generation
#include <chrono>
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);


int main(int argc, char* argv[]){

	int n = std::stoi(argv[1]);
	int m = std::stoi(argv[2]);

	Graph G = ErdosRenyi(n,m);

	std::cout << "Created an ER graph with " << G.number_of_nodes() <<
		" nodes and " << G.number_of_edges() << " edges." << std::endl;

	return 0;

}
