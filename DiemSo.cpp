#include "DiemSo.h"
//Hàm khởi tạo điểm số và in trên cửa sổ game.
DiemSo::DiemSo(Font& font, unsigned int size) : Text("Score: 0", font, size)
{
	this->GiaTri = 0;
}
//Hàm tính điểm tăng dần
void DiemSo::TangDan()
{
	this->GiaTri += 1;
}
// Tăng giá trị điểm lên x
void DiemSo::TangThem(int x)
{
	GiaTri += x; 
}
// Giảm giá trị điểm xuống x
void DiemSo::GiamXuong(int x)
{
	GiaTri -= x; 
	
}
//Hàm cập nhật in điểm theo giá trị tăng dần
void DiemSo::CapNhat()
{
	this->setString("Score: " + std::to_string(this->GiaTri));
}
//Hàm lấy giá trị điểm số
int DiemSo::GetDiem()
{
	return this->GiaTri;
}