#include "stdafx.h"
#include "LoggerBase.h"
#include "FileManager.h"
#include <boost\date_time.hpp>

namespace pan{
	const std::string LoggerBase::logDir("log");

	LoggerBase::LoggerBase()
	{
	}

	LoggerBase::LoggerBase(const std::string& filename, std::unique_ptr<LoggerBase> logger)
	{
		boost::filesystem::path p = FileManager::getInstance().outputPath();
		p /= logDir;
		FileManager::getInstance().createDirectory(p);
		p /= filename;
		stream.reset(new std::ofstream());
		if (!FileManager::getInstance().createOutputStream(p, *stream, true)){
			std::string msg("Could not create logfile: ");
			msg += p.string();
			throw std::exception(msg.c_str());
		}
		else {
			if (logger){
				mLogger = std::move(logger);
				mLogger->setStream(this->stream);
			}
		}
	}

	LoggerBase::~LoggerBase(){
		closeStream();
	}

	void LoggerBase::closeStream()
	{
		if (stream && stream.get()){
			if (stream.use_count() == 1){
				*stream << "END OF LOGFILE";
				stream->close();
			}
			stream.reset();
		}
	}

	std::string LoggerBase::getDateString() const
	{
		return boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
	}

	void LoggerBase::setStream(std::shared_ptr<std::ofstream> stream)
	{
		closeStream();
		this->stream = stream;
		if (mLogger){
			mLogger->setStream(stream);
		}
	}
}
