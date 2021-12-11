#include <cassert>
#include <cstring>

#include <iostream>
#include <unordered_set>
#include <string>

#include "coroutine.h"

class CoroutineTest : public Coroutine {
 public:
  int Run() {
    // 协程, 第一次从头开始执行, 此后从上一次yield之后的地方开始执行.
    // Clion右键宏-Refactor-Inline查看展开.
    reenter(this) {
      yield return 1;
      yield return 2;
    }
    // 协程结束, 后续函数只返回0.
    return 0;
  }
};

// 解析HTTP请求头的第一行, 如: GET /foo/bar HTTP/2.0
class HttpRequestParser : public Coroutine {
 public:
  // 解析成功返回true, 格式有误返回false.
  bool Parse(const std::string& request);

  [[nodiscard]] const std::string& method() const { return method_; }
  [[nodiscard]] const std::string& uri() const { return uri_; }
  [[nodiscard]] const std::string& version() const { return version_; }

 private:
  bool Consume(char c);

 private:
  // 解析结果存在成员变量中.
  std::string method_;
  std::string uri_;
  std::string version_;
};

int main() {
  {
    CoroutineTest ct1, ct2;
    assert(ct1.Run() == 1);
    assert(ct1.Run() == 2);
    assert(ct1.Run() == 0);
    assert(ct1.Run() == 0);

    assert(ct2.Run() == 1);
  }

  {
    HttpRequestParser parser;
    assert(parser.Parse("GET /foo/bar HTTP/2.0"));
    assert(parser.method() == "GET");
    assert(parser.uri() == "/foo/bar");
    assert(parser.version() == "2.0");

    assert(!HttpRequestParser().Parse("/foo/bar HTTP/2.0"));
    assert(!HttpRequestParser().Parse("POST/foo/bar HTTP/2.0"));
    assert(!HttpRequestParser().Parse("Fuck /foo/bar HTTP/2.0"));
    assert(!HttpRequestParser().Parse("POST /foo/bar version/1.1"));
  }
  return 0;
}

bool HttpRequestParser::Consume(char c) {
  reenter(this) {
    // 读取所有连续的字符作为method.
    while (isalpha(c)) {
      method_.push_back(c);
      yield return true;
    }
    if (method_.empty()) {
      std::cerr << "Parse error: no method" << std::endl;
      yield return false;
    }
    if (c == ' ') {
      yield return true;
    } else {
      std::cerr << "Parse error: no space after method" << std::endl;
      yield return false;
    }
    // 读取uri.
    while (std::isalpha(c) || c == '/') {
      uri_.push_back(c);
      yield return true;
    }
    if (uri_.empty()) {
      std::cerr << "Parse error: no uri" << std::endl;
      yield return false;
    }
    if (c == ' ') {
      yield return true;
    } else {
      std::cerr << "Parse error: no space after uri" << std::endl;
      yield return false;
    }
    // 读取version.
    while (std::unordered_set<char>{'H', 'T', 'P', '/', '0', '1', '2', '.'}.count(c)) {
      version_.push_back(c);
      yield return true;
    }
  }
  return true;
}

bool HttpRequestParser::Parse(const std::string& request) {
  for (char c : request) {
    if (!Consume(c)) {
      return false;
    }
  }
  static std::unordered_set<std::string> methods = {"GET", "POST", "DELETE", "PUT", "OPTION"};
  if (!methods.count(method_)) {
    std::cerr << "Parse error: invalid method: " << method_ << std::endl;
    return false;
  }
  if (version_.size() < 5 || strncmp(version_.c_str(), "HTTP/", 5) != 0) {
    std::cerr << "Parse error: must be \"HTTP/\" before version" << std::endl;
    return false;
  }
  version_ = version_.substr(5);
  return true;
}
