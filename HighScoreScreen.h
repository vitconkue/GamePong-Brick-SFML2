#pragma once
#include <iostream>
#include "TrangThaiGame.h"
#include "DiemSo.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "mainGame_Brick.h"

// là một trạng thái
class HighScoreScreen : public TrangThai 
{
private: 
	Text* title; // tiêu đề
	std::vector<Text*> names; // danh sách các tên người đã chơi
	std::vector<DiemSo*> highscores; // Danh sách tương ứng điểm của những người đó
	Font* font; // biến lấy phông chữ
public: 
	void KhoiTao(RenderWindow* window); // khởi tạo màn hình
	void CapNhat(RenderWindow* window); // cập nhật các yếu tố liên quan, nhận input bàn phím
	void Xuat(RenderWindow* window); // xuất ra màn hình
	void Destroy(RenderWindow* window); // hàm huỷ
	void Sort(); // Sắp xếp hai mảng Tên và Điểm số theo thứ tự giảm dần
};

