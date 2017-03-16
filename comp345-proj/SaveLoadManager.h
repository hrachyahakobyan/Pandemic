#pragma once
#include "Game.h"

namespace pan{

	/**
	*	@brief Abstracts away the save/load of the Game object.
	*	The details of the save/load, i.e. the filesystem, fileformat
	*	will vary depending on the platform. 
	*	@author Hrachya Hakobyan
	*/
	class SaveLoadManager
	{
	public:
		~SaveLoadManager() = default;

		static SaveLoadManager& getInstance()
		{
			static SaveLoadManager instance;
			instance.initialize();
			return instance;
		}

		/**
		*	Save the game.
		*	@param game the game to save
		*	@param filename the name of the save file
		*	@param overwrite whether to overwrite an existing game
		*	@return true if save was successful, false otherwise.
		*/
		bool save(const Game& game, const std::string& filename, bool overwrite = false);

		/**
		*	Loads a saved game.
		*	@param filename the savefile of the game
		*	@param game a reference to a game object
		*	@return true if the load was successful, false otherwise
		*/
		bool load(const SaveFile& filename, Game& game) const;

		/**
		*	Returns a vector of all save files
		*	@return a vector of SaveFile objects
		*/
		std::vector<SaveFile> savedGames() const;
	private:
#ifdef _DEBUG
#ifndef DISABLE_TESTS
		friend class SaveLoadTest;
		FRIEND_TEST(SaveLoadTest, createsDirectory);
		FRIEND_TEST(SaveLoadTest, createsFile);
		FRIEND_TEST(SaveLoadTest, savesGame);
		FRIEND_TEST(SaveLoadTest, getsSavedGames);
#endif
#endif
		SaveLoadManager();
		SaveLoadManager(const SaveLoadManager&) = delete;
		SaveLoadManager& operator=(const SaveLoadManager&) = delete;
		void initialize() const;
		const std::string saveDirectory() const;
		std::string outputDirectory = "save";
		std::string extension = "xml";
		bool fileExists(const SaveFile& file) const;
		bool createInputStream(const SaveFile& file, std::ifstream& stream) const;
		bool createOutputStream(const SaveFile& file, std::ofstream& stream, bool overwrite = false) const;
		bool removeFile(const SaveFile& file) const;
		bool writeGame(const Game& game, std::ofstream& file) const;
		bool readGame(std::ifstream& file, Game& game) const;
	};
}

