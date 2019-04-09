#ifndef member
#define member
#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include"Book.h"
#include"Shelf.h"

class Person {
public:
	Person(string user,string pass): user_name(user),password(pass){};
protected:
string user_name;
string password;
};

class Member: public Person{
	public:
		Member(string user,string pass): Person(user,pass) {}
		~Member();
		void like_book(Book*,time_t _time=0,bool first_time=false);
		void add_shelf(string shelf_name,bool first_time=false);
		void add_book(Book*,time_t book_time=0,bool first_time=false);
		void show_favorite();
		void add_shelf_time(int i,long int n);
		void follow(Member*,bool first_time=false);
		void show_book(Book*);
		void add_to_shelf(const string,const string,time_t _time=0,bool first_time=false);
		string get_name(){return user_name;};
		void show_updates();
		void get_updates(time_t); 
		void show_shelf(string);
		string get_password(){return password;};
		void write_in_file(ofstream&);
		void set_last_time(time_t n){last_time=n;}
	private:
		vector<Book*> books;
		vector<Shelf*> shelves;
		vector<Book*> favorite;
		vector<Member*> friends;
		vector<time_t> book_time;
		vector<time_t> like_time;
		time_t last_time;
};

#endif
