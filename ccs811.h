/* ccs811.h
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

#ifndef CCS811_H_
#define CCS811_H_ 1

#include <iostream>
#include <sqlite3.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

class Ccs811
{

public:

                Ccs811( const char* busFile, uint8_t i2cAddress );

    void        read();
    void        reset();
    void        setEnvironmentalData( double humidity, double temperature );
    double      co2() const;
    double      tvoc() const;

protected:

    int         fd_;
    uint8_t     data_[ 8 ];
};

#endif // CCS811_H_
