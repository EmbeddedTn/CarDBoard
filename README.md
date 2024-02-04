# Car Dashboard
Final project for Embedded Systems for the Internet of Things  [UniTn - 145996]

## Idea
Car Dashboard with speed indicator, street sign and speed limit display.
Future idea -> parking sensors

## TODO:
  - prototype all functions (in header files) to avoid _promotion to ints_ for smaller types
  - add informative function comments to the header files
  - contol that the code is using the smallest data types to optimize memory 
  - correctly use _volatile_ keyword for certain global variables

### Libraries 
- LVGL
- TinyGPS++
- ArduinoJSON
- ...

### Useful documentation
- [DriverLib](https://schaumont.dyn.wpi.edu/ece4703b21/_downloads/7a8fc22c23fd2706dfd4d3f5256fad98/msp432-driverlib-user.pdf)
- [Joystick](https://www.ti.com/lit/ug/slau599b/slau599b.pdf?ts=1698864546827&ref_url=https%253A%252F%252Fwww.ti.com%252Ftool%252FBOOSTXL-EDUMKII)
- [Reverse Geocoding for OpenStreetMap](https://nominatim.org/release-docs/develop/api/Reverse/)

### Authors
- [Lorenzo Bodini](mailto:lorenzo.bodini@studenti.unitn.it?subject=Embedded-project-infos)
- [Filippo De Grandi](mailto:filippo.degrandi@studenti.unitn.it?subject=Embedded-project-infos)
- [Lorenzo Pattaro Zonta](mailto:lorenzo.pattarozonta@studenti.unitn.it?subject=Embedded-project-infos)
- [Elia Zonta](mailto:elia.zonta@studenti.unitn.it?subject=Embedded-project-infos)
