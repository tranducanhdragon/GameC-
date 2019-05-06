#ifndef TEXTDIEM_H
#define TEXTDIEM_H

#include"DoiTuongCoBan.h"
#include<string>
#include<SDL_ttf.h>

class TextDiem : public DoiTuongCoBan{
private:
	std::string str_val_;
	SDL_Color text_color_;
public:
	enum TextColor{
		RED_TEXT = 0,
		WHITE_TEXT = 1
	};

	TextDiem();
	~TextDiem();
	void SetText(const std::string &text){
		str_val_ = text;
	}
	void SetColor(const int &type);
	void CreateNameText(TTF_Font *font, SDL_Surface *des);
};

#endif