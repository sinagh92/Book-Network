#ifndef io
#define io
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "Book.h"
#include "Shelf.h"
#include "Member.h"
using namespace std;
void read_mem(vector<Book *> &books, vector<Member *> &members, ifstream &file, int member_num, vector<string> &friends_v);
void get_books(ifstream &, vector<string> &, vector<string> &);
long int str2int(string);
void write_to_mem(vector<Book *> books, vector<Member *> members);
void read_from_mem(vector<Book *> &books, vector<Member *> &members);
#endif
