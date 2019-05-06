#ifndef VUNO_H
#define VUNO_H

#include"XuLiChung.h"
#include"DoiTuongCoBan.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class VuNo : public DoiTuongCoBan{
private:
	int frame_;
	SDL_Rect clip[4];

public:
	VuNo();
	void set_clip();
	void set_frame(const int &fr){
		frame_ = fr;
	}
	void ShowEX(SDL_Surface *des);
};

#endif