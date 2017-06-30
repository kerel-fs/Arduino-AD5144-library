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

#include "AD5144.h"
#include <assert.h>

AD5144::AD5144(const size_t _channels, const int _chip_select_pin) {
  channels = _channels;
  chip_select_pin = _chip_select_pin;

  // Set default settings
  spi_settings = SPISettings(1e6, MSBFIRST, SPI_MODE1);
}

void AD5144::begin() {
  // initialize SPI
  SPI.begin();
  pinMode (chip_select_pin, OUTPUT);
}

void AD5144::begin(const SPISettings _spi_settings) {
  spi_settings = _spi_settings;

  begin();
}

uint16_t AD5144::sendCommand(const byte control, const byte address, const byte data) {
  uint16_t dataToSend = control << 12 | address << 8 | data;

  SPI.beginTransaction(spi_settings);
  digitalWrite(chip_select_pin, LOW);
  uint16_t result = SPI.transfer16(dataToSend);
  digitalWrite(chip_select_pin, HIGH);
  SPI.endTransaction();
  delayMicroseconds(40);

  return result;
}

void AD5144::set_value(const size_t channel, const byte value) {
  assert(channel < channels);

  // Write contents of serial register data to RDAC
  sendCommand(1, channel, value);
}

uint16_t AD5144::get_value(const size_t channel) {
  assert(channel < channels);

  // read back contents of RDAC
  sendCommand(3, channel, 3);
  const uint16_t result = sendCommand(0, 0, 0);

  return result;
}
