// ccs811.h

#ifndef CCS811_H
#define CCS811_H 1

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

#endif // CCS811_H
