#include <tinytest.h>

#include <sstream>

#include "../src/Graph.h"

TEST_SUITE("Graph") {
	
	TEST("Usage") {

		Graph<int> g(5);

		g.addEdge(0, 1, 1);
		g.addEdge(1, 2, 2);
		g.addEdge(2, 3, 3);
		g.addEdge(3, 4, 4);
		g.addEdge(4, 0, 5);

		CHECK(g.edgeWeight(0, 1) == 1);
		CHECK(g.edgeWeight(1, 2) == 2);
		CHECK(g.edgeWeight(2, 3) == 3);
		CHECK(g.edgeWeight(3, 4) == 4);
		CHECK(g.edgeWeight(4, 0) == 5);

		std::stringstream ss;

		ss << g;

		CHECK(ss.str() ==
			"0 1 0 0 0\n"
			"0 0 2 0 0\n"
			"0 0 0 3 0\n"
			"0 0 0 0 4\n"
			"5 0 0 0 0\n"
		);

	};

};