/*
    Copyright (c) 2018-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tasks/blob/main/LICENSE.txt
*/

#include "TasksTests.h"
#include "Ishiko/UserTasks/Tasks.h"

using namespace Ishiko::Tests;
using namespace Ishiko::UserTasks;

TasksTests::TasksTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Tasks tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("add test 1", AddTest1);
    append<HeapAllocationErrorsTest>("addObserver test 1", AddObserverTest1);
    append<HeapAllocationErrorsTest>("removeObserver test 1", RemoveObserverTest1);
}

void TasksTests::CreationTest1(Test& test)
{
    Tasks tasks;

    ISHIKO_FAIL_IF_NOT(tasks.size() == 0);
    ISHIKO_PASS();
}

void TasksTests::AddTest1(Test& test)
{
    Tasks tasks;
    tasks.add(std::make_shared<Task>());
    
    ISHIKO_FAIL_IF_NOT(tasks.size() == 1);
    ISHIKO_PASS();
}

void TasksTests::AddObserverTest1(Test& test)
{
    Tasks tasks;
    std::shared_ptr<Tasks::Observer> observer = std::make_shared<Tasks::Observer>();
    tasks.observers().add(observer);

    ISHIKO_PASS();
}

void TasksTests::RemoveObserverTest1(Test& test)
{
    Tasks tasks;
    std::shared_ptr<Tasks::Observer> observer = std::make_shared<Tasks::Observer>();
    tasks.observers().add(observer);
    tasks.observers().remove(observer);

    ISHIKO_PASS();
}