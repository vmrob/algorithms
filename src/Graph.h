#pragma once

#include <boost/multi_array.hpp>

#include <iostream>
#include <vector>
#include <cassert>

template <typename WeightType>
class Graph {
public:
	Graph(size_t verticies = 0)
		: _adjacencyMatrix(boost::extents[verticies][verticies])
	{
		// init only
	}

	void addEdge(size_t v0, size_t v1, WeightType weight) {
		assert(weight != 0);

		size_t maxVert = std::max(v0, v1);
		if (size() <= maxVert) {
			resize(maxVert + 1);
		}

		_adjacencyMatrix[v0][v1] = weight;
	}

	void addBidirectionalEdge(size_t v0, size_t v1, WeightType weight) {
		addEdge(v0, v1, weight);
		addEdge(v1, v0, weight);
	}

	size_t edgeWeight(size_t v0, size_t v1) const {
		return _adjacencyMatrix[v0][v1];
	}

	size_t edgeSum(size_t vertex) const {
		size_t sum = 0;
		for (size_t i = 0; i < size(); ++i) {
			sum += _adjacencyMatrix[vertex][i];
		}
		return sum;
	}

	typedef std::vector<size_t> Path;

	size_t minEdgeWeight(const Path& path) const {
		assert(path.size() > 1);

		WeightType minWeight = _adjacencyMatrix[path[0]][path[1]];

		for(size_t i = 2; i < path.size(); ++i) {
			auto weight = edgeWeight(path[i - 1], path[i]);
			if (weight < minWeight) {
				minWeight = weight;
			}
		}

		return minWeight;
	}

	void changeWeight(size_t v0, size_t v1, WeightType weight) {
		assert(size() > std::max(v0, v1));
		_adjacencyMatrix[v0][v1] = weight;
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