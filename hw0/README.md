
# Homework 0: Executables #

### This is an individual assignment
### FCOM: DOES **NOT** APPLY
### Points: 5% of your final grade
### **Due: 5 August 2019, 11:59 PM**

## 1 Git

As stated [before](../README.md), to do this and all subsequent assignments, you need to have a GitHub account. Therefore, if you have not done so already, go to https://github.com/join, create an account and follow the instructions given [here](../README.md).
To start working on this assignment, open a terminal, clone this repository into your local directory, and change to the directory "hw-2019/hw0" to access the files for this assignment:
```
git clone https://github.com/WITS-COMS3010/hw-2019.git
cd hw-2019/hw0
```

Update the url of 'origin' to point to your private repository (replace student_number) and push:
```
git remote set-url origin https://github.com/WITS-COMS3010/student_number.git
git push -u origin master
```

If you open the url "https:&#8203;//github.com/WITS-COMS3010/student_number" in your web browser you should now see a copy of this entire repository.

<br />

## 2 **Your assignment**

For this homework, you will be brushing up on your C skills and exploring how a compiled executable is structured.  
Part of this course requires you to solve problems independently. You are encouraged to consult the resources we link to and search the internet for any specific problems you encounter; Googling is a skill. Nevertheless, the teaching assistants are available should you get stuck.

