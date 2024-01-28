

Can just save it from here
You have a shell to go off of so how much should you use it. -- when you litterly dont know how to implement the next section of the project 
``` java 

// so right now you know what you are going to be doing so do that 

        
        // pointer to the first address of string from userInput
        char *cmd = readUserInput(argc, argv);          // int argc is number of args right?             

        printf ("You typed: %s", cmd);                  // then what is up with the number thing that is in the reciation slides

        // code exit as the first check of userInput

        
        
        char *cmd = parseCommand(cmdLine);              // no idea what this is 

        if (0) {                                        // how in the world do I check if it is a built in command or not 

            executeBuiltInCommand(cmd);                 // why are you still tired is there a plugin I am missing
        }
        else {
            // need to fork and look through all executables to see if its there
        }


            // need to pass the char *argv though right? NOOO

            

        char command_Length[200];               // Commands will have a max size of 200 chars


         for (int i=0; i < 200; i++) {          // everything is always harder in C

        if (theCommand == '0') {
            
        }
        else {
            theCommand = theCommand + 8;                   // pointer arithmetic
            theCommandSize++;                              // trying to get the size of the string
        }


         theCommand = theCommand - commandLength;

             // char* theCommand = scanf("%s"); // running into issues with scanf - v annoying


        
    // I do not know the reason why I am supposed to tokenize, just that its what I am supposed to do 
    




    // does it matter if I tokenize all 200 or not? , maybe you have no idea right now if you need a delimiter then you will have to work on that 
    
    // thats exciting

      // what else to I need to accomplish in this method.... break it up into tokens?
    // still needs a return though 
    char* result; // uninitialized

    }

    // Globals restrictions on input 

char argLength[20];                     // max size of arguments will be 20 chars
int argMax = 20;                        // at most 20 arguments
int pluginMax = 10;                     // max number of plugins that need to be loaded in one run

 // scanf("%s", theCommand);             // a 200 character array since the command will never be over 200 chars




    for (int i=1; i<commandLength2; i++) {

        // when you tokenize should you be adding it to another array will it add NULL for you? 
        char* tok = strtok(NULL, " ");                 // go through and tokenize each word in the string
        printf("tokenizing... \n");
        formatCmd[i] = tok;
        
    }

        // am I really supposed to manually check built in commands? like what thats crazy 


    /** Assuming that cmdLocation will be -1 if which command is not found, else must do more work
    if (strcmp(cmdLocation, shellResult) == 0) {  // thats going to need some debug

        result = 1;                                     // built in command!
    }
    */


     char* justCopy = "which";

    

    strcpy(formatCmd+1, justCopy);                      // I am so bad at this

    printStringArray(formatCmd, formatCmd_size);


    
    // 3 strings each 30 chars long? 
    char* cmds[] = {"/usr/bin/which", "mm", NULL};    // works in thoth does not work in VS Code you are at the point of linux dev and debug now :(
    char* cmds2[] = {"/usr/bin/which", "bb", NULL};   // SO THESE ARE READ ONLY???? 

     // execv("/usr/bin/ls", cmd);

      //cmdLocation = execv("/usr/bin/which", cmds2);    // SHOULD BE WHICH, look up how to use execv for which command     

       /**
     * Right now only operate by taking and checking first index of formatCmd
     * use command but 
    */


   

// shouldn't need a fork function okay lets compile so you do need a fork????


   //formatCmd[0] = "/bin/ls";
    //formatCmd_size++;


    
    //printf("tokenizing... \n");

    //   size_t lengthTok = strlen(tok);           // getting length of string to where to stop tokenizing
    //  printf("              lengthTok: %d", lengthTok);           debug


    
// functions the same as a constructor 
/*
int plugin_init() {
    printf("Initializing plugin\n");

    // you have the name ex. "load better_ls" , better ls is the name

    
    

}
*/





 /*
        // CHECK IF ITS A COMMAND, IF COMMAND EXECUTE
        int isThere = 0;                            // boolean equivalent
        
        isThere = builtInCommand(formatCmd);        

        if (isThere) {
            executeBuiltInCommand(formatCmd);      // triggering everytime      
        }
        */

           void* handle = loadedPlugins[i]->handle;
                    
                    void (*RunPlugin)() = dlsym(handle, "run");
                    RunPlugin();




// built in command method that you are using 
int builtInCommand(char* formatCmd) {

    int result = 0;
    int cmdLocation = 0;


    char *command[] = {"which", "ls", NULL};
    
    pid_t pid = fork();                                 // fork time make parent wait while exev child executes
    
    if (pid == 0) {
    //    printf("        Child is calling exec! \n");
        execvp("which", formatCmd);
        execvp(command[0], command);

        kill(pid, SIGKILL);
       
    }
    else {
    //    printf("        Parent got here first but now were going to make it wait \n");
        wait(NULL);
    //    printf("        done waiting!\n");
        
    }
   
    // Why does it not need all listed inside of the else, because since execv replaced process you dont have to worry about the child executing this code since its impossible
    // because it replaces the current process how do I go from here, is that why you fork()?
    // cmdLocation must be declared before execv assignment because execv does not return if it execute successfully
   
    if (cmdLocation == -1) {

    //    printf("Aha you have typed in a faulty command \n");
        
    }
    else {
   //     printf("command founnd!\n");
        result = 1;                                 
    }

    
    return result;                                      // what isThere is going to be set to

}


char *command[] = {"ls", "-l", "-a", NULL};


 //malloc(strlen(newPluginPtr->name)+1);           // what do you need to malloc? 
    //loadedPlugins[loadedPlugins_size] = newPluginPtr


    // tokens (tokenCount+1) = NULL
                    // run (tokens);
                    // so just run with the string array of args which would be formatCommand in this instaance, already has a NULL at the end of the array




                    //void (*run_function)(int, char *[]) = dlsym(loadedPlugins[i]->handle, "run");

                    //char *args[] = {"arg1", "arg2", "arg3", NULL};
                    //run_function(formatCmd_size, formatCmd);
                    // dlsym on that thing that was found 

                    //    void (*InitializePlugin)() = dlsym(newPluginPtr->handle, "initialize");


                     // if commandLength is > 200 then what, 
    /*
    if (commandLength > 200) {

        printf("TOO MUCH \n");
        disregardExtra = 1;
    }
    */

   //int disregardExtra = 0;                        // bitflag for maxSize


 // if (disregardExtra == 0) {

       // }
       // else {
       //     disregardExtra = 0;                     // user input too much but still need to reset when the user ends up inputting the right amt
       //}



```