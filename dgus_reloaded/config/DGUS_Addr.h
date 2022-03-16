/**
  * Marlin 3D Printer Firmware
  * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
  *
  * Based on Sprinter and grbl.
  * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
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
  *
  */
#pragma once

constexpr uint8_t DGUS_LINE_LEN         = 32;
constexpr uint8_t DGUS_STATUS_LEN       = 32;
constexpr uint8_t DGUS_FILE_COUNT       = 5;
constexpr uint8_t DGUS_FILENAME_LEN     = 32;
constexpr uint8_t DGUS_ELLAPSED_LEN     = 15;
constexpr uint8_t DGUS_LEVEL_GRID_SIZE  = GRID_MAX_POINTS_X * GRID_MAX_POINTS_X;
constexpr uint8_t DGUS_MACHINE_LEN      = 24;
constexpr uint8_t DGUS_BUILDVOLUME_LEN  = 24;
constexpr uint8_t DGUS_VERSION_LEN      = 16;
constexpr uint8_t DGUS_PRINTTIME_LEN    = 24;
constexpr uint8_t DGUS_LONGESTPRINT_LEN = 24;
constexpr uint8_t DGUS_FILAMENTUSED_LEN = 24;
constexpr uint8_t DGUS_GCODE_LEN        = 32;

enum class DGUS_SP_Variable : uint8_t {
  X                  = 0x01,
  Y                  = 0x02,
  COLOR              = 0x03,
  Lib_ID_Font_X_Dots = 0x04, // H lid, L x size
  ALIGN_INT          = 0x05, // H: align 00=right, 01=left, 02=center L: number int digits
  DEC_MODE           =0x06,  // H: decimal number, L: mode 00=int, 01=long, 04=int64, 05=uint, 06=ulong
  UNITS              = 0x07  // H: len L: text max 11 bytes
};

enum class DGUS_SP_Text : uint8_t {
  X            = 0x01,
  Y            = 0x02,
  COLOR        = 0x03,
  BOX          = 0x04, // Xs,Ys,Xe,Ye 2 bytes each
  LEN          = 0x08,
  FONT         = 0x09, // H: font0, L: font1
  FONT_SIZE    = 0x0A, // H: X dots, L: y dots
  ENCODE       = 0x0B,
  LINE_SPACING = 0x0C  // H: spacing
};

constexpr uint8_t DGUS_SP_VARIABLE_LEN = 0x08;
constexpr uint8_t DGUS_SP_TEXT_LEN     = 0x0D;

constexpr uint16_t COLOR_WHITE = 0xFFFF;
constexpr uint16_t COLOR_GREEN = 0x07E0;

// TODO: Read these values at init
// variable display box size in dwin screen
constexpr int16_t STATUS_Filename_Box[4]    = {56, 338, 192, 12};
constexpr int16_t WAIT_Message_Line1_Box[4] = {25, 157, 224, 20};
constexpr int16_t WAIT_Message_Line2_Box[4] = {25, 183, 224, 20};
constexpr int16_t WAIT_Message_Line3_Box[4] = {25, 209, 224, 20};
constexpr int16_t WAIT_Message_Line4_Box[4] = {25, 235, 224, 20};

// DWIN DGUS variables are indexed by word. 0x0000-0x6FFFF

enum class DGUS_Addr : uint16_t {
  MESSAGE_Line1            = 0x1100, // 0x1100 - 0x111F
  MESSAGE_Line2            = 0x1120, // 0x1120 - 0x113F
  MESSAGE_Line3            = 0x1140, // 0x1140 - 0x115F
  MESSAGE_Line4            = 0x1160, // 0x1160 - 0x117F

  // READ-ONLY VARIABLES

