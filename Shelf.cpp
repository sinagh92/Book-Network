#include<iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
#include"Book.h"
#include"Shelf.h"

void Shelf::add_to_shelf(Book* B1,time_t _time){
	for(int i=0;i<books.size();i++)
		if(books[i]->get_name()==B1->get_name())
			//do nothing
			return;
	books.push_back(B1);
	size++;
	if(_time==0){
		time_t t=time(0);
		add_time.push_back(t);	}
	else
		add_time.push_back(_time);
}

time_t Shelf::get_time(int number){
	return add_time[number];
};

string Shelf::get_book_name(int number){
	return books[number]->get_name();

}

void Shelf::show_shelf(vector<Book*> fav){
	for(int i=0;i<size;i++){
		cout<<"Book "<<i+1<<" : "<<endl;
		books[i]->show_book();
		for(int j=0;j<fav.size();j++)
			if(fav[j]->get_name()==books[i]->get_name())
				cout<<"This book is a Favorite"<<endl;
	}

};

Shelf::~Shelf(){
	cout<<"shelf deleted"<<endl;
	for(int i=0;i<books.size();i++){
		delete books[i];}
};

void Shelf::write_in_file(ofstream& file){
	file<<shelf_name<<'/'<<size<<endl;
	for(int i=0;i<books.size();i++){
		file<<books[i]->get_name()<<'/';}
	if(books.size()!=0) file<<endl;
	for(int i=0;i<books.size();i++){
		file<<add_time[i]<<'/';}
	if(add_time.size()!=0) file<<endl;
}
