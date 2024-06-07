#if 1

#include <iostream>
#include <memory>

/*

Exception-safe: No cleanup is necessary if make_unique is not evaluated.
Safer than using new directly.

std::unique_ptr<T> std::make_unique<Args...>(Args&&... args);

T: The type of object you want to create.
Args...: Arguments for the constructor of T


*/

class POC {
public:
    POC() { std::cout << "Object Created\n"; }
    ~POC() { std::cout << "Object Destroyed\n"; }
};

void f() {
    std::unique_ptr<Geeks> obj = std::make_unique<Geeks>();
}

int main() {
    f();
    return 0;
}


#endif

#if 0

#include <iostream>
#include <memory>

class POC {
public:
    int value;
    POC(int x) : value(x) { std::cout << "Object Created\n"; }
    ~POC() { std::cout << "Object Destroyed\n"; }
};

void f() {
    std::unique_ptr<Geeks> obj = std::make_unique<Geeks>(10);
    std::cout << "Value: " << obj->value << "\n";
}

int main() {
    f();
    return 0;
}


#endif