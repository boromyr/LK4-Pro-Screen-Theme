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

namespace DGUSRxHandler {

  void ScreenChange(DGUS_VP &, void *);

  #if ENABLED(SDSUPPORT)
    void Scroll(DGUS_VP &, void *);
    void SelectFile(DGUS_VP &, void *);
    void PrintFile(DGUS_VP &, void *);
  #endif

  void PrintAbort(DGUS_VP &, void *);
  void PrintPause(DGUS_VP &, void *);
  void PrintResume(DGUS_VP &, void *);
  void PrintPauseResume(DGUS_VP &, void *);

  void Feedrate(DGUS_VP &, void *);
  void Flowrate(DGUS_VP &, void *);
  void BabystepSet(DGUS_VP &, void *);
  void Babystep(DGUS_VP &, void *);

  void TempPreset(DGUS_VP &, void *);
  void TempTarget(DGUS_VP &, void *);
  void TempCool(DGUS_VP &, void *);

  void Steppers(DGUS_VP &, void *);
  void RunoutControl(DGUS_VP &, void *);
  #if HAS_LEVELING
    void ZOffset(DGUS_VP &, void *);
    void ZOffsetStep(DGUS_VP &, void *);
    void ZOffsetSetStep(DGUS_VP &, void *);
  #endif
  void MoveToPoint(DGUS_VP &, void *);

  #if HAS_LEVELING
    void Probe(DGUS_VP &, void *);
  #endif

  void FilamentSelect(DGUS_VP &, void *);
  void FilamentLength(DGUS_VP &, void *);
  void FilamentMove(DGUS_VP &, void *);
  void FilamentLoadUnload(DGUS_VP &vp, void *data_ptr);

  void Home(DGUS_VP &, void *);
  void Move(DGUS_VP &, void *);
  void MoveStep(DGUS_VP &, void *);
  void MoveSetStep(DGUS_VP &, void *);

  void GcodeClear(DGUS_VP &, void *);
  void GcodeExecute(DGUS_VP &, void *);

  void EEPROMControl(DGUS_VP &, void *);

  void SettingsExtra(DGUS_VP &, void *);

  void PIDSelect(DGUS_VP &, void *);
  void PIDSetTemp(DGUS_VP &, void *);
  void PIDRun(DGUS_VP &, void *);

  #if ENABLED(POWER_LOSS_RECOVERY)
    void PowerLossAbort(DGUS_VP &, void *);
    void PowerLossResume(DGUS_VP &, void *);
  #endif

  void WaitAbort(DGUS_VP &, void *);
  void WaitContinue(DGUS_VP &, void *);

  void FanSpeed(DGUS_VP &, void *);

  void Volume(DGUS_VP &, void *);

  void Brightness(DGUS_VP &, void *);

  void StepsPerMmX(DGUS_VP &, void *);
  void StepsPerMmY(DGUS_VP &, void *);
  void StepsPerMmZ(DGUS_VP &, void *);
  void StepsPerMmE(DGUS_VP &, void *);
  void JerkStepsMmX(DGUS_VP &, void *);
  void JerkStepsMmY(DGUS_VP &, void *);
  void JerkStepsMmZ(DGUS_VP &, void *);
  void JerkStepsMmE(DGUS_VP &, void *);
  void JunctionDeviation(DGUS_VP &, void *);
  void LinearAdvance(DGUS_VP &, void *);
  void AccelerationX(DGUS_VP &, void *);
  void AccelerationY(DGUS_VP &, void *);
  void AccelerationZ(DGUS_VP &, void *);
  void AccelerationE(DGUS_VP &, void *);
  void AccelerationPrint(DGUS_VP &, void *);
  void AccelerationRetract(DGUS_VP &, void *);
  void AccelerationTravel(DGUS_VP &, void *);
  void MaxFeedRateX(DGUS_VP &, void *);
  void MaxFeedRateY(DGUS_VP &, void *);
  void MaxFeedRateZ(DGUS_VP &, void *);
  void MaxFeedRateE(DGUS_VP &, void *);
  void MinPrintFeedRate(DGUS_VP &, void *);
  void MinTravelFeedRate(DGUS_VP &, void *);

  void Debug(DGUS_VP &, void *);

  void StringToExtra(DGUS_VP &, void *);

  template<typename T>
  void IntegerToExtra(DGUS_VP &vp, void *data_ptr) {
    if (!vp.size || !vp.extra) return;
    switch (vp.size) {
      default: return;
      case 1: {
        const uint8_t data = *(uint8_t *)data_ptr;
        *(T *)vp.extra = (T)data;
        break;
      }
      case 2: {
        const uint16_t data = Swap16(*(uint16_t *)data_ptr);
        *(T *)vp.extra = (T)data;
        break;
      }
      case 4: {
        const uint32_t data = dgus_display.SwapBytes(*(uint32_t *)data_ptr);
        *(T *)vp.extra = (T)data;
        break;
      }
    }
  }

}
