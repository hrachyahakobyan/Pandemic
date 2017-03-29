#pragma once
#include <boost\graph\adjacency_list.hpp>

enum vertex_properties_t { vertex_properties };

namespace boost
{
	BOOST_INSTALL_PROPERTY(vertex, properties);
}

namespace pan{
	namespace detail{
		/**
		*	@brief Adapter around boost::adjacency_list
		*	@param first template paramater. set::S to disallow multigraph
		*	@param second template parameter. vec::S to access vertices using indeces
		*	@param third template parameter. undirectedS for undirected graphs.
		*	@param forth template parameter. The type to store as the vertex.
		*	Current configuration of the Class allows represents a simple, undirected graph.
		*	It allows self loop, however the self-edges are not created automatically.
		*	@author Hrachya Hakobyan
		*/
		template<typename N>
		class Graph
		{
		private:
			typedef boost::adjacency_list < boost::setS, boost::vecS, boost::undirectedS,
				boost::property <vertex_properties_t, N >> GraphContainer;
		public:
			typedef typename boost::graph_traits<GraphContainer>::vertex_descriptor VertexDescriptor;
			typedef typename boost::graph_traits<GraphContainer>::edge_descriptor EdgeDescriptor;
			typedef typename boost::graph_traits<GraphContainer>::vertex_iterator VertexIterator;
			typedef typename boost::graph_traits<GraphContainer>::edge_iterator EdgeIterator;
			typedef typename boost::graph_traits<GraphContainer>::adjacency_iterator AdjacencyIterator;
			typedef typename boost::graph_traits<GraphContainer>::out_edge_iterator OutEdgeIterator;
			typedef typename boost::graph_traits<GraphContainer>::degree_size_type VertexDegreeIterator;
			typedef typename boost::property_map<GraphContainer, boost::vertex_index_t>::type IndexMap;
			typedef typename boost::property_map<GraphContainer, vertex_properties_t>::const_type ConstVPropertyIterator;
			typedef std::pair<AdjacencyIterator, AdjacencyIterator> AdjacencyRange;
			typedef std::pair<OutEdgeIterator, OutEdgeIterator> OutEdgeRange;
			typedef std::pair<VertexIterator, VertexIterator> VertexRange;
			typedef std::pair<EdgeIterator, EdgeIterator> EdgeRange;
		public:
			Graph();
			explicit Graph(std::size_t vertexCount);
			Graph(const Graph& g);
			Graph(Graph&&);
			Graph& operator=(const Graph &rhs);
			Graph& operator=(Graph&&);
			~Graph();

			/**
			*	Checks for graph equality.
			*	Isomorphic check is computationally infeasible.
			*	This only checks the number of vertices and edges.
			*/
			inline bool operator==(const Graph& other) const;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive & ar, const unsigned int /* file_version */){
				ar  & BOOST_SERIALIZATION_NVP(container);
			}

			/**
			*	Clears the graph. Removes edges and vertices.
			*/
			void clear();

			/**
			*	Returns the number of vertices.
			*	@return the number of vertices
			*/
			inline std::size_t numVertices() const;
			/**
			*	Returns the number of edges.
			*	@return the number of edges
			*/
			inline std::size_t numEdges() const;

			/**
			*	Check if vertex exists.
			*	The vertex exists if its in the range [0, numVertices())
			*	@return true if vertex exists, false otherwise
			*/
			inline bool vertexExists(VertexDescriptor v) const;

			/**
			*	Adds a new vertex.
			*	@param n the vertex data to be added
			*	@return the vertex descriptor of the newly created vertex
			*/
			inline VertexDescriptor addVertex(const N& n = N());

			/**
			*	Removes a vertex.
			*	The operation will not throw if the vertex is invalid.
			*	@param v the vertex descriptor to be removed
			*/
			inline void removeVertex(VertexDescriptor v);

			/**
			*	Access a vertex data.
			*	@param v the vertex descriptor to access.
			*	@throws std::exception if the index is invalid
			*	@return the reference to the data of the vertex.
			*/
			inline const N& operator[](VertexDescriptor v) const;
			inline N& operator[](VertexDescriptor i);

			/**
			*	Iterate all vertices.
			*	@return the pair of vertex iterators
			*/
			inline VertexRange vertices() const;

			/**
			*	Get the neighbors of the current vertex.
			*	@param v the vertex descriptor to get the neighbors of.
			*	@throws std::exception if the index is invalid
			*	@return the pair of adjacency iterators for the current vertex
			*/
			inline AdjacencyRange neighbors(VertexDescriptor v) const;

			/**
			*	Check if edge exists between two vertices.
			*	Will return false if either of vertices is invalid.
			*	(The default implementation of boost will crash if either of vertices is invalid and 
				is not the next vertex to be added and will add the vertices if it can).
			*	@param v1 the first vertex
			*	@param v2 the second vertex
			*	@return true if edge exists, false otherwise
			*/
			inline bool edgeExists(VertexDescriptor v1, VertexDescriptor v2) const;

