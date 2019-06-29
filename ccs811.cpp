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
    //double co2( static_cast<uint16_t>(data_[0] << 8) | data_[1] );
    //return co2;
    return static_cast<uint16_t>(data_[0] << 8) | data_[1];
}

double
Ccs811::tvoc() const
{
    //double tvoc( static_cast<uint16_t>(data_[2] << 8) | data_[3] );
    //return tvoc;
    return static_cast<uint16_t>(data_[2] << 8) | data_[3];
}
