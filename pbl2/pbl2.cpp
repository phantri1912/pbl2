
#include "user.h"
#include "book.h"
#include "thoigian.h"
#include "trie.h"
#include "file.h"
#include <iostream>
#include <crtdbg.h> // Thư viện hỗ trợ kiểm tra rò rỉ bộ nhớ
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
int cbook = 0;
int ymanhinh = 0;
bool flag = true;
char thongbaoexit[] = "thoat";
char xoachu[] = "                                ";
using namespace std;
//6-9;

void inputText(int x, int y, char* buffer, int maxLength) //nhap chu trong khung dm kho vai cuc
{
    int length = 0; // Độ dài chuỗi hiện tại
    char ch;

    // Thiết lập màu chữ
    setcolor(WHITE);

    while (true) {
        ch = getch(); // Đợi người dùng nhấn phím

        // Nếu là phím Enter, thoát vòng lặp
        if (ch == '\r') {
            break;
        }
        // Nếu là phím Backspace, xóa ký tự cuối cùng
        else if (ch == '\b') {
            if (length > 0) {
                length--;
                
                // Xóa ký tự cuối trên màn hình bằng cách vẽ lại ô nền
                setcolor(BLACK);
                outtextxy(x, y, buffer);
                buffer[length] = ' ';
                setcolor(WHITE);
            }
        }
        // Kiểm tra giới hạn độ dài và ký tự hợp lệ
        else if (length < maxLength - 1 && ch >= 32 && ch <= 126) {
            buffer[length] = ch;
            buffer[length + 1] = '\0';
            length++;
        }

        // Hiển thị lại chuỗi đã nhập
        outtextxy(x, y, buffer);
    }
    while (length > 0 && buffer[length] == ' ') {
        buffer[length--] = '\0';
    }
    while (length > 0 && buffer[length - 1] == ' ') {
        buffer[length--] = '\0';
    }
}
bool dangnhap(string id, string matkhau, Manguser* m)//check tai khoan
{
    if (m->binarySearch(id) == -1 || m->getuser(m->binarySearch(id))->getMatkhau() != matkhau)return false;
    else return true;
}
void luachonmuonsach(User* m, Trie* trie, MuonTra* tt)//hien ra lua  chon muon sach theo yeu cau
{
    while (true)
    {
        int flag = 0;
        char t[] = "nhap id sach";
        char t2[] = "hoan thanh";
        char t3[] = "khong co sach";
        if (flag == 1)
        {
            outtextxy(100, 130, t3);
        }
        char text[100] = "";
        cleardevice();
        rectangle(90, 90, 400, 120);
        outtextxy(100, 100, t);
        inputText(250, 100, text, 100);
        string str1(text);
        TrieNode* p = trie->search(str1);
        if (p != nullptr)
        {
            tt->add(m->getId(), str1);
            break;
        }
        
    }
    return;
}
void inthongtinsach(TrieNode* p, int i,int y)//in thong tin sach thu tu i trong mang
{
    
    
    rectangle(90, 50+y, 800, 230+y);

    //char t2[] = "co sach";
    //outtextxy(100, 130, t2);

    char* cstr = new char[p->books[i]->getAuthor().length() + 1];
    strcpy_s(cstr, p->books[i]->getAuthor().length() + 1, p->books[i]->getAuthor().c_str());
    char text1[] = "ten tac gia :";
    outtextxy(100, 70 + y, text1);
    outtextxy(210, 70 + y, cstr);
    delete[] cstr;

    cstr = new char[p->books[i]->getTitle().length() + 1];
    strcpy_s(cstr, p->books[i]->getTitle().length() + 1, p->books[i]->getTitle().c_str());
    char text2[] = "ten sach :";
    outtextxy(100, 90 + y, text2);
    outtextxy(210, 90 + y, cstr);
    delete[] cstr;

    cstr = new char[p->books[i]->getIsbn().length() + 1];
    strcpy_s(cstr, p->books[i]->getIsbn().length() + 1, p->books[i]->getIsbn().c_str());
    char text3[] = "ma so sach :";
    outtextxy(100, 110 + y, text3);
    outtextxy(210, 110 + y, cstr);
    delete[] cstr;

    cstr = new char[p->books[i]->getPublisher().length() + 1];
    strcpy_s(cstr, p->books[i]->getPublisher().length() + 1, p->books[i]->getPublisher().c_str());
    char text4[] = "nha xuat ban :";
    outtextxy(100, 130 + y, text4);
    outtextxy(210, 130 + y, cstr);
    delete[] cstr;

    cstr = new char[p->books[i]->getSubject().length() + 1];
    strcpy_s(cstr, p->books[i]->getSubject().length() + 1, p->books[i]->getSubject().c_str());
    char text5[] = "the loai :";
    outtextxy(100, 150 + y, text5);
    outtextxy(210, 150 + y, cstr);
    delete[] cstr;

    int ngay = p->books[i]->getDate().getngay();
    int thang = p->books[i]->getDate().getthang();
    int nam = p->books[i]->getDate().getnam();
    char buffer[50];
    sprintf_s(buffer, sizeof(buffer), "%d/%d/%d", ngay, thang, nam); // Sử dụng sprintf_s
    char text6[] = "ngay xuat ban :";
    outtextxy(100, 170 + y, text6);
    outtextxy(210, 170 + y, buffer);

    int sotrang = p->books[i]->getPages();
    char buffer2[50];
    sprintf_s(buffer2, sizeof(buffer2), "%d", sotrang); // Sử dụng sprintf_s
    char text7[] = "so trang :";
    outtextxy(100, 190 + y, text7);
    outtextxy(210, 190 + y, buffer2);

    int soban = p->books[i]->getCopies();
    char buffer3[50];
    sprintf_s(buffer3, sizeof(buffer3), "%d", soban); // Sử dụng sprintf_s
    char text8[] = "so ban :";
    outtextxy(100, 210 + y, text8);
    outtextxy(210, 210 + y, buffer3);



}
bool nutmuonsach(Book* p, User* n, MuonTra* tt)//kiem tra co user hoac book ko,:)))
{
    if (p == nullptr)return false;
    if (n == nullptr)return false;
    if(p->getCopies() == 0)return false;
    if (tt->add(n->getId(), p->getIsbn()))
    {
        p->setbook(p->getCopies() - 1);
        p->setsachbimuon(p->getsosachmuon() + 1);
        return true;
    }
}
void inthongtinsachtrongnodevamuonsach(TrieNode* p,User* n, MuonTra* tt)//in thong tin tat ca book trong sach 1 cach lan luot va co the muon sach,dung cho nguoi dung dang nhap
{
    for (int i = 0; i < p->books.size();)
    {
        cleardevice();
        inthongtinsach(p, i, 0);
        int x, y;
        outtextxy(825, 95, ::thongbaoexit);
        rectangle(800, 90, 1000, 120);

        if (i < p->books.size() - 1)
        {
            char t5[] = "tiep";
            outtextxy(825, 125, t5);
            rectangle(800, 120, 1000, 150);
        }
        char t6[] = "muon sach nay";
        outtextxy(825, 155, t6);
        rectangle(800, 150, 1000, 180);
        while (true)
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x > 800 && x < 1000 && y > 90 && y < 120) {
                    return; 
                }
                if (x > 800 && x < 1000 && y > 120 && y < 150 && i < p->books.size() - 1) {
                    i++; 
                    break;
                }
                if (x > 800 && x < 1000 && y > 150 && y < 180) {

                    if (nutmuonsach(p->books[i], n,tt))
                    {
                        char t7[] = "muon sach thanh cong";
                        outtextxy(825, 185, t7);
                        rectangle(800, 180, 1000, 210);
                    }
                    else
                    {
                        char t7[] = "muon sach that bai";
                        outtextxy(825, 185, t7);
                        rectangle(800, 180, 1000, 210);
                    }
                }
                clearmouseclick(WM_LBUTTONDOWN); 
            }
        }
    }
}
void inthongtinsachtrongnode(TrieNode* p)//in thong tin tat ca book trong sach 1 cach lan luot,dung cho khach
{
    for (int i = 0; i < p->books.size();)
    {
        cleardevice();
        inthongtinsach(p, i,0);
        int x, y;
        outtextxy(825, 95, ::thongbaoexit);
        rectangle(800, 90, 1000, 120);

        if (i < p->books.size() - 1)
        {
            char t5[] = "tiep";
            outtextxy(825, 125, t5);
            rectangle(800, 120, 1000, 150);
        }

        while (true)
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x > 800 && x < 1000 && y > 90 && y < 120) {
                    return; 
                }
                if (x > 800 && x < 1000 && y > 120 && y < 150 && i < p->books.size() - 1) {
                    i++; 
                    break; 
                }
                clearmouseclick(WM_LBUTTONDOWN); 
            }
        }
    }
}

        