			/**
			*	Add a new edge.
			*	Will return false if either of vertices is invalid.
			*	(The default implementation of boost will create a new vertex if the index is invalid).
			*	@param v1 the first vertex
			*	@param v2 the second vertex
			*	@return pair of edge descriptor and boolean flag. The flag is true if the edge
			*	was successfully added.
			*/
			inline std::pair<EdgeDescriptor, bool> addEdge(VertexDescriptor v1, VertexDescriptor v2);
			
			/**
			*	Removes an edge.
			*	@param v1 the first vertex
			*	@param v2 the second vertex
			*/
			inline void removeEdge(VertexDescriptor v1, VertexDescriptor v2);

		private:
			GraphContainer container;
#ifdef _DEBUG
#ifndef DISABLE_TESTS
		FRIEND_TESTS
#endif
#endif
		};

		template<typename N>
		Graph<N>::Graph()
		{
		}

		template<typename N>
		Graph<N>::Graph(std::size_t v) : container(v)
		{
		}

		template<typename N>
		Graph<N>::Graph(const Graph& g) :
			container(g.container)
		{
		}

		template<typename N>
		Graph<N>::Graph(Graph&& o) :
			container(std::move(o.container))
		{
		}

		template<typename N>
		Graph<N>& Graph<N>::operator=(const Graph &rhs)
		{
			container = rhs.container;
			return *this;
		}

		template<typename N>
		Graph<N>& Graph<N>::operator=(Graph&& rhs)
		{
			container = std::move(rhs.container);
			return *this;
		}

		template<typename N>
		Graph<N>::~Graph()
		{
		}

		template<typename N>
		bool Graph<N>::operator==(const Graph& other) const
		{
			return (numVertices() == other.numVertices() && numEdges() == other.numEdges());
		}

		template<typename N>
		void Graph<N>::clear()
		{
			container.clear();
		}

		template<typename N>
		std::size_t Graph<N>::numVertices() const
		{
			return boost::num_vertices(container);
		}

		template<typename N>
		std::size_t Graph<N>::numEdges() const
		{
			return boost::num_edges(container);
		}

		template<typename N>
		bool Graph<N>::vertexExists(VertexDescriptor v) const
		{
			return (v >= 0 && v < numVertices());
		}

		template<typename N>
		typename Graph<N>::VertexDescriptor Graph<N>::addVertex(const N& n)
		{
			return boost::add_vertex(n, container);
		}

		template<typename N>
		void Graph<N>::removeVertex(VertexDescriptor v)
		{
			if (vertexExists(v)){
				boost::clear_vertex(v, container);
				boost::remove_vertex(v, container);
			}
		}

		template<typename N>
		std::pair<typename Graph<N>::EdgeDescriptor, bool> Graph<N>::addEdge(VertexDescriptor v1, VertexDescriptor v2)
		{
			if (!vertexExists(v1) || !vertexExists(v2))
				return std::make_pair(EdgeDescriptor(), false);
			return boost::add_edge(v1, v2, container);
		}

		template<typename N>
		void Graph<N>::removeEdge(VertexDescriptor v1, VertexDescriptor v2)
		{
			if (!vertexExists(v1) || !vertexExists(v2))
				return;
			std::pair<EdgeDescriptor, bool> edge = boost::edge(v1, v2, container);
			if (edge.second)
				container.remove_edge(edge.first);
		}

		template<typename N>
		bool Graph<N>::edgeExists(VertexDescriptor v1, VertexDescriptor v2) const
		{
			if (!vertexExists(v1) || !vertexExists(v2))
				return false;
			return boost::edge(v1, v2, container).second;
		}

		template<typename N>
		const N& Graph<N>::operator[](VertexDescriptor v) const
		{
			if (!vertexExists(v))
				throw std::exception("ERROR: pan::Graph::const N& operator[](VertexDescriptor)const::invalid index");
			boost::property_map<GraphContainer, vertex_properties_t>::const_type param = boost::get(vertex_properties, container);
			return param[v];
		}

		template<typename N>
		N& Graph<N>::operator[](VertexDescriptor v)
		{
			if (!vertexExists(v))
				throw std::exception("ERROR: pan::Graph::N& operator[](VertexDescriptor)::invalid index");
			boost::property_map<GraphContainer, vertex_properties_t>::type param = boost::get(vertex_properties, container);
			return param[v];
		}

		template<typename N>
		typename Graph<N>::VertexRange Graph<N>::vertices() const
		{
			return boost::vertices(container);
		}

		template<typename N>
		typename Graph<N>::AdjacencyRange Graph<N>::neighbors(VertexDescriptor v) const
		{
			if (!vertexExists(v))
				throw std::exception("ERROR: pan::Graph::AdjacencyRange neighbors(VertexDescriptor)const::invalid index");
			return boost::adjacent_vertices(v, container);
		}
	}
}

