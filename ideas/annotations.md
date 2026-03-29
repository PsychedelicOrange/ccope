# Annotation based ideas

@Test
---
> Type: function

Will generate a build target for that function/ add to existing test suit.

@Inline 
---
> Type: function

Will neccesarrily inline the function. usefull in cases where u don't want to create a parameter copy or pass a pointer and do dereferencing in the function body.

@ToString
---
> Type: Enum

Will generate a function to get the string associated with a enum value. usefull for debugging or deserializing.

Example:

```
@ToString
enum Color {
    RED,
    Yellow
};
```
will generate 
```
enum Color{
    RED,
    Yellow
};

const char* ColorToString(enum Color color){
    switch(color){
        case RED:
            return "RED";
            break;
        case Yellow:
            return "Yellow";
            break;
    };
}
```

@namespace("System")
---
> Type: File, Scope

Allows you to contribute definitions to the namespace.

Will rename symbols in the file/scope by adding the prefix specified as argument with the annotation.

Nesting namespaces: Namespaces can be nested, and the child namespaces will be renamed by the prefix of the parent
```
@namespace("Containers"){

    @namespace("Vector"){ // will become Containers.Vector after execution of top level `@namespace` tag
        struct Vector{ // will become Containers.Vector.Vector
            int a[3];
        };
    }
    @namespace("Hashmap"){ // will become Containers.Hashmap after execution of top level `@namespace` tag
        
    }
}

```

Note: This prefix can be overridden by the user while `@import`ing this namespace

@import(.namespace="Module::Namespace::subNamespace",.file="src/log.c",.lib="glu32")
---
> Type: File, Scope

Will make symbols from a namespace/file/lib available to the file/scope.

- `.as` will allow use of the value specified as the prefix for the imported symbols (module::namespace:: ) 
This is useful to prevent naming conflicts when importing two namespaces with clashing prefix !!!!
Note: This can only used with files created for the new module system. 
- `.namespace` will make the namespace symbols accessible to the file/scope.
- `.file` will make the file symbols accessible to the file/scope.
- `.lib` will make the lib symbols accessible to the file/scope.

Note: if the `.as` is specified, only one symbol source is allowed per `@import` (ie. namespace, file, or lib).

@include
---
> Type: File, Scope

old c-style #include symbols from the file into the scope.

@Private
---
> Type: Function, Struct, Enum, Union, Variable

Hides the annotated entity from being `@imported`.

@ForwardDeclare
---
> Type: Function, Struct, Enum, Union, Variable

Creates a forward declaration for the annotated entity at the top of the file. If @ForwardDeclareFunctions is also enabled for the scope, this annotation has not effect on functions.

1. @ForwardDeclareFunctions
> Type: File, Scope

Forward declares all functions which don't have a declaration. This allows for functions to be defined in any order.
