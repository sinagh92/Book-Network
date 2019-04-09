#include<stdlib.h>
#include<vector>
#include<stdlib.h>
#include<fstream>
using namespace std;
#include"Book.h"
#include"Shelf.h"
#include"Member.h"
#include"io.h"

void write_to_mem(vector<Book*> books,vector<Member*> members){
	//books
	ofstream file;
	file.open("mem.txt");
	file<<"<books>"<<endl;
	for(int i=0;i<books.size();i++){
		books[i]->write_in_file(file);
	}
	file<<"<books>/"<<endl;
	//books
	//members
	file<<"<members>"<<endl;
	file<<members.size()<<endl;
	for(int i=0;i<members.size();i++){
		file<<endl;
		members[i]->write_in_file(file);
	}
	file<<"<members>/"<<endl;
	file<<"<end>"<<endl;

	file.close();
}
bool is_empty(ifstream& file)
{return file.peek()==ifstream::traits_type::eof();}

void read_from_mem(vector<Book*>& books,vector<Member*>& members){
	//books
	ifstream file;
	file.open("mem.txt");
	string name,writer,date,pub,tmp;
	if(is_empty(file))
		return;
	bool end_books=false;
	int test=0;
	file>>tmp;
	if(tmp=="<books>")
		while(!end_books){
			getline(file,name,'/');
			for(int i=0;i<name.size()-2;i++)
				if(name[i]=='\n')
					name=name.substr(1,name.size());
			if(name=="<books>")
				end_books=true;
			else{
				getline(file,writer,'/');
				getline(file,date,'/');
				getline(file,pub);
				Book* B1=new Book(name,writer,date,pub);
				books.push_back(B1);

			}	
		}
	//books
	//members
	int member_num=0,member_size;
	string user,pass;
	string last_time;
	vector<string> m_books,book_time;
	vector<vector<string> > friends_list;
	bool end_member=false;
	file>>tmp;
	file>>member_size;
	string tmp2;
	vector<string> friends_v;
	getline(file,tmp2);
	if(tmp=="<members>"){
		for(int i=0;i<member_size;i++){
			read_mem(books,members,file,i,friends_v);
			friends_list.push_back(friends_v);
		}
	}				
	for(int i=0;i<member_size;i++){		
		for(int j=0;j<friends_list[i].size();j++){ 
			for(int k=0;k<members.size();k++){										if(members[k]->get_name()==friends_list[i][j]&&i!=k){
				members[i]->follow(members[k]);

			}
			}
		}
	}
	file.close();
}



void read_mem(vector<Book*>& books,vector<Member*>& members,ifstream& file,int member_num,vector<string>& friends_v){

	string member_size,user,pass;
	string last_time;
	string tmp;
	int books_size;
	getline(file,user,'/');
	getline(file,pass,'/');
	getline(file,last_time);
	while(user[0]=='\n'){
		user=user.substr(1,user.size());
	}
	Member* M1=new Member(user,pass);
	members.push_back(M1);

	time_t l_t=atof(last_time.c_str());
	members[member_num]->set_last_time(l_t);

	file>>tmp;
	if(tmp=="<m_books>"){
		vector<string> mem_books;
		vector<time_t> books_time;
		file>>books_size;
		for(int i=0;i<books_size;i++){
			getline(file,tmp,'/');
			while(tmp[0]=='\n')
				tmp=tmp.substr(1,tmp.size());
			mem_books.push_back(tmp);
		}
		for(int i=0;i<books_size;i++){
			getline(file,tmp,'/');
			time_t t1=atof(tmp.c_str());
			books_time.push_back(t1);
		}
		for(int j=0;j<mem_books.size();j++)
			for(int i=0;i<books.size();i++)
				if(books[i]->get_name()==mem_books[j]){
					members[member_num]->add_book(books[i],books_time[j]);
				}
		file>>tmp;
	}
	file>>tmp;
	if(tmp=="<shelf>"){
		string shelf_name;

		int shelf_size,shelf_b_size;
		file>>shelf_size;
		for(int i=0;i<shelf_size;i++){
			vector<string> shelf_books;
			vector<long int> shelf_book_time;
			getline(file,shelf_name,'/');
			while(shelf_name[0]=='\n')
				shelf_name=shelf_name.substr(1,shelf_name.size());
			file>>shelf_b_size;
			members[member_num]->add_shelf(shelf_name);
			for(int j=0;j<shelf_b_size;j++){
				getline(file,tmp,'/');
				while(tmp[0]=='\n')
					tmp=tmp.substr(1,tmp.size());
				for(int k=0;k<books.size();k++)
					if(books[k]->get_name()==tmp){
						shelf_books.push_back(tmp);
					}
			}
			for(int j=0;j<shelf_b_size;j++){
				getline(file,tmp,'/');
				while(tmp[0]=='\n')
					tmp=tmp.substr(1,tmp.size());
				long int t1=str2int(tmp);
				shelf_book_time.push_back(t1);
			}
			for(int j=0;j<shelf_books.size();j++){
				members[member_num]->add_to_shelf(shelf_name,shelf_books[j],shelf_book_time[j]);
			}
		}

		file>>tmp;
	}
	int favorite_size;
	vector<string> fav;
	vector<time_t> fav_time;
	file>>favorite_size;
	for(int i=0;i<favorite_size;i++){
		getline(file,tmp,'/');
		while(tmp[0]=='\n')
			tmp=tmp.substr(1,tmp.size());
		fav.push_back(tmp);
	}
	for(int i=0;i<favorite_size;i++){
		getline(file,tmp,'/');
		while(tmp[0]=='\n')
			tmp=tmp.substr(1,tmp.size());
		time_t t1=atof(tmp.c_str());
		fav_time.push_back(t1);
	}
	for(int i=0;i<fav.size();i++)
		for(int j=0;j<books.size();j++)
			if(books[j]->get_name()==fav[i]){
				members[member_num]->like_book(books[j],fav_time[i]);}
	int friends_size;
	file>>friends_size;
	for(int i=0;i<friends_size;i++){
		getline(file,tmp,'/');
		while(tmp[0]=='\n')
			tmp=tmp.substr(1,tmp.size());
		friends_v.push_back(tmp);
	}

}	





