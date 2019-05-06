#ifndef XULICHUNG_H
#define XULICHUNG_H

#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<vector>
//Screen
const int WIDTH_BACKGROUND = 1280;
const int HEIGTH_BACKGROUND = 7920;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;
const int SPEED_SCREEN = 1;
//tốc độ và vị trí Human
const int POS_X_START_MAIN_OBJ = 550;
const int POS_Y_START_MAIN_OBJ = 500;
const int SPEED_MAIN_OBJECT = 5;
const int SPEED_BULLET_MAIN = 20;
// Số mạng của human
const int LIFE_MAIN_OBJECT = 3;
//Số lượng Kẻ địch, tốc độ đạn
const int NUM_KEDICH = 3;
const int SPEED_BULLET_THREAT = 8;

static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Event g_even;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_sound_obj[2];
//ảnh đạn và âm thanh đạn cho human
static char g_name_bk_ground[] = {"bkground2.png"};
static char g_name_main_obj[] = {"human80x80.png"};
static char g_name_life_obj[] = {"life.png"};
static char g_exp_main[] = {"exp.png"};
static char g_name_bullet_main_lazer[] = {"lazer.png"};
static char g_name_bullet_main_sphere[] = {"sphere.png"};
static char g_name_audio_bullet_main[] = {"lazer.wav"};
static char g_name_audio_bullet_main1[] = {"sphere.wav"};
static char g_name_audio_exp[] = {"explosion.wav"};
//ảnh và đạn cho kẻ địch
static char g_name_threat[] = {"kedich.png"};
static char g_name_threat1[] = {"kedich1.png"};
static char g_name_threat2[] = {"kedich2.png"};
static char g_name_bullet_threat[] = {"sphere1.png"};
static char g_name_audio_threat[] = {"threat1.wav"};

namespace SDLXuLiChung{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface *src, SDL_Surface *des, SDL_Rect *clip, int x, int y);
	void CleanUp();
	bool VaCham(const SDL_Rect &object1, const SDL_Rect &object2);
}

#endif