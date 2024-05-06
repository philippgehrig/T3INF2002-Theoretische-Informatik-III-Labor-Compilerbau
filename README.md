# Compilerbau

This repo contains all the files for the university course: T3INF2002 Theoretische Informatik III - Labor Compilerbau

## Contributors

This Laboratory was completed by

- [Philipp Konstantin Gehrig](https://github.com/philippgehrig) 
- [Dinar Karchevskii](https://github.com/karchevskii)


##  Task

The creation of a compiler for a predicate logic based language containing:
- Lexical Analysis
- Parsing
- Symbol Table
- Semantic Tree
- Code Optimisation
- Code Generation

## Structure

This repository is structured in multiple different steps. E.G. the Folder compilerbau/flex comntaines all the system files after lexicaical analysis. This was done, because in e.g. the parser functions get included later on. By safing the different Workspaces in their own different folder, others that want to replicate this compiler, can do so more easily. The full compiler is at all times saved in the folder compilerbau/COMPILER

## Build

At first you need to navigate to the Compiler inside the repo
```bash
cd COMPILER
```

Each Folder has its own MAKE-File:
```bash
make
```
In the building you are creating all the necessary object files.
The final file is named: pl1c

Now you need to give the input file for the Compiler:
```bash
./pl1c <input-file>
```

Now the Comnpiler is running and the Code generation returns the optimized code.
