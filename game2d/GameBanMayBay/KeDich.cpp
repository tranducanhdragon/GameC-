#include"KeDich.h"

KeDich::KeDich(){
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_KEDICH;
	rect_.h = HEIGTH_KEDICH;
	x_val_ = 0;
	y_val_ = 0;
}
KeDich::~KeDich(){
	if(p_amo_list_.size() > 0){
		for(int i =0; i < p_amo_list_.size(); i++){
			Dan *p_amo = p_amo_list_.at(i);
			if(p_amo != NULL){
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void KeDich::InitAmo(Dan * p_amo){
	if(p_amo != NULL){
		bool ret = p_amo->LoadImg(g_name_bullet_threat);
		if(ret){
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(Dan::SPHERE);
			p_amo->SetRect(rect_.x + rect_.w*0.5, rect_.y);
			p_amo->set_y_val(SPEED_BULLET_THREAT);
			p_amo_list_.push_back(p_amo);
		}
	}
}

void KeDich::MakeAmo(SDL_Surface *des, const int &x_limit, const int &y_limit){
	for(int i=0; i < p_amo_list_.size(); i++){
		Dan *p_amo = p_amo_list_.at(i);
		if(p_amo){
			if(p_amo->get_is_move()){
				p_amo->Show(des);
				p_amo->HandleMoveUpToDown(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x + rect_.w*0.5, rect_.y + rect_.h);
			}
		}
	}
}
void KeDich::HandleMove(const int& x_border, const int& y_border, Mix_Chunk *threat_sound[2]){
	rect_.y += y_val_;
	if(rect_.y > SCREEN_WIDTH){
		rect_.y = 0;
		int rand_y = rand()%1000;
		if(rand_y > SCREEN_WIDTH){
			rand_y = SCREEN_WIDTH*0.3;
		}
		rect_.x = rand_y;
		Mix_PlayChannel(-1, threat_sound[0], 0);
	}
}

void KeDich::HandleInputAction(SDL_Event events){

}

void KeDich::ResetAmo(Dan *p_amo){
	p_amo->SetRect(rect_.x + rect_.w*0.5, rect_.y + rect_.h);
}
void KeDich::Reset(const int &yborder ){
	rect_.y = yborder;
	int rand_y = rand()%1000;
	if(rand_y > SCREEN_WIDTH){
		rand_y = SCREEN_WIDTH*0.3;
	}
	rect_.x = rand_y;

	//Reset đạn của kẻ địch
// 	for(int i= 0; i < p_amo_list_.size(); i++){
// 		Dan * p_amo = p_amo_list_.at(i);
// 		if(p_amo){
// 			ResetAmo(p_amo);
// 		}
// 	}
}