#pragma once
namespace pan{
	namespace detail{
		class GraphTest : public  ::testing::Test
		{
		protected:
			struct Node{
			public:
				Node(){}
				Node(int index, std::string name) : index(index), name(name){}
				int index;
				std::string name;
				std::vector<int> intVec;
				bool someBool = true;
				template<class Archive>
				void serialize(Archive & ar, const unsigned int /* file_version */){
					ar & BOOST_SERIALIZATION_NVP(index);
					ar & BOOST_SERIALIZATION_NVP(name);
					ar & BOOST_SERIALIZATION_NVP(intVec);
					ar & BOOST_SERIALIZATION_NVP(someBool);
				}
				bool operator==(const Node& other) const{
					return index == other.index;
				}
			};
		};
	}
}

