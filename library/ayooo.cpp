/*
	Class Book should have members for ISBN, title, author, and copyright date
	Store data on whether or not the book is checked out
	Create functions for returning those data values 
	Create functions for checking a book in and out 
	Do simple validation of data entered; for example, accept ISBNs only of the form n-n-n-x where n is integer and x is digit or letter
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

void error(const string& s)
{
	throw runtime_error(s);
}

class Book {
public:
	Book(vector<string> ISBNs, vector<string> titles, vector<string> authors, vector<int> years, bool check); // check for valid user inputs 
	Book(); // default constructor

	// modifying memebers 
	void check_book_in(vector<string>& copy_title, vector<string>& copy_ISBN, vector<string>& copy_author, vector<int>& copy_year, string user); // check book in
	void check_book_out(vector<string>& copy_title, vector<string>& copy_ISBN, vector<string>& copy_author, vector<int>& copy_year, string user); // check book out 
	bool is_title(string user); // is the user inputted title part of inventory
	bool is_checked_out(vector<string>& copy_title, string user); // is the user inputted title checked out
	void print_book_status(vector<string>& copy_title, string user); // print whether or not the book is checked out 
	bool is_isbn(string user); // is the user inputted isbn part of inventory
	bool is_isbn_format(string user); // is the user inputted isbn in the correct format
	void print_title_of_isbn(string user); // print the title of the corresponding isbn if available 
	bool is_author(string user); // is the user inputted author part of inventory 
	void print_book_of_author(string user); // print title(s) of the corresponding if available
	bool valid_year(); // check if book in inventory has valid copyright date
	bool valid_isbn(); // check if book in inventory has valid author name

	// const member functions
	vector<string> isbn() const { return ISBN; }
	vector<string> tit() const { return title; }
	vector<string> auth() const { return author; }
	vector<int> ye() const { return year; }
	bool outchecked() const { return checkedout; }
private:
	vector<string> ISBN; // vector to store ISBNs of the library 
	vector<string> title; // vector to store the title of the books of the library 
	vector<string> author; // vector to store the authors of the books 
	vector<int> year; // copyright date for book usually just the year
	
	bool checkedout = true;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Book& default_book()
{
	vector<string> isbn;
	isbn.push_back("1-2-1-a34");
	isbn.push_back("11-2-8-c");
	isbn.push_back("3-6-1-a");
	isbn.push_back("7-9-12-t");
	isbn.push_back("9-23-2-z");

	vector<string> tit;
	tit.push_back("Math Book");
	tit.push_back("Science Book");
	tit.push_back("History Book");
	tit.push_back("English Book");
	tit.push_back("French Book");

	vector<string> auth;
	auth.push_back("Jim Tory");
	auth.push_back("Ahmed Sakr");
	auth.push_back("Randel Keast");
	auth.push_back("Jim Tory");
	auth.push_back("Pierre LeGay");

	vector<int> ye;
	ye.push_back(2010);
	ye.push_back(1965);
	ye.push_back(2021);
	ye.push_back(1825);
	ye.push_back(1938);

	bool check = true;

	static Book bb(isbn, tit, auth, ye, check);
	return bb;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Book::Book()
	:ISBN(default_book().isbn()),
	title(default_book().tit()), 
	author(default_book().auth()), 
	year(default_book().ye()),
	checkedout(default_book().outchecked())
{
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Book::Book(vector<string> ISBNs, vector<string> titles, vector<string> authors, vector<int> years, bool check)
	:ISBN(ISBNs), title(titles), author(authors), year(years), checkedout(check)
{
	if (!valid_year()) {
		error("Inventory: book has invalid copyright year.");
	}

	if (!valid_isbn()) {
		error("Inventory: book has invalid ISBN.");
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Book::is_title(string user)
{
	for (int i = 0; i < title.size(); ++i) {
		if (user == title[i]) {
			return true;
		}
	}

	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Book::is_checked_out(vector<string>& copy_title, string user)
{
	for (int i = 0; i < copy_title.size(); ++i) {
		if (user == copy_title[i]) {
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Book::print_book_status(vector<string>& copy_title, string user)
{
	cout << "\nEnter the book you want to check.\n\n";
	getline(cin, user);

	// is title in inventory
	if (!is_title(user)) {
		error("The book your looking for is not in the inventory.");
	}

	// check if booked is checked out 
	if (!is_checked_out(copy_title, user)) {
		cout << "\nThe book is not checked out.\n\n";
	}
	else {
		cout << "\nThe book is checked out. Please check again some other time.\n\n";
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Book::is_isbn(string user)
{
	for (int i = 0; i < ISBN.size(); ++i) {
		if (user == ISBN[i]) {
			return true;
		}
	}

	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Book::is_isbn_format(string user)
{
	// correct format is n-n-n-x where n is any integer and x is integer or letter
	// for example: 23-43-1-a2
	int count = 0; // variable for number of hyphens in user input 

	for (int i = 0; i < user.size(); ++i) { // check if each character is proper
		if ((user[i] > '9' || user[i] < '0') && user[i] != '-' && count < 2) { // first two dashes have invalid characters 
			return false;
		}
		else if ((user[i] > '9' || user[i] < '0') && (user[i] > 'z' || user[i] < 'a') && user[i] != '-' && count >= 2) { // invalid charcter in isbn
			return false;
		}
		else if(user[0] == '-' || user[user.size() - 1] == '-') { // if hyphen the first/ last character will get vector subscript error, this prevents that
			return false;
		}

		if (i != 0 && (user[i - 1] >= '0' && user[i - 1] <= '9') && (user[i] == '-') && (user[i + 1] >= '0' && user[i + 1] <= '9') && count < 2) { // correct format
			++count;
		}
		else if (count == 2 && ((user[i - 1] >= '0' && user[i - 1] <= '9')) && (user[i] == '-')
			&& ((user[i + 1] >= '0' && user[i + 1] <= '9') || (user[i + 1] >= 'a' && user[i + 1] <= 'z'))) { // correct format
			++count;
		}
	}

	// needs 3 hyphens to be proper  
	if (count == 3) {
		return true;
	}
	else {
		return false;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Book::print_title_of_isbn(string user)
{
	cout << "\nPlease enter an ISBN and the corresponding book title will be given.\n\n";
	getline(cin, user);

	if (!is_isbn_format(user)) { // check if isbn in correct format
		cout << "\nInproper format of ISBN. Please try again.\n\n";
	}
	else if (!is_isbn(user)) { // check of isbn is in inventory 
		cout << "\nThis ISBN does not exist in the inventory. Please try again.\n\n";
	}
	else { // print corresponding book
		for (int i = 0; i < ISBN.size(); ++i) {
			if (user == ISBN[i]) {
				cout << "\nThe book is " << title[i] << ".\n\n";
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Book::is_author(string user)
{
	for (int i = 0; i < author.size(); ++i) {
		if (user == author[i]) {
			return true;
		}
	}

	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Book::print_book_of_author(string user)
{
	vector<string> books; // vector to put the auhtor's book(s) in

	cout << "\nEnter an author to see what books he has in our inventory.\n\n";
	getline(cin, user);
	
	// check if author is valid and put book(s) into vector
	if (!is_author(user)) {
		cout << "\nThis author is has no books in our inventory. Please input another name.\n\n";
	}
	else {
		for (int i = 0; i < author.size(); ++i) {
			if (user == author[i]) {
				books.push_back(title[i]);
			}
		}
	}

	// output titles of books if available
	if (books.size() == 1) {
		cout << "\nThe author wrote " << books[0] << "\n\n";
	}
	else if (books.size() > 1) {
		cout << "\nThe author has written the following books: ";
		for (int i = 0; i < books.size(); ++i) {
			if (i < books.size() - 1) {
				cout << books[i] << ", ";
			}
			else {
				cout << "and " << books[i] << "\n\n";
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Book::valid_year()
{
	static const int maxyear = 2023;
	static const int minyear = 1790; // year when first book was copyrighted

	for (int i = 0; i < year.size(); ++i) {
		if (year[i] > maxyear || year[i] < minyear) {
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Book::valid_isbn()
{
	int count = 0; // variable for number of hyphens in inventory

	for (int i = 0; i < ISBN.size(); ++i) { // check if each isbn is proper
		int dynamic = i * 3; // dynamic number to help with the condition statements 
		for (int j = 0; j < ISBN[i].size(); ++j) { // check if each character in given isbn is proper
			if (((ISBN[i])[j] > '9' || (ISBN[i])[j] < '0') && (ISBN[i])[j] != '-' && (count == dynamic || count == dynamic + 1)) { // first two dashes have invalid characters 
				return false;
			}
			else if (((ISBN[i])[j] > '9' || (ISBN[i])[j] < '0') && ((ISBN[i])[j] > 'z' || (ISBN[i])[j] < 'a') && (ISBN[i])[j] != '-' && count >= dynamic + 2) { // invalid charcter in isbn
				return false;
			}
			else if ((ISBN[i])[0] == '-' || (ISBN[i])[ISBN[i].size() - 1] == '-') { // if hyphen the first/last character will get vector subscript error, this prevents that
				return false;
			}

			if (j != 0 && ((ISBN[i])[j - 1] >= '0' && (ISBN[i])[j - 1] <= '9') && ((ISBN[i])[j] == '-') && ((ISBN[i])[j + 1] >= '0' && (ISBN[i])[j + 1] <= '9')
				&& (count == dynamic || count == dynamic + 1)) { // correct format
				++count;
			}
			else if (count >= dynamic + 2 && (((ISBN[i])[j - 1] >= '0' && (ISBN[i])[j - 1] <= '9')) && ((ISBN[i])[j] == '-')
				&& (((ISBN[i])[j + 1] >= '0' && (ISBN[i])[j + 1] <= '9') || ((ISBN[i])[j + 1] >= 'a' && (ISBN[i])[j + 1] <= 'z'))) { // correct format
				++count;
			}
		}
	}

	// needs exact number of hyphens for isbn to be proper
	if (count == 3 * ISBN.size()) {
		return true;
	}
	else {
		return false;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Book::check_book_out(vector<string>& copy_title, vector<string>& copy_ISBN, vector<string>& copy_author, vector<int>& copy_year, string user)
{
	cout << "\nPlease enter a book you would wish to check out.\n\n";
	getline(cin, user);

	// check if book valid
	if (!is_title(user)) {
		error("The book your looking for is not in the inventory.");
	}

	// let user check book out and remove the book from the copy vectors
	for (int i = 0; i < copy_title.size(); ++i) {
		if (user == copy_title[i]) {
			cout << "\nYou have succesfully checked out " << copy_title[i] << "\n\n";
			copy_title.erase(copy_title.begin() + i);
			copy_ISBN.erase(copy_ISBN.begin() + i);
			copy_author.erase(copy_author.begin() + i);
			copy_year.erase(copy_year.begin() + i);
			if (copy_title.size() > title.size()) {
				error("check_book_in(): too many books in inventory.");
			}
			checkedout = true;
			break;
		}
		else {
			checkedout = false;
		}
	}

	if (checkedout == false) {
		cout << "\nThe book is already checked out.\n\n";
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Book::check_book_in(vector<string>& copy_title, vector<string>& copy_ISBN, vector<string>& copy_author, vector<int>& copy_year, string user)
{
	cout << "\nPlease enter which book you want to check back in.\n\n";
	bool check = true;

	getline(cin, user);

	// check if book valid
	if (!is_title(user)) {
		error("The book your looking for is not in the inventory.");
	}

	// has the book been checked out
	for (int i = 0; i < copy_title.size(); ++i) {
		if (user == copy_title[i]) {
			check = true;
			break;
		}
		else {
			check = false;
		}
	}

	// let user check in the book and add the book back into the copy vector
	for (int i = 0; i < title.size(); ++i) {
		if (user == title[i] && !check) {
			copy_title.push_back(title[i]); 
			copy_ISBN.push_back(ISBN[i]);
			copy_author.push_back(author[i]);
			copy_year.push_back(year[i]);
			cout << "\nYou have succesfully checked in " << title[i] << "\n\n";
			checkedout = false;
			if (copy_title.size() > title.size()) {
				error("check_book_in(): too many books in inventory.");
			}
			break;
		}
		else {
			checkedout = true;
		}
	}

	if (checkedout == true) {
		cout << "\nThis book has not been checked out by anyone\n\n";
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Book& np) // used to create the output 
{
	for (int i = 0; i < np.auth().size(); ++i) {
		os << "Title: " << np.tit()[i] << "\nISBN: " << np.isbn()[i] << "\nAuthor: " << np.auth()[i] << "\nCopyright: " << np.ye()[i] << "\n\n";
	}
	return os;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	try {
		Book result;
		string pick = "a";
		string user;
		vector<string> copy_title; vector<string> copy_ISBN; vector<string> copy_author; vector<int> copy_year;
		copy_title = result.tit(); copy_ISBN = result.isbn(); copy_author = result.auth(); copy_year = result.ye(); // initialize the vectors with contents of inventory 

		cout << "Welcome to Mister HB's library! Here is our inventory:\n\n";
		cout << result;
		cout << "\nPlease chose one of the following 6 options.\n\n";
		cout << "'1' to check book out. '2' to check book in. '3' to see if book is checked out. '4' to search a book by its ISBN. ";
		cout << "'5' to search for books by author. '6' to exit.\n\n";
		
		while (cin >> pick) {
			if (pick.size() > 1) { // this prevents program from throwing pick.size() number of invlaid messages
				cout << "\nInvalid input. Please try again.\n\n";
			}
			else {
				switch (pick[0]) { // switch can't be used on string, have to turn string into char 
				case '1':
					getline(cin, user); // this needs to be here, why tf???
					result.check_book_out(copy_title, copy_ISBN, copy_author, copy_year, user);
					break;
				case '2':
					getline(cin, user);
					result.check_book_in(copy_title, copy_ISBN, copy_author, copy_year, user);
					break;
				case '3':
					getline(cin, user);
					result.print_book_status(copy_title, user);
					break;
				case '4':
					getline(cin, user);
					result.print_title_of_isbn(user);
					break;
				case '5':
					getline(cin, user);
					result.print_book_of_author(user);
					break;
				case '6':
					if (copy_title.size() == 0) {
						cout << "\nThe inventory is empty.\n\n";
					}
					else {
						cout << "\nThe remaining inventory is\n\n";
						for (int i = 0; i < copy_title.size(); ++i) {
							cout << "Title: " << copy_title[i] << "\nISBN: " << copy_ISBN[i] << "\nAuthor: " << copy_author[i] << "\nCopyright: " << copy_year[i] << "\n\n";
						}
					}
					cout << "You have exited the database. Goodbye.\n\n";
					return 0;
				default:
					cout << "\nInvalid input. Please try again.\n\n";
					break;
				}
			}
				
			cout << "Please chose '1' to check book out. '2' to check book in. '3' to see if book is checked out. '4' to search a book by its ISBN. '5' to search for books by author. '6' to exit.\n\n";
		}
	}
	// e.what() extracts message from the runtime_error
	catch (runtime_error& e) {
		cerr << "\nruntime error: " << e.what() << "\n"; // cerr used for error outputs
		return 1;
	}
	// used to handle excpetions of any type whatsoever
	catch (...) {
		cerr << "\nSomething went wrong\n";
		return 2;
	}
}