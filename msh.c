

/**
 * Author: Brandon Hoover
 * Date: 11/28/23 
 * Copyright: @All rights reserved
 * CS 0449 Project 4
*/

/**
 * Running file: 
 *  gcc -Wall -g -o calculator calculator.c
 *  ./calculator 4 5 +
 * Copying file into thoth: 
 *  scp C:\Users\17174\Desktop\CS_0449\Project_4\msh.c bch60@thoth.cs.pitt.edu:PROJ4\msh.c
 *  Password Copy:
20047Bch15@

 *  
*/


// which libraries do you need 
#include <stdio.h>                      // gives you standard input/output - readFromStdIn
#include <stdlib.h>                     // give you NULL, along with size_t
#include <string.h>                     // gives you stringcmp, parseCommand?

#include <sys/types.h>
#include <unistd.h>                     // gives you execvp
#include <signal.h>                     // gives you SIGNALS 

#include <dlfcn.h>                      // gives you RTLD_LAZY

                                               // might not allow for re-use unless it start from beggining of buffer each time it writes
char theCommand[200];                          // creates 200 character long buffer that can be writtin into from fget(), null terminator is at the end

char* formatCmd[200];     
int formatCmd_size = 0;                        // logical size of the parsed array

typedef struct {                

    char* name[200];
    void* handle;

} Plugin;

Plugin* loadedPlugins[10];                              // an array of plugins, finite since you know there will not be more than 10
int loadedPlugins_size = 0;                             // logical size of array

/********************************************************************PLUGIN SECTION *****************************************************************************************************/

void plugin_init () {

    // need to malloc a plugin so it doesnt 
                             
    Plugin* newPluginPtr;                       // pointer to the new plugin I created

    // Allocate memory for the struct on the heap

    newPluginPtr = (Plugin*)malloc(sizeof(Plugin)); 

    //newPluginPtr->name = formatCmd[1];

    strncpy(newPluginPtr->name, formatCmd[1], sizeof(newPluginPtr->name) - 1);
    newPluginPtr->name[sizeof(newPluginPtr->name) - 1] = '\0';  // Ensure null termination

    // add ./ at the beggining and add .so at the end 

    char slashString[100];
    char* soString = ".so";

    // adding "./"
    slashString[0] = '.';
    slashString[1] = '/';

    slashString[2] = '\0';


    strcat(slashString, formatCmd[1]);                          // "./plugin"
    strcat(slashString, soString);                              // "./plugin.so"

    //printf("\n slashString for dlopen: %s \n", slashString);

    newPluginPtr->handle = dlopen(slashString, RTLD_LAZY);      // should be path name of ./plugin.so
    
    // initialize void (*InitializeFunction) is a function Ptr
    int (*InitializePlugin)() = dlsym(newPluginPtr->handle, "initialize");
    int result = -1;

    // call initialize 

    if (InitializePlugin == NULL ) {

        //printf("Error: Plugin %s initialization failed!", newPluginPtr->name);
        
        
    }
    else {

        result = InitializePlugin();

    }

    if (result != 0 ) {     // if result is anything else for 0, an error occured within initialize

         printf("Error: Plugin %s initialization failed!\n", newPluginPtr->name);
         return;
         
    }


   // loadedPlugins[loadedPlugins_size] = newPluginPtr;          // add the plugin to the plugin array

   // printf("TEsting: Plugin %s \n", newPluginPtr->name);

        loadedPlugins[loadedPlugins_size] = newPluginPtr;
        loadedPlugins_size++;
    

        //strcpy(loadedPlugins[loadedPlugins_size], newPluginPtr->name);

}
    



/*********************************************************************COMMAND EXECUTION *************************************************************************************************/
char* readFromStdIn() {                          // do not need to pass any arguments so dont pass a pointer to data

   // printf("seg fault? \n");
   
    fgets(theCommand, 203, stdin);               // adding \n at the end of each userInput, might be terminal based

    size_t commandLength = strlen(theCommand);   // thats exciting, actually reads it properly, INCLUDES \0 NULL TERMINATOR though
    
    /**
     *  The reason that I replaced the end of the userInput with a null terminator is that fget() implementation pulls '\n'
     *  the '\n' is supposed to signify end of a string but ends causing trouble when executing the commands because the commands have
     *  the newline character attatched to the end. For example "ls\n" even after tokenized
     * 
    */
    theCommand[commandLength-1] = '\0';    

 //   printf("testing fgets  %s", theCommand);

    return theCommand;                    // returning the initial address of the string theCommand

}
// if you declare main last you shouldn't need any function prototypes 


