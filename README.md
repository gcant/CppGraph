# CppGraph
Header files for graph classes in C++ using the standard library.

Nodes are labelled with integers and syntax is similar to networkx.
`Graph` is for undirected graphs, `DiGraph` for directed ones.

An example is in example.cpp.
```bash
g++ -std=c++11 -I ./headers example.cpp -o example.out
./example.out 100 200
```
