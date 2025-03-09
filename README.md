# ccope - written to cope with c syntax and isms.
- repo is a work in progress where i straighten out my ideas about what i would want in a language

# Scope and name conflict management
## module/package/bundle
Whatever name you call it, we use this simple construct for package management. It **is** a directory with source files.
Currently a need for a description file is not necessary, but may be later added to aid automatic dependency gathering.
Structure of a package
```
.
└── stringlibrary/ ( a module )
    └── src/
        ├── main.c
        └── memorylibrary/ ( another module )
            ├── memhelper.c
            ├── memalloc.c
            └── interface.h
```

## Namespaces
These can be split ( contributed to ) across multiple files.

Internally, symbols in a namespace are prefixed by the namespace name.

To prevent name conflicts between namespaces defined in different modules ( by different authors ),
while importing(using) namespaces, the module which has the desired namespace needs to be specified. 

Needless to say, two symbols cannot share the same name inside a module.
Now  modules are achieveing something similar to namespace, why even introduce namespaces when a module works?

Well, modules solve the naming conflicts between multiple modules. But what about internal projects?
Sure we could  solve it via internal nesting of modules in inside projects. But it would look like a java nightmare
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
A neater way, imo, is to allow namespaces to separate symbols across files, rather than force the user to create needless directories.

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

## Pointers for me to stick to
 * make c simpler to learn, understand and write
 * dont stray away from c, think of this like a c reskin ?
 * strip away stuff like order dependent declarations 
 * strip away hidden behaviours and minimize exceptions/ unexplained isms
 * (maybe, if possible) add a module system 
 * try to restrict stupid stuff which we won't use ever in good faith

## Topics
### Pointers and arrays 
This is a really confusing topic for many begginers. the syntax adds to the confusion.
Here are some changes that simplify the understanding

```
int[19] a = {}; # the size will be written next to the type.
    
int[] a = {
    0, 8, 9, 10, 12
};

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

### structs, enums, and unions 
structs, unions, and enums are automatically typedefed.

enums won't pollute the global scope, they will need to be accessed like
```
int value = color.RED
```

### string literals
there is no reason we can't have multiline string literals
```
printf( "Dear %s: you are the best !,
    Regards,
    %s", boss_name,my_name);
# This will transpile to 
printf( "Dear %s: you are the best !,Regards, %s", boss_name,my_name);
        
```

### Variables 
using an uninitialized variable will cause undefined behaviour in c. so we have banned uninitialized variables in this language.
```
int a = {}; # this is not allowed in c99 , it will not be allowed here as well
```
this would mean user has to initialize all variables at declaration.

### the void type 
There are many ways in which void is used. lets try to make its usage simple.
- in function signatures -> skip the usage
```
function(){
}
# instead of 
void function(void){
}

```

- as a unknown / generic pointer
```
idk[] allocate_memory(int size){ # use the keyword idk[] to signify the catch all term instead of void
    return malloc(size);
}
```
### functions and function pointers

```
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

### namespace and moduling TODO
### calling c code/ importing c header files TODO

## add new features ( maybe in a separate fork )
new features, not sure about this, will update 
- multiple value return type
- anonymous structs and unions ( some way to do the vec3 thing )
- designated assigners ( these will not zero unmentioned values )

```
struct mystruct{
    int a;
    float b;
    char c;
};

# designated initializers
mystruct s = { .a = 1 ,
               .b = 0.5f
             }; # c is zero initialized

# designated assigners
s =  {
    .a = 1; # note the semicolon, these are statements, not initializers. these will be executed in order
    .c = 2.0;
} # b remains 0.5f

# these statements are executed one after the other, so we can do something like 
buffer buf = {
    .size = c; 
    .data = malloc(.size);
}; 
```
