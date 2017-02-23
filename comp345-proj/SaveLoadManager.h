#pragma once
#include "Game.h"

namespace pan{
	struct SaveFile{
		std::string filename;
	};

	/**
	*	@brief Abstracts away the save/load of the Game object.
	*	The details of the save/load, i.e. the filesystem, fileformat
	*	will vary depending on the platform. This class takes care of that.
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

		bool save(const Game& game, const std::string& filename);
		bool load(const SaveFile& filename, Game& game) const;
	private:
#ifdef _DEBUG
		friend class SaveLoadTest;
		FRIEND_TEST(SaveLoadTest, createsDirectory);
		FRIEND_TEST(SaveLoadTest, createsFile);
		FRIEND_TEST(SaveLoadTest, savesGame);
#endif
		SaveLoadManager();
		SaveLoadManager(const SaveLoadManager&) = delete;
		SaveLoadManager& operator=(const SaveLoadManager&) = delete;
		void initialize() const;
		const std::string saveDirectory() const;
		std::string folderName = "save";
		const std::string extension = "xml";
		bool fileExists(const SaveFile& file) const;
		bool createInputStream(const SaveFile& file, std::ifstream& stream) const;
		bool createOutputStream(const SaveFile& file, std::ofstream& stream) const;
		bool removeFile(const SaveFile& file) const;
		bool writeGame(const Game& game, std::ofstream& file) const;
		bool readGame(std::ifstream& file, Game& game) const;
	};
}

