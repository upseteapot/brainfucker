# Brainfucker
A minimal brainfuck compiler implemented in C.
## Usage
First, build the brainfuck compiler with the *make*. A new executable named as *brainfucker* should appear in the same directory.  
  
**Simulate [sim]**  
Simulate code in a safe environment. Does not build the executable.
```
./brainfucker sim path-to-file
```  
**Format [for]**  
Formats a brainfuck file, which means delete all whitespaces and new line charcters, as well as comments.
```
./brainfucker for path-to-file new-file-path
```

