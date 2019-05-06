#ifndef MANG_H
#define MANG_H

#include"DoiTuongCoBan.h"
#include<vector>

class Mang : public DoiTuongCoBan{
private:
	int number_;
	std::vector<int> pos_list_;

public:
	Mang();
	~Mang();
	void SetNumber(const int &num){
		number_ = num;
	}
	void AddPos(const int &xpos);
	void Render(SDL_Surface *des);//Vị trí hiển thị mạng
	void Init();
	void Decrease();//Giảm số mạng 
};

#endif