void luachontimsach(Trie* trie)//lua chon cua nguoi dung chua dang nhap
{
    int flag = 1;
    while (true)
    {
        cleardevice();

        char t[] = "nhap id sach";
        
        char t3[] = "khong co sach";

        char text[100] = "";
        if (flag == 0)outtextxy(100, 130, t3);
        rectangle(90, 90, 400, 120);
        outtextxy(100, 100, t);
        inputText(250, 100, text, 100);
        string str1(text);
        TrieNode* p = trie->search(str1);
        if (p != nullptr)
        {
            
            inthongtinsachtrongnode(p);
            return;
        }
        else
        {
            outtextxy(100, 130, t3);
            flag = 0;
        }

    }
}
void luachontimsachvamuon(Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, User* n, MuonTra* tt)
{
    int flag = 1;
    int x, y;
    char text0[] = "Nhap chuoi can tim";
    char text1[] = "Tim sach theo tieu de";
    char text2[] = "Tim sach theo the loai";
    char text3[] = "Tim sach theo tac gia";
    char text4[] = "Tim sach theo NXB";
    char text5[] = "Tim sach theo nam xuat ban";
    char t3[] = "Khong co sach";
    char text[100] = "";

    // Giao diện ban đầu
    cleardevice();
    outtextxy(825, 95, ::thongbaoexit);
    rectangle(800, 90, 1000, 120);
    rectangle(90, 90, 400, 120);
    outtextxy(100, 100, text0);
    rectangle(90, 120, 400, 150);
    outtextxy(100, 130, text1);
    rectangle(90, 150, 400, 180);
    outtextxy(100, 160, text2);
    rectangle(90, 180, 400, 210);
    outtextxy(100, 190, text3);
    rectangle(90, 210, 400, 240);
    outtextxy(100, 220, text4);
    rectangle(90, 240, 400, 270);
    outtextxy(100, 250, text5);

    while (true) {
        // Hiển thị thông báo nếu không tìm thấy sách
        if (flag == 0) {
            outtextxy(100, 130, t3); // Hiển thị "không có sách"
        }

        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            // Nhập chuỗi tìm kiếm
            if (x > 90 && x < 400 && y > 90 && y < 120) {
                inputText(250, 100, text, 100);
            }

            // Tìm theo tiêu đề
            if (x > 90 && x < 400 && y > 120 && y < 150) {
                string str1(text);
                TrieNode* p = caytieude->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevamuonsach(p, n, tt);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo thể loại
            if (x > 90 && x < 400 && y > 150 && y < 180) {
                string str1(text);
                TrieNode* p = caytheloai->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevamuonsach(p, n, tt);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo tác giả
            if (x > 90 && x < 400 && y > 180 && y < 210) {
                string str1(text);
                TrieNode* p = caytacgia->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevamuonsach(p, n, tt);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo NXB
            if (x > 90 && x < 400 && y > 210 && y < 240) {
                string str1(text);
                TrieNode* p = caynxb->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevamuonsach(p, n, tt);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo năm xuất bản (sửa điều kiện cho đúng)
            if (x > 90 && x < 400 && y > 240 && y < 270) {
                string str1(text);
                TrieNode* p = caynam->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevamuonsach(p, n, tt);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Thoát nếu nhấn vào vùng thông báo exit
            if (x > 800 && x < 1000 && y > 90 && y < 120) {
                return;
            }

            // Xóa sự kiện chuột
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

int demsosachtrongnode(TrieNode* node)//dem so sach co trong node
{
    if (node == nullptr)return 0;
    int c=0;
    for (int i = 0; i < 37 ;i++)
    {
        c += demsosachtrongnode(node->children[i]);
    }
    c += node->books.size();
    return c;
}
void innode(TrieNode* node)//chay ham de quy xuong cac node con roi in sach
{
    if (node == nullptr) return;

    // Duyệt qua tất cả các node con
    for (int i = 0; i < 37; i++)
    {
        if (!::flag) return;
        innode(node->children[i]);
    }

    // Chỉ in thông tin sách nếu node có sách
    if (node->books.size() == 0) return;

    int o = 0;
    while (::cbook < 3 && o < node->books.size())
    {
        inthongtinsach(node, o, ::ymanhinh);
        ::ymanhinh += 210;
        ::cbook++;
        o++;

        // Vẽ nút "Thoát"
        

        if (::cbook == 3)
        {
            ::ymanhinh = 0;
            ::cbook = 0;
            rectangle(800, 400, 1000, 500);    
            outtextxy(900, 450, ::thongbaoexit);
            // Vẽ nút "Tiếp"
            rectangle(800, 200, 1000, 300);
            char t2[] = "Tiep";
            outtextxy(900, 250, t2);

            while (true)
            {
                int x, y;
                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    getmouseclick(WM_LBUTTONDOWN, x, y);

                    // Nếu nhấn vào nút "Thoát"
                    if (x > 800 && x < 1000 && y > 400 && y < 500) {
                        ::flag = false;
                        return;
                    }

                    // Nếu nhấn vào nút "Tiếp"
                    if (x > 800 && x < 1000 && y > 200 && y < 300) {
                        break;
                    }

                    clearmouseclick(WM_LBUTTONDOWN);
                }
            }

            cleardevice();
        }
    }
    return;
}

void luachoninallsach(Trie* trieisbn)//in tat ca cac sach
{
    cleardevice();
    TrieNode* root = trieisbn->getroot();

    for (int i = 0; i < 37; i++)
    {   
        if (::flag)innode(root->children[i]);
        else break;
    }
    while (true)
    {
        int x, y;
        rectangle(800, 400, 1000, 500);
        outtextxy(900, 450, ::thongbaoexit);
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 800 && x < 1000 && y > 400 && y < 500) {
                     break;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
    ::ymanhinh = 0;
    ::cbook = 0;
    ::flag = true;
    cleardevice();
    return;
}

void hienthithongtinuser(Trie* trieisbn, User* n, MuonTra* tt)//hien thi thong tin muon sach cua nguoi dung
{   cleardevice();
    while (true)
    {
        
        // Hiển thị thông tin tài khoản
        char t[] = "Thong tin tai khoan";
        
        outtextxy(100, 100, t);

        // Hiển thị ID của người dùng
        char* cstr = new char[n->getId().length() + 1];
        strcpy_s(cstr, n->getId().length() + 1, n->getId().c_str());
        outtextxy(200, 100, cstr);
        delete[] cstr;

        // Kiểm tra nếu người dùng chưa mượn sách
        if (tt->kiemtraid(n->getId()) == -1)
        {
            char t2[] = "Tai khoan chua muon sach";
            outtextxy(100, 120, t2);
        }
        else
        {
            nguoimuon* p = tt->getnguoimuon(tt->kiemtraid(n->getId()));
            string indexStr = "So sach dang muon: " + to_string(p->getcountbook());
            char* pindexStr = new char[indexStr.length() + 1];
            strcpy_s(pindexStr, indexStr.length() + 1, indexStr.c_str());
            outtextxy(100, 140, pindexStr); 
            delete[] pindexStr;
            for (int i = 0; i < p->getcountbook(); i++)
            {   
                Book* book = trieisbn->search(p->getisbn(i))->books[0];
                char* bookTitleCStr = new char[book->getTitle().length() + 1];
                strcpy_s(bookTitleCStr, book->getTitle().length() + 1, book->getTitle().c_str());
                char* bookPublisherCStr = new char[book->getPublisher().length() + 1];
                strcpy_s(bookPublisherCStr, book->getPublisher().length() + 1, book->getPublisher().c_str());
                char* bookAuthor = new char[book->getAuthor().length() + 1];
                strcpy_s(bookAuthor, book->getAuthor().length() + 1, book->getAuthor().c_str());
                char* bookIsbn = new char[book->getIsbn().length() + 1];
                strcpy_s(bookIsbn, book->getIsbn().length() + 1, book->getIsbn().c_str());
                char* bookSubject = new char[book->getSubject().length() + 1];
                strcpy_s(bookSubject, book->getSubject().length() + 1, book->getSubject().c_str());
                outtextxy(100, 160 + i * 20, bookIsbn);
                outtextxy(300, 160 + i * 20, bookTitleCStr);
                outtextxy(200, 160 + i * 20, bookPublisherCStr);
                outtextxy(400, 160 + i * 20, bookSubject);
                outtextxy(500, 160 + i * 20, bookAuthor);
                delete[] bookTitleCStr;
            }
        }
        int x, y;
        outtextxy(825, 55, ::thongbaoexit);
        rectangle(800, 50, 1000, 80);
        while(true){
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x > 800 && x < 1000 && y > 50 && y < 80) {
                return; // Thoát khỏi hàm nếu người dùng nhấn "Thoát"
            }
            clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
        }
        }
    }
}
void luachontrasach(User* m, Trie* trieisbn, MuonTra* tt) {
    cleardevice();

    // Kiểm tra tài khoản và số lượng sách
    if (tt->kiemtraid(m->getId()) == -1 || tt->getnguoimuon(tt->kiemtraid(m->getId()))->getcountbook() == 0) {
        // Hiển thị thông báo tài khoản chưa mượn sách
        char k[] = "Tài khoản chưa mượn sách";
        rectangle(100, 100, 600, 150);
        outtextxy(105, 110, k);
        rectangle(600, 100, 700, 150);
        outtextxy(605, 110, ::thongbaoexit);
        int x, y;
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x > 600 && x < 700 && y > 100 && y < 150) {
                    return; // Thoát khỏi hàm nếu người dùng nhấn "Thoát"
                }
                clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
            }
        }
        return;
    }

    int i = 0;
    nguoimuon* p = tt->getnguoimuon(tt->kiemtraid(m->getId()));
    char tex[] = "Trả sách";

    // Hiển thị danh sách sách mượn
    while (i < p->getcountbook()) {
        TrieNode* node = trieisbn->search(p->getisbn(i));
        if (node != nullptr && !node->books.empty()) {
            inthongtinsach(node, 0, ::ymanhinh);
            rectangle(800, 50 + ::ymanhinh, 900, 170 + ::ymanhinh);
            outtextxy(805, 110 + ::ymanhinh, tex);
            ::ymanhinh += 180;
        }
        ++i;
    }

    int x=0, y=0;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            clearmouseclick(WM_LBUTTONDOWN);

            if (x > 800 && x < 900 && y > 50   && y < 170 && p->getcountbook() >= 1) {
                TrieNode* node = trieisbn->search(p->getisbn(0));
                    if (p->trasach(0)) { // Sử dụng chỉ số j đúng với sách
                        if (node != nullptr && !node->books.empty()) {
                            Book* b = node->books[0];
                            b->setbook(b->getCopies() + 1); // Cập nhật số bản sách
                            b->setsachbimuon(b->getsosachmuon() - 1);
                            std::cout << "Hoàn thành trả sách" <<b->getTitle()<< std::endl;
                            ::ymanhinh = 0;
                        }
                    }
                    return;
                }
            }
        if (x > 800 && x < 900 && y > 50+ 180  && y < 170+ 180 && p->getcountbook()>=2) {
            TrieNode* node = trieisbn->search(p->getisbn(1));
            if (p->trasach(1)) { // Sử dụng chỉ số j đúng với sách
                
                if (node != nullptr && !node->books.empty()) {
                    Book* b = node->books[0];
                    b->setbook(b->getCopies() + 1); // Cập nhật số bản sách
                    b->setsachbimuon(b->getsosachmuon() -1);
                    std::cout << "Hoàn thành trả sách" << b->getTitle() << std::endl;
                    ::ymanhinh = 0;
                }
            }
            return;
        }
    

        if (x > 800 && x < 900 && y > 50 +180*2  && y < 170 +180 * 2&&p->getcountbook() == 3) {
            TrieNode* node = trieisbn->search(p->getisbn(2));
                    if (p->trasach(2)) { // Sử dụng chỉ số j đúng với sách
                        
                        if (node != nullptr && !node->books.empty()) {
                            Book* b = node->books[0];
                            b->setbook(b->getCopies() + 1); // Cập nhật số bản sách
                            b->setsachbimuon(b->getsosachmuon() - 1);
                            std::cout << "Hoàn thành trả sách" <<b->getTitle()<< std::endl;
                            ::ymanhinh = 0;
                        }
                    }
                    return;
                }
            }
        }
    


