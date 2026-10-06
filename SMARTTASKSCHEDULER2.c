#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX_TASKS 100
struct Task{
    int id;
    char name[100];
    int deadline;
    int importance;
    int duration;
    float priority;
    int completed;
    int aiClass;
};
struct TrainingTask{
    int deadline;
    int importance;
    int duration;
    int priorityClass;
};
struct TrainingTask trainingData[]={ {1,3,1,4},
{1,3,2,4},{2,3,2,4},{2,3,4,3},{3,3,4,3},
{3,2,3,3},{4,3,5,3},{4,2,3,2},{5,2,4,2},{6,2,3,2},
{7,2,5,2},{7,1,3,1},{8,1,4,1},{9,1,2,1},{10,1,3,1}
};
float calculateDistance(int deadline1, int importance1, int duration1,
                        int deadline2, int importance2, int duration2){
  float distance;
  distance = sqrt(
  (deadline1-deadline2)*(deadline1-deadline2)+
   (importance1-importance2)*(importance1-importance2)+
    (duration1-duration2)*(duration1-duration2)
    );
  return distance;
}
int aiPriorityClassification(struct Task task){
  int k=3;
  int n=sizeof(trainingData)/sizeof(trainingData[0]);
  float distances[20];
  int classes[20];
  int i, j;
  for(i=0;i<n;i++){
   distances[i]=calculateDistance(
    task.deadline,
    task.importance,
    task.duration,
    trainingData[i].deadline,trainingData[i].importance,
    trainingData[i].duration);
  classes[i]=trainingData[i].priorityClass;
}
for(i=0;i<n-1;i++){
 for(j=i+1;j<n;j++){
     if(distances[i]>distances[j]){
        float tempDistance=distances[i];
        distances[i]=distances[j];
        distances[j]=tempDistance;
        int tempClass=classes[i];
        classes[i]=classes[j];
        classes[j]=tempClass;
      }
    }
}
int count[5]={0};
 for(i=0;i<k;i++){
    count[classes[i]]++;
 }
int bestClass=1;
 for(i=2;i<=4;i++){
    if(count[i]>count[bestClass]){
     bestClass=i;
    }
 }
return bestClass;
}
struct Task tasks[MAX_TASKS];
int taskcount=0;
int nextTaskID=1;
int heap[MAX_TASKS];
int heapSize=0;
float calculatePriority(struct Task task);
void display(){
  printf("====================================\n");
  printf("        SMART TASK SCHEDULER\n");
  printf("====================================\n");
  printf("1. Create New Task\n");
  printf("2. Display All Tasks\n");
  printf("3. Show Top Priority Task\n");
  printf("4. Edit Task\n");
  printf("5. Mark Task as Completed\n");
  printf("6. Delete Task\n");
  printf("7. Display Performance Metrics\n");
  printf("8. AI priority Recommendation\n");
  printf("9. Exit\n");
  printf("------------------------------------\n");
  printf("Enter your choice: ");
}
void clearInputBuffer(){
 int ch;
while((ch=getchar())!='\n'&&ch!=EOF){
}
}
int findTaskById(int id){
 for(int i=0;i<taskcount;i++) {
    if(tasks[i].id==id){
        return i;
    }
 }
 return -1;
}
float calculatePriority(struct Task task){
 float importantScore;
 float deadlineScore;
 float durationScore;
 if(task.importance==3){
    importantScore=100.0;
}
else if(task.importance==2){
    importantScore=60.0;
}
else{
    importantScore=30.0;
}
 deadlineScore=100.0/(task.deadline+1);
 durationScore=100.0/task.duration;
  if(durationScore>100.0){
    durationScore=100.0;
  }
  float basePriority;
    basePriority=(0.50*importantScore)
        +(0.30*deadlineScore)
        +(0.20*durationScore);
if(task.aiClass==1){
  basePriority+=0;
 }
else if(task.aiClass==2){
  basePriority+=5;
 }
else if(task.aiClass==3){
   basePriority+=10;
 }
else if(task.aiClass==4){
  basePriority+=15;
 }
return basePriority;
}
void createTask(){
  if(taskcount>=MAX_TASKS){
    printf(" full! Cannot add more tasks.\n");
    return;
  }
struct Task newTask;
clearInputBuffer();
printf(" Enter task name:\n");
fgets(newTask.name,sizeof(newTask.name),stdin);
newTask.name[strcspn(newTask.name,"\n")]='\0';
printf("Enter deadline(days remaining):");
scanf("%d",&newTask.deadline);
if(newTask.deadline<0){
 printf(" Invalid deadline\n");
 return;
}
printf("Enter importance(high,mid,low=3,2,1 ):");
scanf("%d",&newTask.importance);
if(newTask.importance<1||newTask.importance>3){
 printf("Invalid importance!\n");
 return;
}
printf("Enter estimated duration(hours):");
scanf("%d",&newTask.duration);
if(newTask.duration<=0){
 printf("Invalid duration!\n");
 return;
}
newTask.completed=0;
newTask.aiClass=aiPriorityClassification(newTask);
newTask.priority=calculatePriority(newTask);
newTask.id=nextTaskID;
 nextTaskID++;
tasks[taskcount]=newTask;
   taskcount++;
printf(" Task created successfully\n"); 
printf("Task ID:%d\n",newTask.id); 
printf("Priority:%.2f\n",newTask.priority);
printf("AI Recommendation: ");
switch(newTask.aiClass){
 case 1:
   printf("LOW\n");
    break;
 case 2:
   printf("MEDIUM\n");
    break;
 case 3:
   printf("HIGH\n");
    break;
 case 4:
    printf("CRITICAL\n");
     break;
}
}
void viewTasks(){
 if(taskcount==0){
  printf("no tasks available\n");
    return;
 }
 printf("-------------ALL TASKS------------------\n");
  for(int i=0;i<taskcount;i++){
    printf("Task ID:%d\n",tasks[i].id);
    printf("Task Name:%s\n",tasks[i].name);
    printf("Deadline :%d days\n",tasks[i].deadline);
    printf("Importance:");
 switch(tasks[i].importance){
  case 1:
    printf("Low\n");
    break;
  case 2:
    printf("Medium\n");
    break;
  case 3:
    printf("High\n");
    break;
 }
 printf("Duration:%d hours\n",tasks[i].duration);
 printf("Priority:%.2f\n",tasks[i].priority);
 printf("AI Recommendation: ");
switch(tasks[i].aiClass){
  case 1:
    printf("LOW\n");
     break;
  case 2:
    printf("MEDIUM\n");
     break;
  case 3:
    printf("HIGH\n");
     break;
  case 4:
    printf("CRITICAL\n");
     break;
}
 if(tasks[i].completed==0){
  printf("Status : Pending\n");
 }
 else{
 printf("Status : Completed\n");
 }
  }
}
void editTask(){
    int id;
    int position;
    if (taskcount==0){
        printf("No tasks available to edit!\n");
        return;
    }
    printf("Enter Task ID to edit: ");
    scanf("%d", &id);
    position = findTaskById(id);
    if (position == -1){
        printf("\nTask ID not found!\n");
        return;
    }
    struct Task updatedTask = tasks[position];
    printf("Current Task: %s\n", updatedTask.name);
    clearInputBuffer();
    printf("Enter new task name:");
    fgets(updatedTask.name,sizeof(updatedTask.name),stdin);
    updatedTask.name[strcspn(updatedTask.name,"\n")] ='\0';
    printf("Enter new deadline (days remaining):");
    scanf("%d",&updatedTask.deadline);
    if(updatedTask.deadline<0){
        printf("Invalid deadline!\n");
        return;
    }
    printf("Enter new importance:");
    scanf("%d",&updatedTask.importance);
    if (updatedTask.importance<1||updatedTask.importance>3){
        printf("Invalid importance!\n");
        return;
    }
    printf("Enter new duration(hours):");
    scanf("%d", &updatedTask.duration);
    if (updatedTask.duration<=0){
        printf("Invalid duration!\n");
        return;
    }
   updatedTask.aiClass=aiPriorityClassification(updatedTask);
updatedTask.priority=calculatePriority(updatedTask);
    tasks[position]=updatedTask;
    printf("Task updated successfully!\n");
    printf("Task ID: %d\n",updatedTask.id);
    printf("New Priority: %.2f\n",updatedTask.priority);
    printf("AI Recommendation: ");
switch(updatedTask.aiClass){
  case 1:
     printf("LOW\n");
    break;
  case 2:
     printf("MEDIUM\n");
      break;
  case 3:
     printf("HIGH\n");
      break;
  case 4:
      printf("CRITICAL\n");
       break;
}
}
void finishTask(){
    int id;
    int position;
    if(taskcount==0){
        printf("No task available!\n");
        return;
    }
    printf("Enter Task ID:\n");
    scanf("%d",&id);
    position=findTaskById(id);
    if (position==-1){
        printf("Task ID not found!\n");
        return;
    }
    if (tasks[position].completed==1){
        printf("This task is already completed!\n");
        return;
    }
    tasks[position].completed=1;
    printf("\nTask marked as completed successfully!\n");
    printf("Task:%s\n",tasks[position].name);
}
void deleteTask(){
    int id;
    int position;
    if(taskcount==0){
        printf("No tasks to delete!\n");
        return;
    }
    printf("Enter Task ID to delete:");
    scanf("%d",&id);
    position=findTaskById(id);
    if (position == -1)
    {
        printf("Task ID not found!\n");
        return;
    }

    printf("Deleting task: %s\n", tasks[position].name);

    for(int i=position;i<taskcount-1;i++){
     tasks[i]=tasks[i+1];
    }
    taskcount--;
    printf("Task deleted successfully!\n");
}
void displayPerformanceMetrics(){
    int completed=0;
    int pending=0;
    if(taskcount==0){
        printf("No tasks available for performance analysis!\n");
        return;
    }
    for(int i=0;i<taskcount;i++){
        if(tasks[i].completed==1){
        completed++;
        }
        else{
        pending++;
        }
    }
    float completionRate=((float)completed/taskcount)*100.0;
 printf("========== PERFORMANCE METRICS ==========\n");
 printf("Total Tasks    :%d\n",taskcount);
 printf("Completed Tasks:%d\n",completed);
 printf("Pending Tasks  :%d\n",pending);
 printf("Completion Rate:%.2f%%\n",completionRate);
 printf("            -------------\n");
}
void swap(int *a,int *b){
 int temp=*a;
 *a=*b;
 *b=temp;
}
void heapifDown(int index){
    int largest=index;
    int leftChild=2*index+1;
    int rightChild=2*index+2;
    if (leftChild<heapSize && tasks[heap[leftChild]].priority>tasks[heap[largest]].priority){
    largest=leftChild;
    }
    if(rightChild<heapSize && tasks[heap[rightChild]].priority>tasks[heap[largest]].priority){
    largest=rightChild;
    }
    if (largest != index){
     swap(&heap[index], &heap[largest]);
     heapifDown(largest);
    }
}
void buildMaxHeap(){
    heapSize=0;
    for(int i=0;i<taskcount;i++){
        if(tasks[i].completed==0){
          heap[heapSize]=i;
          heapSize++;
        }
    }
    for(int i=heapSize/2-1;i>=0;i--){
       heapifDown(i);
    }
}
void showTopPriorityTask(){
    if (taskcount==0){
       printf("No tasks available!\n");
       return;
    }
    buildMaxHeap();
    if(heapSize==0){
       printf("All tasks are completed!\n");
       return;
    }
    int top=heap[0];
    printf("---------------- TOP PRIORITY TASK ----------------\n");
    printf("Task ID  : %d\n",tasks[top]. id);
    printf("Task Name: %s\n",tasks[top].name);
    printf("Priority : %.2f\n",tasks[top].priority);
    printf("AI Recommendation: ");
switch(tasks[top].aiClass){
  case 1:
    printf("LOW\n");
     break;
  case 2:
    printf("MEDIUM\n");
     break;
  case 3:
    printf("HIGH\n");
    break;
  case 4:
    printf("CRITICAL\n");
     break;
}
    printf("Deadline  : %d days\n",tasks[top]. deadline);
    printf("Importance:");
    switch(tasks[top].importance){
        case 1:
          printf("Low\n");
          break;
        case 2:
          printf("Medium\n");
          break; 
        case 3:
          printf("High\n");
          break; 
    }
    printf("Duration  :%d hours\n",tasks[top].duration);
}
void showAIRecommendation(){
  int id;
  int position;
 if(taskcount==0){
     printf("No tasks available!..\n");
     return;
  }
 printf("Enter Task ID for AI recommendation: ");
  scanf("%d",&id);
  position=findTaskById(id);
    if(position==-1){
      printf("Task ID not found!\n");
       return;
 }
    printf("----AI PRIORITY RECOMMENDATION ------\n");
    printf("Task Name :%s \n",tasks[position]. name);
    printf("Deadline  :%d  days\n",tasks[position]. deadline);
    printf("Importance:%d\n",tasks[position]. importance);
    printf("Duration  :%d  hours\n",tasks[position]. duration);
    switch(tasks[position].aiClass){
    case 1:
     printf("LOW\n");
      break;
    case 2:
     printf("MEDIUM\n");
      break;
    case 3:
     printf("HIGH\n");
      break;
    case 4:
     printf("CRITICAL\n");
      break;
    }
    printf("Priority Score: %.2f\n", tasks[position]. priority);
    explainAIRecommendation(tasks[position]);
void explainAIRecommendation(struct Task task){
   printf("\nAI Analysis:\n");
  if(task.deadline<=2){
    printf("-Deadline is very close.\n");
  }
  else if(task.deadline<=5){
   printf("-Deadline is approaching.\n");
  }
  else{
     printf("-Deadline has sufficient time remaining.\n");
    }
  if(task.importance==3){
     printf("-Task has high importance.\n");
    }
  else if(task.importance==2){
     printf("-Task has medium importance.\n");
    }
  else{
     printf("-Task has low importance.\n");
    }
    if(task.duration<=2){
     printf("-Task has a short estimated duration.\n");
    }
    else if(task.duration<=5){
     printf("-Task has a moderate estimated duration.\n");
    }
    else{
     printf("-Task requires a longer duration.\n");
    }
}
int main(){
    int choice;
    do{
     display();
    if(scanf("%d",&choice)!=1){
     printf(" Invalid input!enter a number.\n");
      clearInputBuffer();
        continue;
    }
 switch(choice){
 case 1:
   createTask();
    break;
    case 2:
     viewTasks();
     break;
    case 3:
     showTopPriorityTask();
     break;
    case 4:
     editTask();
     break;
    case 5:
     finishTask();
     break;
    case 6:
     deleteTask();
     break;
    case 7:
     displayPerformanceMetrics();
     break;
    case 8:
     showAIRecommendation();
     break; 
    case 9:
     printf("Exiting Smart Task Scheduler. Goodbye!\n");
     break;
   default:
     printf("Invalid choice!enter between 1 to 9.\n");
  }
 } while(choice!=9);
return 0;
}

