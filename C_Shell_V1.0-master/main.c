#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

// declarining Array Size as a constant for quick changes, 500 should be good but if needed
// changing this helps the code be unified
#define ARR_SIZE 500

// --- Utility Commands --- //

// function to attach arg2 to the end of arg1
void attach(char atachto[], char attachment[]){
    // initilizations
    int i = 0;
    int x = 0;
    // getting the size of arg1
    for (; atachto[i]; i++){continue;}
    // adding the arg2 to the end of arg1 using its size found earlier
    for (; attachment[x]; x++){atachto[i+x+1] = attachment[x];}
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to clear an array
void clear_arr(char my_arr[]){
    // itterates through the array and places null chars, C by default will do this after
    // one '\0' however to just keep everything in check the code is setup like so
    for(int i = 0; my_arr[i]; i++){my_arr[i] = '\0';}
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to copy infomration of arg2 into arg1
void copy_arr(char copy_to[], char copy_from[]){
    // clearing the array to help keep a clean slate so you can do it for a larger arr to a smaller one
    clear_arr(copy_to);
    // itterates though arg2 and stores the elms in arg1
    for(int i = 0; copy_from[i]; i++){copy_to[i] = copy_from[i];}
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to test equivelence in two strings
int is_equal(char arr1[], char arr2[]){
    // itterates though each arg while they are true
    for (int i = 0;arr1[i] && arr2[i]; i++){
        // if the values of both args do not match a exit code of zero is sent
        // unlike in most cases where 0 means success, 0 will mean for a binary false
        if (arr1[i] != arr2[i]){return 0;}
    // retruns a 1 to indicate a binary true
    }return 1;
}

// function to remove all chars in an array after a given key
void remove_after(char my_arr[],char my_key){
    // itterates through arg1 and once when the key is found in arg1, all that is after is
    // replaces with a '\0'
    for (int i = 0; my_arr[i]; i++){if(my_arr[i] == my_key){my_arr[i] = '\0';}}
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to remove all chars in an array before a given key
// more complex then the remove_after function
void remove_before(char my_arr[],char my_key){
    // creates and setting aside an array to act as a holder
    char test_arr[ARR_SIZE];
    // copying elements of the arg1 into the holding array
    copy_arr(test_arr, my_arr);
    // clearing the arg1 for text to be appended to
    clear_arr(my_arr);
    // initilization of counters so the code will be able to copy from arg1s copy to arg1
    // binary indicator of if the arg2 was found
    int write = 0;
    // personal counter for when arg1 gets values stored into it
    int counter = 0;
    // itterating though the duplicate of arg1
    for (int i = 0; test_arr[i]; i++){
        // if the key is detected begin to write
        if (test_arr[i] == my_key){write = 1;}
        // if able to write copy arg1 index counter to test_arr index of loop and increment counter
        // while this could be done too with using a pointer to test_arr, and then preforming :
        // copy_arr(my_arr,*test_arr_pointer)
        // I opted not to for the thought not occuring at the time of creation
        if (write){my_arr[counter] = test_arr[i]; counter++;}
    }
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// a function to take one arg and remove the tabs, newlines, and extra spaces
void simple_space(char my_arr[]){
    // initilizing varibles to be used
    // a biniary indicator of if the previous char was a space
    int space_before = 0;
    // a new array to use to help store temporary information into
    char new_arr[ARR_SIZE];
    // a counter for the new array since it should not be in sync with
    // the for loop all of the time
    int arr_counter = 0;
    // itterating through arg1
    for (int i = 0; my_arr[i]; i++){
        // if the arg1 has a space at its i'th element
        if (my_arr[i] == ' '){
            // if there is a space before skip over the entire for loop
            // for this one iteration
            if (space_before){continue;}
            // if not, set the binary indicatory to 1 and continue
            space_before = 1;
        // if their is a tab or newline
        }else if(my_arr[i] == '\t' || my_arr[i] == '\n'){
            // if there is a space before skip over the entire for loop
            // for this information since \t and \n are not wanted
            if (space_before){continue;}
            // if there is no space before, the \t \n is turned into a space
            my_arr[i] = ' ';
            // space before indicator is now true
            space_before = 1;
        // if their is neither a space or a tab or new line set
        // the binary indicator to false
        }else{ space_before = 0; }
        // add information from the current arg to its empty clone
        new_arr[arr_counter] = my_arr[i];
        // increment the clones counter
        arr_counter++;
    }
    // copy the clone to the original arg
    copy_arr(my_arr, new_arr);
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to take arg1 and push either before all spaces to arg2 depending on return type
void tokenizer(char my_command[], char my_token[], int return_type){
    // deletes all information in arg2 for reasignment
    clear_arr(my_token);
    //return_type :
    // 0 : fist word
    // 1 : everything after the first word
    if (return_type == 0){
        // itterates through arg1
        for (int i = 0; my_command[i]; i++){
            // if a space or new line is found, the code is done
            if (my_command[i] == ' ' || my_command[i] == '\n'){break;}
            // if not, add the command to the token
            my_token[i] = my_command[i];
        }
    }else{
        // initializes for the binary indicator and array counter for my_token
        // binary indicator to announce if a space was found
        int begin_copy = 0;
        // token arry counter
        int t_begin = 0;
        // itterates though arg1
        for (int i = 0; my_command[i]; i++){
            // if arg1 has a newline that was the end of the command
            if (my_command[i] == '\n'){my_command[i] = '\0'; break;}
            // if biniary value is true copy the vales of arg1 into arg2 and incrment t_begin by 1
            if (begin_copy){
                my_token[t_begin] = my_command[i];
                t_begin++;
            // else check to see if the white space is found
            }else if (my_command[i] == ' '){begin_copy = 1;}
        }
    }
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// --- Shell Commands --- //

// function to clear the shell
void clear_shell_print(int amount){
    // itterate n amount of times to print a newline
    for (int i = 0; i < amount; i++){ printf("\n");}
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to find the enviorment of the shell
void environ_c(){
    // creating a local array to hold the data of the environment
    char arr[ARR_SIZE];
    // grabbing the enviornment from <unistd.h>
    extern char **environ;
    // changing the string of the 9th element in eniron to the path
    for (int i = 0; i < 4; i++){environ[8]++;}
    // replacing the path to the proper path
    copy_arr(environ[8], getwd(arr));
    // backtracking so the enviorn is left as it was untouched
    for (int i = 0; i < 4; i++){environ[8]--;}
    // itterating through the environ and displaying its content
    for (int i = 1; environ[i]; i++){printf("%s\n",environ[i]);}
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to display the contents in a directory, arg1 is the direactory and arg2 toggles
// weither hidden elments will be shown or not
void dir(char my_path[],int show_type){
    // creating a struct of the directory to be assigned to the active directory
    struct dirent *dir_entry;
    // creating a dir from <dirent.h> to help nagivate a direactory opened from arg1
    DIR *dir_ptr = opendir(my_path);
    
    //make sure dir exists if it doesnt, an error message is sent and the command is over
    if (dir_ptr == NULL){printf("Coult not find / open current directory\n"); return;}
    
    //show_type:
    // 0 : default
    // 1 : all
    if (show_type == 0){
        // itterates through the directory untill there is no more elements
        while((dir_entry = readdir(dir_ptr)) != NULL){
            // if the directory is not hidden display the directory
            if (dir_entry -> d_name[0] != '.'){printf("%s\n", dir_entry -> d_name);}
        }
    }else{
        // itterates through the directory and displays all elements in that directory
        while((dir_entry = readdir(dir_ptr)) != NULL){printf("%s\n", dir_entry -> d_name);}
    // close the directory, while the termination of the function will defaultly do this, its good practice
    }closedir(dir_ptr);
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function to print all of the function
// this all could be done in one print statment; however, this makes it easier to add and edit
void help_c(){
    printf("cd <path>\n");
    printf("clr\n");
    printf("echo <string>\n");
    printf("enviorn\n");
    printf("dir <path>\n");
    printf("help\n");
    printf("pause\n");
    printf("programname < inputfile > outputfile &\n");
    printf("quit\n");
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// --- init commands --- //

// function to get the root of any machine passing in an arr to be a copy of the root
void get_root(char arr_to_root[]){
    // creating a local array to hold the data of the environment
    extern char **environ;
    // removing the root text
    for (int i = 0; i < 5; i++){environ[9]++;}
    // copying the array of the environment root to the passed through array
    copy_arr(arr_to_root,environ[9]);
    // reverting the changes to environs 10th element to leave it as we got it
    for (int i = 0; i < 5; i++){environ[9]--;}
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// function for when the command forks to run an exicutable program
void my_fork_init(char my_exe[],char my_args[]){
    // initialization of arrays
    // file out name array
    char my_fileo_name [ARR_SIZE];
    // file in name array
    char my_filei_name [ARR_SIZE];
    // inupt from file in array
    char my_input [ARR_SIZE];
    // token for input for file in array
    char my_input_t [ARR_SIZE];
    // clearing the input to have a nice clean start
    clear_arr(my_input);
    // giving both string the recent command for stripping the file
    tokenizer(my_args, my_fileo_name, 1);
    tokenizer(my_args, my_filei_name, 1);
    // remove the & and > as well as all the elements after
    remove_after(my_filei_name, '&');
    remove_after(my_filei_name, '>');
    // removes up to but not including the <
    remove_before(my_filei_name,'<');
    // passes argumrnt into and out of tokenizer to set the
    // file in name to the right file
    tokenizer(my_filei_name,my_args, 1);
    tokenizer(my_args,my_filei_name, 0);
    // remove the & and everything after
    remove_after(my_fileo_name, '&');
    // removes up to but not including the >
    remove_before(my_fileo_name,'>');
    // passes argumrnt into and out of tokenizer to set the
    // file out name to the right file
    tokenizer(my_fileo_name,my_args, 1);
    tokenizer(my_args,my_fileo_name, 0);
    // if an input file was found
    if (*my_filei_name){
        // open file for reading
        FILE *my_in_file = fopen(my_filei_name,"r");
        // while the file exists
        while(my_in_file != NULL){
            // if the file still contains content
            if(fgets(my_input_t,ARR_SIZE,my_in_file) == NULL){fclose(my_in_file);break;}
            // if there is no input, copy the token input into the input
            if (!*my_input){copy_arr(my_input, my_input_t);}
            // if there is an input, append to the input more data
            else{attach(my_input, my_input_t); attach(my_input," "); }
        }
    }
    // if there is a file output open the ouput and have all of the information form hear on out
    // in the fork be registered into the output. This will too write error messages into the
    // output if the code is unsucessful
    if (*my_fileo_name){int my_file = open(my_fileo_name,O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); dup2(my_file,1);}
    // creates a char to pass as the args for the exe
    const char *args[]={my_exe,my_input,NULL};
    // executes the exe, this will remove the fork from this code if it is sucessful
    // anything that happens after this execv is ment to catch if the program does not exist
    execv(args[0],args);
    // giving a heads up that the program does not exist
    printf("Couldn't Execute Program : %s\n",my_exe);
    // always return even if voids to help indicate a difinitave start and stop
    return;
}

// --- main --- //

// The main function
int main(int argc, const char * argv[]) {
    // initialization of all varibles to be used
    // char arry to mainly be used for getting the directory
    // (can also be used as a tempary place holder)
    char my_dir[ARR_SIZE];
    // printing the currenet directory that the shell code is in
    printf("shell=%s/My_Shell\n",getcwd(my_dir, ARR_SIZE));
    // calling the get_root function to assign the directory to the root of the OS
    get_root(my_dir);
    // changing the cwd with <unistd.h> to actually be at the root
    chdir(my_dir);
    // boolean initialization for is_paused
    int is_paused = 0;
    // creating an array whos priority is for inputs
    // (can also be used as a tempary place holder)
    char my_input[ARR_SIZE];
    // creating an array whos priority is for the inputs token
    // (can also be used as a tempary place holder)
    char my_token[ARR_SIZE];
    // creating a pointer to a file for whenever myshell batchfile.txt
    FILE *my_file = NULL;
    // clearing the token and imput array. Not 100% needed an can go away
    // however its just a nice safty measure to make sure everything is
    // at a clean slate before begining
    clear_arr(my_input);
    clear_arr(my_token);
    // the main loop, everything will take plaec here
    while (1){
        // if the my_file is assigned to something
        if(my_file != NULL){
            // if there is no more in that file
            if(fgets(my_input, ARR_SIZE, my_file) == NULL){
                // close the file
                fclose(my_file);
                // assigin the file ptr to null
                my_file = NULL;
                // start back from the very begining of the loop
                continue;
            }
            // if there is more information in the file
            // tokenize my_input
            tokenizer(my_input, my_token, 0);
        // if there is no file
        }else{
            // clearing my_input in the event that inputs are of varring sized
            clear_arr(my_input);
            // prints the directory path with a >
            printf("%s > ",getcwd(my_dir, ARR_SIZE));
            // getting the input
            fgets(my_input, ARR_SIZE, stdin);
            // tokenizing the input
            tokenizer(my_input, my_token, 0);
        }
        // if paused is to a 1, then the pause is toggled off
        // and everything is skiped through
        if (is_paused){
            is_paused = 0;
            continue;
        }
        // if the token shares similarities with cd
        if (is_equal(my_token,"cd")){
            // tokenize everything after the 'cd '
            tokenizer(my_input, my_token, 1);
            // tokenize the first thing in the event that
            // there is more into the my_dir
            tokenizer(my_token, my_dir, 0);
            // try to chang the directory
            chdir(my_dir);
        // if the first few chars in the input match 'clr'
        }else if(is_equal(my_token,"clr")){
            // bumps the shell up 20 new lines, this number can be changed
            clear_shell_print(20);
        // if the first few chars in the input match 'echo'
        }else if(is_equal(my_token,"echo")){
            // tokenize everything after the 'echo '
            tokenizer(my_input, my_token, 1);
            // removes extra spaces from the token
            simple_space(my_token);
            // prints the token
            printf("%s\n",my_token);
        // if the first few chars in the input match 'environ'
        }else if (is_equal(my_token,"environ")){
            // calls the environ_c function created earlier
            environ_c();
        // if the first few chars in the input match 'dir'
        }else if (is_equal(my_token,"dir")){
            // tokenize everything after the 'dir '
            tokenizer(my_input, my_token, 1);
            // if there is an existance of only 'dir -a'
            if (is_equal(my_token,"-a") && *my_token){
                // calls the dir function made and tell to print hidden values
                dir(getcwd(my_dir, ARR_SIZE),1);
            // if there is still more to the token ands its not '-a'
            }else if (*my_token){
                // makes the input the values of the token
                copy_arr(my_input,my_token);
                // tokenizes the input to get two things
                // input : dir
                // token : contains -a or doesnt
                tokenizer(my_input, my_token, 1);
                // if the token contains and -a and exists
                if (is_equal(my_token,"-a") && *my_token){
                    // give the input directoy to the token
                    tokenizer(my_input, my_token, 0);
                    // call the directory function showing hidden
                    dir(my_token,1);
                // if theres no '-a' try to show the directory but without hiddens
                }else{dir(my_input,0);}
            // show the current working directorys values if all was entered was 'dir'
            }else{dir(getcwd(my_dir, ARR_SIZE),0);}
        // if the first few chars in the input match 'pause'
        }else if(is_equal(my_token,"pause")){
            // toggle pause to be equal to 1
            is_paused = 1;
        // if the first few chars in the input match 'help'
        }else if(is_equal(my_token,"help")){
            // call help_c function
            help_c();
        // if the first few chars in the input match 'myshell'
        }else if(is_equal(my_token,"myshell")){
            // tokenize my_input to get the file
            tokenizer(my_input, my_token, 1);
            // try to open and read the fill called in myshell
            my_file = fopen(my_token,"r");
        // if the first few chars in the input match 'dir'
        }else if(is_equal(my_token,"quit")){
            // breaks out of the main while loop to return a 0
            break;
        // if there are no inputs then the Shell interperates it as a exe is trying to be invoked
        }else{
            // fork at this location in the code and pass the current input and token
            // if my_fork_init is returned than something went wrong and is announced with
            // and exit code of 1
            if (fork() == 0){my_fork_init(my_token,my_input); return 1;}
            // partent fork
            else{
                // tokenize to get the arguments following the input
                tokenizer(my_input, my_token, 1);
                // this in all sums up to the code is looking and continues to tokenize until the
                // token is empty of an instance of a & is found. if the & is found the Shell doesnt
                // wait for the token to start and end but just continues on
                while (*my_token){
                    copy_arr(my_input,my_token);
                    tokenizer(my_input, my_token, 1);
                }if(*my_input != '&'){scanf("%c",my_token); printf("\n--- Fork Has Ended ---\n");}
            }
        }
    }
    // always return even if voids to help indicate a difinitave start and stop
    // return code 0 ment everything went correctly
    return 0;
}
