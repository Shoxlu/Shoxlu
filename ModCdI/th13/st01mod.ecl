anim { "enemy.anm"; "st01enm.anm"; }
ecli { "default.ecl";}

#include "etama.tecl"
global NEG= 999999;
void main()
{
	enmCreateA("Gnegne", 0f, 120f, 1000, 1000, 1);
	wait(10000);
}

void Gnegne()
{
	anmSelect(2);
	anmSetMain(0, 4);
	etNew(0);
	etAim(0, 1);
	etSprite(0, ET_KNIFE, 3);
	etSpeed(0, -1f, -1f);
	etAngle(0, rad(90), 0f);
	//etExSet(0, 0, 0, EX_WAIT, 10, -999999, -999999f, -999999f);
	//etExSet(0, 0, 0, EX_VELTIME, 60, NEG, 1f, rad(90));
	wait(180);
	etOn(0);
}