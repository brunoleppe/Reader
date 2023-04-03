//
// Created by bleppe on 03/04/23.
//

#ifndef SST26_H
#define SST26_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "gpio.h"

#define     MAX_WRITE_BUFFER    256 ///<Máxima cantidad de bytes que pueden ser escritos en una operación

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Tipo de memoria usada.
 * Las memorias flash comparten comandos, por lo que se puede usar otra memoria
 * compatible.
 */
typedef enum{
    Microchip = 0xBF,  ///< Memoria de Microchip
    ISSI,           ///< Memoria de ISSI
}MEM_TYPE;

typedef struct{
    uint8_t mID;  ///< ID del fabricante
    uint8_t memType;   ///< Tipo de memoria
    uint8_t memID; ///< ID de la memoria
}__attribute__((packed))FlashMemID;

// <editor-fold defaultstate="collapsed" desc="COMANDOS ">
/**
 * Lista de comandos de la memoria
 */
enum SST26_Commands{
    /*Comandos de configuración*/
    NOP     = 0,
    RSTEN   = 0x66,
    RST     = 0x99,
    EQIO    = 0x38,
    RSTQIO  = 0xFF,
    RDSR    = 0x05,
    WRSR    = 0x01,
    RDCR    = 0x35,
    /*Comandos de lectura*/
    READ    = 0x03,
    HSREAD  = 0x0B,
    SQOR    = 0x6B,
    SQIOR   = 0xEB,
    SDOR    = 0x3B,
    SDIOR   = 0xBB,
    SB      = 0xC0,
    RBSQI   = 0x0C,
    RBSPI   = 0xEC,
    /*Comandos de identificación*/
    JEDEC   = 0x9F,
    J_ID    = 0xAF,
    SFPD    = 0xEC,
    /*Comandos de Escritura*/
    WREN    = 0x06,
    WRDI    = 0x04,
    SE      = 0x20,
    BE      = 0xD8,
    CE      = 0xC7,
    PP      = 0x02,
    QPP     = 0x32,
    WRSU    = 0xB0,
    WRRE    = 0x30,
    /*Comandos de protección de memoria*/
    RBPR    = 0x72,
    WBPR    = 0x42,
    LBPR    = 0x8D,
    nVWLDR  = 0xE8,
    ULBPR   = 0x98,
    RSID    = 0x88,
    PSID    = 0xA5,
    LSID    = 0x85,

};
// </editor-fold>
/**
 * Inicialización del driver.
 * @param spi Puntero a una estructura que representa la interfaz de un puerto SPI.
 */
void sst26_initialize(uint32_t spiDriverIndex, GPIO_PinMap ssPin);
/**
 * Obtiene el JEDEC ID de la memoria flash.
 * @return estructura de un JEDEC ID.
 */
FlashMemID* sst26_read_id();
/**
 * Escribe un buffer datos de cierta longitud en una dirección de memoria.
 * @param data buffer de datos.
 * @param length cantidad de bytes a escribir.
 * @param address dirección de memoria en la que se va a escribir.
 * @return verdadero si la escritura fue exitosa, falso si no.
 */
bool sst26_write(void* data, int length, unsigned int address);
/**
 * Lee una cantidad de datos de la dirección de memoria y los escribe en el buffer especificado.
 * @param data buffer en el que se escribirán los datos.
 * @param length longitud de datos que se van a leer.
 * @param address dirección de memoria de la cual se obtendrán los datos.
 * @return verdadero si la lectura fue exitosa, falso si no.
 */
bool sst26_read(void* data, int length, unsigned int address);

/**
 * Retorna el tipo de memoria que se encuentra en el dispositivo.
 * @return MEM_TYPE tipo de memoria.
 */
MEM_TYPE sst26_get_type();

#ifdef	__cplusplus
}
#endif

#endif //SST26_H
