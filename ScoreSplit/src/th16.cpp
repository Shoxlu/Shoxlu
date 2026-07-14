#include "th16.h"


#define DEBUG

zAnmVm *vm;
int recorded_scores[255];
int current_scores[255];
int previous_recorded_scores[255];

int max_index = 16;
int current_index = 0;
int max_index_to_be_shown = 7;

int STARTING_X = 440;
int STARTING_Y = 260;

void reset_scores(int scores[255])
{
	for(int i = 0;i< 255; i++)
	{
		scores[i] = 0;
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
	ascii_sprintf_408260(ASCII_MANAGER_PTR, pos, "Split %d: %d", index, score);
	reset_ascii();
}

void print_current_scores()
{
	int beginning = min(0, max_index_to_be_shown - current_index);
	for (int i = beginning; i < min(max_index_to_be_shown+1+beginning, max_index+1); i++)
	{
		zFloat3 pos;
		pos.x = STARTING_X;
		pos.y = STARTING_Y + (i - beginning) * 24;
		ASCII_MANAGER_PTR->color = (D3DCOLOR)0xFFFFFFFF;
		print_single_score(&pos, current_scores[i]*10, i);
	}
}
void print_recorded_scores()
{
	int beginning = min(0, max_index_to_be_shown - current_index);
	for (int i = beginning; i < min(max_index_to_be_shown+beginning, max_index)+1; i++)
	{
		zFloat3 pos;
		pos.x = STARTING_X;
		pos.y = STARTING_Y + 12 + (i - beginning) * 24;
		ASCII_MANAGER_PTR->color = 0xFF0000FF;
		print_single_score(&pos, recorded_scores[i]*10, i);
	}
}

void register_score(int scores[], int index)
{
	printf("Current score when index %d: %d\n", index, GLOBALS.CURRENT_SCORE);
	scores[index % (max_index+1)] = GLOBALS.CURRENT_SCORE;
}

bool is_register_key_pressed()
{
	return false;
}

bool is_cancel_action_key_pressed()
{
	return false;
}

bool is_reset_key_pressed()
{
	return false;
}

extern "C" void on_update()
{
	// printf("ASCII_MANAGER_PTR:%x\n", ASCII_MANAGER_PTR);
	if(!ASCII_MANAGER_PTR)
	{
		return;
	}
	register_score(current_scores, current_index);
	if(current_scores[current_index] > recorded_scores[current_index])
	{
		register_score(recorded_scores, current_index);
	}
	if(is_register_key_pressed())
	{
		current_index++;
		previous_recorded_scores[current_index] = recorded_scores[current_index];
	}
	if(is_cancel_action_key_pressed())
	{
		recorded_scores[current_index] = previous_recorded_scores[current_index];
		current_scores[current_index] = 0;
		if(current_index > 0)
		{
			current_index--;
			recorded_scores[current_index] = previous_recorded_scores[current_index];
		}
	}
	if(is_reset_key_pressed())
	{
		reset_scores(current_scores);
	}
	print_current_scores();
	print_recorded_scores();
}

extern "C" int hook_entry() {
#ifdef DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	printf("beginning of the func hook_entry at: %x\n", (size_t)hook_entry);
	//printf("location of the func bomb_sanae at: %x\n", (size_t)bomb_sanae);
	//printf("location of the func bomb_sanae_clear_bullets at: %x\n", zBombSanae::bomb_sanae_clear_bullets);
	//std::thread t1(on_update);
#endif // DEBUG
	Sleep(1000);
#ifdef DEBUG
	printf("End of the func hook_entry \n");
#endif

    return 0;
}

extern "C" void coff2binhack_init() {
	//Sleep(5000);
	hook_entry();

}


// const char* find_spell_name(std::string extension) {
// 	const char* new_name = NULL;
// 	int true_id = (SPELLCARD_PTR->spell_id);
// 	json_t* spells = jsondata_game_get("spells.js");
// 	int base_id = SPELLCARD_PTR->spell_id - GLOBALS.inner.DIFFICULTY;
// 	std::vector<std::string> ids = { std::to_string(base_id)+extension, 
// 		std::to_string(base_id + 1) + extension,
// 		std::to_string(base_id + 2) + extension,
// 		std::to_string(base_id + 3) + extension };
// 	for (auto& i : ids) {
// 		if ((new_name = json_object_get_string(spells, i.c_str())))
// 		{
// 			return new_name;
// 		}
// 	}
// 	return "";
// }
