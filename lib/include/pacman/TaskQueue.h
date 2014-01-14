#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <functional>
#include <queue>

namespace pacman {
class TaskQueue {
  public:
    typedef std::queue<std::function<void ()>> Tasks;
    typedef Tasks::size_type size_type;

    void post(const std::function<void ()>& task) { tasks_.push(task); }
    size_type getSize() const { return tasks_.size(); }
    void executeTasks(size_type tasksNumToExecute);
  private:
    Tasks tasks_;
};
} // namespace pacman

#endif // TASKQUEUE_H
