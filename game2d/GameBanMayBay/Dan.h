#ifndef DAN_H
#define DAN_H

#include"DoiTuongCoBan.h"

// tùy chọn khai báo kích thước cho đạn để xử lí va chạm thuận tiện hơn
#define WIDTH_LAZER 20 
#define HEIGHT_LAZER 1

#define WIDTH_SPHERE 1
#define HEIGHT_SPHERE 1

class Dan : public DoiTuongCoBan{
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	unsigned int amo_type_;

public:
	enum AmoType{
		NONE = 0,
		LAZER = 1,
		SPHERE = 2
	};
	Dan();
	~Dan();
	void HandleInputAction(SDL_Event events);
	void HandleMove(const int & x_border, const int &y_border);
	void HandleMoveUpToDown(const int & x_border, const int &y_border);

	int get_type() const {return amo_type_;}
	void set_type(const int &type){ amo_type_ = type;}

	bool get_is_move() const { return is_move_;}
	void set_is_move(bool is_move){ is_move_ = is_move;} 
	void SetWidthHeight(const int &width, const int &height){ rect_.w = width; rect_.h = height;}

	void set_x_val(const int &val){
		x_val_ = val;
	}
	void set_y_val(const int &val){
		y_val_ = val;
	}
	int get_x_val()const {
		return x_val_;
	}
	int get_y_val()const {
		return y_val_;
	}
};
#endif