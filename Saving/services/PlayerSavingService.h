#pragma once
#ifndef PLAYERSAVINGSERVICE_H
#define PLAYERSAVINGSERVICE_H

#include "ISavingService.h"
#include "../security/Obfuscator.h"

class PlayerSavingService : public ISavingService
{
	Obfuscator obfuscator;

public:
	void save(const DataSaveModel& saveModel, const char* addr, bool obfuscate = false) override;
};

#endif // !PLAYERSAVINGSERVICE_H
