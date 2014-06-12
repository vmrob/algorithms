#include <boost/multi_array.hpp>

#include <iostream>

template <typename WeightType>
class Graph {
public:
	Graph(size_t verticies = 0)
		: _adjacencyMatrix(boost::extents[verticies][verticies])
	{
		// init only
	}

	void addEdge(size_t v1, size_t v2, size_t weight) {
		size_t maxVert = std::max(v1, v2);
		if (size() <= maxVert) {
			resize(maxVert);
		}

		_adjacencyMatrix[v1][v2] = weight;
	}

	void addBidirectionalEdge(size_t v1, size_t v2, size_t weight) {
		addEdge(v1, v2, weight);
		addEdge(v2, v1, weight);
	}

	size_t edgeWeight(size_t v1, size_t v2) const {
		return _adjacencyMatrix[v1][v2];
	}

	void resize(size_t newSize) {
		_adjacencyMatrix.resize(boost::extents[newSize][newSize]);
	}

	// returns number of verticies
	inline size_t size() const { return _adjacencyMatrix.shape()[0]; }

	friend std::ostream& operator<< (std::ostream &out, const Graph<WeightType>& graph) {
		size_t size = graph.size();

		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				out << graph.edgeWeight(i, j);
				if (j < size - 1) {
 					out << " ";
				}
			}
			out << std::endl;
		}

		return out;
	}

private:
	boost::multi_array<WeightType, 2> _adjacencyMatrix;
};