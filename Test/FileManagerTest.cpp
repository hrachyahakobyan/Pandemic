#include "stdafx.h"
#include "FileManagerTest.h"
#include <core\FileManager.h>

namespace pan{
	TEST_F(FileManagerTest, createsDirectory){
		FileManager manager;
		using namespace boost::filesystem;
		manager.outputFolder = "testCreateDirectory";
		remove(manager.outputPath());
		ASSERT_FALSE(manager.directoryExists(manager.outputPath()));
		manager.initialize();
		ASSERT_TRUE(manager.directoryExists(manager.outputPath()));
	}

	TEST_F(FileManagerTest, createsFile){
		FileManager manager;
		manager.outputFolder = "testCreateFile";
		manager.initialize();
		using namespace pan;
		using namespace boost::filesystem;

		ASSERT_TRUE(manager.directoryExists(manager.outputPath()));
		path root = manager.outputPath();
		path file1("file1");
		if (exists(root / file1)){
			ASSERT_TRUE(remove(root / file1));
		}

		ASSERT_FALSE(manager.fileExists(root / file1));
		std::ofstream of;
		ASSERT_TRUE(manager.createOutputStream(file1, of));
		of.close();
		ASSERT_TRUE(manager.fileExists(file1));
		ASSERT_TRUE(manager.removeFile(file1));
		ASSERT_FALSE(manager.fileExists(file1));
	}
	
	TEST_F(FileManagerTest, savesGame){
		FileManager manager;
		manager.outputFolder = "testSaveGame";
		manager.initialize();
		using namespace pan;
		using namespace boost::filesystem;

		ASSERT_TRUE(manager.directoryExists(manager.outputPath()));

		path root = manager.outputPath();
		std::string file1 = "game1.xml";
		path fp1 = root/"save"/file1;
		if (exists(fp1)){
			ASSERT_TRUE(remove(fp1));
		}

		ASSERT_FALSE(manager.fileExists(fp1.string()));

		// Writing to a nonexistent file
		Game game;
		ASSERT_TRUE(manager.save(game, file1, "save"));
		// Make sure new file was created
		ASSERT_TRUE(manager.fileExists(root/"save"/file1));

		// Writing to existing file
		ASSERT_FALSE(manager.save(game, file1, "save"));
		// Make sure old file is still there
		ASSERT_TRUE(manager.fileExists(root/"save"/file1));

		// Overwrite existing file
		ASSERT_TRUE(manager.save(game, file1, "save", true));
		ASSERT_TRUE(manager.fileExists(root/"save"/file1));

		// Writing with invalid file name
		ASSERT_FALSE(manager.save(game, "", "save"));
		std::string invalidFile = "";
		ASSERT_FALSE(manager.fileExists(root/"save"/invalidFile));

		Game newGame;
		// attempt to load invalid filename
		ASSERT_FALSE(manager.load(newGame, invalidFile, "save"));

		// Attempt to load corrupted game file
		std::string corruptFile = "corruptGame.xml";

		ASSERT_TRUE(manager.fileExists(root/"save"/corruptFile));
		ASSERT_FALSE(manager.load(newGame, corruptFile, "save"));

		// Read a valid game
		ASSERT_TRUE(manager.load(newGame, file1, "save"));
		ASSERT_EQ(newGame, game);
	}

	TEST_F(FileManagerTest, getsSavedGames){
		using namespace boost::filesystem;

		FileManager manager;
		manager.outputFolder = "testGetSavedGames";
		manager.initialize();

		// Clear the directory
		auto savePath = manager.outputPath();
		for (directory_iterator end_dir_it, it(savePath); it != end_dir_it; ++it) {
			remove_all(it->path());
		}

		// Check initially empty
		auto files = manager.allFiles("");
		ASSERT_EQ(files.size(), 0);

		auto root = manager.outputPath();

		// Check ignores directories
		create_directory(savePath / "dir1");
		files = manager.allFiles("dir1");
		ASSERT_EQ(files.size(), 0);

		std::ofstream of;
		std::string f1 = "file1";
		manager.createOutputStream(root/f1, of);
		of.close();

		// Check counts files
		files = manager.allFiles("");
		ASSERT_EQ(files.size(), 1);

		remove(savePath / "file1");

		// Check no files
		files = manager.allFiles("");
		ASSERT_EQ(files.size(), 0);

	}
	
}
