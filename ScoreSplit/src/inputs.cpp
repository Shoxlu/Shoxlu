#include "inputs.h"
#include "Windows.h"

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
