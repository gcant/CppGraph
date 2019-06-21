#ifndef GRAPHMISC_HEADER 
#define GRAPHMISC_HEADER

#include <tuple>
#include <random>
#include <vector>
#include <numeric>

extern std::default_random_engine generator;

class array2d{
	private:
		std::vector<double> data;
		int dim1,dim2;
	public:
		array2d(int, int);
		double& operator()(int i, int j){return data[i*dim2+j];};
		int len(){return dim1;};
		int width(){return dim2;};
};

array2d::array2d(int n, int m){
	dim1 = n;
	dim2 = m;
	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j) data.push_back(0.0);
	}
}

std::vector<double> dirichlet(std::vector<double> &alpha){
	//generate a Dirichlet random vector

	std::vector<double> x;

	for (int i=0; i<alpha.size(); ++i){
		std::gamma_distribution<double> gamma(alpha[i],1.0);
		x.push_back( gamma(generator) );
	}

	double sum = std::accumulate(x.begin(), x.end(), 0.0);

	for (int i=0; i<x.size(); ++i) x[i] = x[i]/sum;

	return x;
}

#endif
