# Smart Task Scheduler

A menu-driven C program that manages tasks and ranks them by priority using a weighted formula and a max-heap.

## Features
- Create, edit, delete and view tasks
- Automatic priority calculation
- Show the top-priority pending task (max-heap)
- Mark tasks as completed
- Performance metrics (total, completed, pending, completion rate)

## Priority Formula
Priority = 0.5 × Importance + 0.3 × Deadline + 0.2 × Duration

- Importance: High = 100, Medium = 60, Low = 30
- Deadline score = 100 / (days remaining + 1)
- Duration score = 100 / hours (max 100)

## Data Structures Used
- Structure (`struct Task`) for task details
- Array for storing tasks
- Max-Heap for finding the highest-priority task

## Sample Menu
1. Create New Task
2. Display All Tasks
3. Show Top Priority Task
4. Edit Task
5. Mark Task as Completed
6. Delete Task
7. Display Performance Metrics
8. Exit
