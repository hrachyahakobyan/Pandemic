#pragma once

namespace pan{
	namespace detail{
		/**
		*	@brief a modified templated factory with variadic constructor arguments
		*	@author Hrachya Hakobyan
		*/
		template<typename K, typename T, typename ...Us>
		class Factory
		{
		public:
			Factory(const Factory&) = delete;
			void operator=(const Factory&) = delete;

			static Factory& getInstance()
			{
				static Factory<K, T, Us...>    instance; // Guaranteed to be destroyed.
				// Instantiated on first use.
				return instance;
			}

			/**
			* Registers a class to that it can be created via createObject()
			*
			* @param S the class to register, this must ve a subclass of T
			* @param id the id to associate with the class. This ID must be unique
			*/
			template<typename S>
			void registerClass(K id){
				if (mObjectCreator.find(id) != mObjectCreator.end()){
					//your error handling here
				}
				mObjectCreator.insert(std::make_pair<K, CreateObjectFunc>(K(id), &Factory<K, T, Us...>::createObject<S>));
			}

			/**
			* Returns true if a given key exists
			* @param id the id to check exists
			* @return true if the id exists
			*/
			bool hasClass(K id){
				return mObjectCreator.find(id) != mObjectCreator.end();
			}

			/**
			* Creates an object based on an id. It will return null if the key doesn't exist
			*
			* @param id the id of the object to create
			* @return the new object or null if the object id doesn't exist
			*/
			T* createObject(K id, Us... args){
				//Don't use hasClass here as doing so would involve two lookups
				typename std::map<K, CreateObjectFunc>::iterator iter = mObjectCreator.find(id);
				if (iter == mObjectCreator.end()){
					return NULL;
				}
				//calls the required createObject() function
				return ((*iter).second)(args...);
			}	
			Factory(){}
private:
			typedef T *(*CreateObjectFunc)(Us... args);

#ifdef _DEBUG
#ifndef DISABLE_TESTS
			FRIEND_TEST(FactoryTest, constructs);
			FRIEND_TEST(FactoryTest, registers);
#endif
#endif

			/**
			* A map keys (K) to functions (CreateObjectFunc)
			* When creating a new type, we simply call the function with the required key
			*/
			std::map<K, CreateObjectFunc> mObjectCreator;

			/**
			* Pointers to this function are inserted into the map and called when creating objects
			*
			* @param S the type of class to create
			* @return a object with the type of S
			*/
			template<typename S>
			static T* createObject(Us... args){
				return new S(args...);
			}
		};
	}
}
