#include "th16.h"
#include "linkerHacks.h"
#include "utils.h"
#include "th16_defs.h"
#include "config.h"
#include "timer.h"
#include "inputs.h"


#define NCHARACTERS 4
#define NSUBSHOTS 4
extern wchar_t* patch_path;
extern CfgFile cfg;

namespace th16{

enum timer_names
{
	REGISTER,
	RESET,
	CANCEL_RESET,
	CANCEL_ACTION
};


Timer timers[16];


enum Characters
{
	Reimu,
	Marisa,
	Aya,
	Cirno
};

enum Subshots
{
	Spring,
	Winter,
	Autumn,
	Summer,
};


int recorded_scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS];
int current_scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS];
int previous_current_scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS];
int previous_recorded_scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS];

int max_index = 5;
int current_index = 0;
int previous_index = 0;
int max_number_to_be_shown = 8;

int STARTING_X = 440;
int STARTING_Y = 260;



void reset_scores(int scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS], int backup_scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS])
{
	for(int i = 0;i< MAXSPLITS; i++)
	{
		backup_scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON];
		scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = 0;
	}
	current_index = -1;
}

void cancel_reset(int scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS], int backup_scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS])
{
	current_index = previous_index;
	for(int i = 0; i< MAXSPLITS; i++)
	{
		scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = backup_scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON];
	}
}

void reset_ascii()
{
	zAsciiManager* ptr = ASCII_MANAGER_PTR;
	ptr->color = (D3DCOLOR)0xFFFFFFFF;
	ptr->alignment_mode_h = 1;
	ptr->alignment_mode_v = 1;
	ptr->scale.x = 1.0;
	ptr->scale.y = 1.0;
	ptr->font_id = 0;
	ptr->group = 0;
	ptr->duration = 1;
}

void test()
{
	zFloat3 pos;
	pos.x = 128;
	pos.y = 128;
	pos.z = 0;
	zAsciiManager* ptr = ASCII_MANAGER_PTR;
	ptr->color = (D3DCOLOR)0xFFFFFFFF;
	ptr->alignment_mode_h = 1;
	ptr->alignment_mode_v = 1;
	ptr->scale.x = 30.0;
	ptr->scale.y = 30.0;
	ptr->font_id = 0;
	ptr->group = 0;
	ptr->duration = 1;
	ascii_sprintf_408260(ASCII_MANAGER_PTR, &pos, "Aaaaaaah");
	reset_ascii();
	printf("Je print là\n");
}

void print_single_score(zFloat3* pos, int score, int index)
{
	zAsciiManager* ptr = ASCII_MANAGER_PTR;
	ptr->alignment_mode_h = 1;
	ptr->alignment_mode_v = 1;
	ptr->scale.x = 1.0;
	ptr->scale.y = 1.0;
	ptr->font_id = 0;
	ptr->group = 0;
	ptr->duration = 2;
	ascii_sprintf_408260(ASCII_MANAGER_PTR, pos, "%s: %d", cfg.split_names[index], score);
	reset_ascii();
}

void print_current_scores()
{
	int beginning = max(0, - max_number_to_be_shown + current_index);
	for (int i = beginning; i < min(max_number_to_be_shown+beginning, max_index+1); i++)
	{
		zFloat3 pos;
		pos.x = STARTING_X;
		pos.y = STARTING_Y + (i - beginning) * 24;
		ASCII_MANAGER_PTR->color = (D3DCOLOR)0xFFFFFFFF;
		print_single_score(&pos, current_scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON]*10, i);
	}
}
void print_recorded_scores()
{
	int beginning = max(0, - max_number_to_be_shown + current_index);
	for (int i = beginning; i < min(max_number_to_be_shown+beginning, max_index+1); i++)
	{
		zFloat3 pos;
		pos.x = STARTING_X;
		pos.y = STARTING_Y + 12 + (i - beginning) * 24;
		ASCII_MANAGER_PTR->color = 0xFF0000FF;
		print_single_score(&pos, recorded_scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON]*10, i);
	}
}

