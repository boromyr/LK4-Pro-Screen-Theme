# DWIN_LK4Pro

Screen firmware for Longer LK4 Pro. should also work with Alfawise U30 although the boot screen has the Longer3D logo.
I did not test with the LK5 Pro. Since this is a similar printer as the LK4 Pro except for print dimensions, it may work also.

Only use this screen firmware with this version of Marlin https://github.com/boromyr/LK4-Pro-Screen-Theme or https://github.com/Guizz27/Marlin---Longer-LKx-Pro

## Changelog
Theme edited from https://github.com/Guizz27/DWIN_LK4Pro

* Theme inspired by the original Longer firmware
* New keypad and numpad
* Startup screen with skip button (in case of problems)
* Button to switch between Home screen and Home Print screen (in case of problems)
* Fix Z Offset print page 
* Fix extrude/retract buttons
## Download

https://github.com/boromyr/LK4-Pro-Screen-Theme/releases

# Preview 

![001_home272](https://user-images.githubusercontent.com/52782032/156930812-2c2157cc-cee3-4fab-a1b5-a3e259dafb8a.png)
![003_print_status272](https://user-images.githubusercontent.com/52782032/156930813-39da71b4-aa50-461c-a6d2-c54d78865e86.png)
![202_popup_numpad272](https://user-images.githubusercontent.com/52782032/156930811-4f34eeb2-7c7d-4967-85b1-d54340977064.png)

Color verson(beta):

![001_home480](https://user-images.githubusercontent.com/52782032/158834482-6bc6a0cf-6e39-4983-85ac-fb2f22715fe0.png)
![003_print_status480](https://user-images.githubusercontent.com/52782032/158834418-9d229a9e-1a0c-47e4-a42c-405ef9043731.png)
![009_settings_menu480](https://user-images.githubusercontent.com/52782032/158834466-86a0fc53-c496-4529-8cb9-04ea223434c6.png)


# Installation
Below you will find brief installation instructions for the screen firmware. 
Baddflash write a more detailed instructions that also covers the installation of the printer firmware. Take a look here: https://github.com/Baddflash/LK4-Pro-Firmware-Tutorial

**To update the screen firmware you need to use a SD card 32GB or less formatted with FAT32 and 4096 bytes allocation units**

## How to install
1. Use a pre-built version from the release page https://github.com/boromyr/DWIN_LK4Pro/releases.
2. In the Assets section, download the DWIN_SET.zip
3. Unzip it into a folder called DWIN_SET and copy it in the root of a SD card.
4. Make sure the printer is turned off
5. Insert the SD card in the screen SD card slot. You need to disassemble the screen mounting frame to access the card slot
6. Turn on the printer
7. Wait for the update to complete. It will say "end" when it's done
8. Turn off the printer and remove the SD card.
9. Turn the printer on, you should have the new screen.

**Very important**, the printer firmware also has to be updated.

## How to build
Follow these steps if you prefer to use the source files instead of the already prepared DWIN_SET.zip from the release page.
1. Execute BuildRelease.bat.
2. This creates a folder called "Release" with a subfolder "DWIN_SET".
3. Copy this DWIN_SET folder on the SD card then
4. Make sure the printer is turned off
5. Insert the SD card in the screen SD card slot. You need to disassemble the screen mounting frame to access the card slot
6. Turn on the printer
7. Wait for the update to complete. It will say "end" when it's done
8. Turn off the printer and remove the SD card.
9. Turn the printer on, you should have the new screen.

# Disclaimer
You use this firmware at your own risk and I am not responsible for damages it may cause.

# Credits
Keyboard and numpad from https://github.com/CR6Community/CR-6-touchscreen
