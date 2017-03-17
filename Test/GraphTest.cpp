#include "stdafx.h"
#include "GraphTest.h"
#include <core/FileManager.h>

namespace pan{
	namespace detail{

#define rangeDistance(iteratorRange) std::distance(iteratorRange.first, iteratorRange.second)

		/**
		*	@brief tests the functionality of Graph class to insert new vertices
		*	@author Hrachya Hakobyan
		*/
		TEST_F(GraphTest, inserts){
			using namespace detail;
			Graph<Node> graph;
			ASSERT_EQ(graph.numVertices(), 0);
			ASSERT_EQ(graph.numEdges(), 0);
			const int nNodes = 100;
			for (int i = 0; i < nNodes; i++){
				auto v = graph.addVertex();
				ASSERT_EQ(graph.numVertices(), i + 1);
				ASSERT_EQ(graph.numEdges(), 0);
			}
		}

		/**
		*	@brief tests the functionality of Graph class to remove vertices
		*	@author Hrachya Hakobyan
		*/
		TEST_F(GraphTest, removes){
			using namespace detail;
			Graph<Node> graph;
			// Remove nonexistent vertices
			ASSERT_NO_THROW(graph.removeVertex(0));
			ASSERT_NO_THROW(graph.removeVertex(1));
			// Initial size
			ASSERT_EQ(graph.numVertices(), 0);
			auto v1 = graph.addVertex();
			graph.removeVertex(v1);
			ASSERT_EQ(graph.numVertices(), 0);
			// Remove twice
			ASSERT_NO_THROW(graph.removeVertex(v1));
			ASSERT_EQ(graph.numVertices(), 0);
			auto v2 = graph.addVertex();
			ASSERT_EQ(graph.numVertices(), 1);
			graph.removeVertex(v2);
			ASSERT_EQ(graph.numVertices(), 0);
			// Remove again
			ASSERT_NO_THROW(graph.removeVertex(v2));
		}

		/**
		*	@brief tests the functionality of Graph class to clear
		*	@author Hrachya Hakobyan
		*/
		TEST_F(GraphTest, clears){
			using namespace detail;
			Graph<Node> graph;
			// Clear on empty graph
			ASSERT_NO_THROW(graph.clear());
			ASSERT_EQ(graph.numVertices(), 0);
			auto v1 = graph.addVertex();
			auto v2 = graph.addVertex();
			ASSERT_EQ(graph.numVertices(), 2);
			ASSERT_EQ(graph.numEdges(), 0);
			auto edge = graph.addEdge(v1, v2);
			ASSERT_EQ(graph.numEdges(), 1);
			graph.clear();
			// Clear twice
			ASSERT_NO_THROW(graph.clear());
			ASSERT_EQ(graph.numVertices(), 0);
			ASSERT_EQ(graph.numEdges(), 0);
		}

		/**
		*	@brief tests the functionality of Graph class to remove/add edges
		*	@author Hrachya Hakobyan
		*/
		TEST_F(GraphTest, edges){
			using namespace detail;
			Graph<Node> graph;
			// Remove nonexistent edges
			ASSERT_NO_THROW(graph.removeEdge(0, 0));
			ASSERT_NO_THROW(graph.removeEdge(0, 1));
			// Add to nonexistent vertices
			ASSERT_FALSE(graph.addEdge(0, 0).second);
			ASSERT_FALSE(graph.addEdge(1, 0).second);
			ASSERT_EQ(graph.numVertices(), 0);
			ASSERT_EQ(graph.numEdges(), 0);

			auto v1 = graph.addVertex();
			ASSERT_EQ(graph.numEdges(), 0);
			// Remove edge between an existing and nonexistent vertices
			ASSERT_NO_THROW(graph.removeEdge(v1, 0));
			// Add edge with only one existing vertex
			ASSERT_FALSE(graph.addEdge(v1, 2).second);
			// Assert self loop
			ASSERT_TRUE(graph.addEdge(v1, v1).second);
			ASSERT_EQ(graph.numEdges(), 1);
			// Add the same edge twice
			ASSERT_FALSE(graph.addEdge(v1, v1).second);
			ASSERT_EQ(graph.numEdges(), 1);
			// Remove self loop
			ASSERT_NO_THROW(graph.removeEdge(v1, v1));
			// Remove twice
			ASSERT_NO_THROW(graph.removeEdge(v1, v1));
			ASSERT_EQ(graph.numEdges(), 0);
			// Add back the self loop
			ASSERT_TRUE(graph.addEdge(v1, v1).second);
			ASSERT_EQ(graph.numEdges(), 1);
			ASSERT_EQ(graph.numVertices(), 1);
			// Check removing vertex
			graph.removeVertex(v1);
			ASSERT_EQ(graph.numVertices(), 0);
			ASSERT_EQ(graph.numEdges(), 0);
			ASSERT_FALSE(graph.edgeExists(v1, v1));
			ASSERT_FALSE(graph.addEdge(v1, v1).second);

			v1 = graph.addVertex();
			ASSERT_EQ(graph.numVertices(), 1);
			ASSERT_EQ(graph.numEdges(), 0);

			auto v2 = graph.addVertex();
			// Check self loop
			ASSERT_FALSE(graph.edgeExists(v2, v2));
			ASSERT_FALSE(graph.edgeExists(v1, v2));
			ASSERT_FALSE(graph.edgeExists(v2, v1));	
			ASSERT_TRUE(graph.addEdge(v1, v2).second);
			ASSERT_EQ(graph.numEdges(), 1);
			ASSERT_TRUE(graph.edgeExists(v1, v2));
			ASSERT_TRUE(graph.edgeExists(v2, v1));
			// Add the same edge twice
			ASSERT_FALSE(graph.addEdge(v2, v1).second);
			ASSERT_EQ(graph.numEdges(), 1);
			graph.removeEdge(v1, v2);
			// Double removal
			ASSERT_NO_THROW(graph.removeEdge(v2, v1));
			ASSERT_EQ(graph.numEdges(), 0);
			ASSERT_FALSE(graph.edgeExists(v1, v2));
			ASSERT_FALSE(graph.edgeExists(v2, v1));
			ASSERT_TRUE(graph.addEdge(v1, v2).second);
			graph.removeEdge(v2, v1);
			ASSERT_EQ(graph.numEdges(), 0);
			ASSERT_FALSE(graph.edgeExists(v1, v2));
		}

