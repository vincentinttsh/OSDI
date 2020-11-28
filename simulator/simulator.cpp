#include <stdio.h>
#include <algorithm>

struct Process{
    int no; //pid of process
    int arrival_time;
    int cpu_burst;
    int priority;
    int completed_time;
    int left_time;
};

// same arrival time, compare priority
// same priority, compare cpu burst
bool compare(struct Process a, struct Process b){
    if (a.arrival_time != b.arrival_time)
        return a.arrival_time < b.arrival_time;
    if (a.priority != b.priority)
        return a.priority > b.priority;
    return a.cpu_burst < b.cpu_burst;
}


void FCFS(struct Process* process, int len){
    int clock = 0, finishProcess = 0, nowProcess = -1, startClock = 0;
    double totalWait = 0;
    printf("============process scheduling by FCFS============\n");
    while(len > finishProcess){
        if(nowProcess != -1 && process[nowProcess].left_time == 0 ){
            process[nowProcess].completed_time = clock;
            printf("clock %d: P%d", startClock, process[nowProcess].no);
            printf(", arrival time= %d", process[nowProcess].arrival_time);
            printf(", cpu burst= %d", process[nowProcess].cpu_burst);
            printf(", priority= %d", process[nowProcess].priority);
            printf(", completed_time= %d\n", process[nowProcess].completed_time);
            double a = process[nowProcess].completed_time;
            totalWait += a - process[nowProcess].arrival_time - process[nowProcess].cpu_burst;
            ++finishProcess;
        }
        if(nowProcess == -1 && clock >= process[0].arrival_time){
            startClock = clock;
            ++nowProcess;
        }
        if(nowProcess != -1 && process[nowProcess].left_time <= 0)
        if(len > finishProcess && process[nowProcess+1].arrival_time <= clock){
            startClock = clock;
            ++nowProcess;
        }
        ++clock;
        if(nowProcess != -1)
            --process[nowProcess].left_time;
    }
    printf("The average waiting time= %f\n", totalWait / len);
}

void SJF(struct Process* process, int len){
    int clock = 0, finishProcess = 0, nowProcess = -1, startClock = 0;
    double totalWait = 0;
    printf("============process scheduling by SJF============\n");
    while(len > finishProcess){
        if(nowProcess != -1 && process[nowProcess].left_time == 0){
            process[nowProcess].completed_time = clock;
            printf("clock %d: P%d", startClock, process[nowProcess].no);
            printf(", arrival time= %d", process[nowProcess].arrival_time);
            printf(", cpu burst= %d", process[nowProcess].cpu_burst);
            printf(", priority= %d", process[nowProcess].priority);
            printf(", completed_time= %d\n", process[nowProcess].completed_time);
            double a = process[nowProcess].completed_time;
            totalWait += a - process[nowProcess].arrival_time - process[nowProcess].cpu_burst;
            ++finishProcess;
        }
        if(nowProcess == -1 && clock >= process[0].arrival_time){
            startClock = clock;
            nowProcess = 0;
            for (int i = 1; i < len; i++){
                if(process[i].arrival_time > clock)
                    break;
                if(process[i].cpu_burst < process[nowProcess].cpu_burst)
                    nowProcess = i;
            }
        }
        if(nowProcess != -1 && process[nowProcess].left_time <= 0){
            startClock = clock;
            if(len > finishProcess){
                int nowChoice = 2147483647;
                for (int i = 0; i < len; i++){
                    if(process[i].left_time > 0)
                    if(process[i].cpu_burst < nowChoice && process[i].arrival_time <= clock){
                    nowProcess = i;
                    nowChoice = process[i].cpu_burst;
                    }
                }
            }
        }
        ++clock;
        if(nowProcess != -1)
            --process[nowProcess].left_time;
    }
    printf("The average waiting time= %f\n", totalWait / len);
}

