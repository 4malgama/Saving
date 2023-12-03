#include "inventory/InventoryResourceManager.h"
#include "services/SavingFactory.h"
#include "player/Player.h"
#include "save_models/PlayerSaveModel.h"

//Soon refactor
static void InitResources()
{
	InventoryItem magic_stick("Magic stick", "magic_stick");
	magic_stick.addProperty("splash_damage", 4.5f);
	magic_stick.addProperty("atack_speed", 8.0f);

	InventoryItem magic_gear("Magic gear", "magic_gear");
	magic_gear.addProperty("defense", 5.5f);
	magic_gear.addProperty("hot_skin", 1.3f);

	InventoryItem black_apple("Black apple", "black_apple");
	black_apple.addProperty("effect_nausea", 3);

	InventoryResourceManagerPtr IRM = InventoryResourceManager::getInstance();

	IRM->registerItem(magic_stick);
	IRM->registerItem(magic_gear);
	IRM->registerItem(black_apple);
}

/// <summary>
/// The first thing that is executed in the program.
/// You can add any initializations or data loading here.
/// </summary>
void _main_begin()
{
	InitResources();
}

/// <summary>
/// The main body of the program is essentially the same as 'main()'.
/// </summary>
void _main_body()
{
	InventoryResourceManagerPtr IRM = InventoryResourceManager::getInstance();

	Player MyPlayer("Amalgama");
	MyPlayer.addItem(IRM->getItem("magic_stick"));
	MyPlayer.addItem(IRM->getItem("black_apple"));

	PlayerSaveModel saveModel;
	saveModel.setId(0);
	saveModel.LocalPlayer = &MyPlayer;

	SavingFactory savingFactory;

	ISavingService::SavingServicePtr savingService = savingFactory.getPlayerSavingService();
	savingService->save(saveModel, "player.save", true);
}

/// <summary>
/// The final stage of the program. Executed immediately after exiting '_main_body()'.
/// You can add cleaning, saving, and other things here.
/// </summary>
/// <param name="_return">A reference to a variable code indicating the return code from the program.</param>
void _main_end(int& _return)
{
	_return = 0;	//eq: 'return 0' in main()
}