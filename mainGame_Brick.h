#pragma once
#include "TrangThaiGame.h"
#include "ThanhNguoiChoi_Brick.h"
#include "DiemSo.h"
#include "Ball_BrickGame.h"
#include"Brick_BrickGame.h"
#include "Heart_BrickGame.h"
#include "Brick_Prize.h"
#include "SupportFunction.h"
#include <fstream>
#include<Windows.h>


// là một trạng thái
class mainGame_Brick : public TrangThai
{
public: 
	void KhoiTao(RenderWindow* window); // hàm khởi tạo
	void CapNhat(RenderWindow* window); // cập nhật các yếu tố có trong trò chơi
	void Xuat(RenderWindow* window); // Xuất ra màn hình
	void Destroy(RenderWindow* window); // Hàm huỷ
	void InputName(RenderWindow* window); // Hiện màn hình nhập tên
	void LoadBrick(string filename); // Load vị trí, màu gạch từ file
	void SaveGame(string filename); // lưu game
	void LoadGame(string filename); // load game
	int PauseGame(RenderWindow* window);//pause game
	int EndGame(RenderWindow* window);//end game
	string Level(RenderWindow* window);//Chon man choi
	bool checkCleanAllBrick(); 
	string toString(int a);
protected: 
	vector<Heart_BrickGame*> hearts; // vector mạng
	vector<Brick_BrickGame*> brick; // vector chứa các viên gạch
	vector<Brick_Prize*> prize;  //vector chứa các vật phẩm
	ThanhNguoiChoi_Brick* player; // thanh người chơi
	Ball_BrickGame* ball; // bóng
	DiemSo* point; // điểm người chơi
	Text* pausedText; 
	Font* font; 
	Text* win; 
	Text* lose; 
	int Effect;
	bool paused, enterKey; 
	bool endGame; 
	Texture background;
	//Âm thanh
	SoundBuffer* moveBuffer;
	SoundBuffer* selectBuffer;
	SoundBuffer* gameBuffer;
	Sound* mainsound;
	Sound* gameSound;
};

