#include "config.h"
#include <thcrap.h>
#include "util.h"
CfgFile cfg;
extern wchar_t *patch_path;

void read_cfg(const char* fn)
{
    json_t* cfg_json = jsondata_game_get(fn);
	if(cfg_json == nullptr)
	{
		printf("Cfg didn't exist\n");
        create_cfg(fn);
        return;
	}
	char buffer[256];
	for (int i = 0; i < MAXSPLITS; i++)
	{
		auto name = json_object_get_string(cfg_json, itoa(i, buffer, 10));
        if(name == nullptr)
        {
            continue;
        }
        strncpy(cfg.split_names[i],name, 256);
        free((void*)name);
    }
    auto max_index = json_object_get(cfg_json, "n_splits");
    if(max_index == nullptr)
    {
        printf("Cfg isn't updated\n Updating...\n");
        save_cfg(fn);
    }else
    {
        cfg.max_index = json_integer_value(max_index)-1;
    }
}

void create_cfg(const char* fn)
{
    std::string name = "Split ";
    for (int i = 0; i < MAXSPLITS; i++)
	{
        char buffer[10];
        std::string number = itoa(i, buffer, 10);
        std::string full_name = name + number;
        strcpy(cfg.split_names[i], full_name.c_str());
    }
    save_cfg(fn);
}

void save_cfg(const char* fn)
{
    //TODO: Change this function to edit current existing file
	json_t *save = json_object();
	char buffer[100];
    json_object_set(save, "n_splits", json_integer(cfg.max_index+1));
	for (int i = 0; i < MAXSPLITS; i++)
	{
		auto name = cfg.split_names[i];
        auto res = json_object_set_new(save, itoa(i, buffer, 10), json_string(name));
    }
	WCHAR previous_dir[512];
	GetCurrentDirectoryW(512, previous_dir);
	printf("%d %d\n", SetCurrentDirectoryW(patch_path), GetLastError());
	json_dump_file(save, fn, JSON_INDENT(4));
	SetCurrentDirectoryW(previous_dir);
	json_decref(save);
}