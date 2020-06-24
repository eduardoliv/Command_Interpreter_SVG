# Command_Interpreter_SVG
This application uses unix parsers (FLEX and BISON) to read a .txt list of commands and draw them to a .svg file.

## Usage
* Open Linux terminal, navigate to the application folder and run ./logo \< \<commands\> \> \<draw\>
    * \<commands\> Is the first file specified below. (You can use the star.txt file, included here!) 
    * \<draw\> Any name you want, plus the .svg format.
* You can write your own commands, as shown below.

## File format
* This program requires a command file
    * **make "\<var_name\> \<var_value\>** -> lets you attribute a number to a variable. 
    * **forward :\<var_name\>** -> draws forward, given a variable. 
    * **fd :\<var_name\>** -> draws forward, given a variable. 
    * **right :\<var_name\>** -> rotate right (degrees), given a variable. 
    * **rt :\<var_name\>** -> rotate right (degrees), given a variable.
    * **repeat :\<var_name\> [\<command\> :\<var_name\> ...]** -> repeat a command n times. Inside the brackets, you can rewrite any command, as many times as you want.  

## Compilation
* Compile via Linux make command
    * Use \<make\> to create the executable
    * Use \<make clean\> to clean the objects/parser files
    
## Dependencies
* To compile, you need Bison and Flex packages
    * Bison: sudo apt-get install bison
    * Flex: sudo apt-get install flex

## Release History
* 0.0.1
    * Create README.md
 
## Meta
> Eduardo Oliveira - eduardo.oliveira@ieee.org;
