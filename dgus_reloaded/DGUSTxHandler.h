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

#include "DGUSDisplay.h"
#include "definition/DGUS_VP.h"

namespace DGUSTxHandler {

  #if ENABLED(SDSUPPORT)
    void SetFileControlState(int, bool);
    void FileType(DGUS_VP &);
    void FileName(DGUS_VP &);
    void ScrollIcons(DGUS_VP &);
    void SelectedFileName(DGUS_VP &);
    void SelectedFileNameFormat(DGUS_VP &);
  #endif

  void PositionZ(DGUS_VP &);
  void Ellapsed(DGUS_VP &);
  void Percent(DGUS_VP &);
  void StatusIcons(DGUS_VP &);

  void Flowrate(DGUS_VP &);
  void FeedrateMMS(DGUS_VP &);

  void TempMax(DGUS_VP &);

  void StepperStatus(DGUS_VP &);

  void StepIcons(DGUS_VP &);

  void ABLDisableIcon(DGUS_VP &);
  void ABLGrid(DGUS_VP &);
  void ABLGridColor(DGUS_VP &);

  void FilamentIcons(DGUS_VP &);

  void BLTouch(DGUS_VP &);

  void PIDIcons(DGUS_VP &);
  void PIDKp(DGUS_VP &);
  void PIDKi(DGUS_VP &);
  void PIDKd(DGUS_VP &);

  void BuildVolume(DGUS_VP &);
  void TotalPrints(DGUS_VP &);
  void FinishedPrints(DGUS_VP &);
  void PrintTime(DGUS_VP &);
  void LongestPrint(DGUS_VP &);
  void FilamentUsed(DGUS_VP &);

  void WaitIcons(DGUS_VP &);

  void FanSpeed(DGUS_VP &);

  void Volume(DGUS_VP &);

  void Brightness(DGUS_VP &);

  void StepsPerMmX(DGUS_VP &);
  void StepsPerMmY(DGUS_VP &);
  void StepsPerMmZ(DGUS_VP &);
  void StepsPerMmE(DGUS_VP &);
  void JerkStepsMmX(DGUS_VP &);
  void JerkStepsMmY(DGUS_VP &);
  void JerkStepsMmZ(DGUS_VP &);
  void JerkStepsMmE(DGUS_VP &);
  void JunctionDeviation(DGUS_VP &);
  void LinearAdvance(DGUS_VP &);
  void AccelerationX(DGUS_VP &);
  void AccelerationY(DGUS_VP &);
  void AccelerationZ(DGUS_VP &);
  void AccelerationE(DGUS_VP &);
  void AccelerationPrint(DGUS_VP &);
  void AccelerationRetract(DGUS_VP &);
  void AccelerationTravel(DGUS_VP &);
  void MaxFeedRateX(DGUS_VP &);
  void MaxFeedRateY(DGUS_VP &);
  void MaxFeedRateZ(DGUS_VP &);
  void MaxFeedRateE(DGUS_VP &);
  void MinPrintFeedRate(DGUS_VP &);
  void MinTravelFeedRate(DGUS_VP &);

  void ExtraToString(DGUS_VP &);
  void ExtraPGMToString(DGUS_VP &);

  template<typename T>
  void ExtraToInteger(DGUS_VP &vp) {
    if (!vp.size || !vp.extra) return;
    switch (vp.size) {
      default: return;
      case 1: {
        const uint8_t data = (uint8_t)(*(T *)vp.extra);
        dgus_display.Write((uint16_t)vp.addr, data);
        break;
      }
      case 2: {
        const uint16_t data = (uint16_t)(*(T *)vp.extra);
        dgus_display.Write((uint16_t)vp.addr, Swap16(data));
        break;
      }
      case 4: {
        const uint32_t data = (uint32_t)(*(T *)vp.extra);
        dgus_display.Write((uint16_t)vp.addr, dgus_display.SwapBytes(data));
        break;
      }
    }
  }

  template<typename T, uint8_t decimals>
  void ExtraToFixedPoint(DGUS_VP &vp) {
    if (!vp.size || !vp.extra) return;
    switch (vp.size) {
      default: return;
      case 1: {
        const uint8_t data = dgus_display.ToFixedPoint<T, uint8_t, decimals>(*(T *)vp.extra);
        dgus_display.Write((uint16_t)vp.addr, data);
        break;
      }
      case 2: {
        const uint16_t data = dgus_display.ToFixedPoint<T, uint16_t, decimals>(*(T *)vp.extra);
        dgus_display.Write((uint16_t)vp.addr, Swap16(data));
        break;
      }
      case 4: {
        const uint32_t data = dgus_display.ToFixedPoint<T, uint32_t, decimals>(*(T *)vp.extra);
        dgus_display.Write((uint16_t)vp.addr, dgus_display.SwapBytes(data));
        break;
      }
    }
  }

}
