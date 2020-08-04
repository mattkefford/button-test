/*
 * version.h
 *
 *  Created on: 4 Aug 2020
 *      Author: Kefford
 */

#ifndef INC_VERSION_H_
#define INC_VERSION_H_

#define C_SW_VER_MAJOR        2
#define C_SW_VER_MINOR        0
#define C_SW_VER_REVISION     0

#define C_HW_VER_MAJOR        2
#define C_HW_VER_MINOR        0

void version_get_info(uint8_t * pBuff, uint8_t len);

#endif /* INC_VERSION_H_ */
