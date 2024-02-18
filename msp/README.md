# MSP Module Manual

Please refer to this guide to add components to this MSP project.

## Project Structure

- [] `msp`
  - `main.c`: do not modify this
  - `mods.h`: contains data structures for the modules
  - `utils.h`: header file for utils
  - `utils.c`: implementation of utils functions, like `hw__setup`
  - [] `{module_name}`: a module
    - `{module_name}.h`: this file will be included inside `mods.h` and there you can register your module, for setups, interrupts, ecc.
    Try to using the following naming convention:
        - `setup__{module_name}` for the setup function (eg. `void seupt__display()`)
        - `interrupt_{interrupt}__{module_name}` for interrupts (eg: for calling the `TA1_0_IRQHandler` for the module `display` call the function `interrupt_TA1_0__display`)
    - `other_file.h`: other header file
    - `other_file.c`: other source file
    - `...`

## Adding a module
Modify the `msp/mods.h` registering the components of your module

an array of functions (`void (*SETUPS[N_SETUPS])(void)`), that will be executed **in order** during the first phase of the program. Keep the function `hw__setup` as first one, as it disables the watchdog and does somo other low level stuff.
