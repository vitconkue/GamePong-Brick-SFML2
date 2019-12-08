#pragma once
#include "VatThe.h"
#include <cstdlib>
#include <ctime>
#include "Ball_BrickGame.h"
#include "Brick_BrickGame.h"
#include "ThanhNguoiChoi_Brick.h"
class Brick_Prize : public VatThe
{
protected:
	int type; 
	// type 1 : tang gap doi diem
	// type 2: giam nua so diem
	// type 3: tang 1.4 lan chieu dau thanh
	// type 4: giam 1.4 lan chieu dai thanh
	bool touched_player; 
	bool touched_floor; 
public :
	int getType() { return type; }
	bool getTouchedPlayer() { return touched_player; }
	bool getTouchedFloor() { return touched_floor;  }
	Brick_Prize(); 
	void CapNhat(ThanhNguoiChoi_Brick*&player, DiemSo*& point, Ball_BrickGame*& ball); 
	void TaoTexture(); 
};

