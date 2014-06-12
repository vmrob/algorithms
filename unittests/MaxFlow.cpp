#include <tinytest.h>

#include "../src/MaxFlow.h"

TEST_SUITE("Max Flow") {

	TEST("Paths") {
		{
			Graph<int> g;
		
			g.addBidirectionalEdge(0, 1, 1);
			g.addBidirectionalEdge(1, 2, 2);
			g.addBidirectionalEdge(2, 3, 3);
			g.addBidirectionalEdge(3, 4, 4);
			g.addBidirectionalEdge(4, 0, 5);
	
			auto path = FindPath(g, 0, 4);
	
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

			auto path = FindPath(g, 0, 2);

			CHECK(path == Graph<int>::Path({0, 1, 2}));
		}
		{
			Graph<int> g;

			g.addBidirectionalEdge(0, 2, 1);
			g.addBidirectionalEdge(2, 1, 1);
			g.addBidirectionalEdge(1, 3, 1);

			auto path = FindPath(g, 0, 3);

			CHECK(path == Graph<int>::Path({0, 2, 1, 3}));
		}
	};

	TEST("Basic Graphs") {
		{
			Graph<int> g;

			g.addBidirectionalEdge(0, 1, 1);

			CHECK(FordFulkersonMaxFlow(g, 0, 1) == 1);
		}
		{
			Graph<int> g;

			g.addBidirectionalEdge(0, 1, 1);
			g.addBidirectionalEdge(1, 2, 2);

			CHECK(FordFulkersonMaxFlow(g, 0, 2) == 1);
		}
		{
			Graph<int> g;

			g.addBidirectionalEdge(0, 1, 1);
			g.addBidirectionalEdge(1, 2, 2);
			g.addBidirectionalEdge(2, 3, 3);
			g.addBidirectionalEdge(3, 4, 4);
			g.addBidirectionalEdge(4, 0, 5);

			CHECK(FordFulkersonMaxFlow(g, 0, 4) == 6);
		}
		{
			// from http://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm
			// "integral example"
			Graph<int> g;

			g.addBidirectionalEdge(0, 1, 100);
			g.addBidirectionalEdge(1, 2, 1);
			g.addBidirectionalEdge(2, 3, 100);

			g.addBidirectionalEdge(0, 2, 100);
			g.addBidirectionalEdge(1, 3, 100);

			CHECK(FordFulkersonMaxFlow(g, 0, 3) == 200);
		}
	};

};