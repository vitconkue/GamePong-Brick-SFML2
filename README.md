# GamePong-Brick-SFML2
Trường đại học Khoa học Tự nhiên Thành phố Hồ Chí Minh <br/>
Đồ án thực hành phương pháp lập trình hướng đối tượng cuối kì I. <br/>
Thư viện sử dụng: SFML 2.5.1 <br/>
Trang chủ thư viện: [https://www.sfml-dev.org/index.php] <br/>
Ngôn ngữ: C++ <br/>
- Các chức năng chính của game: 
 + Hiện màn hình chơi, điều khiển thanh trượt chạy qua lại để hứng bóng
   + Bóng chạm thanh sẽ bật ra, chạm gạch sẽ phá vỡ dần dần gạch
   + Bóng chạm tường sẽ bật ra theo nguyên tắc phản xạ
   + Nếu phá hết gạch người chơi giành chiến thắng, nếu không phá trước khi hết mạng người chơi thua. 
 + Khi phá được gạch, có thể có các vật phẩm rơi ra, mỗi vật phẩm có hiệu ứng riêng : 
    + Tăng gấp đôi điểm
    + Giảm nửa số điểm
    + Tăng chiều dài thanh (có giới hạn) 
    + Giảm chiều dài thanh (có giới hạn) 
    + Tăng số mạng hiện có (tối đa 6 mạng) 
 + Khi thắng, thua sẽ hiện màn hình nhập tên để người chơi nhập tên, lưu vào danh sách điểm.  
 + Chế độ Bot (thanh trượt tự chạy), thanh trượt tự chạy để hứng quá bóng
 + Người chơi có thể tạo tự tạo màn chơi nếu thích. 
    
