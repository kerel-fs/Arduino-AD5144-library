/*
 * AD5144 Arduino library: Interface with Analog Devices AD5144 digital potentiometer via SPI.
 * Copyright (c) 2017 Fabian P. Schmidt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PotentiometerAD5144_h
#define PotentiometerAD5144_h

#include <Arduino.h>
#include "SPI.h"

class AD5144
{
  public:
    SPISettings spi_settings;

    AD5144::AD5144(const size_t _channels, const int _chip_select_pin);
	void begin();
    void AD5144::begin(const SPISettings _spi_settings);
    uint16_t sendCommand(const byte control, const byte address, const byte data);
	void set_value(const size_t channel, const byte value);
	uint16_t get_value(const size_t channel);

  private:
    size_t channels;
    int chip_select_pin;
};

#endif
