#pragma once
#ifndef PLAYERSAVEMODEL_H
#define PLAYERSAVEMODEL_H

#include "DataSaveModel.h"

class Player;

class PlayerSaveModel : public DataSaveModel
{
public:
	Player* LocalPlayer;
};

#endif // !PLAYERSAVEMODEL_H
