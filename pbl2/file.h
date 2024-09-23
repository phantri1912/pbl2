#pragma once
#ifndef FILE_H
#define FILE_H
#include "book.h"
#include "user.h"
#include "trie.h"
#include "thoigian.h"
#include "muontra.h"
#include <iostream>
#include <fstream>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
bool docfile(Trie* cayisbn,Trie* caytheloai ,Trie* caytacgia ,Trie* caytieude ,Trie* caynxb,Trie* caynam, BookManager* mangbook); // Ch? khai báo hàm, không ??nh ngh?a
void ghifile(Manguser* m, Trie* trie, MuonTra* tt, Trie* trieisbn, BookManager* mangbook);
bool kiemtraisbn(const string& isbn);
#endif
