#ifndef shelf
#define shelf
#include"Book.h"
class Shelf{
	public:
		Shelf(string name):shelf_name(name) {size=0;}
		~Shelf();
		string get_name(){return shelf_name;};
		int get_size(){return size;};
		void add_to_shelf(Book*,time_t _time=0);
		void show_shelf(vector<Book*>);
		string get_book_name(int);
		time_t get_time(int); 
		void write_in_file(ofstream&);
		void set_time(long int n){add_time.push_back(n);}
	private:
		vector<Book*> books;
		string shelf_name;
		int size;
		vector<time_t> add_time;
};

#endif
