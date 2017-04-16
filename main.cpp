#include "execute/execute_code.hpp"
#include "declare_code.hpp"
#include "kernel/thread.hpp"
#include "runtime/io.hpp"


#include <iostream>
#include <iterator>
#include "kernel/io.hpp"

using main_code = decltype(
":main "
        //push parameters
        "mov eax , 0 "
        "push eax "
        "mov eax , 19 "
        "push eax "
        "mov eax , .thread_code "
        "push eax "

        "call .sys_create_thread "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "
        "mov eax , 0 "

        "call .sys_exit_thread"_s);

using thread_code = decltype(
":thread_code "
        "call .sys_exit_thread "_s);

using code = ctai::declare_code<ctai::include::thread ,
                                thread_code,
                                main_code>;

using test_proc = decltype(
":test_proc "
        "ret "_s);

using main2 = decltype(
":main "
        //push parameters
        "mov eax , 97 "
        "call .sys_write "
        "call .sys_exit_thread"_s);

using code2 = ctai::declare_code<ctai::include::thread ,
        ctai::include::sys_write,
        main2>;



using execution_result = ctai::execute2::execute_code<code>;

int main()
{
    const auto output = ctai::runtime::io::make_runtime_output<execution_result::output>();

    std::cout << "Return value: " << execution_result::ret_val << "\n";

    std::cout << "execution output: \n";

    for(auto c : output)
        std::cout<<c;

    return 0;
}

#include "tests/tests_main.hpp"