#include <stdio.h>
void fcfs(int processes[], int n, int burst_time[]) {
int waiting_time[n], turnaround_time[n], total_waiting_time = 0, 
total_turnaround_time = 0;
waiting_time[0] = 0; // Waiting time for first process is 0
// Calculating waiting time for each process
for (int i = 1; i < n; i++) {
waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
total_waiting_time += waiting_time[i];
}
// Calculating turnaround time for each process
for (int i = 0; i < n; i++) {
turnaround_time[i] = burst_time[i] + waiting_time[i];
total_turnaround_time += turnaround_time[i];
}
printf("First-Come, First-Served (FCFS) Scheduling Algorithm\n");
printf("--------------------------------------------------\n");
printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
// Printing process details
for (int i = 0; i < n; i++) {
printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], 
waiting_time[i],
turnaround_time[i]);
}
printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
printf("Average Turnaround Time: %.2f\n", 
(float)total_turnaround_time / n);
printf("\n");
}
int main() {
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
int processes[n], burst_time[n];
printf("Enter the burst time for each process:\n");
for (int i = 0; i < n; i++) {
printf("Process %d: ", i + 1);
scanf("%d", &burst_time[i]);
processes[i] = i + 1;
}
printf("\n");
fcfs(processes, n, burst_time);
return 0;
