#pragma once

#include "TrangThaiGame.h"
#include "mainGame_Brick.h"
#include "Thanh_Bot_Brick.h"

// chế độ thanh trượt tự chạy kế thừa từ chế độ chơi thường
class mainGame_Bot : public mainGame_Brick
{
public: 
	// chỉ cần viết lại 4 hàm dưới, các hàm khác lấy từ class cha
	void KhoiTao(RenderWindow* window); // hàm khởi tạo 
	void CapNhat(RenderWindow* window); // cập nhật các yếu tố có trong trò chơi
	void Xuat(RenderWindow* window); // Xuất ra màn hình
	void Destroy(RenderWindow* window); // Hàm huỷ
private:
	Thanh_Bot_Brick* botPlayer; // đối tượng thanh trượt tự chạy
};

