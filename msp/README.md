# MSP Module Manual

Please refer to this guide to add components to this MSP project.

## Project Structure

- [] `msp`
  - `main.c`: do not modify this
  - `mods.h`: contains data structures for the modules
  - `utils.h`: header file for utils
  - `utils.c`: implementation of utils functions, like `hw__setup`
  - [] `[[module_name]]`: a module
    - `[[module_name]].h`: this file will be included inside `mods.h` and there you can register your module, for setups, interrupts, ecc.
    Try to using the following naming convention:
        - `setup__[[module_name]]` for the setup function (eg. `void seupt__display()`)
        - `interrupt_[[interrupt]]__[[module_name]]` for interrupts (eg: for calling the `TA1_0_IRQHandler` for the module `display` call the function `interrupt_TA1_0__display`)
    - `other_file.h`: other header file
    - `other_file.c`: other source file
    - `...`

## Adding a module
Modify the `msp/mods.h` registering the components of your module:
- Add the setup function to the `SETUPS` array and don't forget to increment `N_SETUPS`
- Add your interrupts functions to the `INTERRUPT_[[interrupt_name]]` array and don't forget to increment `N_INTERRUPT_[[interrupt_name]]`
    - If you need to register a non-existing interrupt you have to:
        - Add these lines to `msp/mods.h`
        ```c
        #define N_INTERRUPT_[[interrupt_name]] 1` to `msp/mods.h`
        void (*INTERRUPT_[[interrupt_name]][N_INTERRUPT_[[interrupt_name]]])(void) = {
            interrupt_[[interrupt_name]]__[[module_name]],
        };
        ```
        - Add these lines to `msp/main.c`
        ```c
        void [[interrupt_name]]_IRQHandler(void) {
            int i = 0;
            for(; i < N_[[interrupt_name]]; i++) {
                INTERRUPT_[[interrupt_name]][i]();
            }
        }
        ```
