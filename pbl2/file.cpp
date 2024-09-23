#include "file.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void ghi(TrieNode* node, ofstream& output) {
    if (node == nullptr) return;

    // Đệ quy qua tất cả các con của node hiện tại
    for (int i = 0; i < 37; i++) {
        ghi(node->children[i], output);
    }

    // Nếu node này có sách, ghi dữ liệu của sách vào file
    if (!node->books.empty()) {
        for (Book* book : node->books) {
            // Dùng std::string để nối các phần của dữ liệu
            string line;
            line += book->getIsbn() + "/";
            line += book->getTitle() + "/";
            line += book->getAuthor() + "/";
            line += book->getSubject() + "/";
            line += book->getPublisher() + "/";

            // Thêm ngày, tháng, năm
            line += to_string(book->getDate().getngay()) + "/";
            line += to_string(book->getDate().getthang()) + "/";
            line += to_string(book->getDate().getnam()) + "/";

            // Thêm số trang và số bản
            line += to_string(book->getPages()) + "/";
            line += to_string(book->getCopies());

            // Ghi dòng này vào file
            output << line << endl;
        }
    }
}

void ghifile(Manguser* m, Trie* trie, MuonTra* tt, Trie* trieisbn, BookManager* mangbook) {
    ofstream output("C:\\Users\\LENOVO\\OneDrive - The University of Technology\\Desktop\\pbl2\\pbl2\\test.txt", ios::out);
    if (!output.is_open()) {
        cerr << "Không thể mở tệp để ghi.\n";
        return;
    }

    // Gọi hàm ghi để ghi dữ liệu từ trie vào file
    ghi(trieisbn->getroot(), output);

    output.close();
}

bool kiemtraisbn(const string& isbn) {
    // Kiểm tra độ dài phải đúng 10 ký tự
    if (isbn.length() != 10) {
        return false;
    }
    // Kiểm tra từng ký tự, chỉ cho phép số
    for (char c : isbn) {
        if (!isdigit(c)) { // isdigit() kiểm tra ký tự có phải là số không
            return false;
        }
    }
    return true;
}
int countgach(const char* line) {
    int count = 0;
    while (*line) {
        if (*line == '/') {
            ++count;
        }
        ++line;
    }
    return count;
}
bool docfile(Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager* mangbook) {
    ifstream input("C:\\Users\\LENOVO\\OneDrive - The University of Technology\\Desktop\\pbl2\\pbl2\\test.txt");
    if (!input.is_open()) {
        cerr << "Không thể mở tệp để đọc.\n";
        return false;
    }
    string iline;

    while (getline(input, iline)) {
        char* cstr = new char[iline.length() + 1];
        strcpy_s(cstr, iline.length() + 1, iline.c_str());
        int count = countgach(cstr);
        if (count != 9)
        {
            initwindow(400, 200, "error");
            setcolor(GREEN);
            char thoat[] = "thoat";
            char textmsg[] = "Loi: file ko dung hoac loi";
            outtextxy(20, 100, textmsg);
            rectangle(170, 150, 230, 180);
            outtextxy(190, 160, thoat);
            int x, y;
            while (true) {
                if (ismouseclick(WM_LBUTTONDOWN)) {
                    getmouseclick(WM_LBUTTONDOWN, x, y);
                    if (x > 170 && x < 230 && y > 150 && y < 180) {

                        clearmouseclick(WM_LBUTTONDOWN);
                        closegraph();
                        return false;
                    }

                    clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
                }
            }
        }
        char* next_token = nullptr;
        char* token = strtok_s(cstr, "/", &next_token);
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

        if (token != nullptr) strcpy_s(text1, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text2, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text3, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text4, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text5, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text6, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text7, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text8, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text9, token); token = strtok_s(nullptr, "/", &next_token);
        if (token != nullptr) strcpy_s(text10, token);

        string isbn = string(text1);
        string title = string(text2);
        string author = string(text3);
        string subject = string(text4);
        string publisher = string(text5);

        int day = atoi(text6);
        int month = atoi(text7);
        int year = atoi(text8);
        int page = atoi(text9);
        int copies = atoi(text10);

        // Kiểm tra điều kiện isbn và các điều kiện khác
        if (kiemtraisbn(isbn) && kiemtrangay(day, month, year) && isbn != "" && title != "" && author != "" && subject != "" && publisher != "" && page > 0 && copies >= 0 && cayisbn->search(isbn) == nullptr) {
            Date date(day, month, year);

            Book* newbook = new Book(isbn, title, author, subject, publisher, date, page, copies);
            caynxb->insert(newbook->getPublisher(), newbook);
            caytieude->insert(newbook->getTitle(), newbook);
            caytacgia->insert(newbook->getAuthor(), newbook);
            caytheloai->insert(newbook->getSubject(), newbook);
            caynam->insert(to_string(newbook->getDate().getnam()), newbook);
            cayisbn->insert(newbook->getIsbn(), newbook);
            mangbook->addBook(newbook);
        }
        else {
            char thoat[] = "thoat";
            initwindow(400, 200, "error");
            setcolor(GREEN);

            if (!kiemtraisbn(isbn)) {
                char textmsg[] = "Loi: ISBN khong hop le (phai co dung 10 ky tu so)";
                outtextxy(20, 100, textmsg);
                rectangle(170, 150, 230, 180);
                outtextxy(190, 160, thoat);
                int x, y;
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if (x > 170 && x < 230 && y > 150 && y < 180) {

                            clearmouseclick(WM_LBUTTONDOWN);
                            closegraph();
                            return false;
                        }

                        clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
                    }
                }
            
            }
            else if (cayisbn->search(isbn) != nullptr) {
                char textmsg[] = "Loi: ISBN da ton tai";
                outtextxy(20, 100, textmsg);
                rectangle(170, 150, 230, 180);
                outtextxy(190, 160, thoat);
                int x, y;
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if (x > 170 && x < 230 && y > 150 && y < 180) {

                            clearmouseclick(WM_LBUTTONDOWN);
                            closegraph();
                            return false;
                        }

                        clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
                    }
                }
            }
            else if (!kiemtrangay(day, month, year)) {
                char textmsg[] = "Loi: Ngay khong hop le";
                outtextxy(20, 100, textmsg); 
                rectangle(170, 150, 230, 180);
                outtextxy(190, 160, thoat);
                int x, y;
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if (x > 170 && x < 230 && y > 150 && y < 180) {

                            clearmouseclick(WM_LBUTTONDOWN);
                            closegraph();
                            return false;
                        }

                        clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
                    }
                }
            }
            else if (isbn == "" || title == "" || author == "" || subject == "" || publisher == "" || page <= 0 || copies < 0) {
                char textmsg[] = "Loi: Du lieu khong hop le";
                outtextxy(20, 50, textmsg);
                rectangle(170, 150, 230, 180);
                outtextxy(190, 160, thoat);
                int x, y;
                while (true) {
                    if (ismouseclick(WM_LBUTTONDOWN)) {
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if (x > 170 && x < 230 && y > 150 && y < 180) {

                            clearmouseclick(WM_LBUTTONDOWN);
                            closegraph();
                            return false;
                        }

                        clearmouseclick(WM_LBUTTONDOWN); // Xóa trạng thái nhấp chuột
                    }
                }
            }
        }

        delete[] cstr;
    }
    
    input.close();
    return true;
}

