#include"DoiTuongCoBan.h"

DoiTuongCoBan::DoiTuongCoBan(){
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
};

DoiTuongCoBan::~DoiTuongCoBan(){
	if(p_object_ != NULL){
		SDL_FreeSurface(p_object_);
	}
}

bool DoiTuongCoBan::LoadImg(const char* file_name){
	p_object_ = SDLXuLiChung::LoadImage(file_name);
	if(p_object_ == NULL){
		return false;
	}
	return true;
}

void DoiTuongCoBan::Show( SDL_Surface *des){
	if(p_object_ != NULL){
		SDLXuLiChung::ApplySurface(p_object_, des, rect_.x, rect_.y);
	}
}