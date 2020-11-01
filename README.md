# CppRouter

Meant to be simple to use and generic.



WORK IN PROGRESS



## Goals

C++ is a great language, but needs a lot of work and knowledge.
For web routing as well as for cli, we have to use different technologies.

This library won't implements directly web server nor cli tools.
It will implement:

* Route matching
* Route call



It should be easy to customise its use.



## Compilation

Currently officially need at least **C++17** and only need the standard library.
Backward compatibility support may be added.



## Usage

```c++

Route<int, int, float> route(
    "hello %d world %d final %f",
    [](int a, int b, float c) {
        std::cout << a << " - " << b  << " " << c << std::endl;
    });

route("hello 52 world 34 final 9.0");  // 52 - 34 9
```





Goal

```c++
Router router;
router.route(
    "hello/{}/world/{}/final/{}",
    [](int a, int b, float c) {
        std::cout << a << " - " << b  << " " << c << std::endl;
    }
);

router.route(
    "hello/{}/world",
    [](const std::string& a) {
        std::cout << "test: " << a << std::endl;
    }
);


router("hello/foo/world");  // test: foo
router("hello/32/world/64/final/5.9");  // 32 - 64 5.9
router("abc");  // Error
```

* Not relying on C formatting
* Automatic route match
* Default parameter