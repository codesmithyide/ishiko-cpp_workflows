/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/CodeSmithyIDE/Tasks/blob/master/LICENSE.txt
*/

#include "TaskTests.h"
#include "CodeSmithy/Tasks/SyncFunctionTask.h"

using namespace Ishiko::Tests;

TaskTests::TaskTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Task tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
    append<HeapAllocationErrorsTest>("run test 3", RunTest3);
}

void TaskTests::CreationTest1(Test& test)
{
    CodeSmithy::Task task;

    ISHTF_FAIL_IF_NEQ(task.status(), CodeSmithy::Task::EStatus::ePending);
    ISHTF_PASS();
}

void TaskTests::RunTest1(Test& test)
{
    CodeSmithy::Task task;
    task.run();

    ISHTF_FAIL_IF_NEQ(task.status(), CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_PASS();
}

void TaskTests::RunTest2(Test& test)
{
    CodeSmithy::SyncFunctionTask task([]() { throw std::exception(); });
    task.run();

    ISHTF_FAIL_IF_NEQ(task.status(), CodeSmithy::Task::EStatus::eFailed);
    ISHTF_PASS();
}

void TaskTests::RunTest3(Test& test)
{
    CodeSmithy::Task task;

    std::shared_ptr<TestTaskObserver> observer = std::make_shared<TestTaskObserver>();
    task.observers().add(observer);

    task.run();

    ISHTF_FAIL_IF_NEQ(task.status(), CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_FAIL_IF_NEQ(observer->statuses().size(), 2);
    ISHTF_FAIL_IF_NEQ(observer->statuses()[0], CodeSmithy::Task::EStatus::eRunning);
    ISHTF_FAIL_IF_NEQ(observer->statuses()[1], CodeSmithy::Task::EStatus::eCompleted);
    ISHTF_PASS();
}

void TestTaskObserver::onStatusChanged(const CodeSmithy::Task& source, CodeSmithy::Task::EStatus status)
{
    m_statuses.push_back(status);
}

const std::vector<CodeSmithy::Task::EStatus> TestTaskObserver::statuses() const
{
    return m_statuses;
}