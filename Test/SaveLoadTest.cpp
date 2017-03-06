#include "stdafx.h"
#include "SaveLoadTest.h"
#include "SaveLoadManager.h"
#include <boost\filesystem.hpp>

namespace pan{
	TEST_F(SaveLoadTest, createsDirectory){
		SaveLoadManager manager;
		manager.initialize();
		using namespace pan;
		using namespace boost::filesystem;

		ASSERT_TRUE(exists(manager.saveDirectory()));
		ASSERT_TRUE(is_directory(manager.saveDirectory()));

		SaveLoadManager manager2;
		manager2.initialize();

		ASSERT_TRUE(exists(manager2.saveDirectory()));
		ASSERT_TRUE(is_directory(manager2.saveDirectory()));

		ASSERT_TRUE(remove(manager2.saveDirectory()));
		SaveLoadManager manager3;
		manager3.initialize();
		ASSERT_TRUE(exists(manager3.saveDirectory()));
		ASSERT_TRUE(is_directory(manager3.saveDirectory()));
	}

	TEST_F(SaveLoadTest, createsFile){
		SaveLoadManager manager;
		manager.outputDirectory = "testCreateFile";
		manager.initialize();
		using namespace pan;
		using namespace boost::filesystem;

		ASSERT_TRUE(exists(manager.saveDirectory()));
		ASSERT_TRUE(is_directory(manager.saveDirectory()));

		path root = manager.saveDirectory();
		SaveFile file1;
		file1.filename = "file1.xml";
		path fp1(manager.saveDirectory());
		fp1 = fp1.append(file1.filename);
		if (exists(fp1)){
			ASSERT_TRUE(remove(fp1));
		}

		ASSERT_FALSE(manager.fileExists(file1));

		std::ofstream of;
		ASSERT_TRUE(manager.createOutputStream(file1, of));
		if (of){
			of.close();
		}
		ASSERT_TRUE(manager.fileExists(file1));
		ASSERT_TRUE(manager.removeFile(file1));
		ASSERT_FALSE(manager.fileExists(file1));	
	}

	TEST_F(SaveLoadTest, savesGame){
		SaveLoadManager manager;
		manager.outputDirectory = "testSaveGame";
		manager.initialize();
		using namespace pan;
		using namespace boost::filesystem;

		ASSERT_TRUE(exists(manager.saveDirectory()));
		ASSERT_TRUE(is_directory(manager.saveDirectory()));

		path root = manager.saveDirectory();
		SaveFile file1;
		file1.filename = "game1.xml";
		path fp1 = manager.saveDirectory();
		fp1 = fp1.append(file1.filename);
		if (exists(fp1)){
			ASSERT_TRUE(remove(fp1));
		}

		ASSERT_FALSE(manager.fileExists(file1));
		
		// Writing to a nonexistent file
		Game game;
		ASSERT_TRUE(manager.save(game, file1.filename));
		// Make sure new file was created
		ASSERT_TRUE(manager.fileExists(file1));

		// Writing to existing file
		ASSERT_FALSE(manager.save(game, file1.filename));
		// Make sure old file is still there
		ASSERT_TRUE(manager.fileExists(file1));

		// Overwrite existing file
		ASSERT_TRUE(manager.save(game, file1.filename, true));
		ASSERT_TRUE(manager.fileExists(file1));

		// Writing with invalid file name
		ASSERT_FALSE(manager.save(game, ""));
		SaveFile invalidFile;
		invalidFile.filename = "";
		ASSERT_FALSE(manager.fileExists(invalidFile));

		Game newGame;
		// attempt to load invalid filename
		ASSERT_FALSE(manager.load(invalidFile, newGame));

		// Attempt to load corrupted game file
		SaveFile corruptFile;
		corruptFile.filename = "corruptGame.xml";
		ASSERT_TRUE(manager.fileExists(corruptFile));
		ASSERT_FALSE(manager.load(corruptFile, newGame));

		// Read a valid game
		ASSERT_TRUE(manager.load(file1, newGame));
		ASSERT_EQ(newGame, game);

		// Clear directory
		for (directory_iterator end_dir_it, it(root); it != end_dir_it; ++it) {
			remove_all(it->path());
		}

		// Save/load multiple times
		const int n = 5;
		for (int i = 0; i < n; i++){
			std::string filename = "file" + std::to_string(i);
			ASSERT_TRUE(manager.save(game, filename));
		}

		auto files = manager.savedGames();
		ASSERT_EQ(files.size(), n);
		for (int i = 0; i < n; i++){
			ASSERT_TRUE(manager.load(files[i], game));
		}
	}

	TEST_F(SaveLoadTest, getsSavedGames){
		using namespace boost::filesystem;

		SaveLoadManager manager;
		manager.outputDirectory = "testGetSavedGames";
		manager.initialize();

		// Clear the directory
		auto savePath = manager.saveDirectory();
		for (directory_iterator end_dir_it, it(savePath); it != end_dir_it; ++it) {
			remove_all(it->path());
		}

		// Check initially empty
		auto files = manager.savedGames();
		ASSERT_EQ(files.size(), 0);

		// Check ignores directories
		create_directory(savePath/"dir1");
		files = manager.savedGames();
		ASSERT_EQ(files.size(), 0);

		std::ofstream of;
		SaveFile f1;
		f1.filename = "file1";
		manager.createOutputStream(f1, of);
		of.close();

		// Check counts files
		files = manager.savedGames();
		ASSERT_EQ(files.size(), 1);

		remove(savePath/"file1");

		// Check no files
		files = manager.savedGames();
		ASSERT_EQ(files.size(), 0);

	}
}