void SRJF(struct Process* process, int len){
    int clock = 0, finishProcess = 0, nowProcess = -1;
    double totalWait = 0;
    printf("============process scheduling by SRJF============\n");
    while(len > finishProcess){
        if(nowProcess != -1 && process[nowProcess].left_time == 0 ){
            process[nowProcess].completed_time = clock;
            printf("clock %d: P%d out", clock, process[nowProcess].no);
            printf(", arrival time= %d", process[nowProcess].arrival_time);
            printf(", cpu burst= %d", process[nowProcess].cpu_burst);
            printf(", priority= %d", process[nowProcess].priority);
            printf(", completed_time= %d\n", process[nowProcess].completed_time);
            double a = process[nowProcess].completed_time;
            totalWait += a - process[nowProcess].arrival_time - process[nowProcess].cpu_burst;
            ++finishProcess;
        }
        if(nowProcess != -1 && process[nowProcess].left_time <= 0 ){
            if(len > finishProcess){
                int nowChoice = 2147483647;
                for (int i = 0; i < len; i++){
                    if(process[i].left_time > 0)
                    if(process[i].left_time < nowChoice && process[i].arrival_time <= clock){
                        nowProcess = i;
                        nowChoice = process[i].left_time;
                    }
                }
                printf("clock %d: P%d in ", clock, process[nowProcess].no);
                printf(", arrival time= %d", process[nowProcess].arrival_time);
                printf(", cpu burst= %d", process[nowProcess].cpu_burst);
                printf(", priority= %d", process[nowProcess].priority);
                printf(", left_time= %d\n", process[nowProcess].left_time);
            }
        }
        if(nowProcess == -1 && clock >= process[0].arrival_time){
            nowProcess = 0;
            for (int i = 1; i < len; i++){
                if(process[i].cpu_burst < process[nowProcess].cpu_burst)
                if(clock >= process[i].arrival_time){
                    nowProcess = i;
                }
            }
        }
        int nextProcess = nowProcess;
        if(nextProcess != -1){
            if(len > finishProcess){
                int nowChoice = process[nowProcess].left_time;
                for (int i = 0; i < len; i++){
                    if(process[i].left_time > 0)
                    if(process[i].left_time < nowChoice && process[i].arrival_time <= clock){
                        nextProcess = i;
                        nowChoice = process[i].left_time;
                    }
                }
            }
        }
        if(nextProcess != nowProcess){
            printf("clock %d: P%d out", clock, process[nowProcess].no);
            printf(", arrival time= %d", process[nowProcess].arrival_time);
            printf(", cpu burst= %d", process[nowProcess].cpu_burst);
            printf(", priority= %d", process[nowProcess].priority);
            printf(", left_time= %d\n", process[nowProcess].left_time);
            nowProcess = nextProcess;
            printf("clock %d: P%d in ", clock, process[nowProcess].no);
            printf(", arrival time= %d", process[nowProcess].arrival_time);
            printf(", cpu burst= %d", process[nowProcess].cpu_burst);
            printf(", priority= %d", process[nowProcess].priority);
            printf(", left_time= %d\n", process[nowProcess].left_time);
        }
        ++clock;
        if(nowProcess != -1)
            --process[nowProcess].left_time;
    }
    printf("The average waiting time= %f\n", totalWait / len);
}

int main(int argc, char* argv[]){
    struct Process process[1000];
    struct Process data[1000];
    int no, a, cpu_burst, priority;
    int len=0;
    while(scanf("%d %d %d %d", &no, &a, &cpu_burst, &priority) != EOF){
        process[len].no = no;
        process[len].arrival_time = a;
        process[len].cpu_burst = cpu_burst;
        process[len].priority = priority;
        process[len].left_time = cpu_burst;
        len++;
    }
    std::sort(process, process+len, compare);
    printf("Input workload (sort by arrival time\n");
    for(int i = 0; i < len; i++){
        printf("clock 0: P%d, arrival time= %d", process[i].no, process[i].arrival_time);
        printf(", cpu burst= %d, priority= %d\n", process[i].cpu_burst, process[i].priority);
    }
    std::copy(process, process + len, data);
    FCFS(data, len);
    std::copy(process, process + len, data);
    SJF(data, len);
    std::copy(process, process + len, data);
    SRJF(data, len);
}