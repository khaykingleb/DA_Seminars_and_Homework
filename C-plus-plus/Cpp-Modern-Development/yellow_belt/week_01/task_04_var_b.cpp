#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>

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

// Выделим в отдельную функцию получение следующего по приоритету типа задачи
// Функция налагает требование на входной параметр: он не должен быть равен DONE
// При этом task_status явно не сравнивается с DONE, что позволяет
// сделать эту функцию максимально эффективной
TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

class TeamTasks {
private:
    map<string, TasksInfo> programmers;
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const;

    // Добавить новую задачу (в статусе NEW) для конкретного разработчика
    void AddNewTask(const string& person);

    // Обновить статусы по данному количеству задач конкретного разработчика
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count);
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string &person) const {
    return programmers.at(person);
}

void TeamTasks::AddNewTask(const string &person) {
    ++programmers[person][TaskStatus::NEW];
}

// Функция для удаления нулей из словаря
void RemoveZeros(TasksInfo& tasks_info) {
    // Соберём те статусы, которые нужно убрать из словаря
    vector<TaskStatus> status_to_remove;
    for (const auto& task_item : tasks_info) {
        if (task_item.second == 0) {
            status_to_remove.push_back(task_item.first);
        }
    }

    for (const TaskStatus status : status_to_remove) {
        tasks_info.erase(status);
    }
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string &person, int task_count) {
    TasksInfo updated_tasks, untouched_tasks;

    // Здесь и далее мы будем пользоваться тем фактом, что в std::map оператор []
    // в случае отсутствия ключа инициализирует значение по умолчанию,
    // если это возможно.
    // std::map::operator[] ->
    // http://ru.cppreference.com/w/cpp/container/map/operator_at
    TasksInfo& tasks = programmers[person];

    // Посчитаем, сколько задач каждого из статусов нужно обновить,
    // пользуясь тем фактом, что по умолчанию enum class инциализирует значения
    // от нуля по возрастанию.
    // enum class -> http://ru.cppreference.com/w/cpp/language/enum
    for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
        // Считаем обновлённые
        updated_tasks[Next(status)] = min(task_count, tasks[status]);
        // Считаем, сколько осталось обновить
        task_count -= updated_tasks[Next(status)];
    }

    // Обновляем статус текущих задач в соответствии с информацией об обновлённых
    // и находим количество нетронутых
    for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
        untouched_tasks[status] = tasks[status] -  updated_tasks[status];
        tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
    }

    // По условию, DONE задачи не нужно возвращать в не обновлённых задачах
    tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

    // По условию в словарях не должно быть нулей
    RemoveZeros(updated_tasks);
    RemoveZeros(untouched_tasks);
    RemoveZeros(programmers.at(person));
    return {updated_tasks, untouched_tasks};
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" << ", "
         << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" << ", "
         << tasks_info[TaskStatus::TESTING] << " tasks are being tested" << ", "
         << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
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
