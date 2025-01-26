/*---------------------------------------------------------------------------------
std::priority_queue: The greatest on top.
It is a container adapter that provides constant time access to the greatest or
smallest element in the container. 
----------------------------------------------------------------------------------*/
#include <iostream>
#include <queue>
#include <functional>

// Task structure
struct Task {
    int priority;                   // Higher value = Higher priority
    std::function<void()> action;   // The function to execute
};

// Needed for proper sorting
bool operator<(const Task& t1, const Task& t2) {
    return t1.priority < t2.priority;  // Higher priority comes first;
}

int main() {
    std::priority_queue<Task> taskQueue;

    //Adding tasks
    taskQueue.emplace(1, [] { std::cout << "Low priority task\n"; });
    taskQueue.emplace(3, [] { std::cout << "High priority task\n"; });
    taskQueue.emplace(2, [] { std::cout << "Medium priority task\n"; });

    while (!taskQueue.empty()) {
        Task currentTask = taskQueue.top();
        taskQueue.pop();
        currentTask.action();   // Execute the task
    }
    return 0;
}
/*---------------------------------------------------------------------------------
High priority task
Medium priority task
Low priority task
----------------------------------------------------------------------------------*/
