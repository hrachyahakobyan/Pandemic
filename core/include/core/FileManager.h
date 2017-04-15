#pragma once
#include <boost/filesystem.hpp>

namespace pan{

	/**
	*	@brief Abstracts away the save/load of game objects.
	*	The details of the save/load, i.e. the filesystem, fileformat
	*	will vary depending on the platform.
	*	@author Hrachya Hakobyan
	*/
	class FileManager
	{
	public:
		~FileManager() = default;
		static FileManager& getInstance()
		{
			static FileManager instance;
			instance.initialize();
			return instance;
		}

		/**
		*	Save an object.
		*	@param t the object to save
		*	@param filename the name of the save file
		*	@param overwrite whether to overwrite an existing game
		*	@return true if save was successful, false otherwise.
		*/
		template<typename T>
		bool save(const T& t, const std::string& filename, const std::string& dir, bool overwrite = true) const;

		/**
		*	Loads a saved object.
		*	@param filename the savefile of the game
		*	@param t a reference to a T object
		*	@return true if the load was successful, false otherwise
		*/
		template<typename T>
		bool load(T& t, const std::string& file, const std::string& dir) const;

		/**
		*	Returns a vector of all save files
		*	@return a vector of SaveFile objects
		*/
		std::vector<std::string> allFiles(const std::string& path) const;

		boost::filesystem::path outputPath() const;
		bool createInputStream(const boost::filesystem::path& file, std::ifstream& stream) const;
		bool createOutputStream(const boost::filesystem::path& file, std::ofstream& stream, bool overwrite = false) const;
		bool createDirectory(const boost::filesystem::path& dir) const;
	private:
#ifdef _DEBUG
#ifndef DISABLE_TESTS
		FRIEND_TESTS
#endif
#endif
		FileManager();
		FileManager(const FileManager&) = delete;
		FileManager& operator=(const FileManager&) = delete;
		void initialize() const;
		std::string outputFolder;

		template<typename T>
		bool write(const T& t, std::ofstream& file) const;

		template<typename T>
		bool read(std::ifstream& file, T& t) const;
		bool removeFile(const boost::filesystem::path& file) const;
		bool fileExists(const boost::filesystem::path& file) const;
		bool directoryExists(const boost::filesystem::path& dir) const;
	};

	template<typename T>
	bool FileManager::save(const T& t, const std::string& filename, const std::string& dirname, bool overwrite) const
	{
		using namespace boost::filesystem;
		if (filename.length() == 0) return false;
		path dir = outputPath() / dirname;
		if (!directoryExists(dir) && !createDirectory(dir))
			return false;
		path filePath = dir / filename;
		if (!overwrite && fileExists(filePath))
			return false;
		std::ofstream os;
		if (!createOutputStream(filePath, os, overwrite)){
			return false;
		}
		return write(t, os);
	}

	template<typename T>
	bool FileManager::load(T& t, const std::string& filename, const std::string& dir) const
	{
		using namespace boost::filesystem;
		if (filename.length() == 0) return false;
		path filePath = outputPath() / dir / filename;
		if (!fileExists(filePath))
			return false;
		std::ifstream is;
		if (!createInputStream(filePath, is)){
			return false;
		}
		return read(is, t);
	}

	template<typename T>
	bool FileManager::read(std::ifstream& file, T& t) const
	{
		try{
			boost::archive::xml_iarchive ia(file);
			ia >> boost::serialization::make_nvp("object", t);
		}
		catch (...){
			std::cout << "Error reading file " << std::endl;
			file.close();
			return false;
		}
		file.close();
		return true;
	}

	template<typename T>
	bool FileManager::write(const T& t, std::ofstream& file) const
	{
		try{
			boost::archive::xml_oarchive oa(file);
			oa << boost::serialization::make_nvp("object", t);
		}
		catch (...){
			std::cout << "Error writing file " << std::endl;
			file.close();
			return false;
		}
		file.close();
		return true;
	}
}

