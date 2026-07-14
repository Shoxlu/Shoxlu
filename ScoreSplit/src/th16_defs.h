#include "all_defs.h"

struct zFloat2
{
    float x;
    float y;
};
  
struct D3DMATRIX
{
  float m00;
  float m01;
  float m02;
  float m03;
  float m10;
  float m11;
  float m12;
  float m13;
  float m20;
  float m21;
  float m22;
  float m23;
  float m30;
  float m31;
  float m32;
  float m33;
};


struct zFloat3
{
    float x;
    float y;
    float z;
};


struct zFloat4
{
    float x;
    float y;
    float z;
    float w;
};

struct zAnmId
{
  int id;
};

struct zTimer
{
  int previous;
  int current;
  float current_f;
  char game_speed__disused;
  int control;
};

struct zInt3
{
  int x;
  int y;
  int z;
};

struct zAnmFastVm;

struct zAnmFastVmList
{
  zAnmFastVm *entry;
  zAnmFastVmList *next;
  zAnmFastVmList *prev;
  int __seldom_used;
};

struct zRenderVertex144
{
  zFloat4 transformed_pos;
  D3DCOLOR diffuse_color;
  zFloat2 texture_uv;
};

struct zRenderVertex044
{
  zFloat4 transformed_pos;
  D3DCOLOR diffuse_color;
};


struct zGlobals
{
  int32_t CUR_STAGE_NUM;
  int32_t WEIRD_CUR_STAGE_NUM_GLOBAL;
  int32_t CURRENT_CHAPTER;
  int32_t TIME_IN_STAGE;
  int32_t TIME_IN_CHAPTER__POSSIBLY_BROKEN;
  int32_t CHARACTER;
  int32_t SUBSHOT__ZERO_IN_TH16;
  int32_t SUBSEASON;
  int32_t CURRENT_SCORE;
  int32_t DIFFICULTY;
  int32_t CONTINUES_USED;
  int32_t RANK;
  int32_t GRAZE;
  int32_t GRAZE_IN_CHAPTER__POSSIBLY_BROKEN;
  int32_t SPELL_ID;
  int32_t GLOBAL_MISS_COUNT;
  int32_t field_40;
  int32_t NUM_POINT_ITEMS_COLLECTED;
  int32_t CURRENT_PIV;
  int32_t INITIAL_PIV;
  int32_t MAXIMUM_PIV;
  int32_t CURRENT_POWER;
  int32_t __CURRENT_POWER_COPY;
  int32_t POWER_PER_LEVEL;
  int32_t field_60;
  int32_t CURRENT_LIVES;
  int32_t CURRENT_LIFE_FRAGMENTS;
  int32_t NEXT_SCORE_EXTEND_INDEX;
  int32_t CURRENT_BOMBS;
  int32_t CURRENT_BOMB_FRAGMENTS;
  int32_t CURRENT_SEASON_POWER;
  int32_t MAX_SEASON_POWER;
  int SEASON_POWER_LEVEL_DELTAS;
  int field_84;
  int field_88;
  int field_8C;
  int field_90;
  int field_94;
  int field_98;
  int field_9C;
  int field_A0;
  int field_A4;
  int field_A8;
  int SEASON_POWER_LEVEL_REQUIREMENTS[6];
  int MAX_SEASON_POWER_COPY;
};


struct zAnmVmList
{
  int entry;
  int next;
  int prev;
  int __seldom_used;
};


struct zAnmVmSuffix
{
  zAnmId id;
  int fast_id;
  zTimer script_time;
  zTimer __timer_1c;
  zAnmVmList node_in_global_list;
  zAnmVmList node_as_child;
  zAnmVmList list_of_children;
  zAnmVmList __wierd_list_see_usage_at_0x46eb58;
  int next_in_layer;
  int __root_vm__or_maybe_not;
  int parent_vm;
  float slowdown;
  int ins_508_extra_data;
  int ins_508_extra_data_size;
  int index_of_on_wait;
  int index_of_on_tick;
  int index_of_on_draw;
  int index_of_on_destroy;
  int index_of_on_interrupt;
  int index_of_on_copy_1__prolly_pointdevice_leftover;
  int index_of_on_copy_2__prolly_pointdevice_leftover;
  int index_of_sprite_mapping_func;
  zFloat3 entity_pos;
  int associated_game_entity;
  zFloat3 __rotation_related;
};

