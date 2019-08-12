# Homework 1: Shell #

### This is an individual assignment
### Points: 15% of your final grade
### **Due: 2 September 2019, 11:59 PM**

<br />
<br />

## Introduction

Now that you've been introduced to some of the intricacies of operating systems and programming in C, you can move onto a more interesting assignment.

You task is to program a simple shell, similar to Bash. The main purpose of a shell is to allow users to run and manage programs. By building your own shell, you'll become
more familiar with these interfaces and learn a bit more about how programs interact.

Do not be intimidated by the scope of this assignment. We have provided skeleton code and ample time for you to complete it. 
Read the instructions carefully, work through this section by section and you'll be fine.

<br />
<br />

## 1 Getting Started

You need to download the source code we've provided. If you did hw0 you should already have your own hw-2019 repository. Open a terminal in your hw-2019 directory and pull from the main homework repository:
```
$ git pull https://github.com/WITS-COMS3010/hw-2019.git
$ cd hw1
```

We have provided skeleton code for your shell and a simple Makefile in the hw1 directory. It includes a string tokenizer, which splits a string into words. In order to run the shell:
```
$ make
$ ./shell
```
To terminate the shell after it starts, either type `quit` or press CTRL-D.

**NOTE:** 
1. You should only need to modify shell.c, shell.h, process.c, and process.h.
1. Strictly adhere to the output specifications.
1. Use the private GitHub repository we assigned you, you should know how to commit and push from the previous homework. **Do NOT use a public repository!**

<br />
<br />

## 2 Built-In Functions

Every shell supports a number of built-in commands, which are functions in the shell itself rather than external programs.
For example, the `quit` command needs to be implemented as a built-in command because it exits the shell itself. The only two built-ins currently supported in your shell are:  
* `help` - prints the help for built-in commands.
* `quit` - exits your shell.

The skeleton code we have provided for you in 'shell.c' has a dispatcher for built-in commands. Look at the code provided for 'cmd_quit' and 'cmd_help' for an idea on how to integrate the following commands.

<br />

### 2.1 pwd

Programs have a working directory when they are executed. You have experienced this whenever you try to open a file in a program, it usually searches for the filename relative to the directory where you executed the program.  
`pwd`, or "print-working-directory", prints the current working directory to standard output. 