  SCREENCHANGE             = 0x2000, // Screen change request. Data contains target screen in low byte.
  SCREENCHANGE_SD          = 0x2001, // Only change if SD card present.
  SCREENCHANGE_Idle        = 0x2002, // Only change if not printing.
  SCREENCHANGE_Printing    = 0x2003, // Only change if printing.
  SD_SelectFile            = 0x2004, // Data: file index (0-4)
  SD_Scroll                = 0x2005, // Data: DGUS_Data::Scroll
  SD_Print                 = 0x2006,
  STATUS_Abort             = 0x2007, // Popup / Data: DGUS_Data::Popup
  STATUS_Pause             = 0x2008, // Popup / Data: DGUS_Data::Popup noe resume/pause
  STATUS_Resume            = 0x2009, // Popup / Data: DGUS_Data::Popup
  ADJUST_SetFeedrate       = 0x200A, // Type: Integer (16 bits signed)
  ADJUST_SetFlowrate_CUR   = 0x200B, // Type: Integer (16 bits signed)
  #if EXTRUDERS > 1
    ADJUST_SetFlowrate_E0  = 0x200C, // Type: Integer (16 bits signed)
    ADJUST_SetFlowrate_E1  = 0x200D, // Type: Integer (16 bits signed)
  #endif
  ADJUST_SetBabystep       = 0x200E, // Type: Fixed point, 2 decimals (16 bits signed)
  ADJUST_Babystep          = 0x200F, // Data: DGUS_Data::Adjust
  TEMP_Preset              = 0x2010, // Popup / Data: DGUS_Data::TempPreset
  TEMP_SetTarget_Bed       = 0x2011, // Type: Integer (16 bits signed)
  TEMP_SetTarget_H0        = 0x2012, // Type: Integer (16 bits signed)
  #if HOTENDS > 1
    TEMP_SetTarget_H1      = 0x2013, // Type: Integer (16 bits signed)
  #endif
  TEMP_Cool                = 0x2014, // Data: DGUS_Data::Heater
  STEPPER_Control          = 0x2015, // Popup / Data: DGUS_Data::Control
  LEVEL_OFFSET_Set         = 0x2016, // Type: Fixed point, 2 decimals (16 bits signed)
  LEVEL_OFFSET_Step        = 0x2017, // Data: DGUS_Data::Adjust
  LEVEL_OFFSET_SetStep     = 0x2018, // Data: DGUS_Data::StepSize
  LEVEL_MANUAL_Point       = 0x2019, // Data: point index (1-5)
  LEVEL_AUTO_Probe         = 0x201A,
  FILAMENT_Select          = 0x201C, // Data: DGUS_Data::Extruder
  FILAMENT_SetLength       = 0x201D, // Type: Integer (16 bits unsigned)
  FILAMENT_Move            = 0x201E, // Data: DGUS_Data::FilamentMove
  MOVE_Home                = 0x201F, // Data: DGUS_Data::Axis
  MOVE_SetX                = 0x2020, // Type: Fixed point, 1 decimal (16 bits signed)
  MOVE_SetY                = 0x2021, // Type: Fixed point, 1 decimal (16 bits signed)
  MOVE_SetZ                = 0x2022, // Type: Fixed point, 1 decimal (16 bits signed)
  MOVE_Step                = 0x2023, // Data: DGUS_Data::MoveDirection
  MOVE_SetStep             = 0x2024, // Data: DGUS_Data::StepSize
  GCODE_Clear              = 0x2025,
  GCODE_Execute            = 0x2026,
  EEPROM_Control           = 0x2027, // Popup / Data: DGUS_Data::Popup
  SETTINGS2_Extra          = 0x2028, // Data: DGUS_Data::Extra
  PID_Select               = 0x2029, // Data: DGUS_Data::Heater
  PID_SetTemp              = 0x202A, // Type: Integer (16 bits unsigned)
  PID_Run                  = 0x202B,
  POWERLOSS_Abort          = 0x202C, // Popup / Data: DGUS_Data::Popup
  POWERLOSS_Resume         = 0x202D, // Popup / Data: DGUS_Data::Popup
  WAIT_Abort               = 0x202E, // Popup / Data: DGUS_Data::Popup
  WAIT_Continue            = 0x202F,
  INFOS_Screen_Version     = 0x2030, // DGUS_VERSION_LEN = 16 chars
  FILAMENT_Load_Unload     = 0x2040, // GCTODO
  RUNOUT_Control           = 0x2041, // GCTODO
  STATUS_PrintPause        = 0x2042,

  // WRITE-ONLY VARIABLES

