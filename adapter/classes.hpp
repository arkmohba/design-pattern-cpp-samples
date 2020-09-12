#include <string>

class Banner {
 private:
  std::string my_message;

 public:
  explicit Banner(std::string message);
  void showWithParen();
  void showWithAster();
};

class Print {
 public:
  virtual void printWeak() = 0;
  virtual void printStrong() = 0;
};

class PrintBanner : public Print, public Banner {
 public:
  explicit PrintBanner(std::string message);
  void printWeak();
  void printStrong();
};

class PrintBannerTransfer: public Print {
 private:
  Banner banner;
 public:
  explicit PrintBannerTransfer(std::string message);
  void printWeak();
  void printStrong();
};