* Implement `pwd` as a built-in command. (Hint: there's a C function to get the working directory)
* Update your shell's main loop to print the current working directory along with the line number.

For example, say that your current directory is "/home/vmuser/Desktop/hw-2019/hw1":
```
0 /home/vmuser/Desktop/hw-2019/hw1# pwd
/home/vmuser/Desktop/hw-2019/hw1

1 /home/vmuser/Desktop/hw-2019/hw1# quit
```

<br />

### 2.2 cd

The `cd` command, "change directory", is another typical built-in command. It changes the current working directory of the shell.
E.g. ```cd /bin``` changes the working directory to '/bin'. The command takes in one argument---a directory name---and changes the current working directory to the specified directory.

**Example:**  
```
0 /home/vmuser/Desktop/hw-2019/hw1# cd /home/vmuser

1 /home/vmuser# cd /bin

2 /bin# quit
```

You should notice how `cd` in Bash handles the special characters tilde '\~', and dash '-'.  
- '\~': Expands to the home directory of the current user. E.g. if username is 'John', then `cd ~` expands to `cd /home/John`, and `cd ~/Desktop` is the same as `cd /home/John/Desktop`.  
- '-': Return to the previous working directory.

**Example:**  
```
0 /home/vmuser/Desktop/hw-2019/hw1# cd ~

1 /home/vmuser# cd /bin

2 /bin# cd ~/Desktop

3 /home/vmuser/Desktop# cd -

4 /bin# quit
```

- Implement the `cd` command.
  - Handle the '\~' character.
  - Handle the '-' character.

Once you're done, push your code to your private repository.
```
git commit -m "Finished adding built-in commands."
git push https://github.com/WITS-COMS3010/<student_number> master
```
You should commit your code periodically, so you can go back to a previous version of your code if you want to.

<br />
<br />

## 3 Program Execution

Currently, if you try to type something into your shell that isn't a built-in command, you'll get a message that the shell doesn't know how to execute programs. You need to implement program execution.

### 3.1 Exec

Modify your shell so that it can execute programs when they are entered into the shell. The first word of the command is the name of the program. The rest of the words are the command-line arguments to the program.
For this step, you can assume that the first word of the command will be the full path to the program. So instead of typing "wc", you would type "/usr/bin/wc".

Your shell should do the following:  
1. Execute the program at the given path, as long as it is not a built-in command.  
1. Pass any arguments to the spawned program.  
1. Print an error message if the path is not valid: "Could not execute 'path': No such file or directory".

Once you finish this section, you should be able to execute programs from your shell.  
**Example:**
```
0 /home/vmuser/Desktop/hw-2019/hw1# /bin/echo asdf
asdf

1 /home/vmuser/Desktop/hw-2019/hw1# /usr/bin/wc io.c -c
542 io.c

2 /home/vmuser/Desktop/hw-2019/hw1# lkjhg
Could not execute 'lkjhg': No such file or directory

3 /home/vmuser/Desktop/hw-2019/hw1# quit
```
We'll give you a hint to start off: when your shell needs to execute a program, it should fork a child process which calls one of the
exec functions such as *execv* (Google them) to run the new program. The parent process should wait until the child process completes and then listen for more commands.

- Implement running executables with the full pathname specified.

In anticipation of future sections where you need to manage multiple processes, you should use the structure defined in 'process.h' to implement launching new processes in 'process.c'.

<br />

### 3.2 Path Resolution

You probably found that it was a pain to test your shell in the previous part, because you had to type the
full pathname of every program. Luckily, every program has access to a set of environment variables,
which is structured as a hashtable of string keys to string values. One of these environment variables is
the PATH variable. You can print the PATH variable of your current environment in Bash:
```
$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:...
```
When a shell executes a program like 'wc', it looks for a program called 'wc' in each directory on
the PATH environment variable and runs the first one that it finds. The directories on the path are separated with a colon.

- Implement path resolution for running executables. (Hint: after getting the PATH variable use "getToks()" from 'parse.c')

You should be able to run any executable in the folders in PATH without specifying the full pathname. Typing in the full pathname of the executable should still be supported, however.  
**Example:**  
```
0 /home/vmuser/Desktop/hw-2019/hw1# echo asdf
asdf

1 /home/vmuser/Desktop/hw-2019/hw1# wc io.c
 27  81 542 io.c
 
2 /home/vmuser/Desktop/hw-2019/hw1# /usr/bin/wc io.c
 27  81 542 io.c

3 /home/vmuser/Desktop/hw-2019/hw1# quit
```

**WARNING:** you are NOT allowed to use *execvp*, *execvpe*, *execlp* or any other function that does path resolution for you. You will receive zero marks for this section if you do.

<br />

### 3.3 Input/Output Redirection

When running programs, it is sometimes useful to provide input from a file or to direct output to a file.  
- `[process] > [file]` - redirect the process's standard output to file. 
- `[process] < [file]` - feed the contents of a file to the process's standard input.
To simplify this task, you may assume that there will always be spaces around special characters '<' and '>'. 

**Example:**
```
0 /home/vmuser/Desktop/hw-2019/hw1# wc io.c > out.txt

1 /home/vmuser/Desktop/hw-2019/hw1# cat out.txt
 27  81 542 io.c

2 /home/vmuser/Desktop/hw-2019/hw1# wc -c < out.txt
17
 
3 /home/vmuser/Desktop/hw-2019/hw1# quit
```

- Modify your shell so that it supports redirecting stdin and stdout.

You do **not** need to support redirection for shell built-in commands. You do **not** need to support stderr redirection, nor appending to files with "[process] >> [file]". 

<br />
<br />

## 4 Signal Handling and Terminal Control

Now for the complicated part. You may have to restructure significant portions of your code to do the final sections if you haven't implemented process handling as we specified in the skeleton code.
Read through everything first and do some planning before you start coding.

Most shells let you stop or pause processes with special key strokes. These special keystrokes, such as
Ctrl-C or Ctrl-Z, work by sending signals to the shell's subprocesses. For example, pressing CTRL-C
sends the SIGINT signal which usually stops the current program, and pressing CTRL-Z sends the SIGTSTP
signal which usually sends the current program to the background. If you try these keystrokes in your shell, the signals are sent directly to the shell process itself. This is not what we want, since for example
attempting to CTRL-Z a subprocess of your shell will also stop the shell itself. We want to have the
signals affect only the subprocesses that our shell creates.

Before we explain how you can achieve this effect, let's discuss some more operating system concepts.

### 4.1 Process Groups

You know that every process has a unique process ID (pid). Every process also has a (possibly non-unique) process group ID (pgid), which by default, is the same as the pgid of its parent process.
Processes can get and set their process group ID with getpgid(), setpgid(), getpgrp(), or setpgrp().
Keep in mind that, when your shell starts a new program, that program might require multiple processes to function correctly. All of these processes will inherit the same process group ID of the
original process. So, it may be a good idea to put each shell subprocess in its own process group, to
simplify your bookkeeping. When you move each subprocess into its own process group, the pgid should
be equal to the pid.

<br />

### 4.2 Foreground Terminal

Every terminal has an associated "foreground" process group ID. When you type CTRL-C, your terminal
sends a signal to every process inside the foreground process group. You can change which process group
is in the foreground of a terminal with "tcsetpgrp(int fd, pid_t pgrp)". The fd should be 0 for standard input.

<br />

### 4.3 Signals

Signals are asynchronous messages that are delivered to processes. They are identified by their signal
number, but they also have human-friendly names that all start with SIG. Some common ones include:  
* **SIGINT** - Delivered when you type CTRL-C. By default, this stops the program.
* **SIGKILL** - There is no keyboard shortcut for this. This signal stops the program forcibly and cannot be overridden by the program. (Most other signals can be ignored by the program.)
* **SIGTERM** - There is no keyboard shortcut for this either. It behaves the same way as SIGQUIT.
* **SIGQUIT** - Delivered when you type CTRL-\\. By default, this also stops the program, but programs treat this signal more seriously than SIGINT. This signal also attempts to produce a core dump of the program before exiting.
* **SIGTSTP** - Delivered when you type CTRL-Z. By default, this pauses the program. In bash, if you type CTRL-Z, the current program will be paused and bash (which can detect that you paused the current program) will start accepting more commands.
* **SIGCONT** - Delivered when you run 'fg' or 'fg [pid]' in Bash. This signal resumes a paused program.
* **SIGTTIN** - Delivered to background processes that are trying to read input from the keyboard. By default, this pauses the program, since background processes cannot read input from the keyboard. When you resume the background process with SIGCONT and put it in the foreground, it can try to read input from the keyboard again.
* **SIGTTOU** - Delivered to background processes that are trying to write output to the terminal console, but there is another foreground process that is using the terminal. Behaves the same as SIGTTIN by default.

You can use either **signal** or **sigaction** in C to ignore signals or change how they are handled by the current process. Your shell
should ignore most of the above signals, whereas the shell's subprocesses should respond with the
default action. Reading ```man 2 signal``` and ```man 7 signal``` will provide more information. Be sure to check out the SIG_DFL and
SIG_IGN constants. For more information about how signals work, you can view a tutorial at <a href="https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/19/lec.html">this link</a>.

You should ensure that each program you start is in its own process group. When you start a process,
its process group should be placed in the foreground.

- Update your shell to ignore SIGINT, SIGTSTP, SIGTTIN, SIGTTOU.
- If SIGINT or SIGTSTP is received, your shell should send the signal to the spawned subprocesses instead. 

**NOTE**: forked processes will inherit the signal handlers of the original process, so you have to reset to default signal handling for subprocesses.

The SIGINT command should no longer terminate your shell when a subprocess is running.  
**Example:**  
```
0 /home/vmuser/Desktop/hw-2019/hw1# sleep 5
// Press CTRL-C

1 /home/vmuser/Desktop/hw-2019/hw1# quit
```

<br />
<br />

## 5 Background Processing

So far, your shell waits for each program to finish before starting the next one. Many shells allow you run
a command in the background by putting an ampersand, '&', at the end of the command line. After the background
program is started, the shell allows you to start more processes without waiting for background process
to finish.

### 5.1 &

Modify your shell so that it runs commands that end in an '&' in the background. You only need
to support background processing for external programs, not built-in commands. Once you've implemented this
part, you should be able to run programs in the background with a command such as `sleep 10 &`.
You should also add a new built-in command `wait`, which waits until all background jobs have
terminated before returning to the prompt. You can assume that there will always be a space before the '&' character. You can assume that, if
there is an '&' character, it will be the last token on that line.

- Update your shell to run any external program (not built-in) that ends in an '&' in the background.
- Implement the built-in `wait` command.

<br />

### 5.2 Foreground/Background Switching

Now that you can execute processes in the background, we need some way to bring them back to the foreground. Code the following built-in command:  
`fg [pid]`: Move the process with id pid to the foreground. If pid is not specified, move the most recently launched process to the foreground.

The process should resume if it was paused (hint: SIGCONT). You should ensure that each program you start is in its own process group. The process group id of a program should be the same as its pid. You should keep a list of all programs you've started and whether
they are in the foreground or background, we have provided such a structure in 'process.h'. Inside this list, "struct termios" stores the terminal settings of each program.

- Implement the built-in `fg` command.

<br />
<br />

## 6 Submission

This assignment is due **02 September 2019, 11:59 PM**. Ensure your final code is in your private repository by then! 

To submit, as usual, commit your changes and push to your private repository:
```
git commit -m "Finished hw1."
git push https://github.com/WITS-COMS3010/<student_number> master
```

**NOTE:**  
1. If your code doesn't compile or run you will get 0. If you haven't quite finished the last sections, it's better to submit code where the first parts are in working order than code where nothing works.
1. Don't print any extraneous output, such as debug messages. Any extra output not specified in this brief may negatively affect your mark.
1. Keep your directory structure intact. That is, inside the top level of your repository you should have a folder called 'hw1' (case sensitive) with your source files.
1. You must use GitHub to submit your assignment, email submissions will not be accepted!
