#pragma once
/**
*	Tests boost::serialization with a hierarchy of classes.
*	Test STL collection with std::unique_ptr-s to polymorphic objects.
*/

#define EPSILON 0.000001
#define FEQUAL(a, b) std::fabs(a - b) < EPSILON

class SerializationTest1 : public ::testing::Test
{
protected:
	class A{
	public:
		int mInt;
		double mDouble;
		float mFloat;
		std::string mString;
		std::vector<int> mIntVec;
		std::vector<std::string> mStringVec;
		std::vector<std::pair<int, double>> mPairVec;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar  & BOOST_SERIALIZATION_NVP(mInt);
			ar 	& BOOST_SERIALIZATION_NVP(mDouble);
			ar	& BOOST_SERIALIZATION_NVP(mFloat);
			ar	& BOOST_SERIALIZATION_NVP(mString);
			ar	& BOOST_SERIALIZATION_NVP(mIntVec);
			ar	& BOOST_SERIALIZATION_NVP(mStringVec);
			ar	& BOOST_SERIALIZATION_NVP(mPairVec);
		}

		bool operator==(const A& other) {
			return mInt == other.mInt &&
				FEQUAL(mDouble, other.mDouble) &&
				FEQUAL(mFloat, other.mFloat) &&
				mIntVec == other.mIntVec &&
				mStringVec == other.mStringVec &&
				mPairVec == other.mPairVec;
		}
	};

	class C{
	public:
		C() = default;
		C(const C&) = default;
		virtual ~C() = default;
		std::string mString;
		int mInt;

		bool operator==(const C& other) {
			return mString == other.mString &&
				mInt == other.mInt;
		}

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_NVP(mString);
			ar & BOOST_SERIALIZATION_NVP(mInt);
		}
	};

	class D : public C{
	public:
		D() = default;
		~D() = default;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(C);
		}
	};

	class B : public A{
	public:
		char mChar;
		std::vector<std::unique_ptr<C>> mCVector;
		void addC(const C& c){
			mCVector.push_back(std::unique_ptr<C>(new C(c)));
		}
		void addD(const D& d){
			mCVector.push_back(std::unique_ptr<C>(new D(d)));
		}
		bool operator==(const B& other) {
			if (mChar != other.mChar)
				return false;
			if (mCVector.size() != other.mCVector.size())
				return false;
			for (std::size_t i = 0; i < mCVector.size(); i++)
			{
				// Unique pointers, compare by value
				if (!((*(mCVector[i])) == (*(other.mCVector[i]))))
					return false;
			}
			return true;
		}

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file_version */){
			ar.register_type(static_cast<C*>(NULL));
			ar.register_type(static_cast<D*>(NULL));
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(A);
			ar & BOOST_SERIALIZATION_NVP(mChar);
			ar & BOOST_SERIALIZATION_NVP(mCVector);
		}
	};

	A aInitial;
	B bInitial;
	C cInitial;
	D dInitial;
	virtual void SetUp() {
		aInitial.mInt = 10;
		aInitial.mDouble = 123.23423;
		aInitial.mFloat = 12.123f;
		aInitial.mIntVec = { 1, 0, -10, -100000, 12312123 };
		aInitial.mString = "Some string";
		aInitial.mStringVec = { "1", "23234", "sdfsdf" };

		cInitial.mInt = 10;
		cInitial.mString = "String";

		bInitial.mChar = 'X';
		cInitial.mString = "C1";
		bInitial.addC(cInitial);
		cInitial.mString = "C2";
		bInitial.addC(cInitial);
		cInitial.mString = "C3";
		bInitial.addC(cInitial);

		dInitial.mString = "D1";
		bInitial.addD(dInitial);
		dInitial.mString = "D2";
		bInitial.addD(dInitial);
	}
};

