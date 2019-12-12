#pragma once
#include "VatThe.h"
#include "Thanh.h"
class ThanhNguoiChoi_Brick :
	public Thanh
{
public: 
	void CapNhat(RenderWindow* window); // cập nhật các yếu tố liên quan
	ThanhNguoiChoi_Brick(); // constructor
};

