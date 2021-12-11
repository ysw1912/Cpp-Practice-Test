#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <tuple>

#include <cassert>
#include <pthread.h>


void Sleep(int sec, const std::string& msg) {
  std::this_thread::sleep_for(std::chrono::seconds(sec));
  std::cout << "  Have slept for " << sec << " seconds: " << msg << std::endl;
}

struct ThreadArgs {
  int sec;
  std::string msg;
};

void* SleepFun(void* args) {
  auto* thread_args = static_cast<ThreadArgs*>(args);
  Sleep(thread_args->sec, thread_args->msg);
  return nullptr;
}

namespace {

template <size_t...>
struct TupleIndices {};

// 泛化
template <size_t Start, size_t End, class IntTuple>
struct MakeTupleIndicesImpl;

// 递归
template <size_t Start, size_t End, size_t... Indices>
struct MakeTupleIndicesImpl<Start, End, TupleIndices<Indices...>> {
  using type = typename MakeTupleIndicesImpl<Start + 1, End, TupleIndices<Indices..., Start>>::type;
};

// 递归终止条件：Start == End
template <std::size_t End, std::size_t... Indices>
struct MakeTupleIndicesImpl<End, End, TupleIndices<Indices...>> {
  using type = TupleIndices<Indices...>;
};

template <size_t End, std::size_t Start = 0>
struct MakeTupleIndices {
  using type = typename MakeTupleIndicesImpl<Start, End, TupleIndices<>>::type;
};

struct ThreadDataBase {
  virtual ~ThreadDataBase() = default;
  virtual void Run() = 0;
};

template <class F, class... Args>
class ThreadData : public ThreadDataBase {
 public:
  explicit ThreadData(F&& f, Args&& ...args) : fp_(std::forward<F>(f), std::forward<Args>(args)...) {}

  void Run() override {
    std::cout << "  In ThreadData::Run()" << std::endl;
    using IndexType = typename MakeTupleIndices<std::tuple_size_v<TupleType>, 1>::type;
    RunImpl(IndexType());
  }

 private:
  template <size_t... Indices>
  void RunImpl(TupleIndices<Indices...>) {
    std::invoke(std::move(std::get<0>(fp_)), std::move(std::get<Indices>(fp_))...);
  }

  using TupleType = std::tuple<std::decay_t<F>, std::decay_t<Args>...>;
  TupleType fp_;
};

template<class F, class... Args>
inline ThreadDataBase* MakeThreadData(F&& f, Args&&... args) {
  std::cout << "  Making thread data" << std::endl;
  return new ThreadData<std::remove_reference_t<F>, Args...>(
      std::forward<F>(f), std::forward<Args>(args)...);
}

void* ThreadEntryPoint(void* args) {
  std::cout << "  In ThreadEntryPoint()" << std::endl;
  std::unique_ptr<ThreadDataBase> thread_data(static_cast<ThreadDataBase*>(args));
  thread_data->Run();
  return nullptr;
}

}  // namespace

class Thread {
 public:
  template<class F, class... Args>
  explicit Thread(F&& f, Args&&... args) {
    auto* thread_data = MakeThreadData(std::forward<F>(f), std::forward<Args>(args)...);
    assert(pthread_create(&thread_id_,
                          nullptr,
                          ThreadEntryPoint,
                          static_cast<void *>(thread_data)) == 0);
  }

  void Join() {
    assert(pthread_join(thread_id_, nullptr) == 0);
  }

 private:
  pthread_t thread_id_{};
};

int main(int argc, char const *argv[]) {
  std::cout << "Linux pthread way:" << std::endl;
  pthread_t thread_id;
  ThreadArgs args{3, "Awesome!"};
  assert(pthread_create(&thread_id, nullptr, SleepFun, static_cast<void*>(&args)) == 0);
  assert(pthread_join(thread_id, nullptr) == 0);

  std::cout << std::endl << "Wrapped thread class way:" << std::endl;
  Thread thread(Sleep, 3, "Awesome!");
  thread.Join();
  return 0;
}
