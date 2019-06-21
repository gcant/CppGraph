#ifndef RANDOMGRAPHS_HEADER
#define RANDOMGRAPHS_HEADER

#include "Graph.h"
#include <vector>
#include <math.h>

extern std::default_random_engine generator;

Graph ErdosRenyi(int n, int m){
	// Erdos-Renyi random graph G(n,m)

	Graph G;
	std::uniform_int_distribution<int> randint(0,n-1);

	for (int i=0; i<n; ++i) G.add_node(i);

	while (G.number_of_edges()<m){
		int i = randint(generator);
		int j = randint(generator);
		if (i!=j) G.add_edge(i,j);
	}

	return G;
}

Graph PreferentialAttachment(int n){
	// Simple preferential attachment model.
	// Each node brings one new edge and attaches
	// proportional to degree.

	Graph G;
	std::uniform_real_distribution<double> rand(0.0,1.0);
	std::vector<int> stubs;

	G.add_edge(0,1);
	stubs.push_back(0); stubs.push_back(1);

	for (int i=2; i<n; ++i){
		int j = stubs[(int)(rand(generator)*i)];
		G.add_edge(i,j);
		stubs.push_back(i); stubs.push_back(j);
	}

	return G;
}

std::pair<Graph,std::vector<int>> SymmetricSBM(int n, int c,
		double p_in, double p_out){
	Graph G;
	std::vector<int> g;
	std::vector<double> pi;

	std::uniform_real_distribution<double> rand(0.0,1.0);

	for (int r=0; r<c; ++r) pi.push_back(1.0/c);
	std::discrete_distribution<int> category(pi.begin(), pi.end());

	for (int i=0; i<n; ++i){
		G.add_node(i);
		g.push_back( category(generator) );
	}

	for (int i=0; i<n; ++i){
		for (int j=i+1; j<n; ++j){
			if ((g[i]==g[j]) && (rand(generator)<p_in)) G.add_edge(i,j);
			else if ((g[i]!=g[j]) && (rand(generator)<p_out)) G.add_edge(i,j);
		}
	}

	std::pair<Graph,std::vector<int>> out(G,g);
	return out;
}

Graph NormalNetwork(int n, double t, double rho){
	// Network created from thresholding a multivariate normal
	// distribution, as descibed in Cantwell et al.,
	// Thresholding normally distributed data creates complex
	// networks.

	Graph G;
	double t_prime = t / sqrt(1.0-2.0*rho);
	double sqrt_rho_over = sqrt( rho / (1.0-2.0*rho) );

	std::normal_distribution<double> normal(0.0,1.0);

	std::vector<double> z;
	for (int i=0; i<n; ++i){
		z.push_back( normal(generator) * sqrt_rho_over );
		G.add_node(i);
	}

	for (int i=0; i<n; ++i){
		for (int j=i+1; j<n; j++){
			if ( normal(generator) > t_prime - z[i] - z[j])
				G.add_edge(i,j);
		}
	}

	return G;
}

Graph ExpectedDegree(std::vector<double> theta){
	Graph G;
	int n = theta.size();
	double twom = 0;

	std::uniform_real_distribution<double> rand(0.0,1.0);

	for (int i=0; i<n; ++i){
		G.add_node(i);
		twom += theta[i];
	}

	for (int i=0; i<n; ++i){
		for (int j=i+1; j<n; ++j){
			if (rand(generator) < theta[i]*theta[j]/twom) G.add_edge(i,j);
		}
	}

	return G;
}

Graph ExpectedDegree(std::vector<int> theta){
	std::vector<double> theta_double;
	for (int i=0; i<theta.size(); ++i) theta_double.push_back( (double)theta[i] );
	return ExpectedDegree(theta_double);
}

#endif
