#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "Book.h"
#include "Shelf.h"
#include "Member.h"
#include "io.h"
void update_database(vector<Book *> &books);

void login_admin(vector<Book *> &lib_books)
{
	string inst;
	cout << "Welcome Admin" << endl;
	bool be_here = true;
	while (be_here)
	{
		getline(cin, inst);
		if (inst == "logout")
		{
			be_here = false;
			cout << "loged out" << endl;
		}
		else if (inst == "update_database")
		{
			update_database(lib_books);
			cout << "DataBase is updated" << endl;
		}
		else if (inst == "")
			;
		else
			cout << "Please try again" << endl;
	}
}

void logedin(vector<Member *> members, vector<Book *> lib_books, const int m_num)
{
	bool be_in = true;
	string inst;
	string book_name;
	bool is_saved = false;
	while (be_in)
	{
		cin >> inst;
		if (inst == "add_book")
		{
			is_saved = false;
			getline(cin, book_name);
			book_name = book_name.substr(1, book_name.size());

			for (int i = 0; i < lib_books.size(); i++)
				if (lib_books[i]->get_name() == book_name)
				{
					members[m_num]->add_book(lib_books[i], 0, true);
					cout << book_name << " is succesfuly added to your library." << endl;
					is_saved = true;
				}

			if (!is_saved)
			{
				cout << "There is no book named :" << book_name << " in this library" << endl;
			}
		}
		else if (inst == "show_book")
		{
			bool book_found = false;
			getline(cin, book_name);
			book_name = book_name.substr(1, book_name.size());

			for (int i = 0; i < lib_books.size(); i++)
				if (lib_books[i]->get_name() == book_name)
				{
					members[m_num]->show_book(lib_books[i]);
					book_found = true;
				}
			if (!book_found)
			{
				cout << "There is no book named : " << book_name << endl;
			}
		}
		else if (inst == "like")
		{
			bool book_found = false;
			getline(cin, book_name);
			book_name = book_name.substr(1, book_name.size());
			for (int i = 0; i < lib_books.size(); i++)
				if (lib_books[i]->get_name() == book_name)
				{
					members[m_num]->like_book(lib_books[i], 0, true);
					book_found = true;
				}
			if (!book_found)
			{
				cout << "There is no book named : " << book_name << " in library" << endl;
			}
		}
		else if (inst == "show_favorites")
		{
			members[m_num]->show_favorite();
		}
		else if (inst == "show_books")
		{
			string shelf_name;
			getline(cin, shelf_name);
			shelf_name = shelf_name.substr(1, shelf_name.size());
			members[m_num]->show_shelf(shelf_name);
		}
		else if (inst == "add_shelf")
		{
			string shelf_name;
			getline(cin, shelf_name);
			shelf_name = shelf_name.substr(1, shelf_name.size());
			members[m_num]->add_shelf(shelf_name, true);
		}
		else if (inst == "add_to_shelf")
		{
			string shelf_name;
			string book_name;
			getline(cin, shelf_name, ' ');
			getline(cin, shelf_name, ' ');
			shelf_name = shelf_name.substr(0, shelf_name.size());
			getline(cin, book_name);
			book_name = book_name.substr(0, book_name.size());
			cout << book_name << "===" << shelf_name << endl;
			members[m_num]->add_to_shelf(shelf_name, book_name, 0, true);
		}
		else if (inst == "show_all_books")
		{
			if (lib_books.size() == 0)
				cout << "There is no book in library" << endl;
			for (int i = 0; i < lib_books.size(); i++)
			{
				members[m_num]->show_book(lib_books[i]);
			}
		}
		else if (inst == "follow")
		{
			string user_name;
			bool user_found = false;
			int user_num;
			getline(cin, user_name);
			user_name = user_name.substr(1, user_name.size());
			for (int i = 0; i < members.size(); i++)
				if (members[i]->get_name() == user_name)
				{
					user_found = true;
					user_num = i;
				}

			if (user_found == false)
				cout << "There is no user named : " << user_name << endl;
			else
			{
				members[m_num]->follow(members[user_num], true);
			}
		}
		else if (inst == "show_updates")
		{
			members[m_num]->show_updates();
		}
		else if (inst == "logout")
			be_in = false;
		else
		{
			cout << "Please Try Again" << endl;
		}
	}
}

int main()
{
	vector<Member *> members;
	vector<Book *> lib_books;
	cout << "Loading data ... " << endl;
	read_from_mem(lib_books, members);
	cout << "Loaded" << endl;
	cout << "Welcome to my Library" << endl;
	bool end = false;
	string inst, par1;
	string name, pass;
	while (!end)
	{
		cin >> inst;
		if (inst == "exit")
			end = true;
		else
		{
			if (inst == "register")
			{
				bool save = true;
				cin >> name;
				cin >> pass;
				for (int i = 0; i < members.size(); i++)
					if (members[i]->get_name() == name)
					{
						cout << "This username has been used. please try again" << endl;
						save = false;
					}
				if (save)
				{
					Member *m = new Member(name, pass);
					members.push_back(m);
					cout << " user_name: " << name << " pass: " << pass << " is registered." << endl;
					cout << "Welcome " << name << endl;
					logedin(members, lib_books, members.size() - 1);
				}
			}
			else if (inst == "login")
			{
				bool enter = false;
				int num;
				cin >> name;
				cin >> pass;
				if (name == "admin" & pass == "admin")
					login_admin(lib_books);

				else
				{
					for (int i = 0; i < members.size(); i++)
						if (members[i]->get_name() == name)
						{
							if (members[i]->get_password() == pass)
							{
								enter = true;
								num = i;
							}
						}
					if (enter)
					{
						cout << "Welcome " << name << endl;
						logedin(members, lib_books, num);
					}
					else
						cout << "Your Username or Password is incorrect" << endl;
				}
			}
			else if (inst == "show_members")
			{
				for (int i = 0; i < members.size(); i++)
					cout << members[i]->get_name() << endl;
			}
			else
			{
				cout << endl;
				cout << "please try again" << endl;
			}
			cout << "saving changes ..." << endl;
			write_to_mem(lib_books, members);
			cout << "saved" << endl;
		}
	}
	cout << "Thenk you for using this Library!!" << endl;
	return 0;
}
