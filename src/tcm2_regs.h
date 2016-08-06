/*
TCM2lib - MPico TCS gen2 E-ink arduino driver
Copyright (C) 2016  OXullo Intersecans <x@brainrapers.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TCM2_REGS_H
#define TCM2_REGS_H


// Response codes
#define EP_SW_NORMAL_PROCESSING             0x9000
#define EP_SW_WRONG_LENGTH                  0x6700
#define EP_FRAMEBUFFER_SLOT_NOT_AVAILABLE   0x6981
#define EP_SW_INVALID_LE                    0x6c00
#define EP_SW_WRONG_PARAMETERS_P1P2         0x6a00
#define EP_FRAMEBUFFER_SLOT_OVERRUN         0x6a84
#define EP_SW_INSTRUCTION_NOT_SUPPORTED     0x6d00
#define EP_SW_GENERAL_ERROR                 0x6f00

// Commands chrunch the INS and P1 bytes together
// since they're always constant
#define CMD_UPLOAD_IMAGE_DATA               0x2001
#define CMD_GET_IMAGE_DATA                  0xa000
#define CMD_GET_CHECKSUM                    0x2e01
#define CMD_RESET_DATA_POINTER              0x200d
#define CMD_IMAGE_ERASE_FRAME_BUFFER        0x200e
#define CMD_UPLOAD_IMAGE_SET_ROI            0x200a
#define CMD_UPLOAD_IMAGE_FIX_VAL            0x200b
#define CMD_UPLOAD_IMAGE_COPY_SLOTS         0x200c
#define CMD_DISPLAY_UPDATE_DEFAULT          0x2401
#define CMD_DISPLAY_UPDATE_FLASHLESS        0x8501
#define CMD_DISPLAY_UPDATE_FLASHLESS_INV    0x8601
#define CMD_GET_DEVICE_INFO                 0x3001
#define CMD_GET_DEVICE_ID                   0x3002
#define CMD_GET_SYSTEM_INFO                 0x3101
#define CMD_GET_SYSTEM_VERSION_CODE         0x3102
#define CMD_GET_SENSOR_DATA                 0xe501

#endif