char* parseCommand(char* cmdLine) {                    

    size_t commandLength2 = strlen(cmdLine);           // getting length of string to where to stop tokenizin;
    
    // before we can intepret the input we need to tokenize it 

    char* tok = strtok(cmdLine, " ");
    int phonyBoolean = 1;

  //  printf("tok: %s \n", tok);

    formatCmd[0] = tok;
  //  printf("    Array print: %s \n", formatCmd[formatCmd_size]);
    formatCmd_size++;

    while (phonyBoolean == 1) {

        char* tok = strtok(NULL, " ");                     // grabbing the first token since it is unique, (starting from char*)
       
        // kind of a weird way of getting out of the loop, strtok fails it sets tok to 0x0, when while comparrison pulls a good address of 0x7f4454...
        if (tok == 0x0) {

            break;
        }
        
        formatCmd[formatCmd_size] = tok;  // check if this works
     //   printf("    Array print: %s \n", formatCmd[formatCmd_size]);
     //   printf("        tok: %s \n", tok);
        formatCmd_size++;
            

        if (formatCmd_size > commandLength2) {             // preventing infinite loop if for some reason tok != 0x0

            phonyBoolean = 0;
        }


    }

                          
    // is fine the input is ending in newline for some reason, vs code helps gdb doesnt
    formatCmd[formatCmd_size] = NULL;                  // execv() requires a NULL as a terminator when passing args        
    formatCmd_size++;                                    // still gotta add to commandSize

    //printStringArray(formatCmd, formatCmd_size);    // debug

    // cmdLine points to theCommand which has the string data of user
    return cmdLine;                                     // returning cmdLine which is the initial position of the string but it is now tokenized
}


void executeBuiltInCommand(char** exeCmd) {


    // using execV or something to execute the found command, but why use the parsed version? because it takes strings
    //printf("EXECUTING COMMAND....\n");

    pid_t pid = fork();                                 // fork time make parent wait while exev child executes
    
    if (pid == 0) { 
        //printf("        2 Chi is calling exec! \n");
        execvp(formatCmd[0], formatCmd);
       // execvp(command[0], command);
       // int cmdLocation = execvp(exeCmd[0], exeCmd);  // SHOULD BE WHICH, look up how to use execv for which command 
       
       
       // kill(getppid(), SIGUSR1); 0---------- for killing zombies
       kill(pid, SIGKILL);
    }

    else {
       // printf("        2 Par got here first but now were going to make it wait \n");
        wait(NULL);
       
        // printf("        done waiting!\n");
    }


}


// helper function
void printStringArray(char** array, int size) {           // passing in a pointer of a pointer

   
    printf("printing contents: \n");
    // Calculate the size of the array
    //int arraySize = sizeof(array);              // 8 because its a pointer bro need to keep seperate variable dang it

    // Print each string in the array
    for (int i = 0; i < size; i++) {
       printf("    String %d: %s\n", i + 1, array[i]);
    }


}

// wait you are going to be typing into terminal each iteration so you can take args dummy so there should be no args for main because you dont need to call anything with it 
int main (int argc, char *argv []) {

    // why do I need "\n"?? and will I need it on thoth? 
    char* exitString = "exit";                    // does not need reinitialized each time, 
    char* loadString = "load";  

    // you would break out of this loop when Ctr ^C gets hit which is a terminate signal 
    while (1) {                                     // infinite loop that will never end

        int isAPlugin = 0;

        printf("> ");                           // printCommandPrompt();
    
        formatCmd_size = 0;                         // resetting command size

        char* cmdLine = readFromStdIn();            // readFromStdInt(); type string then? yes because of the return

        // EXIT
        if (strcmp(cmdLine, exitString) == 0) {

            // the user typed in exit to exit program exit inside of here
            //      printf("exit triggered!");
            return 0;
            
        }


        // PARSE (tokenizes everything )
        parseCommand(cmdLine);         
        
      
       
        // LOAD PLUGIN
        if (strcmp(formatCmd[0], loadString) == 0) {      // load function

           // printf("INITIALIZE \n");
            

            isAPlugin = 1;                      // its a plugin trying to load so dont try to execute a command for no reason
            int dontLoad = 0;                   // should be 0 each time


            for (int i=0; i < loadedPlugins_size; i++) {

                //printf("here\n");

                // formatCmd[1] now becuase load examplePlugin so plugin is second arg
                if (strcmp(formatCmd[1], loadedPlugins[i]->name) == 0) {

                    printf("Error: Plugin %s initialization failed!\n", loadedPlugins[i]->name);
                    dontLoad = 1;
                   
                } 
   
    
            }


            //printf("its here right %d \n", formatCmd_size);        // omg you have size
            
            if (formatCmd_size-1 == 1) {          // size would have to be larger than 1, first arg is 'load' second is the plugin 

                dontLoad = 1;
                printf("Error: Plugin some_string initialization failed!\n");
                
            }
           
            
            //printf("you better not call init %d \n ", dontLoad);
            if (dontLoad != 1) {

                //printf("valid load! \n");

               plugin_init();     // dont need function arguments because you are using the parsed as a global
            }
            
                
        }
        else {

           // printf("load was not typed \n");
           // printf("    size of loadedPlugins: %d \n", loadedPlugins_size);

            // CHECK IF ITS A PLUGIN            
            for (int i=0; i < loadedPlugins_size; i++) {

                //printf("    checking %d ", i);
                
                //printf("        loadedPlugins[i]: %s \n", loadedPlugins[i]->name);


                // if the the plugin exists in the plugin array then try to run it --- load 
                if (strcmp(formatCmd[0], loadedPlugins[i]->name) == 0) {

                   // printf("            loaded plugin found attempt to run it\n");

                    isAPlugin = 1;

                    void (*RunPlugin)() = dlsym(loadedPlugins[i]->handle, "run"); 
                    
                    RunPlugin(formatCmd);

                } 

            }

            //printf("                        IS A PLUGIN DONT EXECUTE %d \n", isAPlugin);
            if (isAPlugin != 1) {           // if you didnt find it in the load execute it

                executeBuiltInCommand(formatCmd);

            }
        }

       
       
    
    }

    // could call a cleanup here, cant run through and get these things 

    

    

}