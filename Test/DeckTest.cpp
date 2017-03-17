#include "stdafx.h"
#include "DeckTest.h"
#include  <core/FileManager.h>

namespace pan{
	namespace detail{
		TEST_F(DeckTest, Constructs)
		{
			std::vector<int> vec{ 1, 2, 3, 4 };
			int arr[] = { 1, 2, 3, 4 };

			// Default constructor
			Deck<int> d1;
			ASSERT_EQ(d1.size(), 0);

			// Deck with default size
			Deck<int> d2(static_cast<std::size_t>(10));
			ASSERT_EQ(d2.size(), 10);

			// Deck with container
			Deck<int> d3(vec);
			Deck<int> d4(arr);
			ASSERT_EQ(d3.size(), vec.size());
			ASSERT_EQ(d4.size(), sizeof(arr) / sizeof(int));
		}

		TEST_F(DeckTest, Pushes)
		{
			Deck<int> d;
			ASSERT_TRUE(d.empty());
			d.push(1);
			ASSERT_EQ(d.size(), 1);
			d.push(d);
			ASSERT_EQ(d.size(), 2);
			std::vector<int> vec{ 1, 2 };
			d.push(vec);
			ASSERT_EQ(d.size(), 4);
			vec.clear();
			d.push(vec);
			ASSERT_EQ(d.size(), 4);
			int arr[] = { 1, 2 };
			d.push(arr);
			ASSERT_EQ(d.size(), 6);
			Deck<int> dEmpty;
			d.push(dEmpty);
			ASSERT_EQ(d.size(), 6);
		}

		TEST_F(DeckTest, Pops)
		{
			Deck<int> d;
			ASSERT_TRUE(d.empty());
			d.push(1);
			ASSERT_EQ(d.top(), 1);
			d.pop();
			ASSERT_TRUE(d.empty());
		}

		TEST_F(DeckTest, Deals)
		{
			Deck<int> d;
			ASSERT_TRUE(d.empty());
			const std::size_t n = 10;
			// Create a 10x10 matrix with values 0...99
			std::vector<std::vector<int>> mat(10);
			for (auto i = 0; i < n; i++){
				std::vector<int> v(10);
				for (auto j = 0; j < n; j++){
					v[j] = i * 10 + j;
				}
				// Insert into deck
				d.push(v);
				mat[i] = v;
			}
			// Deal 10 by 10
			for (auto i = 0; i < 10; i++){
				auto delt = d.deal(10);
				ASSERT_EQ(delt.size(), 10);
				//The cards are dealt in the opposite direction of push
				ASSERT_EQ(delt._Get_container(), mat[10 - i - 1]);
				ASSERT_EQ(d.size(), 100 - (i + 1) * 10);
			}
		}

		TEST_F(DeckTest, Serializes)
		{
			Deck<int> deck;
			for (int i = 0; i < 100; i++) deck.push(i);

			ASSERT_TRUE(FileManager::getInstance().save(deck, "DeckSerialization.xml", "temp", true));
			Deck<int> deckNew;
			ASSERT_TRUE(FileManager::getInstance().load(deckNew, "DeckSerialization.xml", "temp"));
			

			ASSERT_TRUE(deckNew == deck);
		}
	}
}
