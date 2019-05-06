#ifndef DOITUONGCHINH_H
#define DOITUONGCHINH_H

#include"XuLiChung.h"
#include"DoiTuongCoBan.h"
#include"Dan.h"
#include<vector>


#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 80

class DoiTuongChinh : public DoiTuongCoBan{
private:
	int x_val_;
	int y_val_;
	std::vector<Dan*> p_amo_list_;

public:
	DoiTuongChinh();
	~DoiTuongChinh();
	void HandleInputAction(SDL_Event events, Mix_Chunk * bullet_sound[2]);
	void HandleMove();
	void SetAmoList(std::vector<Dan*> amo_list){
		p_amo_list_ = amo_list;
	}
	std::vector<Dan*> GetAmoList()const {
		return p_amo_list_;
	}
	void MakeAmo(SDL_Surface* des);
	void RemoveAmo(const int &idx);
};
#endif