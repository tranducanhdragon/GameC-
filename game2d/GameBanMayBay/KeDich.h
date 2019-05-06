#ifndef KEDICH_H
#define KEDICH_H

#include"XuLiChung.h"
#include"DoiTuongCoBan.h"
#include"Dan.h"
#include<vector>

#define WIDTH_KEDICH 80
#define HEIGTH_KEDICH 80

class KeDich : public DoiTuongCoBan{
private:
	int x_val_;
	int y_val_;
	std::vector<Dan*> p_amo_list_;

public:
	KeDich();
	~KeDich();
	void HandleMove(const int &x_border, const int &y_border,  Mix_Chunk *threat_sound[2]);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const int &val){
		x_val_ = val;
	}
	void set_y_val(const int &val){
		y_val_ = val;
	}
	int get_x_val()const {
		return x_val_;
	}
	int get_y_val()const{
		return y_val_;
	}
	void SetAmoList(std::vector<Dan*> amo_list){
		p_amo_list_ = amo_list;
	}
	std::vector<Dan*> GetAmoList()const {
		return p_amo_list_;
	}
	void InitAmo(Dan * p_amo);
	void MakeAmo(SDL_Surface *des, const int &x_limit, const int &y_limit);
	void Reset(const int &yborder);
	void ResetAmo(Dan * p_amo);
};
#endif