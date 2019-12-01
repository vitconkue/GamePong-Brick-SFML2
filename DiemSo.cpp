#include "DiemSo.h"
//Hàm khởi tạo điểm số và in trên cửa sổ game.
DiemSo::DiemSo(Font& font, unsigned int size) : Text("Diem: 0", font, size)
{
	this->GiaTri = 0;
}
//Hàm tính điểm tăng dần
void DiemSo::TangDan()
{
	this->GiaTri += 1;
}
//Hàm cập nhật in điểm theo giá trị tăng dần
void DiemSo::CapNhat()
{
	this->setString("Diem: " + std::to_string(this->GiaTri));
}
//Hàm lấy giá trị điểm số
int DiemSo::GetDiem()
{
	return this->GiaTri;
}