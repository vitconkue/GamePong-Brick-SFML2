#pragma once
#include "VatThe.h"
#include "SupportFunction.h"
#include "Ball_BrickGame.h"
#include "Brick_BrickGame.h"
#include "ThanhNguoiChoi_Brick.h"
class Brick_Prize : public VatThe
{
protected:
	int type; 
	// type 1 : tăng gấp đôi điểm
	// type 2: giảm nửa số điểm
	// type 3: tăng 1.4 lần chiều dài thanh
	// type 4: giảm 1.4 lần chiều dài thanh
	// type 5: tăng số mạng hiện có
	bool touched_player; // biến cho biết người chơi lấy được vật phẩm rơi xuống hay chưa
	bool touched_floor; // biến cho biết vật phẩm đã vượt qua người chơi hay chưa
public :
	int getType() { return type; } // getter lấy loại vật phẩm
	void setType(int a) { type = 1; }
	bool getTouchedPlayer() { return touched_player; } // getter trạng thái người chơi lấy được vật phẩm  hay chưa
	bool getTouchedFloor() { return touched_floor; } // getter trạng thái vật phẩm vượt qua người chơi hay chưa
	Brick_Prize(); // constructor
	Brick_Prize(int _type); 
	void CapNhat(ThanhNguoiChoi_Brick*&player, DiemSo*& point, Ball_BrickGame*& ball);  // cập nhật các yếu tố liên quan 
	void TaoTexture(); // tạo texture, load hình ảnh vào
};

