#include "PlayerSavingService.h"
#include "../player/Player.h"
#include "../save_models/PlayerSaveModel.h"

void PlayerSavingService::save(const DataSaveModel& saveModel, const char* addr, bool obfuscate)
{
	const PlayerSaveModel& sm = (const PlayerSaveModel&)saveModel;
	const std::list<InventoryItem>& items = sm.LocalPlayer->getItems();
	uint64_t exp = sm.LocalPlayer->getExp();
	int lvl = sm.LocalPlayer->getLevel();
	const std::string& name = sm.LocalPlayer->getName();

	FILE* fp;
	if (fopen_s(&fp, addr, "w+b") == 0)
	{
		fprintf_s(fp, "player.name=%s\nplayer.exp=%llu\nplayer.lvl=%d\n", name.c_str(), exp, lvl);
		int n = 0;
		for (auto i = items.cbegin(); i != items.cend(); ++i)
		{
			fprintf_s(fp, "player.inv.%d=%s\n", n, i->getCode().c_str());
			n++;
		}
		fprintf_s(fp, "end");
		fclose(fp);

		if (obfuscate)
		{
			char fullPath[MAX_PATH];
			GetFullPathNameA(addr, MAX_PATH, fullPath, NULL);
			obfuscator.fileXor(fullPath, 0x55);
		}
	}
}