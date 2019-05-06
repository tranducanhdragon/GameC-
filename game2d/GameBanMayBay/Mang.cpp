#include"Mang.h"

Mang::Mang(){

}
Mang::~Mang(){

}

void Mang::AddPos(const int &xpos){
	pos_list_.push_back(xpos);
}

void Mang::Render(SDL_Surface *des){
	if(number_ == pos_list_.size()){
		for(int i= 0; i < pos_list_.size(); i++){
			rect_.x = pos_list_.at(i);
			Show(des);
		}
	}
}

void Mang::Init(){
	LoadImg(g_name_life_obj);
	number_ = LIFE_MAIN_OBJECT;
	if(pos_list_.size() > 0){
		pos_list_.clear();
	}
	AddPos(20);
	AddPos(60);
	AddPos(100);
}

void Mang::Decrease(){
	number_ --;
	if(pos_list_.empty() == false){
        pos_list_.pop_back();
	}
}