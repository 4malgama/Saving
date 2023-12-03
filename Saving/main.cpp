#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <errno.h>
#include <Windows.h>
#pragma message( "Lonely Amalgama wants to play." )

#pragma warning( disable : 4172 )

#pragma warning( disable : 26495 ) //initialize some fields
class Variant
{
	union
	{
		int i;
		float f;
		bool b;
	} value;

	std::string* str;

	bool empty;
	enum
	{
		VARINT,
		VARFLOAT,
		VARBOOL,
		VARSTRING,
		VARNONE
	} type;

public:
	Variant()
	{
		empty = true;
		type = VARNONE;
	}

	Variant(int v)
	{
		value.i = v;
		empty = true;
		type = VARINT;
	}

	Variant(float v)
	{
		value.f = v;
		empty = true;
		type = VARFLOAT;
	}

	Variant(bool v)
	{
		value.b = v;
		empty = true;
		type = VARBOOL;
	}

	Variant(const std::string& v)
	{
		str = new std::string(v);
		empty = true;
		type = VARSTRING;
	}

	~Variant()
	{
		if (str != nullptr && type == VARSTRING)
			delete str;
	}

	void setValue(int newValue)
	{
		value.i = newValue;
		empty = false;
		type = VARINT;
	}

	void setValue(float newValue)
	{
		value.f = newValue;
		empty = false;
		type = VARFLOAT;
	}

	void setValue(bool newValue)
	{
		value.b = newValue;
		empty = false;
		type = VARBOOL;
	}

	void setValue(std::string newValue)
	{
		str = new std::string(newValue);
		empty = false;
		type = VARSTRING;
	}

	inline int toInt() const { return value.i; }
	inline float toFloat() const  { return value.f; }
	inline bool toBool() const  { return value.b; }
	inline std::string toString() const { return *str; }
	inline bool isEmpty() const { return empty; }
};

#pragma warning( default : 26495 )

class PropertyValue : public Variant
{
public:
	PropertyValue()
		: Variant()
	{}

	PropertyValue(int value)
		: Variant(value)
	{}

	PropertyValue(float value)
		: Variant(value)
	{}

	PropertyValue(bool value)
		: Variant(value)
	{}

	PropertyValue(const std::string& value)
		: Variant(value)
	{}
};

class InventoryItem
{
	std::string m_Name;
	std::string m_Code;
	std::map<std::string, PropertyValue> m_Properties;

	bool m_Empty;

public:
	InventoryItem()
	{
		m_Empty = true;
	}

	InventoryItem(const std::string& name, const std::string& code)
	{
		m_Name = name;
		m_Code = code;
		m_Empty = false;
	}

	void addProperty(const std::string& name, const PropertyValue& value)
	{
		m_Properties.insert(std::make_pair(name, value));
	}

	const std::string& getName() const
	{
		return m_Name;
	}

	const std::string& getCode() const
	{
		return m_Code;
	}

	const std::list<std::string> getPropNames() const
	{
		std::list<std::string> ret;
		for (auto i = m_Properties.cbegin(); i != m_Properties.cend(); ++i)
			ret.push_back(i->first);
		return ret;
	}

	const bool hasProperty(const std::string& name) const
	{
		return m_Properties.find(name) != m_Properties.end();
	}

	const PropertyValue& propertyValue(const std::string& name) const
	{
		if (hasProperty(name))
		{
			return m_Properties.at(name);
		}
		return PropertyValue();
	}
};

class Weapon : public InventoryItem
{
};

class Armor : public InventoryItem
{
};

class Player
{
	std::string m_Username;
	mutable std::list<InventoryItem> m_Inventory;
	int m_Level;
	uint64_t m_Expirience;
	bool bot;

public:
	Player()
	{
		m_Level = 1; //synch with Database
		m_Expirience = 0; //synch with Database
		bot = true;
	}

	Player(const std::string& nick)
	{
		m_Username = nick;
		m_Level = 1; //synch with Database
		m_Expirience = 0; //synch with Database
		bot = false;
	}

	const std::string& getName() const
	{
		return m_Username;
	}

