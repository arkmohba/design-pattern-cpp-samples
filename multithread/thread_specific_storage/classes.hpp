#include <condition_variable>
#include <deque>
#include <fstream>
#include <memory>
#include <mutex>
#include <string>

class TSLog {
 private:
  std::ofstream ofs;

 public:
  explicit TSLog(std::string file_path) { ofs = std::ofstream(file_path); }
  void print_ln(std::string s) { ofs << s << std::endl; }
  void close() {
    ofs << "==== End of log ====" << std::endl;
    ofs.close();
  }
};

class Log {
 private:
  static thread_local std::string __name;
  static std::shared_ptr<TSLog> get_ts_log();

 public:
  static void set_name(std::string name) {__name = name;}
  static void print_ln(std::string s) { get_ts_log()->print_ln(s); }
  static void close() { get_ts_log()->close(); }
};

void thread_func_client(std::string name);
