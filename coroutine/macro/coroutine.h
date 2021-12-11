//
// Created by 79337 on 2021/12/11.
//
#ifndef COROUTINE_MACRO_COROUTINE_H_
#define COROUTINE_MACRO_COROUTINE_H_

class Coroutine {
 public:
  [[nodiscard]] bool IsChild() const { return value_ < 0; }
  [[nodiscard]] bool IsParent() const { return !IsChild(); }
  [[nodiscard]] bool IsComplete() const { return value_ == -1; }

 private:
  friend class CoroutineRef;
  int value_ = 0;
};

class CoroutineRef {
 public:
  CoroutineRef(Coroutine& coroutine) : value_(coroutine.value_) {}
  CoroutineRef(Coroutine* coroutine) : value_(coroutine->value_) {}
  ~CoroutineRef() {
    if (!modified_) {
      value_ = -1;
    }
  }
  void operator=(const CoroutineRef&) = delete;

  operator int() const { return value_; }

  int& operator=(int v) {
    modified_ = true;
    return value_ = v;
  }

 private:
  int& value_;
  bool modified_ = false;
};

#define CORO_REENTER(c) \
  switch (CoroutineRef _coroutine_value = c) \
    case -1: \
      if (_coroutine_value) { \
        goto terminate_coroutine; \
        terminate_coroutine: \
        _coroutine_value = -1; \
        goto bail_out_of_coroutine; \
        bail_out_of_coroutine: \
        break; \
      } \
      else case 0: \

#define CORO_YIELD_IMPL(n) \
  for (_coroutine_value = (n);;) \
    if (_coroutine_value == 0) { \
      case (n): ; \
      break; \
    } \
    else \
      switch (_coroutine_value ? 0 : 1) \
        for (;;) \
          case -1: if (_coroutine_value) \
            goto terminate_coroutine; \
          else for (;;) \
            case 1: if (_coroutine_value) \
                goto bail_out_of_coroutine; \
            else case 0:

#define CORO_FORK_IMPL(n) \
  for (_coroutine_value = -(n);; _coroutine_value = (n)) \
    if (_coroutine_value == (n)) { \
      case -(n): ; \
      break; \
    } \
    else

#define reenter(c) CORO_REENTER(c)
#define yield CORO_YIELD_IMPL(__LINE__)
#define fork CORO_FORK_IMPL(__LINE__)

#endif  // COROUTINE_MACRO_COROUTINE_H_
