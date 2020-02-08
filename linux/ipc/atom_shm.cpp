#include <atomic>
#include <string>
#include <iostream>
#include <cstdlib>
#include <boost/interprocess/managed_shared_memory.hpp>

using namespace std::string_literals;
namespace bip = boost::interprocess;

int main(int argc, char *argv[])
{
    if(argc == 1) //Parent process
    {
        struct shm_remove {
            shm_remove() {
                bip::shared_memory_object::remove("szMem");
            }
            ~shm_remove() {
                bip::shared_memory_object::remove("szMem");
            }
        } remover;

        bip::managed_shared_memory segment(bip::create_only, "szMem", 65536);

        auto ap = segment.construct<std::atomic_int>("the counter")(0);
        //Launch 5 child processes
        std::string s = argv[0] +" child"s;
        std::system((s + '&' + s + '&' + s + '&' + s + '&' + s).c_str());
        std::cout << "parent existing: counter = " << *ap << '\n';
        segment.destroy<std::atomic_int>("the counter");
    } else { // child
        bip::managed_shared_memory segment(bip::open_only, "szMem");
        auto res = segment.find<std::atomic_int>("the counter");
        for(int n = 0; n < 100000; ++n)
            ++*res.first; 
        std::cout << "child exiting, counter = " << *res.first << '\n';
    }
}