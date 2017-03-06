#include "stdafx.h"
#include "SaveLoadManager.h"
#include "Player.h"
#include <boost/filesystem.hpp>

namespace pan{

	SaveLoadManager::SaveLoadManager()
	{
	}

	void SaveLoadManager::initialize() const
	{
		using namespace boost::filesystem;
		path p(this->saveDirectory());
		if (!exists(p) || !is_directory(p)){
			create_directory(p);
		} 
	}

	const std::string SaveLoadManager::saveDirectory() const
	{
		boost::filesystem::path full_path(boost::filesystem::current_path());
		return full_path.append(outputDirectory).string();
	}

	std::vector<SaveFile> SaveLoadManager::savedGames() const
	{
		using namespace boost::filesystem;
		std::vector<SaveFile> saveFiles;
		path saveDir = path(saveDirectory());
		directory_iterator iter(saveDir), end;
		for (; iter != end; ++iter)
		{
			if (is_regular_file(*iter)){
				SaveFile saveFile;
				saveFile.filename = (*iter).path().stem().string();
				saveFiles.push_back(saveFile);
			}
		}
		return saveFiles;
	}

	bool SaveLoadManager::save(const Game& game, const std::string& filename, bool overwrite)
	{
		if (filename.length() == 0)
			return false;
		SaveFile file;
		file.filename = filename;
		if (!overwrite && fileExists(file))
			return false;
		std::ofstream os;
		if (!createOutputStream(file, os, overwrite)){
			return false;
		}
		return writeGame(game, os);
	}

	bool SaveLoadManager::writeGame(const Game& game, std::ofstream& file) const
	{
		boost::archive::xml_oarchive oa(file);
		oa.template register_type<pan::Player<pan::Medic>>();
		oa.template register_type<pan::Player<pan::Dispatcher>>();
		try{
			oa << boost::serialization::make_nvp("Game", game);
		}
		catch (boost::archive::archive_exception& e){
			std::cout << e.what() << std::endl;
			file.close();
			return false;
		}
		file.close();
		return true;
	}

	bool SaveLoadManager::load(const SaveFile& file, Game& game) const
	{
		if (!fileExists(file))
			return false;
		std::ifstream is;
		if (!createInputStream(file, is)){
			return false;	
		}
		return readGame(is, game);
	}

	bool SaveLoadManager::readGame(std::ifstream& file, Game& game) const
	{
		boost::archive::xml_iarchive ia(file);
		ia.template register_type<pan::Player<pan::Medic>>();
		ia.template register_type<pan::Player<pan::Dispatcher>>();
		try{
			ia >> boost::serialization::make_nvp("Game", game);
		}
		catch (boost::archive::archive_exception& e){
			std::cout << e.what() << std::endl;
			file.close();
			return false;
		}
		file.close();
		return true;
	}

	bool SaveLoadManager::fileExists(const SaveFile& file) const
	{
		if (file.filename.length() == 0)
			return false;
		using namespace boost::filesystem;
		path dir(this->saveDirectory());
		path filePath = dir.append(file.filename);
		return exists(filePath) && is_regular_file(filePath);
	}


	bool SaveLoadManager::createOutputStream(const SaveFile& file, std::ofstream& stream, bool overwrite) const
	{
		if (file.filename.length() == 0)
			throw std::exception("Invalid file name");
		using namespace boost::filesystem;
		path dir(this->saveDirectory());
		path filePath = dir.append(file.filename);
		// Disallow overwriting existing files for output streams
		if (!overwrite && exists(filePath) && is_regular_file(filePath) ){
			return false;
		}
		stream.open(filePath.c_str());
		if (!stream){
			return false;
		}
		return true;
	}

	bool SaveLoadManager::createInputStream(const SaveFile& file, std::ifstream& stream) const
	{
		if (file.filename.length() == 0)
			throw std::exception("Invalid file name");
		using namespace boost::filesystem;
		path dir(this->saveDirectory());
		path filePath = dir.append(file.filename);
		// Disallow creation of new files of input streams
		if (!exists(filePath) || !is_regular_file(filePath)){
			return false;
		}
		stream.open(filePath.c_str());
		if (!stream){
			return false;
		}
		return true;
	}

	bool SaveLoadManager::removeFile(const SaveFile& file) const
	{
		if (file.filename.length() == 0)
			return false;
		using namespace boost::filesystem;
		path dir(this->saveDirectory());
		path filePath = dir.append(file.filename);
		if (!exists(filePath) || !is_regular_file(filePath))
			return false;
		return remove(filePath);
	}
}