#include "th16.h"


#define DEBUG

#define MAXSPLITS 255

zAnmVm *vm;
wchar_t* patch_path;

int recorded_scores[MAXSPLITS];
int current_scores[MAXSPLITS];
int previous_current_scores[MAXSPLITS];
int previous_recorded_scores[MAXSPLITS];

int max_index = 6;
int current_index = 0;
int previous_index = 0;
int max_number_to_be_shown = 8;

int STARTING_X = 440;
int STARTING_Y = 260;

enum timer_names
{
	REGISTER,
	RESET,
	CANCEL_RESET,
	CANCEL_ACTION
};

struct Timer{
	unsigned int previous;
	unsigned int current;
	unsigned int duration;
	bool is_finished()
	{
		return this->current == 0;
	}
	void tick_timer()
	{
		if(!is_finished())
		{
			this->previous = this->current;
			this->current--;
		}
	}
	void set_timer(unsigned int duration){
		this->current = duration;
		this->previous = duration;
		this->duration = duration;
	}
	void reset()
	{
		set_timer(this->duration);
	}
	
};

Timer timers[16];

void tick_all_timers(Timer timers[], int size){
	for (int i = 0; i< size; i++)
	{
		timers[i].tick_timer();
	}
}

void reset_scores(int scores[MAXSPLITS], int backup_scores[MAXSPLITS])
{
	for(int i = 0;i< MAXSPLITS; i++)
	{
		backup_scores[i] = scores[i];
		scores[i] = 0;
	}
	current_index = -1;
}

void cancel_reset(int scores[MAXSPLITS], int backup_scores[MAXSPLITS])
{
	current_index = previous_index;
	for(int i = 0; i< MAXSPLITS; i++)
	{
		scores[i] = backup_scores[i];
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
	int beginning = max(0, - max_number_to_be_shown + current_index);
	for (int i = beginning; i < min(max_number_to_be_shown+beginning, max_index+1); i++)
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
	int beginning = max(0, - max_number_to_be_shown + current_index);
	for (int i = beginning; i < min(max_number_to_be_shown+beginning, max_index+1); i++)
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
	//printf("Current score when index %d: %d\n", index, GLOBALS.CURRENT_SCORE);
	scores[index % (max_index+1)] = GLOBALS.CURRENT_SCORE;
}

bool is_register_key_pressed()
{
	return (GetKeyState(VK_SPACE) & 0x8000);
}

bool is_cancel_action_key_pressed()
{
	return (GetKeyState(VK_BACK) & 0x8000);
}

bool is_reset_key_pressed()
{
	return (GetKeyState('L') & 0x8000);
}
bool is_cancel_reset_key_pressed()
{
	return (GetKeyState('M') & 0x8000);
}


void update_scores()
{
	register_score(current_scores, current_index);
	if(current_scores[current_index] > recorded_scores[current_index])
	{
		register_score(recorded_scores, current_index);
	}
}

void next_split()
{
	printf("Next split !\n");
	if(current_index < max_index)
	{
		previous_recorded_scores[current_index] = recorded_scores[current_index];
		previous_index = current_index++;
		timers[REGISTER].reset();
	}
}

void cancel_action()
{
	printf("Cancel action !\n");
	recorded_scores[current_index] = previous_recorded_scores[current_index];
	current_scores[current_index] = 0;
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
		recorded_scores[i] = atoi(score);
		previous_recorded_scores[i] = atoi(score);
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
		auto score = recorded_scores[i];
		json_object_set_new(save, itoa(i, buffer, 10), json_string(itoa(score, buffer, 10)));
	}
	WCHAR previous_dir[512];
	GetCurrentDirectoryW(512, previous_dir);
	printf("%d %d\n", SetCurrentDirectoryW(patch_path), GetLastError());
	json_dump_file(save, filename, JSON_INDENT(4));
	SetCurrentDirectoryW(previous_dir);
	json_decref(save);
}

extern "C" void on_update()
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

int find(std::string path, const char* s, size_t s_len)
{
	int len = path.length();
	for (int i = 0; i < len; i++)
	{
		int j = 0;
		while(j < s_len && s[j] == path[j+i])
		{
			j++;
		}
		if(j == s_len)
		{
			return i;
		}
	}
	return -1;
}


wchar_t *utf8_to_wchar(const char *utf8)
{
    int size = MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8,
        -1,
        NULL,
        0
    );

    if (size == 0)
        return NULL;

    wchar_t *result = (wchar_t*)malloc(size * sizeof(wchar_t));
    if (!result)
        return NULL;

    MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8,
        -1,
        result,
        size
    );

    return result;
}

wchar_t* get_full_patch_path()
{
	const char *fn = ".t";

	std::string path = fn;
	char **chain = resolve_chain_game(path.c_str());
	char *c_full_path = stack_fn_resolve_chain(chain);
	chain_free(chain);

	path.assign(c_full_path, strlen(c_full_path) - strlen(fn));
	thcrap_free(c_full_path);

	int ds_pos = find(path, "//", strlen("//"));

	while(ds_pos >= 0)
	{
		path.replace(ds_pos, 2, "/");
		ds_pos = find(path, "//", strlen("//"));
	}
	wchar_t *conv = utf8_to_wchar(path.c_str());
	
	return conv;
}

extern "C" int hook_entry() {
#ifdef DEBUG

	AllocConsole();
	// SetConsoleOutputCP(CP_UTF8);
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
	timers[REGISTER].set_timer(50);
	timers[CANCEL_RESET].set_timer(50);
	timers[CANCEL_ACTION].set_timer(50);
	timers[RESET].set_timer(50);
	hook_entry();
	get_scores();
	patch_path = get_full_patch_path();

	save_scores("save.back.json");

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
