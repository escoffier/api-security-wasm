#pragma once

#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

template <class T> class BlockingQueue {
public:  
  void push(T value) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
    cond_.notify_one();
  };

  bool pop(T & item) {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this] { return !queue_.empty() || quit_; });
    if (quit_) {
      return false;
    }
    item = queue_.front();
    queue_.pop();
    return true;
  }

  void quit() {
    quit_.store(true);
  }

private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
  mutable std::atomic<bool> quit_ = false;
};