### 2.1 make
You probably used *gcc* to compile your programs from the command line in first year, but this grows tedious and complicated as the number of files you need to compile increases. Makefiles simplify the compilation process into a simple call to ```make```. If this is new to you, consult one of the following tutorials or documentation: [Intro to Make](http://matt.might.net/articles/intro-to-make/), [MakefileTutorial.com](https://makefiletutorial.com/), [GNU Make Documentation](https://www.gnu.org/software/make/manual/html_node/Introduction.html#Introduction).

First, create a file called "Makefile" in your hw0 directory and edit it. We have provided basic code below that compiles hello_world.c:
```make
all: hello_world

hello_world: hello_world.c
	gcc hello_world.c -Wall -Wextra -pedantic -o hello_world
    
clean:
	rm -f hello_world
``` 
Note that the indentation must be a tab, **not** spaces! After saving your Makefile, executing `make` from the terminal should produce the "hello_world" executable. Calling `make clean` should remove the executable.

- **Complete the Makefile**
  - It should compile hello_world.c, arguments.c, main.c, wc.c, and map.c.
  - You also need to write a target clean (to be invoked by `make clean`) to remove your executables.
<br />
<br />
  
### 2.2 Saving with Git
After creating the Makefile, run `git status`. You should see something similar to the following:
```diff
Untracked files:
  (use "git add <file>..." to include in what will be committed)

-       Makefile
```
This indicates that Makefile is new and untracked by git. Execute `git add Makefile` then run `git status` again:
```diff
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

+       new file:   Makefile
```
Notice the file is now green, this means it is staged for the next commit.  
Run:
```
git commit -m "Added Makefile"
git push origin master
```
Make sure you changed the url of 'origin' in section 1, otherwise the push will fail. If you open your private repository in a web browser and open hw0, you should see Makefile is now uploaded.
<br />
<br />

### 2.3 Hello, World
There are several differences between C and C++, most notably in string handling and IO. For example:
```C
int val = 3010;
char word[] = "student";
printf("I am a %s doing COMS%d\n",word,val);
```  
The formatting options presented above are string (%s) and signed integer (%d). Also note that there are no built-in string objects in C, you use null-terminated char arrays. We have listed several tutorials and reference sites for C at https://wits-coms3010.github.io/resources.html that you should consult for techniques such as string and file handling.

- Open hello_world.c and look at how to manipulate strings using strcpy and strcat. Then, complete the program by making it print the length of the string.
<br />
<br />

### 2.4 Arguments

In arguments.c, you will notice that main takes in two parameters:

   `argv`: the array of parameters passed to the program. For example: ```arguments file1.txt file2.txt```, *argv* is then ["arguments","file1.txt","file2.txt"].  
   `argc`: the number of parameters passed to the program and will always be at least 1, since the program name is always the first parameter.

<br />
   
- Complete arguments.c to print the executable name and the arguments passed to it in a comma-separated list. Strictly adhere to the output format.

Example output:
```
./arguments asdf qwerty
Program name: ./arguments
Arguments: asdf,qwerty
```
```
./arguments
Program name: ./arguments
Arguments: NONE
```
<br />
<br />

### 2.5 wc
Now we are going to get you thinking in C, with an eye to how applications utilize the operating system by passing command line arguments from the shell, reading and writing files, and standard file descriptors. You might be familiar with these concepts from your earlier courses, but this course will cover them in more depth. Your task is to write a clone of the Unix tool wc, which counts the number of lines, words, and characters inside text files. You can run Unix’s wc to see what your output should look like. e.g. ```wc map.c```, and read about it using the *man* command. *man* allows you to access manual pages for certain functions to see what exactly they do. e.g. ```man wc```.  

- **Replicate the ```wc``` function in wc.c** 
  - It must give the same output as ```wc```. Don’t worry about the flags it takes or spacing in the output.
  - It must be able to handle multiple input files. 
  - If no input files are specified, it should read from stdin. 

Example output (the actual numbers will differ based on what you change in the file):
```
./wc wc.c
      80     272    1727   wc.c 
```
```
./wc wc.c main.c
      80     272    1727   wc.c 
      21      59     489   main.c
     101     331    2216   total 
```
<br />
<br />

### 2.6 **Executables and addresses**
Now that you have dusted off your C skills, we want you to understand what is really inside of a running program and what the operating system needs to deal with.

### 2.6.1 gdb
Debugging C programs is difficult. Crashes don’t give you nice exception messages or stack traces by default. Fortunately, there’s gdb. If you compile your programs with a special flag **-ggdb3**, then the output executable will have debug symbols, which allow gdb to do its magic. If you run your C program inside gdb it will allow you to not only look get a stack trace, but inspect variables, change variables, and pause code, among other things. 
Normal gdb has a very plain interface, so you might prefer to use **cgdb**, which has syntax highlighting and few other features. <a href="http://dirac.org/linux/gdb/">This</a> is an excellent read on understanding not only how to use gdb, but also how your programs work. If you have never used gdb before, consult <a href="http://dirac.org/linux/gdb/">this tutorial</a>.  

Compile wc with the `-ggdb3` flag. Load up your wc executable in gdb, set a breakpoint at wc, and run it on wc.c. Take a look at the stack using `where` or `backtrace` (bt):   
```
gdb ./wc
break wc
run wc.c
bt
```

While you are looking through gdb, think about the following questions and put your answers in a file called 'gdb.txt':  
1. What is the value of infile? (hint: `print infile`)
1. What is the object referenced by infile? (hint: `*infile`)
1. What is the address of the function wc?
1. Try `info stack`. Explain what you see.
1. Try `info frame`. Explain what you see.
1. Try `info registers`. Which registers are holding aspects of the program that you recognize?  
<br />
<br />

### 2.6.2 objdump
We have just peeled away the abstraction layers that is the onion of an executing program: the source
code, compiled into an object, linked into a executable, that is loaded and executed on a computer. The
operating system meets the application as an executable file when you run it. There is more to the
executable than meets the eye. Let’s look down inside:  

```objdump -x wc```

You will see that it has several segments, names of functions and variables in your program correspond to labels with addresses or values, and the guts of everything is chunks of stuff within segments. While you are looking through the objdump, try and think about the following questions and put the answers in a file called 'objdump.txt':  
1. What file format is used for this binary? What architecture is it compiled for?
1. What are the names of segments you find?
1. What segment contains wc (the function) and what is its address? (hint: ```objdump -w wc | grep wc```)
1. What about main?
1. How do these correspond to what you observed in gdb when you were looking at the loaded, executing program?
1. Do you see the stack segment anywhere? What about the heap? Explain.
<br />
<br />

### 2.6.3 map
Okay, now you are ready to write a program that reveals its own executing structure. The map.c file provides a rather complete skeleton. 

* Modify map.c to print the addresses that you are looking for and get the type casts right so that it compiles without warning. 

The output of the solution looks like the following (the addresses will be different):
```
./map  

Main @ 40058c  
recur @ 400544  
Main stack: 7fffda11f73c  
static data: 601028  
Heap: malloc 1: 671010  
Heap: malloc 2: 671080  
recur call 3: stack@ 7fffda11f6fc  
recur call 2: stack@ 7fffda11f6cc  
recur call 1: stack@ 7fffda11f69c  
recur call 0: stack@ 7fffda11f66c  
```

Now write down the answers to the following questions in a file called 'map.txt':
1. Use objdump with the -D flag on the map executable. Which of the addresses from the output of running ./map are defined in the executable, and which segment/section is each defined in?
1. Make a list of the important segments, and what they are used for (look up their names on the internet if you don't know).
1. What direction is the stack growing in?
1. How large is the stack frame for each recursive call?
1. Where is the heap? What direction is it growing in?
1. Are the two malloc()ed memory areas contiguous? (i.e. is there any extra space between their addresses?)
<br />
<br />

### 2.7 User limits
The size of the dynamically allocated segments, stack and heap, is something the operating system has to deal with. How large should these be? Poke around a bit to find out how to get and set user limits on linux. Modify main.c so that it prints out the maximum stack size, the maximum number of processes,
and maximum number of file descriptors. Currently, when you compile and run main.c you will see it print out a bunch of system resource limits (stack size, heap size, ..etc). Unfortunately all the values will be 0.

* Correct main.c to print the actual limits. (Hint: ```man rlimit```) 
 
You should expect output similar to this:
```
./main

stack size: 8192
process limit: 2782
max file descriptors: 1024
```
<br />
<br />

## 3 **Submission**

You will be saving all your work to your assigned private GitHub repository.

Once you've finished coding the assignment or just want to save your changes, try executing the following:  
* ```git status``` - see what files are changed and staged for the next commit, those are displayed in red and green respectively. Everything should be red if you have yet to commit.
* ```git diff``` - see what changes have been made since your last commit in each of the files.  
* ```git add arguments.c hello_world.c wc.c main.c map.c gdb.txt objdump.txt map.txt Makefile``` - stage all changed files in the current directory for your next commit.
* ```git status``` - the files you specified in ```git add``` should be green .
* ```git commit -m "Finished hw0"``` - creates a commit with the message "Finished hw0", saving a snapshot of those files locally.

Once you have finished your work on your local repository, push to your assigned GitHub repository, which is named after your student number. Having done this once, you can continue your work by cloning the repository on another computer.
* ```git push https://github.com/WITS-COMS3010/student_number master```

If you just type ```git push```, it will try to push to 'origin'. We changed the url of 'origin' in section 1, if you did not it will try to push to WITS-COMS3010/hw-2019 and fail.

NOTE: 
1. You must use GitHub to submit your assignment, we will not accept email submissions!
2. Keep your directory structure intact. That is, inside hw-2019 you should have a folder called 'hw0' with your source files. Future assignments will be in separate folders, 'hw1' and so on, in the same repository.
