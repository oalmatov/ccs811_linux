#include "ccs811.h"
#include <getopt.h>
//#include "sht20.h"

using namespace std;

static struct option LONGOPTIONS_[] = 
{
    { "reset",          no_argument,    nullptr, 'r' },
    { "environment",    no_argument,    nullptr, 'e' },
    { "help",           no_argument,    nullptr, 'h' },
    { nullptr,          0,              nullptr,  0  }
};

int main( int argc, char* argv[] )
{
    string      progname( argv[0] );
    int         opt;
    Ccs811      ccs811( "/dev/i2c-1", 0x5A );
    //Sht20       sht20( "/dev/i2c-1", 0x40 );

    while ( (opt = getopt_long(argc,argv,"reh",LONGOPTIONS_,nullptr)) != -1 )
    {
        switch ( opt )
        {
            case 'r':

                ccs811.reset();

            break;

            case 'e':

                ccs811.setEnvironmentalData( 0.0, 0.0 );

            break;
            
            case 'h':
            default:

            cout << 
            "Usage: " << progname << " [options]\n"
            "\t-r --reset\t\tReset CCS811\n"
            "\t-e --humidity\t\tSet environmental data\n"
            "\t-h --help \t\tPrint help message\n";

            return EXIT_SUCCESS;
        }
    }

    ccs811.read();

    cout << "CO2: " << ccs811.co2() << endl;
    cout << "TVOC: " << ccs811.tvoc() << endl;
}
