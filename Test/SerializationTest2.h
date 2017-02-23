#pragma once
/**
*	Tests boost::serialization with a hierarchy of classes 
*	with shared_ptr-s of polymorphic objects.
*/

class SerializationTest2 : public ::testing::Test
{
protected:
	class A{
	public:
		std::string name;
		A() = default;
		~A() = default;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_NVP(name);
		}

		virtual A* clone() const{
			return new A(*this);
		}

		bool operator==(const A& o){
			return name == o.name;
		}
	};

	class B : public A{
	public:
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(A);
		}

		B* clone() const{
			return new B(*this);
		}
	};

	class C{
	public:
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar.register_type(static_cast<A*>(NULL));
			ar.register_type(static_cast<B*>(NULL));
			ar & BOOST_SERIALIZATION_NVP(name);
			ar & BOOST_SERIALIZATION_NVP(objs);
		}
		std::string name;
		std::vector<std::shared_ptr<A>> objs;

		bool operator==(const C& o){
			if (name != o.name || objs.size() != o.objs.size())
				return false;
			for (std::size_t i = 0; i < objs.size(); i++){
				// Shared pointers, compare pointers
				if (objs[i] != o.objs[i]){
					return false;
				}
			}
			return true;
		}
	};
	C c1Initial;
	C c2Initial;
};



