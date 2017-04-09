#pragma once

namespace pan{
	class LoggerBase
	{
	public:
		LoggerBase();
		LoggerBase(const std::string& filename, std::unique_ptr<LoggerBase> logger = nullptr);
		LoggerBase(const LoggerBase&) = delete;
		LoggerBase& operator=(const LoggerBase&) = delete;
		virtual ~LoggerBase();
		void setStream(std::shared_ptr<std::ofstream> stream);
	protected:
		static const std::string logDir;
		std::unique_ptr<LoggerBase> mLogger;
		std::shared_ptr<std::ofstream> stream;
		std::string getDateString() const;
		void closeStream();
	};
}

