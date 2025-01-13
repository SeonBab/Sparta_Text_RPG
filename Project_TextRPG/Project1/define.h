#pragma once

#define GameMainSingleton(Class)\
private:\
Class() = default;\
~Class() = default;\
Class(Class& other) = delete;\
Class& operator = (const Class& other) = delete;\
static void Deleter(Class* ptr)\
{\
    delete ptr;\
}\
static shared_ptr<Class> instance;\
static shared_ptr<Class>& GetInstance()\
{\
    if (nullptr == instance)\
    {\
        instance = shared_ptr<Class>(new Class(), Deleter);\
    }\
    return instance;\
}\
friend class GameMain;

#define GetterSetter(Type, FuncPostFix, Property)\
const Type& Get##FuncPostFix(){return Property;}\
void Set##FuncPostFix(const Type& InProperty ){Property = InProperty;}

#define Getter(Type, FuncPostFix, Property)\
const Type& Get##FuncPostFix(){return Property;}

#define Setter(Type, FuncPostFix, Property)\
void Set##FuncPostFix(const Type& InProperty ){Property = InProperty;}