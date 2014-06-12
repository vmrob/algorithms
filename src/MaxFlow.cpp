#include "MaxFlow.h"

// true on path complete, false if no path from current.back to v1 was found
static bool _FindPath(const Graph<int>& graph, Graph<int>::Path& current, size_t v1) {
	assert(!current.empty());

	size_t start = current.back();

	if (start == v1) {
		return true;
	}

	size_t verticies = graph.size();
	for (size_t i = 0; i < verticies; ++i) {
		if (graph.edgeWeight(start, i) <= 0) {
			continue;
		}

		auto it = std::find(current.begin(), current.end(), i);
		if (it != current.end()) {
			// vertex is already in path
			continue;
		}

		current.push_back(i);
		if (_FindPath(graph, current, v1)) {
			return true;
		}
		current.pop_back();
	}

	return false;
}

Graph<int>::Path FindPath(const Graph<int>& graph, size_t v0, size_t v1) {
	Graph<int>::Path p = {v0};
	
	if (!_FindPath(graph, p, v1)) {
		p.pop_back();
	}

	return p;
}

int FordFulkersonMaxFlow(const Graph<int>& graph, size_t start, size_t end) {
	Graph<int> residual = graph;
	Graph<int> flow(graph.size());

	Graph<int>::Path p = FindPath(residual, 0, residual.size() - 1);

	while (!p.empty()) {
		size_t minEdgeWeight = graph.minEdgeWeight(p);

		assert(p.size() > 1);
		for (size_t i = 1; i < p.size(); ++i) {
			flow.changeWeight(p[i - 1], p[i], minEdgeWeight);
			flow.changeWeight(p[i], p[i - 1], minEdgeWeight);
		}

		for (size_t i = 0; i < graph.size(); ++i) {
			for (size_t j = 0; j < graph.size(); ++j) {
				residual.changeWeight(i, j, graph.edgeWeight(i, j) - flow.edgeWeight(i, j));
			}
		}
		p = FindPath(residual, 0, residual.size() - 1);
	}

	return flow.edgeSum(graph.size() - 1);
}