Making A Shell In C

The goal at my university was to make a version of a shell using C. In the creation of the shell we had to make our own commands of : clr, cd, dir, echo, environ, help, myshell, pause, invoking/executing programs, and quit. This was all preformed within the span of a week. I managed to accomplish all of the commands by truly making a shell and not making code to invoke a preexisting shell such as calling shell(command)

Getting Started

To get a copy of this shell running on your machine please go to your command line, find the directory this folder is in, and preform :
make -f Makefile.make
From there you will have an exe output of my_shell_exe

Give examples

Do note that all the commands are case sensitive

cd ..
clr
dir Documents
echo this is my echo
environ
help
myshell bachfile.txt
pause
ProgramName < input_file.txt > output_file.txt
quit
