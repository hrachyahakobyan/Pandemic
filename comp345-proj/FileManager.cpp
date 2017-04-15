#include "stdafx.h"
#include "FileManager.h"

namespace pan{
	using namespace boost::filesystem;

	FileManager::FileManager() :
		outputFolder("data")
	{
	}

	void FileManager::initialize() const
	{
		path p = outputPath();
		if (!exists(p) || !is_directory(p)){
			create_directory(p);
		}
	}

	bool FileManager::fileExists(const path& filename) const
	{
		return exists(filename) && is_regular_file(filename);
	}

	bool FileManager::directoryExists(const boost::filesystem::path& dir) const
	{
		return is_directory(dir);
	}

	bool FileManager::createDirectory(const boost::filesystem::path& dir) const
	{
		if (directoryExists(dir)) return false;
		return create_directories(dir);
	}

	bool FileManager::createOutputStream(const path& filename, std::ofstream& stream, bool overwrite) const
	{
		stream.open(filename.c_str());
		if (!stream){
			return false;
		}
		return true;
	}

	bool FileManager::createInputStream(const path& filename, std::ifstream& stream) const
	{
		stream.open(filename.c_str());
		if (!stream){
			return false;
		}
		return true;
	}

	bool FileManager::removeFile(const path& file) const
	{
		if (fileExists(file))
			return remove(file);
		return false;
	}

	path FileManager::outputPath() const
	{
		return current_path() / outputFolder;
	}

	std::vector<std::string> FileManager::allFiles(const std::string& dir) const
	{
		std::vector<std::string> saveFiles;
		auto dirPath = dir.length() == 0 ? outputPath() : outputPath() / dir;
		if (!directoryExists(dirPath)) return saveFiles;
		directory_iterator iter(dirPath), end;
		for (; iter != end; ++iter)
		{
			if (is_regular_file(*iter)){
				saveFiles.push_back((*iter).path().filename().string());
			}
		}
		return saveFiles;
	}
}