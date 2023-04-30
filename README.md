# 2048_Game  - Game đã được nâng độ khó

Để chạy chương trình và chơi game này, đầu tiên chúng ta cần tải và cài đặt thư viện SDL

Tải và cài đặt thư viện SDL: https://www.libsdl.org/                       
Với thư viện SDL, sau khi tải về:

  Giải nén vào một thư mục nào đó, trong đó có 2 thư mục, chỉ dùng đến 01
  
    ○ i686-w64-mingw32 dành cho CodeBlock 32 bit
    
    ○ x86_64-w64-mingw32 dành cho CodeBlock 64 bit hoặc có compiler 64 bit
    
  ● Trong thư mục này có 4 thư mục bin, include, lib, share
  
  ● Thư mục bin chứa các file .dll cần dùng khi chạy chương trình, trong bộ SDL cơ
  bản là SDL2.dll
    
  ● Thư mục include chứa các file .h (như stdio.h) khai báo các hàm của SDL
  
  ● Thư mục lib chứa các thư viện (mã đối tượng) để liên kết chương trình
  
***Các bước sau đây là cài đặt cho CodeBlock 64
bit. Với CodeBlock 32 bit, bạn chỉ cần thay thế
thư mục x86.... bằng thư mục i686...

***Các bước cài SDL

1. Copy file dll
.....\x86_64-w64-mingw32\bin\SDL2.dll
vào thư mục mã nguồn project (nơi có các file .cpp)
2. Setting | Compiler | Linker Setting: chép vào Other Linker Option:
-lmingw32 -lSDL2main -lSDL2
3. Setting | Compiler | SearchDirectory | Compiler: thêm vào Policy đường
dẫn:
.....\x86_64-w64-mingw32\include\SDL2
4. Setting | Compiler | SearchDirectory | Linker: thêm vào Policy đường dẫn:
.....\x86_64-w64-mingw32\lib

***Quy trình cài các thư viện mở rộng của SDL2.0
hoàn toàn tương tự


**Cách chơi:

  Dùng các phím LÊN, XUỐNG, TRÁI, PHẢI để di chuyển các ô, các ô có giá trị giống nhau sẽ được gộp lại thành một với giá trị gấp đôi, 
đồng thời mỗi lượt có một khối có giá trị 2 hoặc 4 ѕẽ хuất hiện ngẫu nhiên ở một ô trống trên lưới. Khi không còn 2 ô nào cạnh nhau mà 
có giá trị như nhau thì khi đó game oᴠer. Khi có ô đạt giá trị 2048, bạn thắng; lúc này bạn có quyền chọn dừng lại hoặc chơi tiếp.

