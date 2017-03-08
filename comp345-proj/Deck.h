#pragma once

namespace detail{
	/**
	*	@brief Class to hold a logic of a deck.
	*	The actual type of the contained object is a template parameter.
	*	The container could also be templatized, but it adds too much complexity to
	*	the code and not too much flexibility. The only containers that could possibly be used
	*	are std::vector and std::deque, since they are contiguous and provide random access iterator
	*	required for random shuffling.
	*	@author Hrachya Hakobyan
	*/
	template<typename T>
	class Deck
	{
	public:
		typedef T value_type;
		typedef std::vector<T> container_type;

		Deck();
		explicit Deck(std::size_t size);

		/**
		*	Construct using arbitrary container providing const iterators.
		*/
		template<typename C>
		explicit Deck(const C&);

		Deck(const Deck&);
		Deck& operator=(const Deck&);
		Deck(Deck&&);
		Deck& operator=(Deck&&);
		~Deck();

		inline bool operator==(const Deck&) const;
		inline bool operator!=(const Deck&) const;

		/**
		*	Concatenate the current Deck to a type that can be converted
		*	to a concatanable type. Can be T, Deck<T>, or a container of value type T providing const iterators
		*	@param c the item to concatenate
		*	@return reference to the original deck
		*/
		template<typename C>
		Deck& operator+=(const C& c);

		/**
		*	Merge two decks.
		*	@param bottom the deck that will contribute to the bottom part of the new deck
		*	@param top the deck that will contribute to the top part of the new deck
		*	@return a new deck consisting of bottom and top decks
		*/
		template<typename T>
		friend Deck<T> operator+(const Deck<T>& bottom, const Deck<T>& top);

		inline std::size_t size() const;
		inline bool empty() const;
		inline void clear();
		inline const container_type& _Get_container() const;

		inline const T& top() const;
		inline void pop();

		/**
		*	Push a single item
		*	@param t the item to push
		*/
		void push(const T& t);

		/**
		*	Push a new deck.
		*	@param deck the deck to push
		*/
		void push(const Deck<T>& deck);

		/**
		*	Push a container of value type T providing iterators
		*	@param c the container
		*/
		template<typename C>
		void push(const C& c);

		/**
		*	Returns a new deck containing at most size number of items from the top of the original deck.
		*	@param size of the dealed deck
		*/
		Deck<T> deal(std::size_t size);

		/**
		*	Randomly shuffle the deck.
		*	Does not set the seed.
		*/
		inline void shuffle();

		/**
		*	Inserts the element to a randomly selected position in the deck
		*/
		void insert(const T& val);

	private:
		template<typename T>
		friend std::ostream& operator<<(std::ostream& os, const Deck<T>& d);
		std::vector<T> deck;
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Deck<T>& d)
	{
		for (const auto& t : d.deck){
			os << t << ' ';
		}
		return os;
	}

	template<typename T>
	Deck<T> operator+(const Deck<T>& bottom, const Deck<T>& top)
	{
		auto merge = bottom;
		merge += top;
		return merge;
	}

	template<typename T>
	Deck<T>::Deck(){}

	template<typename T>
	Deck<T>::Deck(std::size_t s) : deck(s){}

	template<typename T>
	template<typename C>
	Deck<T>::Deck(const C& c) : deck(std::begin(c), std::end(c)){}

	template<typename T>
	Deck<T>::Deck(const Deck& d) : deck(d.deck){}

	template<typename T>
	Deck<T>::Deck(Deck&& d) : deck(std::move(d.deck)){}

	template<typename T>
	Deck<T>::~Deck(){}

	template<typename T>
	Deck<T>& Deck<T>::operator=(const Deck& d)
	{
		deck = d.deck;
		return *this;
	}

	template<typename T>
	Deck<T>& Deck<T>::operator=(Deck&& d)
	{
		deck = std::move(d.deck);
		return *this;
	}

	template<typename T>
	bool Deck<T>::operator==(const Deck& d) const
	{
		return deck == d.deck;
	}

	template<typename T>
	bool Deck<T>::operator!=(const Deck& d) const
	{
		return !((*this) == d);
	}

	template<typename T>
	template<typename C>
	Deck<T>& Deck<T>::operator+=(const C& c)
	{
		push(c);
		return *this;
	}

	template<typename T>
	std::size_t Deck<T>::size() const
	{
		return deck.size();
	}

	template<typename T>
	bool Deck<T>::empty() const
	{
		return deck.empty();
	}

	template<typename T>
	void Deck<T>::clear()
	{
		deck.clear();
	}

	template<typename T>
	const typename Deck<T>::container_type& Deck<T>::_Get_container() const
	{
		return deck;
	}

	template<typename T>
	const T& Deck<T>::top() const
	{
		return deck.back();
	}

	template<typename T>
	void Deck<T>::pop()
	{
		deck.pop_back();
	}

	template<typename T>
	void Deck<T>::push(const T& val)
	{
		deck.push_back(val);
	}

	template<typename T>
	void Deck<T>::push(const Deck<T>& d)
	{
		push(d.deck);
	}

	template<typename T>
	template<typename C>
	void Deck<T>::push(const C& c)
	{
		deck.insert(deck.end(), std::begin(c), std::end(c));
	}

	template<typename T>
	Deck<T> Deck<T>::deal(std::size_t size)
	{
		std::vector<T> v;
		auto it = std::prev(deck.end(), std::min(size, deck.size()));
		std::move(it, deck.end(), std::back_inserter(v));
		deck.erase(it, deck.end());
		return Deck<T>(v);
	}

	template<typename T>
	void Deck<T>::shuffle()
	{
		std::random_shuffle(deck.begin(), deck.end());
	}
}

