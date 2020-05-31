#include <iostream>
#include <string>
#include "classes.hpp"

using namespace std;

int main() {
  BookShelf* book_shelf = new BookShelf(4);
  book_shelf->appendBook("Around the World in 80 Days");
  book_shelf->appendBook("Bible");
  book_shelf->appendBook("Cinderella");
  book_shelf->appendBook("Daddy-Long-Legs");
  Iterator<Book>* it = book_shelf->iterator();
  while(it->hasNext()) {
    Book book = it->next();
    cout << book.getName() << endl;
  }
  return 0;
}


