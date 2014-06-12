#pragma once

#include "Graph.h"

// empty path means none was found
Graph<int>::Path FindPath(const Graph<int>& graph, size_t v0, size_t v1);

int FordFulkersonMaxFlow(const Graph<int>& graph, size_t start, size_t end);