struct zInterpFloat3
{
  zFloat3 initial;
  zFloat3 goal;
  zFloat3 bezier_1;
  zFloat3 bezier_2;
  zFloat3 current;
  zTimer time;
  int end_time;
  int method;
};


struct zInterpInt3
{
  zInt3 initial;
  zInt3 goal;
  zInt3 bezier_1;
  zInt3 bezier_2;
  zInt3 current;
  zTimer time;
  int end_time;
  int method;
};


struct zInterpInt
{
  int initial;
  int goal;
  int bezier_1;
  int bezier_2;
  int current;
  zTimer time;
  int end_time;
  int method;
};
struct zInterpFloat
{
  float initial;
  float goal;
  float bezier_1;
  float bezier_2;
  float current;
  zTimer time;
  int end_time;
  int method;
};



struct zInterpFloat2
{
  zFloat2 initial;
  zFloat2 goal;
  zFloat2 bezier_1;
  zFloat2 bezier_2;
  zFloat2 current;
  zTimer time;
  int end_time;
  int method;
};

struct zAnmVmPrefix
{
  zTimer interrupt_return_time;
  int interrupt_return_offset;
  int layer;
  int anm_loaded_index;
  int sprite_id;
  int script_id;
  int instr_offset;
  zFloat3 pos;
  zFloat3 rotation;
  zFloat3 angular_velocity;
  zFloat2 scale;
  zFloat2 scale_2;
  zFloat2 scale_growth;
  zFloat2 uv_scale;
  zFloat2 sprite_size;
  zFloat2 uv_scroll_pos;
  zFloat2 anchor_offset;
  char __unknown_136;
  zInterpFloat3 pos_i;
  zInterpInt3 rgb1_i;
  zInterpInt alpha1_i;
  zInterpFloat3 rotate_i;
  zInterpFloat rotate_2d_i;
  zInterpFloat2 scale_i;
  zInterpFloat2 op_434_i;
  zInterpFloat2 uv_scale_i;
  zInterpInt3 rgb2_i;
  zInterpInt alpha2_i;
  zInterpFloat u_vel_i;
  zInterpFloat v_vel_i;
  zFloat2 uv_quad_of_sprite[4];
  zFloat2 uv_scroll_vel;
  D3DMATRIX __matrix_3d0;
  D3DMATRIX __matrix_410;
  D3DMATRIX __matrix_450;
  int pending_interrupt;
  int __time_of_last_sprite_set__unused_;
  int __looks_unused_498;
  __int16 __related_to_script_index;
  char __unknown_1182;
  int int_script_vars[4];
  float float_script_vars[4];
  zFloat3 __script_vars_33_34_35__rotation_related;
  int __script_var_8;
  int __script_var_9;
  float rand_scale_one;
  float rand_scale_pi;
  int num_cycles_in_texture;
  zFloat3 __pos_2;
  zFloat3 last_rendered_quad_in_surface_space[4];
  int mode_of_create_child;
  D3DCOLOR color_1;
  D3DCOLOR color_2;
  D3DCOLOR mixed_inherited_color;
  char font_dims[2];
  char __unknown_1326;
  int flags_lo;
  int flags_hi;
};

struct zAnmVm
{
  zAnmVmPrefix p;
  zAnmVmSuffix s;
};


struct zAnmFastVm
{
  zAnmVm vm;
  zAnmFastVmList freelist_node;
  int is_alive;
  int fast_id;
};

struct zThread
{
  int vtable;
  int thread;
  int tid;
  int __bool_c;
  int __bool_10;
  char __unknown_20;
  char phModule;
};


