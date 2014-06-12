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

	typedef std::vector<size_t> Path;

	// empty path means none was found
	Path findPath(size_t v0, size_t v1) {
		Path p = {v0};
		
		if (!_findPath(p, v1)) {
			p.pop_back();
		}

		return p;
	}

private:
	boost::multi_array<WeightType, 2> _adjacencyMatrix;

	// true on path complete, false if no path from p.back to v1 was found
	bool _findPath(Path& current, size_t v1) {
		assert(!current.empty());

		size_t start = current.back();

		if (start == v1) {
			return true;
		}

		size_t verticies = size();
		for (size_t i = 0; i < verticies; ++i) {
			if (_adjacencyMatrix[start][i] == 0) {
				// edge doesn't exist
				// TODO: use a different list for edges? Allow 0 weight edges?
				continue;
			}

			auto it = std::find(current.begin(), current.end(), i);
			if (it != current.end()) {
				// vertex is already in path
				continue;
			}

			current.push_back(i);
			if (_findPath(current, v1)) {
				return true;
			}
			current.pop_back();
		}

		return false;
	}
};