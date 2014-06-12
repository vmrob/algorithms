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
	};

	TEST("Basic Graphs") {
		{
			Graph<int> g;

			g.addBidirectionalEdge(0, 1, 1);

			CHECK(FordFulkersonMaxFlow(g, 0, 1) == 1);
		}
	};

};