void register_score(int scores[MAXSPLITS][NCHARACTERS][NSUBSHOTS], int index)
{
	//printf("Current score when index %d: %d\n", index, GLOBALS.CURRENT_SCORE);
	scores[index % (max_index+1)][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = GLOBALS.CURRENT_SCORE;
}

void update_scores()
{
	register_score(current_scores, current_index);
	if(current_scores[current_index][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] > recorded_scores[current_index][GLOBALS.CHARACTER][GLOBALS.SUBSEASON])
	{
		register_score(recorded_scores, current_index);
	}
}

void next_split()
{
	printf("Next split !\n");
	if(current_index < max_index)
	{
		previous_recorded_scores[current_index][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = recorded_scores[current_index][GLOBALS.CHARACTER][GLOBALS.SUBSEASON];
		previous_index = current_index++;
		timers[REGISTER].reset();
	}
}

void cancel_action()
{
	printf("Cancel action !\n");
	recorded_scores[current_index][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = previous_recorded_scores[current_index][GLOBALS.CHARACTER][GLOBALS.SUBSEASON];
	current_scores[current_index][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = 0;
	current_index = previous_index;
	timers[CANCEL_ACTION].reset();
}

void reset_splits()
{
	printf("Reset !\n");
	previous_index = current_index;
	reset_scores(current_scores, previous_current_scores);
	timers[RESET].reset();
}

void get_scores()
{
	jsondata_game_add("save.json");
	json_t* save = jsondata_game_get("save.json");
	if(save == nullptr)
	{
		printf("Save didn't exist\n");
		return;
	}
	char buffer[100];
	for (int i = 0; i < MAXSPLITS; i++)
	{
		auto score = json_object_get_string(save, itoa(i, buffer, 10));
		recorded_scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = atoi(score);
		previous_recorded_scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON] = atoi(score);
		free((void*)score);
	}
}

void save_scores(const char* filename)
{
	//In one file named "save.json", put all current records as they are during current session
	//TODO: Change this function to edit current existing file
	json_t *save = json_object();
	char buffer[100];
	for (int i = 0; i < MAXSPLITS; i++)
	{
		auto score = recorded_scores[i][GLOBALS.CHARACTER][GLOBALS.SUBSEASON];
		json_t *value =  json_string(itoa(score, buffer, 10));
		json_object_set_new(save, itoa(i, buffer, 10),value);

	}
	WCHAR previous_dir[512];
	GetCurrentDirectoryW(512, previous_dir);
	printf("%d %d\n", SetCurrentDirectoryW(patch_path), GetLastError());
	json_dump_file(save, filename, JSON_INDENT(4));
	SetCurrentDirectoryW(previous_dir);
	json_decref(save);
}

void on_update()
{
	//printf("current:%d, previous %d\n", current_index, previous_index);
	if(!ASCII_MANAGER_PTR)
	{
		return;
	}
	if(current_index >= 0 && current_index <= max_index)
	{
		update_scores();
	}
	if(is_register_key_pressed() && timers[REGISTER].is_finished())
	{
		next_split();
		save_scores("save.json");
	}else
	if(is_cancel_action_key_pressed() && timers[CANCEL_ACTION].is_finished())
	{
		cancel_action();
	}else
	// if(is_cancel_reset_key_pressed() && timers[CANCEL_RESET].is_finished())
	// {
	// 	printf("Cancel reset !\n");
	// 	previous_index = current_index;
	// 	cancel_reset(recorded_scores, previous_recorded_scores);
	// 	timers[CANCEL_RESET].reset();
	// }else
	if(is_reset_key_pressed() && timers[RESET].is_finished())
	{
		reset_splits();
	}
	print_current_scores();
	print_recorded_scores();
	tick_all_timers(timers, 16);
}

void init()
{
	timers[REGISTER].set_timer(50);
	timers[CANCEL_RESET].set_timer(50);
	timers[CANCEL_ACTION].set_timer(50);
	timers[RESET].set_timer(50);

	get_scores();
	jsondata_game_add("cfg.json");
	printf("scores ok\n");
	read_cfg("cfg.json");
	printf("cfg okay\n");
	save_scores("save.back.json");
}

};