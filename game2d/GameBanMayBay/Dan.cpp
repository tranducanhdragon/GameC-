#include"Dan.h"
Dan::Dan(){
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	amo_type_ = NONE;
}

Dan::~Dan(){
}

void Dan::HandleMove(const int & x_border, const int &y_border){
	rect_.y -= y_val_;
	if(rect_.y < 0){
		is_move_ = false;
	}
}

void Dan::HandleMoveUpToDown(const int & x_border, const int &y_border){
	rect_.y += y_val_;
	if(rect_.y > y_border){
		is_move_ = false;
	}
}
void Dan::HandleInputAction(SDL_Event events){

}