  MESSAGE_Status           = 0x3000, // 0x3000 - 0x301F
  SD_Type                  = 0x3020, // 0x3020 - 0x3024 / Data: DGUS_Data::SDType
  SD_FileName0             = 0x3025, // 0x3025 - 0x3044
  SD_FileName1             = 0x3045, // 0x3045 - 0x3064
  SD_FileName2             = 0x3065, // 0x3065 - 0x3084
  SD_FileName3             = 0x3085, // 0x3085 - 0x30A4
  SD_FileName4             = 0x30A5, // 0x30A5 - 0x30C4
  SD_ScrollIcons           = 0x30C5, // Bits: DGUS_Data::ScrollIcon
  SD_SelectedFileName      = 0x30C6, // 0x30C6 - 0x30E5
  STATUS_Ellapsed          = 0x30E7, // 0x30E7 - 0x30F5
  STATUS_Percent           = 0x30F6, // Type: Integer (16 bits unsigned)
//  STATUS_Icons              = 0x30F7, // Bits: DGUS_Data::StatusIcon
  ADJUST_Feedrate          = 0x30F8, // Type: Integer (16 bits signed)
  ADJUST_Flowrate_CUR      = 0x30F9, // Type: Integer (16 bits signed)
  #if EXTRUDERS > 1
    ADJUST_Flowrate_E0     = 0x30FA, // Type: Integer (16 bits signed)
    ADJUST_Flowrate_E1     = 0x30FB, // Type: Integer (16 bits signed)
  #endif
  TEMP_Current_Bed         = 0x30FC, // Type: Integer (16 bits signed)
  TEMP_Target_Bed          = 0x30FD, // Type: Integer (16 bits signed)
  TEMP_Max_Bed             = 0x30FE, // Type: Integer (16 bits unsigned)
  TEMP_Current_H0          = 0x30FF, // Type: Integer (16 bits signed)
  TEMP_Target_H0           = 0x3100, // Type: Integer (16 bits signed)
  TEMP_Max_H0              = 0x3101, // Type: Integer (16 bits unsigned)
  #if HOTENDS > 1
    TEMP_Current_H1        = 0x3102, // Type: Integer (16 bits signed)
    TEMP_Target_H1         = 0x3103, // Type: Integer (16 bits signed)
    TEMP_Max_H1            = 0x3104, // Type: Integer (16 bits unsigned)
  #endif
//  STEPPER_Status            = 0x3105, // Data: DGUS_Data::Status
  LEVEL_OFFSET_Current     = 0x3106, // Type: Fixed point, 2 decimals (16 bits signed)
  LEVEL_OFFSET_StepIcons   = 0x3107, // Bits: DGUS_Data::StepIcon
  STATUS_PositionZ         = 0x3108, // Long 2 Words 0x3108-0x3109  old value 0x30E6, // Type: Fixed point, 1 decimal (16 bits signed)
//  LEVEL_AUTO_DisableIcon    = 0x3108, // Data: DGUS_Data::Status
//  LEVEL_AUTO_Grid           = 0x3109, // 0x3109 - 0x3121 / Type: Fixed point, 3 decimals (16 bits signed)
  // LEVEL_PROBING_Icons1      = 0x3122, // Type: Integer (16 bits unsigned) / Each bit represents a grid point
  // LEVEL_PROBING_Icons2      = 0x3123, // Type: Integer (16 bits unsigned) / Each bit represents a grid point
  FILAMENT_ExtruderIcons   = 0x3124, // Data: DGUS_Data::ExtruderIcon
  FILAMENT_Length          = 0x3125, // Type: Integer (16 bits unsigned)
  MOVE_CurrentX            = 0x3126, // Type: Fixed point, 1 decimal (16 bits signed)
  MOVE_CurrentY            = 0x3127, // Type: Fixed point, 1 decimal (16 bits signed)
  MOVE_CurrentZ            = 0x3128, // Type: Fixed point, 1 decimal (16 bits signed)
  MOVE_StepIcons           = 0x3129, // Bits: DGUS_Data::StepIcon
  SETTINGS2_BLTouch        = 0x312A, // Data: DGUS_Data::Status
  PID_HeaterIcons          = 0x312B, // Data: DGUS_Data::HeaterIcon
  PID_Temp                 = 0x312C, // Type: Integer (16 bits unsigned)
  PID_Kp                   = 0x312D, // Type: Fixed point, 2 decimals (32 bits signed)
  PID_Ki                   = 0x312F, // Type: Fixed point, 2 decimals (32 bits signed)
  PID_Kd                   = 0x3131, // Type: Fixed point, 2 decimals (32 bits signed)
  INFOS_Machine            = 0x3133, // 0x3133 - 0x314A
  INFOS_BuildVolume        = 0x314B, // 0x314B - 0x3162
  INFOS_Version            = 0x3163, // 0x3163 - 0x3172
  INFOS_TotalPrints        = 0x3173, // Type: Integer (16 bits unsigned)
  INFOS_FinishedPrints     = 0x3174, // Type: Integer (16 bits unsigned)
  INFOS_PrintTime          = 0x3175, // 0x3175 - 0x318C
  INFOS_LongestPrint       = 0x318D, // 0x318D - 0x31A4
  INFOS_FilamentUsed       = 0x31A5, // 0x31A5 - 0x31BC
  WAIT_Icons               = 0x31BD, // Bits: DGUS_Data::WaitIcon
  STATUS_Feedrate_MMS      = 0x31BF,
  FAN0_Speed_CUR           = 0x31C1,
  MOVE_CurrentE            = 0x31C3, // Type: Fixed point, 1 decimal (16 bits signed)
  STATUS_Pause_Resume_Icon = 0x31C5, // 1 byte 0: resume, 1: pause
  LEVEL_AUTO_Grid          = 0x31C6, // 0x31C6 - 0x31DE / Type: Fixed point, 3 decimals (16 bits signed)


