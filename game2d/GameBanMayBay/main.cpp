#include"XuLiChung.h"
#include"DoiTuongChinh.h"
#include"KeDich.h"
#include"VuNo.h"
#include"Mang.h"
#include"TextDiem.h"

TTF_Font* g_font_text = NULL;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		return false;
	}
	g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_bullet_main);
	g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_bullet_main1);
	g_sound_exp[0] = Mix_LoadWAV(g_name_audio_exp);
	g_sound_obj[0] = Mix_LoadWAV(g_name_audio_threat);
	if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL || g_sound_obj[0] == NULL){
		return false;
	}

	if(TTF_Init() == -1){
		return false;
	}
	g_font_text = TTF_OpenFont("diem.ttf", 20);
	if(g_font_text == NULL){
		return false;
	}

	return true;
}


int main(int arc, char * argv[]){
	bool is_run_screen = true;
	int bkgn_y = 0;
	bool is_quit = false;
	if (Init() == false){
    	return 0;
	}
	g_bkground = SDLXuLiChung::LoadImage(g_name_bk_ground);
	if (g_bkground == NULL)
	{
		return 0;
	}
	//Tạo hiển thị mạng cho người chơi
	Mang player_power;
	player_power.Init();

	//Tạo điểm cho người chơi
	TextDiem mark_game;
	mark_game.SetColor(TextDiem::WHITE_TEXT);

	//tạo đối tượng người chơi human(plane )
	DoiTuongChinh plane_object;
	plane_object.SetRect(POS_X_START_MAIN_OBJ , POS_Y_START_MAIN_OBJ );
	bool ret = plane_object.LoadImg(g_name_main_obj);

	if(!ret ){
		return 0;
	}

	//tạo vụ nổ cho human
	VuNo  exp_plane;
	VuNo exp_kedich;

	ret = exp_plane.LoadImg(g_exp_main);
	exp_plane.set_clip();
	if(ret == false){
		return 0;
	}

/*	std::vector<KeDich*> kedich_list = TaoKeDichList();*/
		
	//tạo kẻ địch
	KeDich *p_KeDich = new KeDich[NUM_KEDICH];

	for(int t=0; t < NUM_KEDICH; t++){
		KeDich *p_kedich = (p_KeDich + t );
		if(p_kedich){
			ret = p_kedich->LoadImg(g_name_threat);
			if(ret == false ){
				return 0;
			}

			int rand_x = rand()%1000;
			if(rand_x > SCREEN_WIDTH){
				rand_x = SCREEN_WIDTH*0.3;
			}

			p_kedich->SetRect( rand_x, SCREEN_HEIGHT + t*50);
			p_kedich->set_y_val(3);

			Dan *p_amo = new Dan();
			p_kedich->InitAmo(p_amo);

		}	
	}


	unsigned int life_number = 0;
	unsigned int mark_value = 0;

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			plane_object.HandleInputAction(g_even, g_sound_bullet);
		}
		//Apply background
		bkgn_y += SPEED_SCREEN;
		SDLXuLiChung::ApplySurface(g_bkground, g_screen, 0, bkgn_y);
		SDLXuLiChung::ApplySurface(g_bkground, g_screen, 0, bkgn_y - SCREEN_HEIGHT);
		if(bkgn_y >= SCREEN_HEIGHT){
			bkgn_y = 0;
		}

		//Hiển thị mạng của người chơi
		player_power.Render(g_screen);

		//Tạo đối tượng người chơi
		plane_object.HandleMove();//Di chuyển cho human
		plane_object.Show(g_screen);// Cập nhật lại ảnh nền
		plane_object.MakeAmo(g_screen); // Bắn đạn cho human
		
		//Run nhiều kẻ địch
		for(int tt= 0; tt < NUM_KEDICH; tt++){
			KeDich *p_kedich = (p_KeDich + tt);
			if(p_kedich){
				p_kedich->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT, g_sound_obj);
				p_kedich->Show(g_screen);
				p_kedich->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				//Va chạm giữa đạn của kẻ địch và người chơi human
				bool is_col1 = false;
				std::vector<Dan*> amo_arr = p_kedich->GetAmoList();
				for(int am= 0; am < amo_arr.size(); am++){
					Dan *p_amo = amo_arr.at(am);
					if(p_amo){
						is_col1 = SDLXuLiChung::VaCham(plane_object.GetRect(), p_amo->GetRect());
						if(is_col1 == true){
							p_kedich->ResetAmo(p_amo);
							break;
						}
					}
				}

				// Kiểm tra va chạm giữa human và kẻ địch
				bool is_col = SDLXuLiChung::VaCham(plane_object.GetRect(), p_kedich->GetRect());
				if(is_col1 || is_col){

					for(int ex = 0; ex < 4; ex++){
						int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH*0.5;
						int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT*0.5;

						exp_plane.set_frame(ex);
						exp_plane.SetRect(x_pos, y_pos);
						exp_plane.ShowEX(g_screen);

						//Khi va chạm giữa người chơi và kẻ địch, kẻ địch biến mất
						if(is_col){
                            p_kedich->Reset( SCREEN_HEIGHT + tt*500);//Reset kẻ địch về vị trí ban đầu
						}

						//Update screen
						if ( SDL_Flip(g_screen) == -1){
							delete [] p_KeDich;
							SDLXuLiChung::CleanUp();
							SDL_Quit();
							return 0;
						}
					}
					Mix_PlayChannel(-1, g_sound_exp[0], 0);
					life_number ++;
					if(life_number <= LIFE_MAIN_OBJECT ){
						SDL_Delay(1000);
						plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
						player_power.Decrease();
						player_power.Render(g_screen);

						if(SDL_Flip(g_screen) == -1){
							delete [] p_KeDich;
							SDLXuLiChung::CleanUp();
							SDL_Quit();
							return 0;
						}
					}
					else{
						if( MessageBoxW(NULL, L"GAME OVER!", L"Infor", MB_OK) == IDOK){
							delete []p_KeDich;
							SDLXuLiChung::CleanUp();
							SDL_Quit();
							return 1;
						}
					}

				}

				// va chạm giữa đạn của người chơi( human) và kẻ địch
				std::vector<Dan*> amo_list = plane_object.GetAmoList();
				for(int im =0; im < amo_list.size(); im++){
					Dan *p_amo = amo_list.at(im);
					if(p_amo != NULL){
						bool ret_col = SDLXuLiChung::VaCham(p_amo->GetRect(), p_kedich->GetRect());
						if(ret_col){

							mark_value++;
							for(int tx = 0; tx < 4; tx++){
								int x_pos = p_amo->GetRect().x - EXP_WIDTH*0.5;
								int y_pos = p_amo->GetRect().y - EXP_HEIGHT*0.5;

								exp_plane.set_frame(tx);
								exp_plane.SetRect(x_pos, y_pos);
								exp_plane.ShowEX(g_screen);
								//Update screen
								if ( SDL_Flip(g_screen) == -1){
									delete [] p_KeDich;
									SDLXuLiChung::CleanUp();
									SDL_Quit();
									return 0;
								}
							}

							p_kedich->Reset( SCREEN_HEIGHT + tt*500);//Reset kẻ địch về vị trí ban đầu
							plane_object.RemoveAmo(im);// Xóa viên đạn được bắn vào kẻ địch
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
						}
					}
				}
			}
		}


		//Hiển thị điểm của người chơi
		std::string val_str_mark = std::to_string(static_cast<long long>(mark_value));
		std::string strMark("SCORE: ");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		mark_game.CreateNameText(g_font_text, g_screen);

		//Update screen
		if ( SDL_Flip(g_screen) == -1){
			delete [] p_KeDich;
			SDLXuLiChung::CleanUp();
			SDL_Quit();
			return 0;
		}
	}
	delete [] p_KeDich;
	SDLXuLiChung::CleanUp();
	SDL_Quit();
	return 0;

}