struct zAnmPreloadedArray
{
  int anm_00_text;
  int anm_01_sig;
  int anm_02_ascii;
  int anm_03_stage_wl_even;
  int anm_04_stage_wl_odd;
  int anm_05_front;
  int anm_06_stage_logo;
  int anm_07_bullet;
  int anm_08_effect;
  int anm_09_player;
  int anm_10_anms_for_ecl_anim;
  _BYTE gap2C[12];
  char __unknown_56;
  _BYTE gap39[7];
  int anm_16_title;
  int anm_17_title_v;
  char __unknown_72;
  int anm_19_help;
  int anm_20_ending_or_staff;
  char __unknown_84;
  _BYTE gap55[35];
  int anm_30_subseason;
};



struct zAnmVertexBuffers
{
  int unrendered_sprite_count;
  zRenderVertex144 sprite_vertex_data[131072];
  int sprite_write_cursor;
  int sprite_render_cursor;
  int unrendered_primitive_count;
  zRenderVertex044 primitive_vertex_data[32768];
  int primitive_write_cursor;
  int primitive_render_cursor;
};


struct zAnmManager
{
  zThread thread;
  char __unknown_28;
  _BYTE gap1D[187];
  int useless_count;
  int world_list_head;
  int world_list_tail;
  int ui_list_head;
  int ui_list_tail;
  zAnmFastVm fast_array[8191];
  int __lolk_next_snapshot_fast_id;
  int __lolk_next_snapshot_discriminator;
  zAnmVmList __lolk_vm_snapshot_list_head;
  zAnmFastVm __lolk_fast_snapshot_array[8191];
  zAnmFastVmList freelist_head;
  char __unknown_25490668;
  zAnmPreloadedArray preloaded;
  D3DMATRIX __matrix_184f56c__used_during_rendering;
  zAnmVm __vm_184f5ac;
  char __unknown_25492392;
  _BYTE gap184FBA9[111];
  zAnmVertexBuffers vertex_buffers;
  zAnmVm layer_list_dummy_heads[43];
  int last_discriminator__19bit;
  char __unknown_29883784;
  static zAnmVm * allocate_vm();
  
};
struct zAsciiStr
{
  char text[256];
  zFloat3 pos;
  D3DCOLOR color;
  zFloat2 scale;
  int __field_118;
  int __field_11c;
  int font_id;
  int draw_shadows;
  int render_group;
  int remaining_time;
  int align_h;
  int align_v;
};

struct zAsciiManager
{
  char __unknown_0;
  _BYTE gap1[7];
  int on_tick;
  int on_draw_1;
  zAnmVm __vm_1;
  zAnmVm __vm_2;
  zAsciiStr strings[320];
  int num_strings;
  D3DCOLOR color;
  zFloat2 scale;
  int __str_field_11c;
  int __unused;
  int draw_shadows;
  int font_id;
  int group;
  int duration;
  int alignment_mode_h;
  int alignment_mode_v;
  int character_spacing_for_font_0;
  int num_ticks_alive;
  int ascii_anm;
  zAnmId __unknown_anm_id;
  zAnmId id_for__now_loading;
  int on_draw_2;
  int on_draw_3;
};


int ascii_sprintf_408260(zAsciiManager *a1, zFloat3 *a2, const char *Buffer, ...);
unsigned int draw_text2(zAnmManager *a1, zAnmFastVm *vm, COLORREF color, int a4, int a5, int a6, char *Buffer, int size__, ...);
extern "C" HWND g_window;
extern "C" HWND hDlg;
// extern "C" zBomb * BOMB_PTR;
// extern "C" zPlayer * PLAYER_PTR;
// extern "C" zBulletManager * BULLET_MANAGER_PTR;
// extern "C" zSpellcard * SPELLCARD_PTR;
// extern "C" zLaserManager * LASER_MANAGER_PTR;
extern "C" zAnmManager * ANM_MANAGER_PTR;
extern "C" zAsciiManager * ASCII_MANAGER_PTR;
// extern "C" zMainMenu * MAINMENU_PTR;
extern "C" zGlobals GLOBALS;
