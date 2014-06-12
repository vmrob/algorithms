#include <tinytest.h>

#include <sstream>

#include "../src/Graph.h"

TEST_SUITE("Graph") {
	
	TEST("Edges") {

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

	TEST("Bidirectional Edges") {

		Graph<int> g(5);

		g.addBidirectionalEdge(0, 1, 1);
		g.addBidirectionalEdge(1, 2, 2);
		g.addBidirectionalEdge(2, 3, 3);
		g.addBidirectionalEdge(3, 4, 4);
		g.addBidirectionalEdge(4, 0, 5);

		CHECK(g.edgeWeight(0, 1) == 1);
		CHECK(g.edgeWeight(1, 2) == 2);
		CHECK(g.edgeWeight(2, 3) == 3);
		CHECK(g.edgeWeight(3, 4) == 4);
		CHECK(g.edgeWeight(4, 0) == 5);

		CHECK(g.edgeWeight(1, 0) == 1);
		CHECK(g.edgeWeight(2, 1) == 2);
		CHECK(g.edgeWeight(3, 2) == 3);
		CHECK(g.edgeWeight(4, 3) == 4);
		CHECK(g.edgeWeight(0, 4) == 5);

		std::stringstream ss;

		ss << g;

		CHECK(ss.str() ==
			"0 1 0 0 5\n"
			"1 0 2 0 0\n"
			"0 2 0 3 0\n"
			"0 0 3 0 4\n"
			"5 0 0 4 0\n"
		);

	};

	TEST("Paths") {
		{
			Graph<int> g;
		
			g.addBidirectionalEdge(0, 1, 1);
			g.addBidirectionalEdge(1, 2, 2);
			g.addBidirectionalEdge(2, 3, 3);
			g.addBidirectionalEdge(3, 4, 4);
			g.addBidirectionalEdge(4, 0, 5);
	
			auto path = g.findPath(0, 4);
	
			CHECK(path.size() > 0);
	
			CHECK( false
				|| path == Graph<int>::Path({0, 1, 2, 3, 4})
				|| path == Graph<int>::Path({0, 4})
			);
		}

		{
			Graph<int> g;

			g.addBidirectionalEdge(0, 1, 1);
			g.addBidirectionalEdge(1, 2, 2);

			auto path = g.findPath(0, 2);

			CHECK(path == Graph<int>::Path({0, 1, 2}));
		}
	};

	TEST("Change Weights") {
		Graph<int> g;
		
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

		g.changeWeight(0, 1, 2);

		CHECK(g.edgeWeight(0, 1) == 2);
	};

};