void themsach(Trie* trieisbn, Trie* trie, BookManager *mangbook) {
    int x, y, flag[10] = { 0,0,0,0,0,0,0,0,0,0 };
    char tex[50] = ""; // Khởi tạo chuỗi rỗng
    cleardevice(); // Xóa màn hình
    // Khởi tạo các biến nhập liệu ngoài vòng lặp để không bị reset mỗi lần vòng lặp chạy
    char text1[100] = "";
    char text2[100] = "";
    char text3[100] = "";
    char text4[100] = "";
    char text5[100] = "";
    char text6[100] = "";
    char text7[100] = "";
    char text8[100] = "";
    char text9[100] = "";
    char text10[100] = "";
    string check;
    while (true) {
       

        // Các chuỗi để in ra giao diện
        char t1[] = "Nhap ma so: ";
        char t2[] = "Nhap tieu de: ";
        char t3[] = "Nhap chu de: ";
        char t4[] = "Nhap tac gia: ";
        char t5[] = "Nhap NXB: ";
        char t6[] = "Nhap ngay: ";
        char t7[] = "Nhap thang: ";
        char t8[] = "Nhap nam: ";
        char t9[] = "Nhap so ban in: ";
        char t10[] = "Nhap so trang: ";
        char t11[] = "Xac nhan";

        // Vẽ khung nhập liệu
        setcolor(GREEN);
        rectangle(90, 90, 400, 120); outtextxy(100, 100, t1);
        rectangle(90, 120, 400, 150); outtextxy(100, 130, t2);
        rectangle(90, 150, 400, 180); outtextxy(100, 160, t3);
        rectangle(90, 180, 400, 210); outtextxy(100, 190, t4);
        rectangle(90, 210, 400, 240); outtextxy(100, 220, t5);
        rectangle(90, 240, 400, 270); outtextxy(100, 250, t6);
        rectangle(90, 270, 400, 300); outtextxy(100, 280, t7);
        rectangle(90, 300, 400, 330); outtextxy(100, 310, t8);
        rectangle(90, 330, 400, 360); outtextxy(100, 340, t9);
        rectangle(90, 360, 400, 390); outtextxy(100, 370, t10);
        rectangle(90, 390, 400, 420); outtextxy(100, 400, t11);
        rectangle(90, 420, 400, 450); outtextxy(100, 430, ::thongbaoexit);

        // Vòng lặp nhập dữ liệu
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                // Xử lý từng ô nhập liệu dựa trên vị trí chuột
                if (x > 90 && x < 400 && y > 90 && y < 120) {
                    setcolor(BLACK); outtextxy(250, 100, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 100, text1, 100); // Nhập mã số
                    check = string(text1);
                    if (!kiemtraisbn(check)) {
                        strcpy_s(tex, sizeof(tex), "Loi ma so");
                        outtextxy(410, 100, tex);
                        flag[0] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[0] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 120 && y < 150) {
                    setcolor(BLACK); outtextxy(250, 130, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 130, text2, 100); // Nhập tiêu đề
                    if (strlen(text2) == 0) {
                        strcpy_s(tex, sizeof(tex), "Loi tieu de");
                        outtextxy(410, 130, tex);
                        flag[1] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[1] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 150 && y < 180) {
                    setcolor(BLACK); outtextxy(250, 160, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 160, text3, 100); // Nhập chủ đề
                    if (strlen(text3) == 0) {
                        strcpy_s(tex, sizeof(tex), "Loi chu de");
                        outtextxy(410, 160, tex);
                        flag[2] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[2] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 180 && y < 210) {
                    setcolor(BLACK); outtextxy(250, 190, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 190, text4, 100); // Nhập tác giả
                    if (strlen(text4) == 0) {
                        strcpy_s(tex, sizeof(tex), "Loi tac gia");
                        outtextxy(410, 190, tex);
                        flag[3] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[3] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 210 && y < 240) {
                    setcolor(BLACK); outtextxy(250, 220, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 220, text5, 100); // Nhập NXB
                    if (strlen(text5) == 0) {
                        strcpy_s(tex, sizeof(tex), "Loi NXB");
                        outtextxy(410, 220, tex);
                        flag[4] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[4] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 240 && y < 270) {
                    setcolor(BLACK); outtextxy(250, 250, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 250, text6, 100); // Nhập ngày
                    int day = atoi(text6);
                    if (day < 1 || day > 31) {
                        strcpy_s(tex, sizeof(tex), "Loi ngay");
                        outtextxy(410, 250, tex);
                        flag[5] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[5] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 270 && y < 300) {
                    setcolor(BLACK); outtextxy(250, 280, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 280, text7, 100); // Nhập tháng
                    int month = atoi(text7);
                    if (month < 1 || month > 12) {
                        strcpy_s(tex, sizeof(tex), "Loi thang");
                        outtextxy(410, 280, tex);
                        flag[6] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[6] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 300 && y < 330) {
                    setcolor(BLACK); outtextxy(250, 310, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 310, text8, 100); // Nhập năm
                    int year = atoi(text8);
                    if (year > 2024) {
                        strcpy_s(tex, sizeof(tex), "Loi nam");
                        outtextxy(410, 310, tex);
                        flag[7] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[7] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 330 && y < 360) {
                    setcolor(BLACK); outtextxy(250, 340, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 340, text9, 100); // Nhập số bản in
                    if (atoi(text9) <= 0) {
                        strcpy_s(tex, sizeof(tex), "Loi so ban in");
                        outtextxy(410, 340, tex);
                        flag[8] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[8] = 1;
                    }
                }

                if (x > 90 && x < 400 && y > 360 && y < 390) {
                    setcolor(BLACK); outtextxy(250, 370, ::xoachu);
                    setcolor(GREEN);
                    inputText(250, 370, text10, 100); // Nhập số trang
                    if (atoi(text10) <= 0) {
                        strcpy_s(tex, sizeof(tex), "Loi so trang");
                        outtextxy(410, 370, tex);
                        flag[9] = 0;
                    }
                    else {
                        setcolor(GREEN); flag[9] = 1;
                    }
                }

                // Nút xác nhận
                if (x > 90 && x < 400 && y > 390 && y < 420) {
                    bool allFlagsSet = true;
                    for (int i = 0; i < 10; i++) {
                        if (flag[i] != 1) {
                            allFlagsSet = false;
                            break;
                        }
                    }
                    if (allFlagsSet) {
                        clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái chuột
                        Date date(atoi(text6), atoi(text7), atoi(text8));
                        Book* newbook = new Book(string(text1), string(text2), string(text3), string(text4), string(text5),date, atoi(text9), atoi(text10));

                        trie->insert(newbook->getSubject(), newbook);
                        trieisbn->insert(newbook->getIsbn(), newbook);
                        mangbook->addBook(newbook);
                        return; // Thoát ra nếu mọi điều kiện đều thỏa mãn
                    }
                }

                // Nút thoát
                if (x > 90 && x < 400 && y > 420 && y < 450) {
                    clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái chuột
                    return;
                }
            }
        }
    }
}
bool xoasach(Book* book, Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager* mangbook)
{
    TrieNode* n = cayisbn->search(book->getIsbn());
    int i = 0;
    while (n->books[i] != book)
    {
        i++;
    }

    int length = n->books[i]->getIsbn().length();
    bool* indexneedfree_isbn = new bool[length];
    TrieNode** nodeneedfree_isbn = new TrieNode * [length];
    TrieNode* rmnode = cayisbn->getroot();
    n->books.erase(n->books.begin() + i);
    for (int y = 0; y < length; y++)
    {
        indexneedfree_isbn[y] = true;
        nodeneedfree_isbn[y] = rmnode;
        int index;
        char digit = book->getIsbn()[y];
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        for (int z = 0; z < 37; z++)
        {
            if (rmnode->children[z] != nullptr && z != index)
            {
                indexneedfree_isbn[y] = false;
                break;
            }
        }
        rmnode = rmnode->children[index];

    }
    for (int y = length - 1; y >= 0; y--)
    {
        if (indexneedfree_isbn[y] == true)
        {
            delete nodeneedfree_isbn[y];
            nodeneedfree_isbn[y] = nullptr;
        }
        else break;
    }
    delete[] nodeneedfree_isbn;
    delete[] indexneedfree_isbn;

     n = caytieude->search(book->getTitle());
    i = 0;
    while (n->books[i] != book)
    {
        i++;
    }
      
    length = n->books[i]->getTitle().length();
    bool* indexneedfree_title = new bool[length];
    TrieNode** nodeneedfree_title = new TrieNode * [length];
    rmnode = caytieude->getroot();
    n->books.erase(n->books.begin() + i);
    for (int y = 0; y < length; y++)
    {
        indexneedfree_title[y] = true;
        nodeneedfree_title[y] = rmnode;
        int index;
        char digit = book->getTitle()[y];
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        for (int z = 0; z < 37; z++)
        {
            if (rmnode->children[z] != nullptr&&z!=index)
            {
                indexneedfree_title[y] = false;
                break;
            }
        }
        rmnode = rmnode->children[index];
    
    }
    for (int y = length - 1; y >= 0; y--)
    {
        if (indexneedfree_title[y] == true)
        {
            delete nodeneedfree_title[y];
            nodeneedfree_title[y] = nullptr;
        }
        else break;
    }
    delete[] nodeneedfree_title;
    delete[] indexneedfree_title;

    n = caytheloai->search(book->getSubject());
    i = 0;
    while (n->books[i] != book)
    {
        i++;
    }
    length = n->books[i]->getSubject().length();
    bool* indexneedfree_subject = new bool[length];

    TrieNode** nodeneedfree_subject = new TrieNode * [length];
    rmnode = caytheloai->getroot();
    n->books.erase(n->books.begin() + i);
    for (int y = 0; y < length; y++)
    {
        indexneedfree_subject[y] = true;
        nodeneedfree_subject[y] = rmnode;
        int index;
        char digit = book->getSubject()[y];
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        for (int z = 0; z < 37; z++)
        {
            if (rmnode->children[z] != nullptr)
            {
                indexneedfree_subject[y] = false;
                break;
            }
        }
        rmnode = rmnode->children[index];
    }
    for (int y = length - 1; y >= 0; y--)
    {
        if (indexneedfree_subject[y] == true)
        {
            delete nodeneedfree_subject[y];
            nodeneedfree_subject[y] = nullptr;
        }
        else break;
    }
    delete[] nodeneedfree_subject;
    delete[] indexneedfree_subject;

    n = caytacgia->search(book->getAuthor());
    i = 0;
    while (n->books[i] != book)
    {
        i++;
    }
    length = n->books[i]->getAuthor().length();
    bool* indexneedfree_author = new bool[length];

    TrieNode** nodeneedfree_author = new TrieNode * [length];
    rmnode = caytacgia->getroot();
    n->books.erase(n->books.begin() + i);
    for (int y = 0; y < length; y++)
    {
        indexneedfree_author[y] = true;
        nodeneedfree_author[y] = rmnode;
        int index;
        char digit = book->getAuthor()[y];
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        for (int z = 0; z < 37; z++)
        {
            if (rmnode->children[z] != nullptr)
            {
                indexneedfree_author[y] = false;
                break;
            }
        }
        rmnode = rmnode->children[index];
    }

    for (int y = length - 1; y >= 0; y--)
    {
        if (indexneedfree_author[y] == true)
        {
            delete nodeneedfree_author[y];
        }
        else break;
    }
    delete[] nodeneedfree_author;
    delete[] indexneedfree_author;

    n = caynxb->search(book->getPublisher());
    i = 0;
    while (n->books[i] != book)
    {
        i++;
    }
    length = n->books[i]->getPublisher().length();
    bool* indexneedfree_publisher = new bool[length];

    TrieNode** nodeneedfree_publisher = new TrieNode * [length];
    rmnode = caynxb->getroot();
    n->books.erase(n->books.begin() + i);
    for (int y = 0; y < length; y++)
    {
        indexneedfree_publisher[y] = true;
        nodeneedfree_publisher[y] = rmnode;
        int index;
        char digit = book->getPublisher()[y];
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        for (int z = 0; z < 37; z++)
        {
            if (rmnode->children[z] != nullptr)
            {
                indexneedfree_publisher[y] = false;
                break;
            }
        }
        rmnode = rmnode->children[index];
    }
    for (int y = length - 1; y >= 0; y--)
    {
        if (indexneedfree_publisher[y] == true)
        {
            delete nodeneedfree_publisher[y];
        }
        else break;
    }
    delete[] nodeneedfree_publisher;
    delete[] indexneedfree_publisher;

    string nam = to_string(book->getDate().getnam());
    n = caynam->search(nam);
    i = 0;
    while (n->books[i] != book)
    {
        i++;
    }
    length =nam.length();
    bool* indexneedfree_year = new bool[length];

    TrieNode** nodeneedfree_year = new TrieNode * [length];
    rmnode = caynam->getroot();
    n->books.erase(n->books.begin() + i);
    for (int y = 0; y < length; y++)
    {
        indexneedfree_year[y] = true;
        nodeneedfree_year[y] = rmnode;
        int index;
        char digit = nam[y];
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        for (int z = 0; z < 37; z++)
        {
            if (rmnode->children[z] != nullptr)
            {
                indexneedfree_year[y] = false;
                break;
            }
        }
        rmnode = rmnode->children[index];
    }
    for (int y = length - 1; y >= 0; y--)
    {
        if (indexneedfree_year[y] == true)
        {
            delete nodeneedfree_year[y];
        }
        else break;
    }
    delete[] nodeneedfree_year;
    delete[] indexneedfree_year;
    mangbook->rmbook(book);
    return true;

}
void inthongtinsachtrongnodevaxoasach(TrieNode * n,Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager* bookManager)
{
    for (int i = 0; i < n->books.size();)
    {
        cleardevice();
        inthongtinsach(n, i, 0);
        int x, y;
        outtextxy(825, 95, ::thongbaoexit);
        rectangle(800, 90, 1000, 120);

        if (i < n->books.size() - 1)
        {
            char t5[] = "tiep";
            outtextxy(825, 125, t5);
            rectangle(800, 120, 1000, 150);
        }
        char t6[] = "xoa sach nay";
        outtextxy(825, 155, t6);
        rectangle(800, 150, 1000, 180);
        while (true)
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x > 800 && x < 1000 && y > 90 && y < 120) {
                    return;
                }
                if (x > 800 && x < 1000 && y > 120 && y < 150 && i < n->books.size() - 1) {
                    i++;
                    break;
                }
                if (x > 800 && x < 1000 && y > 150 && y < 180) {

                    if (xoasach(n->books[i],cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager))
                    {
                        char t7[] = "xoa sach thanh cong";
                        cout << "xoa sach thanh cong";
                        outtextxy(825, 185, t7);
                        rectangle(800, 180, 1000, 210);   
                        return;
                    }
                    else
                    {
                        char t7[] = "xoa sach that bai";
                        cout << "xoa sach that bai";
                        outtextxy(825, 185, t7);
                        rectangle(800, 180, 1000, 210);
                    }
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }
        }
    }
}
void timsachdexoa(Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager* bookManager)
{
    int flag = 1;
    int x, y;
    char text0[] = "Nhap chuoi can tim";
    char text1[] = "xoa sach theo tieu de";
    char text2[] = "xoa sach theo the loai";
    char text3[] = "xoa sach theo tac gia";
    char text4[] = "xoa sach theo NXB";
    char text5[] = "xoa sach theo nam xuat ban";
    char t3[] = "Khong co sach";
    char text[100] = "";

    // Giao diện ban đầu
    cleardevice();
    outtextxy(825, 95, ::thongbaoexit);
    rectangle(800, 90, 1000, 120);
    rectangle(90, 90, 400, 120);
    outtextxy(100, 100, text0);
    rectangle(90, 120, 400, 150);
    outtextxy(100, 130, text1);
    rectangle(90, 150, 400, 180);
    outtextxy(100, 160, text2);
    rectangle(90, 180, 400, 210);
    outtextxy(100, 190, text3);
    rectangle(90, 210, 400, 240);
    outtextxy(100, 220, text4);
    rectangle(90, 240, 400, 270);
    outtextxy(100, 250, text5);

    while (true) {
        // Hiển thị thông báo nếu không tìm thấy sách
        if (flag == 0) {
            outtextxy(100, 130, t3); // Hiển thị "không có sách"
        }

        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            // Nhập chuỗi tìm kiếm
            if (x > 90 && x < 400 && y > 90 && y < 120) {
                inputText(250, 100, text, 100);
            }

            // Tìm theo tiêu đề
            if (x > 90 && x < 400 && y > 120 && y < 150) {
                string str1(text);
                TrieNode* p = caytieude->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevaxoasach(p, cayisbn, caytheloai, caytacgia, caytieude,  caynxb, caynam, bookManager);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo thể loại
            if (x > 90 && x < 400 && y > 150 && y < 180) {
                string str1(text);
                TrieNode* p = caytheloai->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevaxoasach(p, cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo tác giả
            if (x > 90 && x < 400 && y > 180 && y < 210) {
                string str1(text);
                TrieNode* p = caytacgia->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevaxoasach(p, cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo NXB
            if (x > 90 && x < 400 && y > 210 && y < 240) {
                string str1(text);
                TrieNode* p = caynxb->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevaxoasach(p, cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Tìm theo năm xuất bản (sửa điều kiện cho đúng)
            if (x > 90 && x < 400 && y > 240 && y < 270) {
                string str1(text);
                TrieNode* p = caynam->search(str1);
                if (p != nullptr) {
                    inthongtinsachtrongnodevaxoasach(p, cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
                    return;
                }
                else {
                    flag = 0;
                }
            }

            // Thoát nếu nhấn vào vùng thông báo exit
            if (x > 800 && x < 1000 && y > 90 && y < 120) {
                return;
            }

            // Xóa sự kiện chuột
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

void luachondangnhap(User* m, MuonTra* tt, Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager* bookManager) //chay neu dang nhap thanh cong
{
    int x, y;
    
    while (true) {
    char t[] = "muon sach";
    char te[] = "tim sach";
    char tex[] = "tra sach";
    char tex2[] = "muon sach thanh cong";
    char tex3[] = "hien thi tat cac sach";
    char tex4[] = "dang xuat";
    char tex5[] = "chao ban";
    char tex6[] = "hien thi thong tin";
    char tex7[] = "them sach";
    char tex8[] = "xoasach";

    setcolor(GREEN); 
    char* cstr = new char[m->getId().length() + 1];
    strcpy_s(cstr, m->getId().length() + 1, m->getId().c_str());

    outtextxy(90, 50, tex5);
    outtextxy(150, 50, cstr);
    rectangle(90, 90, 400, 120);
    outtextxy(100, 100, t);
    rectangle(90, 120, 400, 150);
    outtextxy(100, 130, te);
    rectangle(90, 150, 400, 180);
    outtextxy(100, 160, tex);

    rectangle(90, 180, 400, 210);
    outtextxy(100, 190, tex3);
    rectangle(90, 210, 400, 240);
    outtextxy(100, 220, tex4);
    rectangle(90, 240, 400, 270);
    outtextxy(100, 250, tex6);
    rectangle(90, 270, 400, 300);
    outtextxy(100, 280, tex7);
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            /*if (x > 90 && x < 400 && y > 90 && y < 120) {
                luachonmuonsach(m, cayisbn, tt);
                cleardevice();
           
                outtextxy(100, 70, tex2);
            }*/

            if (x > 90 && x < 400 && y > 120 && y < 150) {
                luachontimsachvamuon( caytheloai,caytacgia, caytieude, caynxb, caynam, m,tt);
                cleardevice();
            }
            if (x > 90 && x < 400 && y > 150 && y < 180) {
                luachontrasach(m, cayisbn, tt);//ok
                cleardevice();
            }
            if (x > 90 && x < 400 && y > 180 && y < 210) {
                luachoninallsach(cayisbn);//ok
                cleardevice();
            }
            if (x > 90 && x < 400 && y > 210 && y < 240) {
                break;
            }
            if (x > 90 && x < 400 && y>240 && y < 270)
            {
                hienthithongtinuser( cayisbn,m,tt);//ok
                cleardevice();
            }
            if (x > 90 && x < 400 && y>270 && y < 300)
            {
                themsach(cayisbn, caytheloai, bookManager);
                cleardevice();
            }
            if (x > 90 && x < 400 && y>300 && y < 330)
            {
                timsachdexoa(cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
                cleardevice();
            }

            clearmouseclick(WM_LBUTTONDOWN); 
            delete[] cstr;
        }

    }
    
}
void luachon1(Manguser* m, MuonTra* tt, Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager* bookManager)//chay neu chon khung |dang nhap| 
{
    // Khởi tạo cửa sổ đồ họa    
    int x, y,flag=0;
    while(true){
    cleardevice();
    if (flag == 1)
    {
        char tex[] = "dang nhap that bai";
        outtextxy(100, 190, tex);
    }  
    char text[100] = "";
    char textt[100] = "";
    char t[] = "Nhap ma so:";
    char te[] = "Nhap mat khau:";
    char tex[] = "dang nhap";
    setcolor(GREEN);
    rectangle(90, 90, 400, 120);
    outtextxy(100, 100, t);
    rectangle(90, 120, 400, 150);
    outtextxy(100, 130, te);
    rectangle(90, 150, 400, 180);
    outtextxy(100, 160, tex);
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y); 

            if (x > 90 && x < 400 && y > 90 && y < 120) {
                inputText(250, 100, text, 100);
            }

            if (x > 90 && x < 400 && y > 120 && y < 150) {
                inputText(260, 130, textt, 100);
            }
            if (x > 90 && x < 400 && y > 150 && y < 180) {
                break;
            }
            
            clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
        }
        
    }
    string str1(text);
    string str2(textt);
    if(dangnhap(str1, str2, m)&&str1!="" && str2 !="")
    {
         flag = 0;
         cleardevice();
         luachondangnhap(m->getuser(m->binarySearch(str1)), tt, cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
         return;
    }
    else
    {   
         flag = 1;
    }
    }
 
}
void luachon2(Trie* trie)//chay neu chon khung |khach|
{
    int x, y;
    cleardevice();
        
    while (true) {
        char tex1[] = "tim sach";
        char tex3[] = "hien thi tat cac sach";
        


        setcolor(GREEN);
        
        rectangle(90, 90, 400, 120);
        outtextxy(100, 100, tex1);
        rectangle(90, 120, 400, 150);
        outtextxy(100, 130, tex3);
        rectangle(90, 150, 400, 180);
        outtextxy(100, 160, ::thongbaoexit);
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x > 90 && x < 400 && y > 90 && y < 120) {
                luachontimsach(trie);
                cleardevice();

            }


            if (x > 90 && x < 400 && y > 120 && y < 150) {
                luachoninallsach(trie);
                cleardevice();
            }
            if (x > 90 && x < 400 && y > 150 && y < 180) {
                cleardevice();
                return;
            }

            clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
        }

    }
}

void manhinhchinh(Manguser* m,MuonTra* tt, Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager *bookManager)
{
    initwindow(1000, 800, "Mouse and Keyboard Events");
    char text[100] = "";
    char textt[100] = "";
    

    int x, y;

    while (true) {
    char t[] = "Dang nhap";
    char te[] = "khach";
    setcolor(GREEN);
    rectangle(90, 90, 400, 120);
    outtextxy(100, 100, t);
    rectangle(90, 120, 400, 150);
    outtextxy(100, 130, te);
    rectangle(90, 150, 400, 180);
    outtextxy(100, 160, ::thongbaoexit);
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x > 90 && x < 400 && y > 90 && y < 120) {
                
                luachon1(m, tt, cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
                cleardevice();
            }

            if (x > 90 && x < 400 && y > 120 && y < 150) {
                luachon2(cayisbn);
                cleardevice();
                //luachon2();
            }
            if (x > 90 && x < 400 && y > 150 && y < 180) {
                
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph();
                return;
            }

            clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
        }
    }
}
int main() {
    // Kích hoạt kiểm tra rò rỉ bộ nhớ
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    {
        
        User* user = new User("1", "password");
        Manguser* m = new Manguser();
        m->adduser(user);

        // Tạo đối tượng Admin
        Admin* admin2 = new Admin("2", "password");
        Manguser* m2 = new Manguser();
        m2->adduser(admin2);

        // Truy cập đối tượng Admin
        User* u = m2->getuser(0);
      
           
        
        BookManager* bookManager = new BookManager;
       
        Date t(2, 2, 2);
        
        Trie* cayisbn = new Trie();
        Trie* caytheloai = new Trie();
        Trie* caytacgia = new Trie();
        Trie* caytieude =  new Trie();
        Trie* caynxb = new Trie();
        Trie* caynam= new Trie();


         MuonTra* tt = new MuonTra();
         if (docfile(cayisbn,caytheloai ,caytacgia ,caytieude, caynxb, caynam, bookManager))
         {
             cout << "Doc file hoan thanh";
         }

         manhinhchinh(m, tt, cayisbn, caytheloai, caytacgia, caytieude, caynxb, caynam, bookManager);
         (*m).printallUsers();
         ghifile(m, cayisbn, tt, caytheloai, bookManager);
         delete tt;
         delete cayisbn;
         delete caytheloai;
         delete caytacgia;
         delete caytieude;
         delete caynxb;
         delete caynam;
         delete m;
         bookManager->deleteAllBooks();

    }
    // Báo cáo rò rỉ bộ nhớ (nếu có)
    _CrtDumpMemoryLeaks();
    return 0;
}
