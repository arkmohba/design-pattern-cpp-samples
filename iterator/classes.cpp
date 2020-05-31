#include "classes.hpp"


Iterator<Book>* BookShelf::iterator() {
  return new BookShelfIterator(this);
}
