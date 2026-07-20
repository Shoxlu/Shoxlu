#include "main.h"
#include "th16.h"


#define DEBUG

wchar_t* patch_path;

#define UPDATE_FUNC void (*func_ptr)(void)
#define INIT_FUNC 

void (*on_update_ptr)(void);
void (*on_init)(void);

int get_game()
{
    return 16;
}

void init_func_ptrs(int game)
{
    switch (game)
    {
    case 16:
        on_update_ptr = th16::on_update;
        th16::init();
        break;
    
    default:
        break;
    }
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

extern "C" void on_update()
{
    on_update_ptr();
}

extern "C" void coff2binhack_init() {
	//Sleep(5000);
    hook_entry();
    patch_path = get_full_patch_path();
	printf("%s\n", patch_path);
	init_func_ptrs(get_game());
    printf("End of init\n");
}