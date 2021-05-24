#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

const TasksInfo& DeleteEmptyElements(TasksInfo& tasks) {
    vector<TaskStatus> keys_for_delete;

    for (const auto& [key, value] : tasks) {
        if (value == 0) {
            keys_for_delete.push_back(key);
        }
    }

    for (const TaskStatus& key : keys_for_delete) {
        tasks.erase(key);
    }

    return tasks;
}

class TeamTasks {
private:
    map<string, TasksInfo> programmers;
public:
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        if (programmers.count(person) == 1) {
            ++programmers[person][TaskStatus::NEW];

        } else {
            TasksInfo programmer_tasks;
            ++programmer_tasks[TaskStatus::NEW];
            programmers.insert({person, programmer_tasks});
        }
    }

    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person)  {
        return DeleteEmptyElements(programmers[person]);
    };

    // Обновить статусы по данному количеству задач конкретного разработчика,
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated_tasks;
        TasksInfo untouched_tasks;

        if (programmers.count(person) == 1) {
            untouched_tasks = programmers[person];
            untouched_tasks.erase(TaskStatus::DONE);
        } else {
            return tie(updated_tasks, untouched_tasks);
        }

        for (size_t i = 0; i < task_count; ++i) {
            if (untouched_tasks[TaskStatus::NEW] != 0) {
                --untouched_tasks[TaskStatus::NEW];
                --programmers[person][TaskStatus::NEW];
                ++updated_tasks[TaskStatus::IN_PROGRESS];
                ++programmers[person][TaskStatus::IN_PROGRESS];
                continue;
            }

            if (untouched_tasks[TaskStatus::IN_PROGRESS] != 0) {
                --untouched_tasks[TaskStatus::IN_PROGRESS];
                --programmers[person][TaskStatus::IN_PROGRESS];
                ++updated_tasks[TaskStatus::TESTING];
                ++programmers[person][TaskStatus::TESTING];
                continue;
            }

            if (untouched_tasks[TaskStatus::TESTING] != 0) {
                --untouched_tasks[TaskStatus::TESTING];
                --programmers[person][TaskStatus::TESTING];
                ++updated_tasks[TaskStatus::DONE];
                ++programmers[person][TaskStatus::DONE];
            }
        }

        updated_tasks = DeleteEmptyElements(updated_tasks);
        untouched_tasks = DeleteEmptyElements(untouched_tasks);

        return tie(updated_tasks, untouched_tasks);
    };
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" << ", "
         << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" << ", "
         << tasks_info[TaskStatus::TESTING] << " tasks are being tested" << ", "
         << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