		/**
		*	@brief tests the functionality of Graph class to check the neighbors of a vertex
		*	@author Hrachya Hakobyan
		*/
		TEST_F(GraphTest, neighbors){
			using namespace detail;
			Graph<Node> graph;
			// Access neighbors of nonexistent vertex
			ASSERT_THROW(graph.neighbors(0), std::exception);
			auto v1 = graph.addVertex();
			auto v2 = graph.addVertex();
			ASSERT_NO_THROW(graph.neighbors(v1));
			ASSERT_NO_THROW(graph.neighbors(v2));
			auto v1NRange = graph.neighbors(v1);
			ASSERT_EQ(rangeDistance(v1NRange), 0);
			auto edgev1v1 = graph.addEdge(v1, v1);
			v1NRange = graph.neighbors(v1);
			ASSERT_EQ(rangeDistance(v1NRange), 1);
			graph.removeEdge(v1, v1);
			v1NRange = graph.neighbors(v1);
			ASSERT_EQ(rangeDistance(v1NRange), 0);
			auto edgev1v2 = graph.addEdge(v1, v2);
			auto edgev2v1 = graph.addEdge(v2, v1);
			v1NRange = graph.neighbors(v1);
			ASSERT_EQ(rangeDistance(v1NRange), 1);
			auto v3 = graph.addVertex();
			auto edgev1v3 = graph.addEdge(v1, v3);
			auto edgev2v3 = graph.addEdge(v2, v3);
			ASSERT_EQ(rangeDistance(graph.neighbors(v1)), 2);
			ASSERT_EQ(rangeDistance(graph.neighbors(v2)), 2);
			ASSERT_EQ(rangeDistance(graph.neighbors(v3)), 2);
			graph.removeVertex(v3);
			ASSERT_THROW(graph.neighbors(v3), std::exception);
			ASSERT_EQ(rangeDistance(graph.neighbors(v1)), 1);
			ASSERT_EQ(rangeDistance(graph.neighbors(v2)), 1);
			graph.clear();
			ASSERT_THROW(graph.neighbors(v2), std::exception);
			ASSERT_THROW(graph.neighbors(v1), std::exception);
		}

		/**
		*	@brief tests the functionality of Graph class to serialize
		*	@author Hrachya Hakobyan
		*/
		TEST_F(GraphTest, serializes){
			using namespace detail;

			Graph<Node> gInitial;
			Node n1(0, "0");
			Node n2(1, "1");
			n1.intVec = { 1, 2, 3, 4 };
			n2.intVec = { -1, -10, 0 };
			auto n1Index = gInitial.addVertex(n1);
			auto n2Index = gInitial.addVertex(n2);
			gInitial.addEdge(n1Index, n2Index);
			gInitial.addEdge(n1Index, n1Index);

			ASSERT_TRUE(FileManager::getInstance().save(gInitial, "GraphSerialization.xml", "temp", true));
			Graph<Node> gNew;;
			ASSERT_TRUE(FileManager::getInstance().load(gNew, "GraphSerialization.xml", "temp"));
			ASSERT_EQ(gInitial, gNew);
		}
	}
}