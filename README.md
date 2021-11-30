# Brainfucker
**WORK IN PROGRESS**  
- [x] Simplified simulation
- [x] Simplified assembly generation
- [ ] Multiple loops
- [ ] Advanced brainfuck
A minimal brainfuck compiler implemented in C.
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
**(for) format**  
Formats a brainfuck file, which means delete all whitespaces and new line charcters, as well as comments.
```
./brainfucker for path-to-file.b new-file-path.b
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
## What is Brainfuck?
Brainfuck is an esotheric language (esolang) created by Urban Müller in 1993. It is a minimalist language, while still being turing complete. Because of its difficult to program with and its lack of features, it is not intended to create large scale projects, but rather to be a challange, or just to impress people.  
In the standart brainfuck programming language we have a buffer of integers, each individual integer is called cell. We have eight instructions to manipulate this cells:
```brainfuck
+        # Increment the value in the current cell.
-        # Decrease the value in the current cell.
>        # Move cursor to the cell on the right.
<        # Move cursor to the cell on the left.
[        # Start of loop.
]        # End of loop, if the value on the current cell is equal to 0, break loop.
.        # Print the current cell value, for instance, if the value stored is 48, 
           it will print '0', because the ASCII code for 0 is 48.
,        # Accept one byte (char) as input and store it in the current cell.
#        # This is used to create comments :)
```
There is also an extension to the brainfuck language, know as 'Advanced Brainfuck', it introduces the 'file mode' that gives you the ability to open and manipulate files. So, yes, it is possible to create a brainfuck compiler using brainfuck if you are asking.  
With this set of instructions you can create whatever you want, for instance, take a look at a very simple 'Hello world!' project for brainfuck:
```brainfuck
++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.
```
