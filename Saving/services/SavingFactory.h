#pragma once
#ifndef SAVINGFACTORY_H
#define SAVINGFACTORY_H

#include "PlayerSavingService.h"

class SavingFactory
{
public:
	[[nodiscard]] ISavingService::SavingServicePtr getPlayerSavingService();
};

#endif // !SAVINGFACTORY_H
