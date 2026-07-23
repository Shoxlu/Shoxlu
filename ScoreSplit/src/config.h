#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#pragma clang diagnostic ignored "-Wdll-attribute-on-redeclaration"

#define MAXSPLITS 255

struct CfgFile
{
    
    int max_index = 5;
    char split_names[MAXSPLITS][256];
};

void read_cfg(const char *fn);
void create_cfg(const char *fn);
void save_cfg(const char *fn);