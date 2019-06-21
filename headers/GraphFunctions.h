#ifndef GRAPHFUNCTIONS_HEADER
#define GRAPHFUNCTIONS_HEADER

#include "Graph.h"
#include "GraphMisc.h"
#include <vector>

double transitivity(Graph const &G){
	double triangles = 0;
	double two_stars = 0;
	for (int i : G.nodes()){
		for (int j : G.neighbors(i)){
			for (int k : G.neighbors(i)){
				if (j<k){
					two_stars += 1;
					if (G.has_edge(j,k)) triangles += 1;
				}
			}
		}
	}
	return triangles / two_stars;
}

array2d mixing_matrix(Graph const &G, std::vector<int> const &g, int c){

	array2d M(c,c);

	for (int i : G.nodes()){
		for (int j : G.neighbors(i)) M(g[i],g[j]) += 1;
	}

	return M;
}

std::vector<int> degree_sequence(Graph const &G){
	std::vector<int> k;
	for (int node : G.nodes()) k.push_back(G.degree(node));
	return k;
}


#endif
