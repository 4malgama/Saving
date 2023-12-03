#pragma once
#ifndef ISAVINGSERVICE_H
#define ISAVINGSERVICE_H

#include <memory>

class DataSaveModel;

class ISavingService
{
public:
	typedef std::shared_ptr<ISavingService> SavingServicePtr;

	virtual void save(const DataSaveModel& saveModel, const char* addr, bool obfuscate) = 0;
};

#endif // !ISAVINGSERVICE_H
