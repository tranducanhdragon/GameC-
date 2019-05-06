#include"DoiTuongChinh.h"

DoiTuongChinh::DoiTuongChinh(){
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

DoiTuongChinh::~DoiTuongChinh(){
}

void DoiTuongChinh::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2] ){
	if(events.type == SDL_KEYDOWN){
		switch(events.key.keysym.sym){
		    case SDLK_UP:
			    y_val_ -= HEIGHT_MAIN_OBJECT/SPEED_MAIN_OBJECT;
			    break;
		    case SDLK_DOWN:
			    y_val_ += HEIGHT_MAIN_OBJECT/SPEED_MAIN_OBJECT;
			    break;
		    case SDLK_RIGHT:
			    x_val_ += WIDTH_MAIN_OBJECT/SPEED_MAIN_OBJECT;
			    break;
		    case SDLK_LEFT:
			    x_val_ -= WIDTH_MAIN_OBJECT/SPEED_MAIN_OBJECT;
			    break;
			case SDLK_LSHIFT:{
				Dan* p_amo = new Dan();
				p_amo->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
				p_amo->LoadImg(g_name_bullet_main_lazer);
				p_amo->set_type(Dan::LAZER);
				Mix_PlayChannel(-1, bullet_sound[0], 0);
				p_amo->SetRect(this->rect_.x + this->rect_.w - 20, this->rect_.y + this->rect_.h - 70);
				/*		p_amo->SetRect(this->rect_.x + this->rect_.w - 70, this->rect_.y + this->rect_.h - 70);*/
				p_amo->set_is_move(true);
				p_amo->set_y_val(SPEED_BULLET_MAIN);
				p_amo_list_.push_back(p_amo);					
			}
			break;
			case SDLK_SPACE:{
				Dan* p_amo = new Dan();
				p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
				p_amo->LoadImg(g_name_bullet_main_sphere);
				p_amo->set_type(Dan::SPHERE);
				Mix_PlayChannel(-1, bullet_sound[1], 0);
				p_amo->SetRect(this->rect_.x + this->rect_.w - 20, this->rect_.y + this->rect_.h - 70);
				/*		p_amo->SetRect(this->rect_.x + this->rect_.w - 70, this->rect_.y + this->rect_.h - 70);*/
				p_amo->set_is_move(true);
				p_amo->set_y_val(SPEED_BULLET_MAIN);
				p_amo_list_.push_back(p_amo);
			}
			break;

		    default:
			    break;
		}
	}
	else if(events.type == SDL_KEYUP){
		switch(events.key.keysym.sym){
		    case SDLK_UP:
				y_val_ += HEIGHT_MAIN_OBJECT/SPEED_MAIN_OBJECT; 
				break;
			case SDLK_DOWN:
				y_val_ -= HEIGHT_MAIN_OBJECT/SPEED_MAIN_OBJECT;
				break;
			case SDLK_LEFT:
				x_val_ += WIDTH_MAIN_OBJECT/SPEED_MAIN_OBJECT; 
				break;
			case SDLK_RIGHT:
				x_val_ -= WIDTH_MAIN_OBJECT/SPEED_MAIN_OBJECT;
				break;
		}
	}
	else if(events.type == SDL_MOUSEBUTTONDOWN){
		Dan* p_amo = new Dan();
		if(events.button.button == SDL_BUTTON_LEFT){
			p_amo->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
			p_amo->LoadImg(g_name_bullet_main_lazer);
			p_amo->set_type(Dan::LAZER);
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
		else if(events.button.button == SDL_BUTTON_RIGHT){
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg(g_name_bullet_main_sphere);
			p_amo->set_type(Dan::SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}
		p_amo->SetRect(this->rect_.x + this->rect_.w - 20, this->rect_.y + this->rect_.h - 70);
/*		p_amo->SetRect(this->rect_.x + this->rect_.w - 70, this->rect_.y + this->rect_.h - 70);*/
		p_amo->set_is_move(true);
		p_amo->set_y_val(SPEED_BULLET_MAIN);
		p_amo_list_.push_back(p_amo);
	}
	else if(events.type == SDL_MOUSEBUTTONUP){

	}
	else{

	}
}

void DoiTuongChinh::MakeAmo(SDL_Surface *des){
	//Xử lí bắn đạn cho human
	for(int i = 0; i < p_amo_list_.size(); i++){
		Dan * p_amo = p_amo_list_.at(i);
		if(p_amo != NULL){
			if(p_amo->get_is_move()){
				p_amo->Show(des);
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else{
				if(p_amo != NULL){
					p_amo_list_.erase(p_amo_list_.begin() + i);
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}

void DoiTuongChinh::HandleMove(){
	rect_.x += x_val_;
	if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH){
		rect_.x -= x_val_;
	}

	rect_.y += y_val_;
	if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT){
		rect_.y -= y_val_;
	}
}

void DoiTuongChinh::RemoveAmo(const int &idx){
	int size_am = p_amo_list_.size();
	if( size_am > 0 && idx < size_am){
		for(int i =0; i< size_am; i++){
			Dan *p_amo = p_amo_list_.at(idx);
			p_amo_list_.erase(p_amo_list_.begin() + idx);

			if(p_amo != NULL){
				delete p_amo;
				p_amo = NULL;
				break;
			}
		}
	}
}