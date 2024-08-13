#include "file_log_consumer.h"



structures::FileLogConsumer::FileLogConsumer(const std::string& path)
	:fileStream_(path)
{
	if (!this->fileStream_.is_open()) {
		throw std::invalid_argument("FileLogConsumer::FileLogConsumer: failed to open file " + path);
	}
}
	

void structures::FileLogConsumer::logMessage(structures::LogType type, const std::string& message)
{
	this->fileStream_ << logTypeToString(type) << ";" << message << std::endl;
}

void structures::FileLogConsumer::logString(const std::string& message)
{
	this->fileStream_ << message << std::endl;
}

void structures::FileLogConsumer::logDuration(size_t size, std::chrono::nanoseconds duration, const std::string& message)
{
	this->fileStream_ << size << ";" << duration.count() << ";" << message << std::endl;
}
