# Brainfucker
A minimal brainfuck compiler implemented in C.
## Usage
First, build the brainfuck compiler with the *make* command. A new executable named as *brainfucker* should appear in the same directory.  
  
**(sim) simulate**  
Simulates code in a safe environment. Does not build the executable.
```
./brainfucker sim path-to-file.b
```  
**(for) format**  
Formats a brainfuck file, which means delete all whitespaces and new line charcters, as well as comments.
```
./brainfucker for path-to-file.b new-file-path.b
```  
**(asm) generate x86_64 assembly**  
Generates x86_64 assembly code. The output file will be created in the same directory as the source file, following this file pattern: *file_name.b.asm*.
```
./brainfucker asm path-to-file.b
```
