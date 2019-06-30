/* ccs811runner.cpp
****************************************************************************************************************
****************************************************************************************************************
    Copyright (C) 2019 Omar Almatov
     
    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
    Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.
    
    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
    License for more details.
    
    You should have received a copy of the GNU General Public License along with this program. If not, see
    <http://www.gnu.org/licenses/>.
*/

#include <getopt.h>

#include "ccs811.h"

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

    while ( (opt = getopt_long(argc,argv,"reh",LONGOPTIONS_,nullptr)) != -1 )
    {
        switch ( opt )
        {
            case 'r':

                ccs811.reset();

            break;

            case 'e':

                ccs811.setEnvironmentalData( 0.0, 0.0 ); //insert humidity and temperature data

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
