# Brainfucker
A minimal brainfuck compiler implemented in C for Linux x86_64 (does not handle 'Advanced Brainfucking').
## Usage
First, build the brainfuck compiler with the *make* command. A new executable named as *brainfucker* should appear in the same directory.  
```bash
git clone https://github.com/upseteapot/brainfucker
cd brainfucker
make
```  
  
**(sim) simulate**  
Simulates code in a safe environment. Does not build the executable.  
```
./brainfucker sim path-to-file.b
```  
**(asm) generate x86_64 assembly**  
Generates x86_64 assembly code. The output file will be created in the directory where the 'brainfucker' was called in, following this name pattern: *file_name.b.asm*.
```
./brainfucker asm path-to-file.b
```
**(com) compile**  
Generates x86_64 assembly code, converts it to binary format and link it. The executable will be created and named based on the provided path.
```
./brainfucker com path-to-file.b path-to-exe
```
**(for) format**  
Formats a brainfuck file, which means delete all whitespaces and new line charcters, as well as comments.
```
./brainfucker for path-to-file.b new-file-path.b
```  
