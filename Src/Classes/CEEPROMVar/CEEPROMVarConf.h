/*
 * CEEPROMVarConf.h
 *
 *  Created on: 11-03-2013
 *      Author: sporysz
 */

#ifndef CEEPROMVARCONF_H_
#define CEEPROMVARCONF_H_


/**
 * @brief Zmienne definiują rozmiar i położenie bloku w pamięci EEPROM zarzązanego przez klasy CEEPROMVar i CEEPROMArr.
 *
 * Plik powininen być umieszczony w katalogu projektu.
 */
namespace CEEPROMVarConf
{
/**
 * @brief Początkowy adres bloku.
 */
const uint32_t EEPROM_MANAGED_BLOCK_START = 0;

/**
 * @brief Końcowy adres bloku.
 */
const uint32_t EEPROM_MANAGED_BLOCK_END = 8191;
}  // namespace CEEPROMVarConf


#endif /* CEEPROMVARCONF_H_ */
