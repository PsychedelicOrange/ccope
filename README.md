# ccope - written to cope with c syntax and isms.
- repo is a work in progress where i straighten out my ideas about what i would want in a language
- many of the details mentioned below are subject to change

# About
- Who it's for - C lovers who want optional convinience and better package management
- C is still C - core language is untouched.
- A new, powerful and extendable annotation-based pre-processor, with access to the AST!
- Namspaces and modules for package management ( no config files neccessary, modules are folders )
- Dependency management ( use git submodules - modules are just folders ) (TODO: maybe pick Version management ?)
- A new std lib with more convinience builtin - dynamic strings, Abstract data types, and much more!

# Core features
The features are all (almost) based on annotations, which are special functions which are processed by the pre-processor.

These features are baked in, and wouldn't make sense to skip if we are using this library. 
Also these won't work on old pre-processor based C project.
- [ ] order independent declarations/definitions in a file. 
- [ ] order independent imports. 
- [ ] modules and namespaces resolution.

These features are optional

[Ideas about annotations](idea/annotations.md)

# Reasoning behind decisions
## Scope and name conflict management
### module/package/bundle
Whatever name you call it, we use this simple construct for package management. It **is** a directory with source files.
```
Structure of a package
.
└── stringlibrary/ ( a module )
    └── src/
        ├── main.c
        └── memorylibrary/ ( another module )
            ├── memhelper.c
            ├── memalloc.c
            └── interface.h
```
**Why a folder was chosen**
If a folder was not chosen to mark a module, we would have to chose something to mark the files with. Maybe an annotation like
```
@module("stringlibrary")
```
Would have to be placed in all files beneath, which is :thumbs-down: . Although the folder limits the flexibility of the project structure, 
I think this is a valid sacrifice for simpler project management.

### Namespaces

These can be split ( contributed to ) across multiple files, just like cpp namespaces.

Internally, symbols in a namespace are prefixed by the namespace name.

To prevent name conflicts between namespaces defined in different modules ( by different authors ),
while importing(using) namespaces, the module which has the desired namespace needs to be specified. 

Needless to say, two symbols cannot share the same name inside a module.
Now modules are achieveing something similar to namespace, why even introduce namespaces when a module works?

We introduce it to manage intra-module conflicts.

Say, We could  solve it via internal nesting of modules. But it would look like a java nightmare
```
.
└── algorithms/
    ├── Vector/
    │   ├── print.c
    │   └── vector.c
    ├── HashMap/
    │   ├── test/
    │   │   ├── test1.c
    │   │   └── test2.c
    │   ├── map.c
    │   └── print.c
    └── log/
        └── log.c
```
A neater way, imo, is to allow namespaces to separate inside a module, rather than force the user to create needless directories.

So we could do something like this, with each file containing a @namespace.
```
algorithms/
├── vector.c
├── hashmap.c
├── test.c
├── print.c
└── log.c
```

or even everything in a single file if we wish.
```C algorithms.c
@namespace("hashmap"){
...
    @namespace("test"){
    ...
    }
}
@namespace("vector"){
...
    @namespace("test"){
    ...
    }
}
@namespace("log"){
...
}
```
So namespaces allow much more flexibility to the user to use their own philosophy for project structure management.

## Dependency management

Dependencies are placed into modules in the project files. 
- if possible, you can use git submodules for the simplest approach 
- for old C projects you can manually copy files ( headers, static/dynamic libs, etc ) into a folder
- (not sure about this) you can use `@dependency(url)` anywhere in the module, which will download the dependency at pre-preprocess stage into a submodule.


# Features that would change the language (Crazy idea which will go in a fork, if they survive)
## anonymous structs and unions ( some way to do the vec3 thing )
## Pointers and arrays 
This is a really confusing topic for many begginers. the syntax adds to the confusion.
Here are some changes that simplify the understanding

```
int[19] a = {}; # the size will be written next to the type.
    
int[] a = {
    0, 8, 9, 10, 12
};

int a = 6;
int& addy = &a; 
// int& != int*

int[?] a = 0; # better way to declare pointer is to write as an array with unknown size, instead of int* a;

a[0] # better way to derefrence a pointer instead of *a

user_struct[1] a = {{0}}; # a single element array of struct
user_struct[?] a = 0; # a pointer to a struct

a[0].member; # instead of a->member, the -> operater is another thing to remember

int myfunction ( user_struct[1] a ){ # better way to pass a single element pointer, also able to signal to the caller about size
user_struct b = 0;
myfunction(&b); # address of operator works fine and can be used to get the address of stack variables
}
```

so * and -> symbols will be removed from the language

for begginers we can teach them,
 arrays are passed by reference
while single values are passed by value
arrays without the [] are address to the start of the array. address of a single variable can be accessed via & operator
- pointer arithmetic TODO

## structs, enums, and unions 
structs, unions, and enums are automatically typedefed.

enums won't pollute the global scope, they will need to be accessed like
```
int value = color.RED
```

## string literals ( can't figure out any good reason to do this except increasing parser workload )
there is no reason we can't have multiline string literals
```
printf( "Dear %s: you are the best !,
    Regards,
    %s", boss_name,my_name);
# This will transpile to 
printf( "Dear %s: you are the best !,Regards, %s", boss_name,my_name);
        
```

## Variables ( not doing as it messes up convinience, but still open issue )
using an uninitialized variable will cause undefined behaviour in c. so we have banned uninitialized variables in this language.
```
int a = {}; # this is not allowed in c99 , it will not be allowed here as well
```
this would mean user has to initialize all variables at declaration.

## the void type (defunct)
There are many ways in which void is used. lets try to make its usage simple.
- in function signatures -> skip the usage
```C
function(){
}
# instead of 
void function(void){
}

```

- as a unknown / generic pointer
```C
idk[] allocate_memory(int size){ # use the keyword idk[] to signify the catch all term instead of void
    return malloc(size);
}
```
## functions and function pointers

```C
[1]addInt(int n, int m) int {
    return n+m;
}

int (function(int,int) summer; # transpiles to 'typedef int (*summer)(int,int);'
(int,int)) swallow_two_numbers; # incase of void return type

summer s = addInt;

idk[1] myfunc = addInt;
s = myfunc;

int getValues(int a,int b,summer s){
    s(a,b);
}

# array of function pointers

```
## designated assigners ( these will not zero unmentioned values )

```C
struct mystruct{
    int a;
    float b;
    char c;
};

# designated initializers
mystruct s = { .a = 1 ,
               .b = 0.5f
             }; # c is zero initialized

# designated assigners (use round brace)
s = ( 
    .a = 1; # note the semicolon, these are statements, not initializers. these will be executed in order
    .c = 2.0;
    );
 # b remains 0.5f

# these statements are executed one after the other, so we can do something like 
buffer buf = (
    .size = c; 
    .data = malloc(.size);
); 
```
## Enums values need to written with the enum name
Enum values are bad in regards to visibility/scoping and ORANGE doesn't tell me which enum it belongs to
```C
enum Fruits{
    ORANGE,
    BANANA
};
enum Colors{
    ORANGE,
    YELLOW
};

struct data{
    enum Fruit myData;
};

struct data d = {
    .myData = Fruits.ORANGE
};

```
lol i know this is a convulated example
