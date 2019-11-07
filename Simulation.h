#ifndef _SIMULATION_H
#define _SIMULATION_H
#include "Queue.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Student
{
    int window;
    int waitingTime;
    int serviceTime;
    int finishTime;
};

struct Window
{
    Queue<Student> q;
    int idleTime;
    int currentServiceTime;
};

struct Event
{
    int time;
    int numStudents;
    Student* students;
};

class Simulation
{
    Window* windows;
    DoubleLinkedList<Student> finishedStudents;
    Queue<Event*> eventQueue;
    int numberOfWindows;
    int time;
public:
    Simulation(const string& fileName);
    void printEventQueue();
    void Simulate();
    void ComputeStatistics();
private:
    void LoadData(const string& fileName);
    bool isFinished();
    void sortList();
};
//takes in the file
Simulation::Simulation(const string& fileName)
{
    LoadData(fileName);
    time = 1;
}

void Simulation::LoadData(const string& fileName)
{
  //check if file exists 
    fstream file(fileName.c_str(), ios::in);
    if(!file)
    {
        cout << "Error Opening File!" << endl;
        return;
    }

    file >> numberOfWindows;
    windows = new Window[numberOfWindows];
    for (int i = 0; i < numberOfWindows; i++)
    {
        windows[i].currentServiceTime = 0;
        windows[i].idleTime = 0;
    }
    while (!file.eof())
    {
        int time;
        file >> time;
        int numStudents;
        file >> numStudents;
        if (file.eof())
        {
            break;
        }
        Event* e = new Event;
        Student* stu = new Student[numStudents];
        for (int i = 0; i < numStudents; i++)
        {
            file >> stu[i].serviceTime;
        }
        e->time = time;
        e->students = stu;
        e->numStudents = numStudents;
        eventQueue.Enqueue(e);
    }
    file.close();
}

void Simulation::printEventQueue()
{
    Queue<Event*> eq = eventQueue;
    Event* e;
    while(eq.Dqueue(e))
    {
        cout << "time: " << e->time << endl;
        cout << "Num " << e->numStudents << endl;
        for (int i = 0 ; i < e->numStudents; i++)
        {
            cout << e->students[i].serviceTime << endl;
        }
    }
}

void Simulation::Simulate()
{
    Event* e;
    while(!isFinished())
    {
        cout << "Time " << time << " minutes:" << endl << endl;
        if (eventQueue.Peek(e))
        {
            if (e->time == time)
            {
                eventQueue.Dqueue(e);
                for (int i = 0; i < e->numStudents; i++)
                {
                    int minWindow;
                    int minTime = windows[0].currentServiceTime;
                    for (int j = 1; j < numberOfWindows; j++)
                    {
                        if (windows[j].currentServiceTime < minTime)
                        {
                            minWindow = j;
                        }
                    }
                    e->students[i].waitingTime = windows[minWindow].currentServiceTime + e->students[i].serviceTime;
                    e->students[i].finishTime = e->students[i].waitingTime + time;
                    windows[minWindow].q.Enqueue(e->students[i]);
                    windows[minWindow].currentServiceTime += e->students[i].serviceTime;
                    cout << "A Student arrived and is added to the queue of window number " << minWindow << endl << endl;
                    cout << "He will finish service in time " << e->students[i].finishTime << "." << endl << endl;
                }
            }
        }

        for (int i = 0; i < numberOfWindows; i++)
        {
            Student st;
            if (windows[i].q.Peek(st))
            {
                if (st.finishTime == time)
                {
                    windows[i].q.Dqueue(st);
                    finishedStudents.InsertEnd(st);
                    cout << "Window number " << i << " finished serving a student, and he's leaving now." << endl;
                }
                windows[i].currentServiceTime--;
            }
            else
            {
                windows[i].idleTime++;
                cout << "Window number << " << i << " is currently idle." << endl << endl;
            }
        }
        time++;
        cout << "Press any key to simulate next timestep" << endl;
        char c;
        cin >> c;
        cout << "--------------------------------------------------------------------" << endl;
    }
}

bool Simulation::isFinished()
{
    bool isfinish = eventQueue.IsEmpty();
    for (int i = 0; i < numberOfWindows; i++)
    {
        isfinish = isfinish & (windows[i].q.IsEmpty());
    }
    return isfinish;
}

void Simulation::ComputeStatistics()
{
    Student temp;
    double mean = 0;
    int above10 = 0;
    int longest = 0;
    for (int i = 0; i <= finishedStudents.GetSize(); i++)
    {
        finishedStudents.GetItem(temp, i);
        mean += temp.waitingTime;
        if (temp.waitingTime > 10)
        {
            above10++;
        }
        if (temp.waitingTime > longest)
        {
            longest = temp.waitingTime;
        }
    }
    mean /= finishedStudents.GetSize() + 1;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Mean Student Waiting time = " << mean << " minutes." << endl;
    sortList();
    int middle = finishedStudents.GetSize() / 2;
    finishedStudents.GetItem(temp, middle);
    int median = temp.waitingTime;
    cout << "Median Student Waiting time = " << median << endl;
    cout << "Number of students waiting more than 10 minutes = " << above10 << " students" << endl;
    cout << "Longest Student waiting time = " << longest << endl;

    double meanIdle = 0;
    int longestIdle = 0, above5 = 0;
    for (int i = 0; i < numberOfWindows; i++)
    {
        meanIdle += windows[i].idleTime;
        if (windows[i].idleTime > longestIdle)
        {
            longestIdle = windows[i].idleTime;
        }

        if (windows[i].idleTime > 5)
        {
            above5++;
        }
    }
    meanIdle /= numberOfWindows;
    cout << "Mean Windows Idle Time = " << meanIdle << " minutes." << endl;
    cout << "Longest Window Idle Time = " << longestIdle << " minutes." << endl;
    cout << "Number of Window Idle Time longer than 5 minutes = " << above5 << " windows." << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
}

void Simulation::sortList()
{
    for (int i = 0; i <= finishedStudents.GetSize(); i++)
    {
        for (int j = 1; j <= finishedStudents.GetSize(); j++)
        {
            Student st1, st2;
            finishedStudents.GetItem(st1, j);
            finishedStudents.GetItem(st2, j - 1);
            if (st1.waitingTime < st2.waitingTime)
            {
                finishedStudents.SetItem(st1, j - 1);
                finishedStudents.SetItem(st2, j);
            }
        }
    }
}

#endif
