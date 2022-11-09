/*
        Class Book should have members for ISBN, title, author, and copyright
   date Store data on whether or not the book is checked out Create functions
   for returning those data values Create functions for checking a book in and
   out Do simple validation of data entered; for example, accept ISBNs only of
   the form n-n-n-x where n is integer and x is digit or letter
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void error(const string &s) { throw runtime_error(s); }

class Library {
public:
  struct Book {
    string ISBN;
    string title;
    string author;
    int year;
    bool is_checked_out;
    Book(string const ISBN, string const title, string const author,
         int const year, bool is_checked_out)
        : ISBN(ISBN), title(title), author(author), year(year),
          is_checked_out(is_checked_out) {}
  };

  Library();
  Library(vector<Library::Book> &books);

  void check_book_in(string &input);
  void check_book_out(string &input);
  bool is_title_in_library(string const &title) const;
  bool is_checked_out(string const &title) const;
  void print_book_status(string &input) const;
  bool is_isbn_in_inventory(string const &isbn) const;
  static bool is_isbn_correct_format(string const &isbn);
  void print_title_of_isbn(string &isbn) const;
  bool does_author_have_books_in_inventory(string const &author) const;
  void print_book_of_author(string &author) const;
  bool books_have_valid_years() const;
  bool books_have_valid_isbn() const;
  bool is_inventory_empty() const;
  void print_remaining_inventory() const;
  friend ostream &operator<<(ostream &os, const Library &library);

private:
  vector<Book> books;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Library::Library() {
  books.push_back(
      Library::Book("1-2-1-a", "Math Book", "Jim Tory", 2010, false));
  books.push_back(
      Library::Book("1-2-8-c", "Science Book", "Ahmed Sakr", 1965, false));
  books.push_back(
      Library::Book("3-6-1-a", "History Book", "Randel Keast", 2021, false));
  books.push_back(
      Library::Book("7-9-1-t", "English Book", "Jim Tory", 1825, false));
  books.push_back(
      Library::Book("9-2-2-z", "French Book", "Pierre LeGay", 1938, false));
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Library::Library(vector<Library::Book> &books) : books(books) {
  if (!books_have_valid_years()) {
    error("Inventory: book has invalid copyright year.");
  }

  if (!books_have_valid_isbn()) {
    error("Inventory: book has invalid ISBN.");
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::is_title_in_library(string const &title) const {
  for (auto &book : books) {
    if (title == book.title) {
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::is_checked_out(string const &title) const {
  for (auto &book : books) {
    if (title == book.title && book.is_checked_out) {
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Library::print_book_status(string &input) const {
  cout << "\nEnter the book you want to check.\n\n";
  getline(cin, input);

  // is title in inventory
  if (!is_title_in_library(input)) {
    error("The book your looking for is not in the inventory.");
  }

  // check if booked is checked out
  if (!is_checked_out(input)) {
    cout << "\nThe book is not checked out.\n\n";
  } else {
    cout
        << "\nThe book is checked out. Please check again some other time.\n\n";
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::is_isbn_in_inventory(string const &isbn) const {
  for (auto &book : books) {
    if (isbn == book.ISBN) {
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::is_isbn_correct_format(string const &isbn) {
  // correct format is n-n-n-x where n is any integer and x is integer or letter
  // for example: 2-4-1-a

  if (input.size() != 7) {
    return false;
  }

  for (int i = 0; i < input.size(); i++) {
    switch (i) {
    case 0:
    case 2:
    case 4:
      if (input[i] < '0' || input[i] > '9') {
        return false;
      }
      break;
    case 1:
    case 3:
    case 5:
      if (input[i] != '-') {
        return false;
      }
      break;
    case 6:
      if (!isalpha(input[i])) {
        return false;
      }
      break;
    }
  }

  return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Library::print_title_of_isbn(string &isbn) const {
  cout << "\nPlease enter an ISBN and the corresponding book title will be "
          "given.\n\n";
  getline(cin, isbn);

  if (!is_isbn_correct_format(isbn)) { // check if isbn in correct format
    cout << "\nInproper format of ISBN. Please try again.\n\n";
  } else if (!is_isbn_in_inventory(isbn)) { // check of isbn is in inventory
    cout
        << "\nThis ISBN does not exist in the inventory. Please try again.\n\n";
  } else { // print corresponding book

    for (auto &book : books) {
      if (isbn == book.ISBN) {
        cout << "\nThe book is " << book.title << ".\n\n";
      }
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::does_author_have_books_in_inventory(string const &author) const {
  for (auto &book : books) {
    if (author == book.author) {
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Library::print_book_of_author(string &author) const {

  cout << "\nEnter an author to see what books he has in our inventory.\n\n";
  getline(cin, author);

  if (!does_author_have_books_in_inventory(author)) {
    cout << "\nThis author is has no books in our inventory. Please input "
            "another name.\n\n";
    return;
  }

	int num_books_by_author = 0;
	int last_book_index_written_by_author = 0;

	for (int i = 0; i < books.size(); ++i) {
    if (author == books[i].author) {
      num_books_by_author += 1;
			last_book_index_written_by_author = i;
    }
  }
	
	if(num_books_by_author == 1) {
		cout << "\nThe author wrote " << books[last_book_index_written_by_author].title << "\n\n";	
		return;
	}

  cout << "\nThe author has written the following books: ";
  for (int i = 0; i < books.size(); ++i) {
    if (books[i].author == author) {
      if (i < books.size() - 1) {
        cout << books[i].title << ", ";
      } else {
        cout << "and " << books[i].title << "\n\n";
      }
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::books_have_valid_years() const {
  static const int maxyear = 2023;
  static const int minyear = 1790; // year when first book was copyrighted

  for (auto &book : books) {
    if (book.year > maxyear || book.year < minyear) {
      return true;
    }
  }

  return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::books_have_valid_isbn() const {

  for (auto &book : books) {
    if (!is_isbn_correct_format(book.ISBN)) {
      return false;
    }
  }

  return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Library::check_book_out(string &input) {
  cout << "\nPlease enter a book you would wish to check out.\n\n";
  getline(cin, input);

  // check if book valid
  if (!is_title_in_library(input)) {
    error("The book your looking for is not in the inventory.");
  }

  for (auto &book : books) {
    if (book.title == input && !book.is_checked_out) {
      book.is_checked_out = true;
      cout << "\nYou have succesfully checked out " << book.title << "\n\n";
      return;
    }
  }

  cout << "\nThe book is already checked out.\n\n";
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Library::check_book_in(string &input) {
  cout << "\nPlease enter which book you want to check back in.\n\n";
  getline(cin, input);

  // check if book valid
  if (!is_title_in_library(input)) {
    error("The book you're looking for is not in the inventory.");
  }

  for (auto &book : books) {
    if (book.title == input && book.is_checked_out) {
      book.is_checked_out = false;
      cout << "\nYou have succesfully checked in " << book.title << "\n\n";
      return;
    }
  }

  cout << "\nThis book has not been checked out by anyone\n\n";
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

ostream &operator<<(ostream &os, const Library &library) {
  for (auto &book : library.books) {
    os << "Title: " << book.title << "\nISBN: " << book.ISBN
       << "\nAuthor: " << book.author << "\nCopyright: " << book.year << "\n\n";
  }

  return os;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Library::is_inventory_empty() const { return books.size() == 0; }

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Library::print_remaining_inventory() const {
  cout << "\nThe remaining inventory is\n\n";
  for (auto &book : books) {
    if (!book.is_checked_out) {
      cout << "Title: " << book.title << "\nISBN: " << book.ISBN
           << "\nAuthor: " << book.author << "\nCopyright: " << book.year
           << "\n\n";
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() {
  try {
    Library library;
    string input;

    cout << "Welcome to Mister HB's library! Here is our inventory:\n\n";
    cout << library;
    cout << "\nPlease chose one of the following 6 options.\n\n";
    cout << "'1' to check book out. '2' to check book in. '3' to see if book "
            "is checked out. '4' to search a book by its ISBN. ";
    cout << "'5' to search for books by author. '6' to exit.\n\n";

    while (getline(cin, input)) {
      if (input.size() > 1 ||
          !isdigit(input[0])) { // this prevents program from throwing
                                // pick.size() number of invlaid messages
        cout << "\nInvalid input. Please try again.\n\n";
      } else {
        switch (input[0]) { // switch can't be used on string, have to turn
                            // string into char
        case '1':
          library.check_book_out(input);
          break;
        case '2':
          library.check_book_in(input);
          break;
        case '3':
          library.print_book_status(input);
          break;
        case '4':
          library.print_title_of_isbn(input);
          break;
        case '5':
          library.print_book_of_author(input);
          break;
        case '6':
          if (library.is_inventory_empty()) {
            cout << "\nThe inventory is empty.\n\n";
          } else {
            library.print_remaining_inventory();
          }
          cout << "You have exited the database. Goodbye.\n\n";
          return 0;
        default:
          cout << "\nInvalid input. Please try again.\n\n";
          break;
        }
      }

      cout << "Please chose '1' to check book out. '2' to check book in. '3' "
              "to see if book is checked out. '4' to search a book by its "
              "ISBN. '5' to search for books by author. '6' to exit.\n\n";
    }
  }
  // e.what() extracts message from the runtime_error
  catch (runtime_error &e) {
    cerr << "\nruntime error: " << e.what()
         << "\n"; // cerr used for error outputs
    return 1;
  }
  // used to handle excpetions of any type whatsoever
  catch (...) {
    cerr << "\nSomething went wrong\n";
    return 2;
  }
}