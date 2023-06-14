***********************************************************************
Breakdown of how my code satisfies each of the Project Requirements:
***********************************************************************
* requirement (a.) is satisfied in the phonecall thread function where I use the binary semaphore only for when I am dealing with the connected variable.

* requirement (b.) is satisfied in the phonecall thread function with the call of sem_wait and sem_post with the operators semaphore.

* requirement (c.) is satisfied in the main function where the binary semaphore connected_lock and the counting semaphore is initialized with the use of the sem_init function. These are also correctly destroyed with the use of a helper function clean() that calls sem_destroy for the two semaphores.

* requirement (d.) is satisfied with the implementation of the phonecall thread function.

* requirement (e.) is satisfied with the implementation of the wait_func thread function.

* requirement (f.) is satisfied with the implementation of the phonecall thread function making use of the pthread_detach function and the main thread making use of the pthread_join with the wait_func thread.

* requirement (g.) is satisfied with the global variable next_id being initalized to 0 with the other global variables given at the top of worldcup.c and the phonecall thread function having a local variable id being initialized to next_id. The next_id is incremented at the bottom of the phonecall thread function.

* requirement (h.) is satisfied with the use of a while loop in the phonecall thread function that checks if the line is busy or not and updates connected accordingly.

* requirement (i.) is satisfied in the phonecall thread function with the format of the printed messages being similar to the ones shown in the Synchronization section of the Project 5 goodle doc.

* requirement (j.) is satisfied in the phonecall thread function and the main as all the given static global variables are utilized for their purposes.

* requirement (k.) is satisfied in the main as there is an if condition that checks for invalid command line argument in which case a message is printed notifying the user about invalid input along with the call to exit function to terminate the process.

* requirement (l.) is satisfied as I received no errors when testing with the verifier.cpp. One test example:
abhinitgiri@elnux2:~/Projects/Project5$ ./worldcup 3 | ./verifier > output.txt
Attempting to connect format: Thread \d+ is attempting to connect to the conference center ...
Connects to an available line format: Thread \d+ connects to an available line, call ringing ...
Speaking to operator format: Thread \d+ is speaking to an operator.
Proposed a question format: Thread \d+ has proposed a question for the USA soccer team! The operator has left ...
Verifier finished!

* requirement (m.) is satisfied as the verifier.cpp showed no errors when running with different times given in the Testing section of the Project 5 google doc.

* requirement (n.) is satisfied in the main where a thread_val variable is used to store the return value of the call to pthread functions along with an if statement that checks for invalid return values for those functions in which case an appropriate message is printed along with the call to exit to terminate the process.

* requirement (o.) is satisfied as the code compiles with no mentions of seg faults.

****************************************************************************
Breakdown of how my code satisfies each of the Design and Implementation:
****************************************************************************
* requirement (a.) is satisfied as the variables and helper functions I have created have a comment explaining its purpose and where I am using it in the program.

* requirement (b.) is satisfied as I use all given global variables from the Project 5 google doc along with the next_id variable that was asked to be created.

* requirement (c.) is satisfied as I explain my purpose in all instances where I use any control flow statements in worldcup.c.

* requirement (d.) is satisfied as I have an explanation for what I have done in the algorithm for the phonecall thread function as it follows the guideline for the creation for the creation of the algorithm given in the Synchronization section of the Project 5 google doc.

***************************************************************
Breakdown of how my code satisfies each of the Coding Style:
***************************************************************
* requirement (a.) is satisfied as I am consistent with my style throughout the code written in worldcup..

* requirement (b.) is satisfied as there is no identifiable inconsistent indenting and spacing throughout the program.

* requirement (c.) is satisfied as all the variable names have a relation to the purpose and requirement for it's usage in the project.

***************************************************************
Breakdown of how my code satisfies each of the Comments:
***************************************************************
* requirement (a.) is satisfied as all the comments written explain the piece of code that the comment is near.

* requirement (b.) is satisfied as all the comments are redable and are written consisely to give the reader the main idea of what the code is doing.

* requirement (c.) is satisfied as all the variable names are explained for their purpose and use in the program.