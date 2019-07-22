# COMS3010 Homework Assignments #

Read the following carefully before starting your lab assignment.

## Git and GitHub

Git is a version control tool that helps you to keep track of
different versions of your files and synchronize them across different
machines. [GitHub](https://github.com) is a hosting service for git
repositories with a convenient web interface.

It is worthwhile investing time and effort into learning how to
use Git and GitHub effectively -- you will be using them throughout
this course, and possibly for a very long time afterwards. A good
place to start is [this book](https://git-scm.com/book/en/v2). Additional resources are
suggested at the [course webpage](https://wits-coms3010.github.io).  GitHub's [help
page](https://help.github.com/) also contains numerous links to resources for learning about both
Git and GitHub.

## GitHub repositories

All assignments will be submitted by pushing to your private
repository associated with this course.

For the duration of the course, you will have access to two 
repositories in the 'WITS-3010' GitHub organization:

1. [This homework repository](https://github.com/WITS-COMS3010/hw-2019)
   containing public information about the homework assignments. You only
   have the read access to this repository.  All lab assignments will be uploaded here. 
   You should also check the course website regularly for announcements related to homework assignments.

# NB
2. A personal repository corresponding to your student
   number.  This repository is private -- only you and the course
   staff can access this repository: you should keep the contents of
   this repository private and secure. You will be using this repository
   to submit your assignments. We will create this for you once you have submitted 
   your student number and username to us at [https://forms.gle/WQCtyhVMMhoLKdET9](https://forms.gle/WQCtyhVMMhoLKdET9).

   Each assignment will reside in a separate folder with skeleton code and a `README.md` containing the instructions.
   Right now, you are reading a `README.md` for hw-2019.

   At the start of the course, your personal repository will be empty.

## Git Setup ##

To be able to submit your assignments, you need to perform the
following steps:

1. If you don't have a GitHub account, create one at [https://github.com/join](https://github.com/join).

2. Register your GitHub username for this course by filling out this
form: [https://forms.gle/WQCtyhVMMhoLKdET9](https://forms.gle/WQCtyhVMMhoLKdET9). This is due by the end of the first lab on Monday, 22 July. **You will not be able to submit any assignments if this is not done.**

3. Before you can use GitHub on a campus computer, you need to configure
Git to use the proxy server. Execute the following commands, replacing 'student_number' and 'password' with your CNS details:

   **This needs to be done every time you use a wits/lab computer or 'vmuser'.**

   ```
   git config --global http.proxy 'http://students\<student_number>:password@proxyss.wits.ac.za:80'
   git config --global https.proxy 'https://students\<student_number>:password@proxyss.wits.ac.za:80'
   history -c
   ```
   
   **Make sure to clear your bash history if you are using a wits/lab computer or 'vmuser'.**

   NOTE: If you still get 407 errors, check whether you have special characters (@,:,!,#,$)
   in your password and try escape them with a backslash, e.g. '\\$'. If that doesn't work, substitute
   the special characters with their unicode equivalent, see
   <a href="http://www.cyberciti.biz/faq/unix-linux-export-variable-http_proxy-with-special-characters/">this link</a>
   for more details.

   NOTE: The above commands with the `--global` flag change your user's global git configuration at `~/.gitconfig`
   and would make the proxy settings permanent for your user. If you ommit `--global` the settings will only be
   changed for your current repository and override any conflicting global settings - *This is probably the way
   you want to do it on vmuser, as you have more control over your personal information*.

4. Configure your GitHub username and email for commits:

   **This needs to be done every time you use a wits/lab computer or 'vmuser'.**

   ```
   git config --global user.name "<github_username>"
   git config --global user.email "<student_number>@students.wits.ac.za"
   ```

Further instructions will be provided in each of the homework folders, but remember to complete the above steps when needed. To get started with your first assignment, go to [hw0](./hw0).

## Academic Integrity

The code for each lab assignment is to be completed by you alone. Students may not share code, may not copy code, and may not discuss code in detail while it is being written or afterwards. Your code is your responsibility. 

We may use various code comparison tools including automated tools to help spot assignments that have been
submitted in violation of university plagiarism rules. The tools take all assignments from all sections and all prior terms and compares them, highlighting regions of the code that are similar. We (the instructor and the teaching assistants)
check flagged pairs of assignments very carefully ourselves, and make our own judgement about which students
violated the rules of academic integrity on programming assignments. When we believe an incident of academic
dishonesty has occurred, we contact the students involved. All students caught cheating on a programming
assignment (both the copier and the provider) will receive an automatic 0 for that assignment, and be subject 
to university disciplinary processes.
