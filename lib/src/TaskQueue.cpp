#include "pacman/TaskQueue.h"

using namespace pacman;

void TaskQueue::executeTasks(TaskQueue::size_type tasksNumToExecute) {
    while (!tasks_.empty() && tasksNumToExecute--) {
        tasks_.front()();
        tasks_.pop();
    }
}
