/* ccs811.cpp
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

#include "ccs811.h"

using namespace std;

Ccs811::Ccs811( const char* busFile, uint8_t i2cAddress )
{
    fd_ = open(busFile, O_RDWR);

    ioctl( fd_, I2C_SLAVE, i2cAddress );
    usleep( 1000 );
}

void
Ccs811::read()
{
    i2c_smbus_read_i2c_block_data( fd_, 0x02, sizeof(data_), data_ );
    usleep( 1000 );
}

void
Ccs811::reset()
{
    uint8_t   reset[] = { 0x11, 0xE5, 0x72, 0x8A };

    while ( i2c_smbus_read_byte_data(fd_, 0x00) & 0x01 )
    {
        cout << "reset" << endl;
        i2c_smbus_write_i2c_block_data( fd_, 0xFF, sizeof(reset), reset );
        usleep( 1000 );
        i2c_smbus_write_byte( fd_, 0xF4 );
        usleep( 1000 );
        i2c_smbus_write_byte_data( fd_, 0x01, 0x10 );
        usleep( 100000 );
    }

}
void
Ccs811::setEnvironmentalData( double humidity, double temperature )
{
    uint16_t    temp( (temperature + 25) * 512 );
    uint16_t    hum( humidity * 512 );
    uint8_t     envData[ 4 ] = { temp >> 8, temp & 0xFF, hum >> 8, hum & 0xFF };
    
    i2c_smbus_write_i2c_block_data( fd_, 0x05, sizeof(envData), envData );
}

double
Ccs811::co2() const
{
    return static_cast<uint16_t>(data_[0] << 8) | data_[1];
}

double
Ccs811::tvoc() const
{
    return static_cast<uint16_t>(data_[2] << 8) | data_[3];
}
