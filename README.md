# compiler-design
This is a simple compiler for Kotlin. 

## Project Setup
```
cd compiler
make
cd ../javaa
make
cd ..
```

## To compile
### 1. Use a.out in folder compiler to generate a .jasm file
```
cd compiler
./a.out < <filename>.kt
```
### 2. Use javaa to generate a .class file
```
../javaa/javaa <className>.jasm
```
### 3. Use java to run it
```
java <className>.class
```
