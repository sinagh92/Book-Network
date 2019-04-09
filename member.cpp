#include<iostream>
#include<vector>
#include <string>
#include<fstream>
using namespace std;
#include "Book.h"
#include "Shelf.h"
#include "Member.h"

void Member::like_book(Book* B1,time_t _time,bool first_time){
	bool added=false;
	for(int i=0;i<favorite.size();i++)
		if(B1->get_name()==favorite[i]->get_name())
		{cout<<"This book is already in your favorites"<<endl;		//do nothing
			return;}
	for(int i=0;i<books.size();i++)
		if(B1->get_name()==books[i]->get_name())
		{
			if(first_time==true)	cout<<"The book : "<<B1->get_name()<<" has been added to favorites"<<endl;

			favorite.push_back(B1);
			if(first_time==true){
				time_t t=time(0);
				like_time.push_back(t);}
			else like_time.push_back(_time);
			added=true;
			return;
		}
	if(!added)
		cout<<"This Book is not in your Library"<<endl;
}

void Member::add_shelf(string shelf_name,bool first_time){
	for(int i=0;i<shelves.size();i++)
		if(shelf_name==shelves[i]->get_name())
		{	cout<<"This shelf is already in your library"<<endl;		//do nothing
			return;}
	Shelf* sh=new Shelf(shelf_name);
	shelves.push_back(sh);
	if(first_time==true)	
		cout<<"shelf "<<shelf_name<<" has been added"<<endl;
}

void Member::add_book(Book* B1,time_t book_t,bool first_time){
	for(int i=0;i<books.size();i++)
		if(books[i]->get_name()==B1->get_name())
			//do nothing
			return;
	if(first_time==true){
		time_t t=time(0);
		book_time.push_back(t);
	}
	if(book_t!=0){
		book_time.push_back(book_t);
	}
	books.push_back(B1);
}

void Member::show_favorite(){
	if(favorite.size()==0)
		cout<<"Nothing is added to favorites"<<endl;
	else	cout<<"Favorite Books :"<<endl;
	for(int i=0;i<favorite.size();i++){
		cout<<"Book "<<i+1<<" : "<<endl;
		favorite[i]->show_book();
	}
}

void Member::follow(Member* m1,bool first_time){

	for(int i=0;i<friends.size();i++)
		if(m1->get_name()==friends[i]->get_name())
		{
			if(first_time==true)cout<<m1->get_name()<<" is already your friend"<<endl; //do nothing
			return;}
	if(first_time==true) cout<<m1->get_name()<<" is added to your friends"<<endl;
	friends.push_back(m1);
}

void Member::show_book(Book* B1){
	B1->Book::show_book();
	for(int i=0;i<favorite.size();i++)
		if(B1->get_name()==favorite[i]->get_name()){
			cout<<"This Book is a Favorite"<<endl;
			cout<<"================================"<<endl<<endl;
			return;}
	for(int i=0;i<books.size();i++)
		if(B1->get_name()==books[i]->get_name())
			cout<<"You have added this book"<<endl;
	cout<<"================================"<<endl<<endl;
}

void Member::add_to_shelf(string sh,string B1,time_t _time,bool first_time){
	bool shelf_found=false,book_found=false;
	int shelf_num,book_num;
	for(int i=0;i<shelves.size();i++)
		if(shelves[i]->get_name()==sh)
		{
			shelf_found=true;
			shelf_num=i;
		}
	for(int i=0;i<books.size();i++)
		if(books[i]->get_name()==B1)
		{
			book_found=true;
			book_num=i;
		}
	if(book_found==false||shelf_found==false)
		cout<<"Shelf name or Book name is incorrect or is not in your library"<<endl;
	else if(first_time==true){
		_time=time(0);
		shelves[shelf_num]->Shelf::add_to_shelf(books[book_num],_time);
		cout<<"The book "<<B1<<" is added to shelf "<<sh<<endl;
	}
	else{
		shelves[shelf_num]->Shelf::add_to_shelf(books[book_num],_time);
	}
};

void Member::add_shelf_time(int i,long int n){
	shelves[i]->set_time(n);
}

void Member::show_shelf(string shelf_name){
	int shelf_num;
	bool shelf_found=false;
	for(int i=0;i<shelves.size();i++)
		if(shelves[i]->get_name()==shelf_name)
		{	
			shelf_num=i;
			shelf_found=true;
		}
	if(shelf_found==false)
		cout<<"There is no shelf named : "<<shelf_name<<endl<<endl;
	else{
		shelves[shelf_num]->show_shelf(favorite);
	}		


}

void Member::show_updates(){
	time_t t=time(0);
	for(int i=0;i<friends.size();i++){
		friends[i]->get_updates(last_time);
	}
	last_time=t;
};

void Member::get_updates(time_t last_time){
	for(int i=0;i<book_time.size();i++)
		if(last_time<book_time[i]){
			cout<<user_name<<" has added "<<books[i]->get_name()<<" to library"<<endl;
		}
	for(int i=0;i<like_time.size();i++)
		if(last_time<like_time[i]){
			cout<<user_name<<" has added "<<favorite[i]->get_name()<<" to favorites"<<endl;
		}
	for(int i=0;i<shelves.size();i++)
		for(int j=0;j<shelves[i]->get_size();j++){
			if(shelves[i]->get_time(j)>last_time)
				cout<<user_name<< " has added "<<shelves[i]->get_book_name(j)<<" to shelf "<<	shelves[i]->get_name()<<endl;		}
}

Member::~Member(){
	cout<<"members deleted\n";
	for(int i=0;i<shelves.size();i++)
		delete shelves[i];
	for(int i=0;i<books.size();i++)
		delete books[i];
	for(int i=0;i<friends.size();i++)
		delete friends[i];
	for(int i=0;i<favorite.size();i++)
		delete favorite[i];
}

void Member::write_in_file(ofstream& file){
	file<<user_name<<'/'<<password<<'/'<<last_time<<endl;
	file<<"<m_books>"<<endl;
	file<<books.size()<<endl;
	for(int i=0;i<books.size();i++){
		file<<books[i]->get_name()<<'/';}
	if(books.size()!=0) file<<endl;
	for(int i=0;i<books.size();i++){
		file<<book_time[i]<<'/';}
	if(book_time.size()!=0) file<<endl;
	file<<"<m_books>/"<<endl;
	file<<"<shelf>"<<endl;
	file<<shelves.size()<<endl;
	for(int i=0;i<shelves.size();i++)
		shelves[i]->write_in_file(file);
	file<<"<shelf>/"<<endl;

	file<<favorite.size()<<endl;

	for(int i=0;i<favorite.size();i++){
		file<<favorite[i]->get_name()<<'/';}
	if(favorite.size()!=0) file<<endl;

	for(int i=0;i<like_time.size();i++){
		file<<like_time[i]<<'/';}
	if(like_time.size()!=0)	file<<endl;

	file<<friends.size()<<endl;
	for(int i=0;i<friends.size();i++){
		file<<friends[i]->get_name()<<'/';}
	if(friends.size()!=0) file<<endl;
}
