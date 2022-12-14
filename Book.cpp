#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
#include "Book.h"

void Book::show_book()
{
	cout << "Name         : " << name << endl;
	cout << "Writer	     : " << writer << endl;
	cout << "Release Year : " << release_year << endl;
	cout << "Publication  : " << publication << endl;
	cout << endl;
}

void Book::write_in_file(ofstream &file)
{
	file << name << '/' << writer << '/' << release_year << '/' << publication << endl;
}
