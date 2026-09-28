#include<stdio.h>
#include<string.h>
#define MAX_TASKS 100
struct Task{
    int id;
    char name[100];
    int deadline;
    int importance;
    int duration;
    float priority;
    int completed;
};
struct Task tasks[MAX_TASKS];
int taskcount=0;
int nextTaskID=1;
int heap[MAX_TASKS];
int heapSize=0;
//
float calculatePriority(struct Task task);
void display(){
    printf("\n====================================\n");
    printf("        SMART TASK SCHEDULER\n");
    printf("====================================\n");
    printf("1. Create New Task\n");
    printf("2. Display All Tasks\n");
    printf("3. Show Top Priority Task\n");
    printf("4. Edit Task\n");
    printf("5. Mark Task as Completed\n");
    printf("6. Delete Task\n");
    printf("7. Display Performance Metrics\n");
    printf("8. Exit\n");
    printf("------------------------------------\n");
    printf("Enter your choice: ");
}
void clearInputBuffer(){
    int ch;
    while((ch=getchar())!='\n'&&ch!=EOF){
    }
}
int findTaskById(int id){
    for(int i=0;i<taskcount;i++){
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
    return (0.50*importantScore)+(0.30*deadlineScore)+(0.20*durationScore);
}
void createTask(){
    if(taskcount>=MAX_TASKS){
        printf("\nfull! Cannot add more tasks.\n");
        return;
    }
    

struct Task newTask;
clearInputBuffer();
printf("\nEnter task name:\n");
fgets(newTask.name,sizeof(newTask.name),stdin);
newTask.name[strcspn(newTask.name,"\n")]='\0';
printf("Enter deadline(days remaining):");
scanf("%d",&newTask.deadline);
if(newTask.deadline<0){
    printf("Invalid deadline!\n");
    return;
}
printf("Enter importance(3=High,2=Medium,1=Low):");
scanf("%d", &newTask.importance);
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
newTask.priority=calculatePriority(newTask);
newTask.id=nextTaskID;
   nextTaskID++;
tasks[taskcount]=newTask;
   taskcount++;
   printf("\nTask created successfully!\n");
   printf("Task ID: %d\n",newTask.id);
   printf("Priority: %.2f\n",newTask.priority);
}
void viewTasks(){
    if(taskcount==0){
            printf("no tasks available\n");
            return;
    }
    printf("=========ALL TASKS==========\n");
    for(int i=0;i<taskcount;i++){
        printf("\nTask ID :%d\n",tasks[i].id);
        printf("Task Name :%s\n",tasks[i].name);
        printf("Deadline  :%d days\n",tasks[i].deadline);
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
        printf("Duration  :%d hours\n",tasks[i].duration);
        printf("Priority  :%.2f\n",tasks[i].priority);
        if(tasks[i].completed==0){
          printf("Status  : Pending\n");
        }
        else{
            printf("Status  : Completed\n");
        }
        printf("-----------------------\n");
        }
    }
void editTask(){
    int id;
    int position;
    if (taskcount==0){
        printf("\nNo tasks available to edit!\n");
        return;
    }
    printf("\nEnter Task ID to edit: ");
    scanf("%d", &id);
    position = findTaskById(id);
    if (position == -1){
        printf("\nTask ID not found!\n");
        return;
    }
    struct Task updatedTask = tasks[position];
    printf("\nCurrent Task: %s\n", updatedTask.name);
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
    printf("Enter new importance(3=High,2=Medium,1=Low):");
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
    updatedTask.priority = calculatePriority(updatedTask);
    tasks[position]=updatedTask;
    printf("\nTask updated successfully!\n");
    printf("Task ID: %d\n",updatedTask.id);
    printf("New Priority: %.2f\n",updatedTask.priority);
}
void finishTask(){
    int id;
    int position;
    if(taskcount==0){
        printf("\nNo task available!\n");
        return;
    }
    printf("\nEnter Task ID to complete:\n");
    scanf("%d",&id);
    position=findTaskById(id);
    if (position==-1){
        printf("\nTask ID not found!\n");
        return;
    }
    if (tasks[position].completed==1){
        printf("\nThis task is already completed!\n");
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
        printf("\nNo tasks available to delete!\n");
        return;
    }
    printf("\nEnter Task ID to delete:");
    scanf("%d",&id);
    position=findTaskById(id);
    if (position == -1)
    {
        printf("\nTask ID not found!\n");
        return;
    }

    printf("\nDeleting task: %s\n", tasks[position].name);

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
        printf("\nNo tasks available for performance analysis!\n");
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
    printf("\n========== PERFORMANCE METRICS ==========\n");
    printf("Total Tasks    :%d\n",taskcount);
    printf("Completed Tasks:%d\n",completed);
    printf("Pending Tasks  :%d\n",pending);
    printf("Completion Rate:%.2f%%\n",completionRate);
    printf("=========================================\n");
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
       printf("\nNo tasks available!\n");
       return;
    }
    buildMaxHeap();
    if(heapSize==0){
       printf("\nAll tasks are completed!\n");
       return;
    }
    int top=heap[0];
    printf("\n========== TOP PRIORITY TASK ==========\n");
    printf("Task ID   : %d\n",tasks[top].id);
    printf("Task Name : %s\n",tasks[top].name);
    printf("Priority  : %.2f\n",tasks[top].priority);
    printf("Deadline  : %d days\n",tasks[top].deadline);
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
    printf("==================================\n");
}
int main(){
    int choice;
    do{
        display();
        if(scanf("%d",&choice)!=1){
          printf("\nInvalid input! Please enter a number.\n");
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
               printf("\nExiting Smart Task Scheduler. Goodbye!\n");
                break;
          default:
              printf("\nInvalid choice! Please select 1 to 8.\n");
    }

    }while(choice!=8);
    return 0;
}

    




