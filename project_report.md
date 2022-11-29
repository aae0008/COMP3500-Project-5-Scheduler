# Project Report

## 7.1. Solution Description

1. How did you separate scheduling mechanism from scheduling policies?
    * Each scheduling policy is implemented in a seperate function. When the simulation
runs, the scheduling mechanism calls the function corresponding to the scheduling 
policy that the user provides.

2. How did implement the three scheduling algorithms?
    * I learned how to create the basic structure of each scheduling policy from the lecture
material in class. By incrementally developing and testing the scheduling policies 
with the VSCode debugger, I managed to successfully implement each algorithm.
The first policy I implemented was the First Come First Serve policy. It works
by choosing the first process among all of the processes that have arrived.
When the process is completed, it is added to an array of finished processes.
The second policy I implemented was the Shortest Remaining Time First policy.
In this algorithm, the process with the smallest remaining time left is chosen
by scanning through an array of processes that have already arrived. When the
process finishes, it is added to an array of finished processes. The final
policy I implemented was the Round Robin policy. To implement this, the algorithm
keeps track of a variable indicating how many steps a process has left before 
the scheduler moves onto the next process.

3. How did you calculate waiting times?
    * The waiting time of a process equals its finish time minus its arrival time
minus the process's burst time, ie. waiting_time = finished_time - arrival_time - burst_time

4. How did you calculate response times? 
    * The response time of a process equals its start time minus its arrival time, ie.
response_time = start_time - arrival time

5. How did you calculate turnaround times?
    * The turnaround time of a process equals its finish time minus its arrival time, ie.
turnaround_time = finish_time - arrival_time

6. How did you implement the command-line parser?
    * I used the sample code provided in the instructions as a baseline for my 
command-line parser. The command-line parser is implemented inside of my main
function. The main function makes sure that there are between 2 and 3 command-line
arguments, it confirms that the file can be read, and it confirms that a valid
scheduling policy got chosen.

## 7.2 Generality and Error Checking

1. How general is your solution?
    * Generality can be measured in a variety of ways. This response will analyze
    3 different forms of generality -- 1) generality in terms of the scheduling policies,
    2) generality in terms of the number of tasks, and 3) generality in terms of 
    simulation speed.
        1) Scheduling policies: The program is moderately general when analyzed from
    a scheduling policy perspective. The scheduling mechanism is loosely coupled 
    to the scheduling policies because each policy is implemented in a seperate
    function. However, there are hard-coded references to each of the 3 scheduling 
    policies. These hard-coded references are designed to 1) check that an 
    appropriate policy has been selected, and 2) determine the correct function 
    to call for the scheduling policy. The precense of these references makes
    the program less general because there is more involvement on the developer's side
    if a current policy is removed, or if a new policy is added.
        2) Number of tasks: The program is not very general from a number of tasks
    perspective. Currently, the maximum number of tasks is 32. Any additional tasks
    after the 32nd task will be ignored. This behavior can be changed by the
    developer, however, if it is determined that the system has enough memory
    to reasonably accommodate more than 32 tasks.
        3) Simulation speed: The program can be made highly general from a simulation
    speed perspective. Currently, only the developer can change the speed, but
    if it was made as an command-line argument, the user would be able to set the
    speed with very few restrictions.

2. How easy would it be to add a new scheduling policy into your scheduler?
    * Adding a new policy is straightforward. The developer would need to 1)
    implement the policy in a function. 2) Add a branch in the if statement of 
    the coordinator function allowing the policy to be invoked if it is selected,
    and 3) Add a clause for the name of the policy in the portion of code in
    the main function that checks to see if the policy name passed in corresponds
    to a valid policy.

3. Does your program offer input error checking?
    * Yes. There are three types of input checking: 1) a check to make sure
    the task file can be read, 2) a check to make sure that the provided 
    scheduling policy is appropriate, and 3) a check to make sure that a
    quantum value was passed in if the scheduling policy was Round Robin.

## 7.3 Miscellaneous factors

1. Is your code elegant?
    * Among many things, elegant code uses meaningful, descriptive variable names, 
    uses uninitialized variables sparingly, avoids large, complex functions, 
    and includes comments about the programmer's intentions. Overall my code is
    elegant. I use meaningful variable names throughout my code. Two instances
    are when I use `policy_name` to represent the policy passed in and 
    `processes_completed` to represent the number of processes that a policy 
    completes in one step. All of my code has inline and block comments. And, 
    I don't have functions that are unecessarily large.

2. How innovative is your solution? Did you try any ideas not suggested here?
    * My solution is reasonably innovative. The way I calculated the statistics
    (avg response time, avg turnaround time, avg waiting time, and cpu usage)
    involves O(n) time complexity. I made heavy use of pointers (pass by reference)
    instead of passing by value. I also learned how to create launch files in
    VSCode to debug C programs. Additionally, my code is stored in a git
    repository.

3. Did you document all outside sources?
    * Yes. My solution made use of Dr. Qin's source code for parsing command
    line arguments and reading tasks from the task file. I made a note at the
    top of the files that include his source code giving him credit.