/*
 * version.c
 *
 *  Created on: 4 Aug 2020
 *      Author: Kefford
 */

#include <stdio.h>
#include "version.h"

const uint8_t boardName[30] = "Thorvald Main PCB";

static uint8_t product_name_to_buffer(uint8_t * pBuff, uint8_t buffSize);
static uint8_t sw_ver_to_buffer(uint8_t * pBuff, uint8_t buffSize);
static uint8_t hw_ver_to_buffer(uint8_t * pBuff, uint8_t buffSize);



void version_get_info(uint8_t * pBuff, uint8_t len)
{
  uint8_t buffSizeRemaining   = len;
  uint8_t bytesWritten        = 0;
  uint8_t writePosition       = 0;

  bytesWritten = product_name_to_buffer(pBuff, buffSizeRemaining);

  buffSizeRemaining -= bytesWritten;
  writePosition += bytesWritten;

  bytesWritten = sw_ver_to_buffer(&pBuff[writePosition], buffSizeRemaining);

  buffSizeRemaining -= bytesWritten;
  writePosition += bytesWritten;

  bytesWritten = hw_ver_to_buffer(&pBuff[writePosition], buffSizeRemaining);

  buffSizeRemaining -= bytesWritten;
  writePosition += bytesWritten;
}



static uint8_t product_name_to_buffer(uint8_t * pBuff, uint8_t buffSize)
{
  char format[] = "%s - ";
  return snprintf((char *)pBuff, buffSize, format, boardName);
}

static uint8_t sw_ver_to_buffer(uint8_t * pBuff, uint8_t buffSize)
{
  char format[] = "SW v%i.%i.%i - ";
  return snprintf((char *)pBuff, buffSize, format, C_SW_VER_MAJOR, C_SW_VER_MINOR, C_SW_VER_REVISION);
}

static uint8_t hw_ver_to_buffer(uint8_t * pBuff, uint8_t buffSize)
{
  char format[] = "HW v%i rev%i ";
  return snprintf((char *)pBuff, buffSize, format, C_HW_VER_MAJOR, C_HW_VER_MINOR);
}


