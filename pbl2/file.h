#pragma once
#ifndef FILE_H
#define FILE_H

#include "trie.h"
#include "user.h"
#include "muontra.h"
#include <iostream>
#include <fstream>
#include <string>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
	bool kiemtraisbn(const string& isbn, Trie* trieisbn);
	bool docfilebook(Trie* cayisbn, Trie* caytheloai, Trie* caytacgia, Trie* caytieude, Trie* caynxb, Trie* caynam, BookManager* mangbook);
	bool docfileuser(Manguser* m);
	bool docfilemuontra(MuonTra* m, Trie* cayisbn, Manguser* muser);
	void ghifilebook(Trie* trie);
	void ghifileuser(Manguser* m);
	void ghifilemuontra(MuonTra* tt);

#endif
