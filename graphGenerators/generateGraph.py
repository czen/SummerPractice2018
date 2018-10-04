import numpy
import networkx as nx

# Graph generators:
# https://networkx.github.io/documentation/networkx-1.10/reference/generators.html
G = nx.random_regular_graph(400,1000)
m = nx.to_numpy_matrix(G)
a = numpy.asarray(m)
numpy.savetxt("graph.csv", a, fmt='%i', delimiter=",")