# Smart Task Scheduler

A menu-driven C program that manages tasks and ranks them by priority using a weighted formula and a Max-Heap. The project also includes an AI-based priority classification module using k-Nearest Neighbors (k-NN).

## Features

- Create, edit, delete and view tasks
- Automatic priority calculation
- AI-based priority classification using k-NN
- Uses deadline, importance and estimated duration for AI classification
- AI priority classes: Low, Medium, High and Critical
- Show the top-priority pending task using a Max-Heap
- Mark tasks as completed
- Performance metrics (total, completed, pending, completion rate)

## AI Priority Recommendation

The AI module uses k-Nearest Neighbors (k-NN) to classify tasks into four priority classes:

- Low
- Medium
- High
- Critical

### AI Input Features

- Deadline (days remaining)
- Importance (1 = Low, 2 = Medium, 3 = High)
- Estimated duration (hours)

The AI compares the task with predefined training examples and predicts its priority class.

## Priority Formula

Priority = 0.5 × Importance Score + 0.3 × Deadline Score + 0.2 × Duration Score + AI Adjustment

- Importance: High = 100, Medium = 60, Low = 30
- Deadline score = 100 / (days remaining + 1)
- Duration score = 100 / hours (maximum 100)
- AI Adjustment:
  - Low = +0
  - Medium = +5
  - High = +10
  - Critical = +15

## Data Structures Used

- Structure (`struct Task`) for task details
- Array for storing tasks
- Max-Heap for finding the highest-priority task
- Priority Queue concept

## Algorithms Used

- k-Nearest Neighbors (k-NN)
- Max-Heap / Heapify
- Priority calculation
- Linear search

## How It Works

1. User creates a task by entering its name, deadline, importance and estimated duration.
2. The k-NN module classifies the task priority.
3. The AI classification is used to adjust the final priority score.
4. Pending tasks are organized using a Max-Heap.
5. The highest-priority task can be displayed.
6. Tasks can be edited, completed or deleted.
7. Performance metrics show task completion statistics.

## Sample Menu

1. Create New Task
2. Display All Tasks
3. Show Top Priority Task
4. Edit Task
5. Mark Task as Completed
6. Delete Task
7. Display Performance Metrics
8. Exit
