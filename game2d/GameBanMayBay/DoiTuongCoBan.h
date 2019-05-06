#ifndef DOITUONGCOBAN_H
#define DOITUONGCOBAN_H

#include"XuLiChung.h"

class DoiTuongCoBan{
protected:
	SDL_Rect rect_;
	SDL_Surface *p_object_;

public:
	DoiTuongCoBan();
	~DoiTuongCoBan();
	void Show(SDL_Surface* des);
	bool LoadImg(const char* file_name);
	void SetRect(const int &x, const int &y){
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const {return rect_;}
	SDL_Surface *GetObject(){return p_object_;}

};
#endif