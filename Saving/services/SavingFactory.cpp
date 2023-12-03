#include "SavingFactory.h"

ISavingService::SavingServicePtr SavingFactory::getPlayerSavingService()
{
	return std::make_shared<PlayerSavingService>();
}