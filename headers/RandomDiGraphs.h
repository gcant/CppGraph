#ifndef RANDOMDIGRAPHS_HEADER
#define RANDOMDIGRAPHS_HEADER

#include "DiGraph.h"
#include "GraphMisc.h"
#include <vector>
#include <numeric>

extern std::default_random_engine generator;


std::pair<DiGraph,std::vector<int>> SymmetricDirichletModel(int n, int c,
		double theta, double alpha){

	DiGraph G;
	std::vector<int> g;
	std::vector<double> pi;
	std::vector<double> alpha_vector;
	std::vector<double> group_counts;

	std::uniform_real_distribution<double> rand(0.0,1.0);

	for (int r=0; r<c; ++r) pi.push_back(1.0/c);
	std::discrete_distribution<int> category(pi.begin(), pi.end());
	for (int r=0; r<c; ++r) alpha_vector.push_back(alpha);
	for (int r=0; r<c; ++r) group_counts.push_back(0);

	for (int i=0; i<n; ++i){
		G.add_node(i);
		g.push_back( category(generator) );
		group_counts[g[i]] += 1;
	}

	for (int i=0; i<n; ++i){
		std::vector<double> x = dirichlet(alpha_vector);
		for (int j=0; j<n; j++){
			if ((i!=j) && (rand(generator) < theta*x[g[j]]/group_counts[g[j]]))
				G.add_edge(i,j);
		}
	}

	std::pair<DiGraph,std::vector<int>> out(G,g);

	return out;
};


#endif
