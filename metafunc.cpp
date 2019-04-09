#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
#include"Book.h"
#include"Shelf.h"
#include"Member.h"

void update_database(vector<Book*>& books){
	ifstream db_file;
	db_file.open("database.txt");
	string name;
	string writer;
	string date;
	string pub;
	while(getline(db_file,name,'/')){
		bool is_same=false;
		getline(db_file,writer,'/');
		getline(db_file,date,'/');
		getline(db_file,pub);
		Book* B1=new Book(name,writer,date,pub);
		for(int i=0;i<books.size();i++){
			if(books[i]->get_name()==name)
				is_same=true;
		}
		cout<<"is same is : "<<is_same<<endl;
		if(is_same==false)	
			books.push_back(B1);
	}

	db_file.close();
}

long int str2int(string str){
	long int num=0;
	for(int i=0;i<str.size();i++)
	{
		long int temp=1;
		for(int j=0;j<i;j++)
			temp=10*temp;
		long int temp2=str[str.size()-i-1]-'0';
		num=temp2*temp+num;
	}
	return num;
}

