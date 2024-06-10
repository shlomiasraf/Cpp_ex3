#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
using namespace doctest;

int main(int argc, char **argv)
{
    Context context;
    context.addFilter("reporters", "console");

    int res = context.run(); 

    if (context.shouldExit()) 
        return res;        

    int client_stuff_return_code = 0;

    return res + client_stuff_return_code; 
}
