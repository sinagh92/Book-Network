#ifndef book
#define book

class Book{
	public:
		Book(string n,string w,string r,string p):name(n),writer(w),release_year(r),publication(p){}
		void show_book();
		string get_name(){return name;};
		void write_in_file(ofstream&);
	private:
		string name;
		string writer;
		string release_year;
		string publication;
};

#endif
