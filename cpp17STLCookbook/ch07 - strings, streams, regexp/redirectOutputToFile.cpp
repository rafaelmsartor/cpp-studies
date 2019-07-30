
#include <iostream>
#include <fstream>

class redirect_cout_region
{
    using buftype = decltype( std::cout.rdbuf() );
    std::ofstream ofs;
    buftype buf_backup;

public:
    explicit redirect_cout_region( std::string const& filename )
        : ofs{ filename }
        , buf_backup{ std::cout.rdbuf( ofs.rdbuf() ) }
    {}

    redirect_cout_region()
        : ofs{}
        , buf_backup{ std::cout.rdbuf( ofs.rdbuf() ) }
    {}

    ~redirect_cout_region()
    {
        std::cout.rdbuf( buf_backup );
    }
};

void my_output_heavy_function()
{
    std::cout << "some output\n";
    std::cout << "this function does really heavy work\n";
    std::cout << "... and lots of it ...\n";
}

int main()
{
    std::cout << "Readable from normal stdout\n";

    {
        redirect_cout_region _ { "output.txt" };
        std::cout << "Only visible in output.txt\n";
        my_output_heavy_function();
    }

    {
        redirect_cout_region _;
        std::cout << "This output will completly vanish\n";
    }

    std::cout << "Readable from normal stdout again\n";
}