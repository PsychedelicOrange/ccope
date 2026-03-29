These are annotations which don't have a target. 
They are 'plugins' to the transpiler and they will affect the whole program/module (TODO: Decide)

1. @ForwardDeclareFunctions
Forward declares all functions which don't have a declaration. This allows for functions to be defined in any order.

2. @KeyWordArguments
Allows to use the struct initializer syntax to pass parameters to a function call

```C++
float divide(float divisor, float dividend){
    return dividend / divisor;
}

int main(){
    divide({.dividend = 25, .divisor = 8});
}
```

3. @FirstArgumentSugar (might change title)
sum(int a, int b)
can be written as a.sum(b)
OR
a.sum(b) === sum(a,b)
reason: https://graic.net/p/left-to-right-programming , but only makes sense if we get far enough to make a lsp 
