#pragma once

namespace pan{
	/**
	*	@brief base class for all Loggers.
	*	Nested loggers share the same output stream, i.e. the output from
	*	the chain of nested logger objects goes into the same output stream.
	*	The stream is closed by the logger when it is destroyed. 
	*	The destruction of the outermost logger will destroy all nested loggers down the chain.
	*	@author Hrachya Hakobyan
	*/
	class LoggerBase
	{
	public:
		LoggerBase();
		LoggerBase(const std::string& filename, std::unique_ptr<LoggerBase> logger = nullptr);
		LoggerBase(const LoggerBase&) = delete;
		LoggerBase& operator=(const LoggerBase&) = delete;
		virtual ~LoggerBase();
		/**
		*	Set a new output file stream for the logger
		*	@param stream a shared pointer to a ofstream object
		*/
		void setStream(std::shared_ptr<std::ofstream> stream);
		static std::string getDateString();
	protected:
		static const std::string logDir;
		std::unique_ptr<LoggerBase> mLogger;
		std::shared_ptr<std::ofstream> stream;
		void closeStream();
	};
}