	int getLevel() const
	{
		return m_Level;
	}

	uint64_t getExp() const
	{
		return m_Expirience;
	}

	void addItem(const InventoryItem& item)
	{
		m_Inventory.push_back(item);
	}

	const InventoryItem& getItem(const std::string& name) const
	{
		auto res = std::find_if(m_Inventory.cbegin(), m_Inventory.cend(), [&name] (const InventoryItem& v) {
			return v.getName() == name;
		});
		if (res != m_Inventory.cend())
			return *res;
		return InventoryItem();
	}

	const std::list<InventoryItem>& getItems() const
	{
		return m_Inventory;
	}

	int itemCount() const
	{
		return m_Inventory.size();
	}
};

class DataSaveModel
{
	int id;

public:
	void setId(int id) { this->id = id; }
};

struct PlayerSaveModel : public DataSaveModel
{
	Player LocalPlayer;
};

class Obfuscator
{
	HMODULE handle;
	bool invalid;
	typedef bool (__cdecl * _fXor) (const char*, int);

public:
	Obfuscator()
	{
		handle = LoadLibraryA("Packer.dll");
		if (handle == INVALID_HANDLE_VALUE)
		{
			invalid = true;
			std::cerr << "Error load 'Packer.dll'." << std::endl;
			MessageBoxA(GetConsoleWindow(), "Error load 'Packer.dll'.", "Error obfuscating", MB_OK);
		}
		invalid = false;
	}

	~Obfuscator()
	{
		if (handle != INVALID_HANDLE_VALUE)
			FreeLibrary(handle);
	}

	void fileXor(const char* addr, int key)
	{
		if (invalid) return;

		_fXor fXor = (_fXor) GetProcAddress(handle, "pathXor");
		if (fXor != NULL)
		{
			fXor(addr, key);
		}
	}
};

class ISavingService
{
public:
	virtual void save(const DataSaveModel& saveModel, const char* addr) = 0;
};

class PlayerSavingService : public ISavingService
{
	Obfuscator obfuscator;

public:
	void save(const DataSaveModel& saveModel, const char* addr) override
	{
		const PlayerSaveModel& sm = (const PlayerSaveModel&) saveModel;
		const std::list<InventoryItem>& items = sm.LocalPlayer.getItems();
		uint64_t exp = sm.LocalPlayer.getExp();
		int lvl = sm.LocalPlayer.getLevel();
		const std::string& name = sm.LocalPlayer.getName();

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
			
			char fullPath[MAX_PATH];
			GetFullPathNameA(addr, MAX_PATH, fullPath, NULL);
			obfuscator.fileXor(fullPath, 0x55);
		}
	}
};

class SavingFactory
{
public:
	[[nodiscard]] PlayerSavingService* getPlayerSavingModel()
	{
		return new PlayerSavingService();
	}
};

class StaticItemResources
{
	std::map<std::string, InventoryItem> m_Items;

public:
	void registerItem(const std::string& name, const InventoryItem& item)
	{
		m_Items.insert(std::make_pair(name, item));
	}

	const InventoryItem& getItem(const std::string& name) const
	{
		auto ret = m_Items.find(name);
		if (ret != m_Items.end())
			return ret->second;
		return InventoryItem();
	}
};

namespace StaticResources
{
	StaticItemResources staticItemResources;
}

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

	StaticResources::staticItemResources.registerItem("magic_stick", magic_stick);
	StaticResources::staticItemResources.registerItem("magic_gear", magic_gear);
	StaticResources::staticItemResources.registerItem("black_apple", black_apple);
}

int main()
{
	InitResources();

	Player MyPlayer("Amalgama");
	MyPlayer.addItem(StaticResources::staticItemResources.getItem("magic_stick"));
	MyPlayer.addItem(StaticResources::staticItemResources.getItem("black_apple"));

	PlayerSaveModel saveModel;
	saveModel.setId(0);
	saveModel.LocalPlayer = MyPlayer;

	SavingFactory savingFactory;

	ISavingService* savingService = savingFactory.getPlayerSavingModel();
	savingService->save(saveModel, "player.save");

	delete savingService;
	return 0;
}