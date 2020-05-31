#include <string>
#include <iostream>

template <class T>
class Iterator {
 public:
  virtual bool hasNext() = 0;
  virtual T next() = 0;
};

template <class T>
class Aggregate {
 public:
  virtual Iterator<T>* iterator() = 0;
};

class Book {
 private:
  std::string name_;

 public:
  Book(std::string name) { name_ = name; }
  std::string getName() { return name_; }
};

class BookShelf : public Aggregate<Book> {
 private:
  Book** books_;
  int last = 0;

 public:
  BookShelf(int max_size) {
    if (max_size <= 0) {
      std::cout << "please set max_size > 0, input : " << max_size << std::endl;
    }
    books_ = new Book*[max_size];
  }
  Book getBookAt(int index) {
    if (index < 0) {
      std::cout << "please set index >= 0" << std::endl;
    }
    return *books_[index];
  }
  void appendBook(Book* book) {
    books_[last] = book;
    last++;
  }
  void appendBook(std::string name) {
    Book* new_book = new Book(name);
    appendBook(new_book);
  }
  int getLength() { return last; }
  Iterator<Book>* iterator();
  ~BookShelf() {
    for (int i = 0; i < last; i++) {
      delete books_[i];
    }
    delete books_;
  }
};

class BookShelfIterator : public Iterator<Book> {
 private:
  BookShelf* book_shelf_;
  int index_;

 public:
  BookShelfIterator(BookShelf* bookshelf) {
    book_shelf_ = bookshelf;
    index_ = 0;
  }
  bool hasNext() {
    if (index_ < book_shelf_->getLength()) {
      return true;
    } else {
      return false;
    }
  }
  Book next() {
    Book book = book_shelf_->getBookAt(index_);
    index_++;
    return book;
  }
};