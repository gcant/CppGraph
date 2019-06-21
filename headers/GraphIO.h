#ifndef GRAPHIO_HEADER 
#define GRAPHIO_HEADER

#include "Graph.h"
#include "DiGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

void write_edgelist(Graph G, std::string f_name){
	std::ofstream out_file(f_name);
	for (int i : G.nodes()){
		for (int j : G.neighbors(i)){
			if (i<=j) out_file << i << " " << j << '\n';
		}
	}
	out_file.close();
}

void write_edgelist(DiGraph G, std::string f_name){
	std::ofstream out_file(f_name);
	for (int i : G.nodes()){
		for (int j : G.successors(i)){
			out_file << i << " " << j << '\n';
		}
	}
	out_file.close();
}

Graph read_edgelist(std::string f_name){

	std::ifstream in_file(f_name);
	Graph G;
	int i,j;

	while (in_file >> i >> j){
		G.add_edge(i,j);
		in_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	in_file.close();

	return G;
}

DiGraph read_directed_edgelist(std::string f_name){

	std::ifstream in_file(f_name);
	DiGraph G;
	int i,j;

	while (in_file >> i >> j){
		G.add_edge(i,j);
		in_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	in_file.close();

	return G;
}

#endif