  // READ-WRITE VARIABLES

  FAN0_Speed               = 0x4000, // Type: Integer (16 bits unsigned) / Data: fan speed as percent (0-100)
  GCODE_Data               = 0x4001, // 0x4001 - 0x4020
  PID_Cycles               = 0x4021, // Type: Integer (16 bits unsigned)
  VOLUME_Level             = 0x4022, // Type: Integer (16 bits unsigned) / Data: volume as percent (0-100)
  BRIGHTNESS_Level         = 0x4023, // Type: Integer (16 bits unsigned) / Data: brightness as percent (0-100)
  X_Steps_mm               = 0x4025, // long: 4.2
  Y_Steps_mm               = 0x4029, // long : 4.2
  X_Jerk_Steps_mm          = 0x402D, // int: 3.1
  Y_Jerk_Steps_mm          = 0x402F, // int: 3.1
  Z_Jerk_Steps_mm          = 0x4031, // int: 3.1
  E_Jerk_Steps_mm          = 0x4033, // int: 3.1
  JunctionDeviation        = 0x4035, // int: 1.3
  Linear_Advance           = 0x4037, // int: 2.2
  X_Acceleration           = 0x4039, // int: 4.0
  Y_Acceleration           = 0x403B, // int: 4.0
  Z_Acceleration           = 0x403D, // int: 4.0
  E_Acceleration           = 0x403F, // int: 4.0
  Print_Acceleration       = 0x4041, // int: 4.0
  Retract_Acceleration     = 0x4043, // int: 4.0
  Travel_Acceleration      = 0x4045, // int: 4.0
  X_Max_Speed              = 0x4047, // int 4.0
  Y_Max_Speed              = 0x4049, // int 4.0
  Z_Max_Speed              = 0x404B, // int 4.0
  E_Max_Speed              = 0x404D, // int 4.0
  Min_Speed                = 0x404F, // int 3.1
  Min_Travel_Speed         = 0x4051, // int 3.1
  Z_Steps_mm               = 0x4053, // long 4.2
  E_Steps_mm               = 0x4057, // long 4.2


  // SPECIAL CASES

  STATUS_Percent_Complete  = 0x5000, // Same as STATUS_Percent, but always 100%
  INFOS_Debug              = 0x5001,

  // Display properties
  SP_LEVEL_AUTO_Grid       = 0x6000, // 8 * 25 = 200, 0x6000-0x60C7
  SP_SD_FileName0          = 0x60C8, // 13 * 5 = 65, 0x60C8-0x6108
  SP_STATUS_Filename       = 0x6109, // 13 0x6109-0x6115
  SP_MSG_LINE1             = 0x6116, // 13 0x6116-0x6122
  SP_MSG_LINE2             = 0x6123, // 13 0x6123-0x612F
  SP_MSG_LINE3             = 0x6130, // 13 0x6130-0x613C
  SP_MSG_LINE4             = 0x613D  // 13 0x613D-0x6149

};
