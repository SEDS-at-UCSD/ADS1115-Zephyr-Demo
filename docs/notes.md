## Aldrin's Notes 
- in app/pcu.cpp all global variables can be moved to main.cpp to keep track of all of them
- the noise of the FUEL flow rate is not accounted for in the LOX algorithm
    - ![](temp_noNoiseForFuelInLox.png)
- password in HEX in CAN uint32_t format
    - 7BBE0000
- for p_ccmd
    - https://gregstoll.com/~gregstoll/floattohex/


## How to use Hardware-in-the-loop feature/hardware-loop
- UART
    - "p_c:#####.####\n" (must have 4 digit after decimal dot)
    - "lng_w:#####.####\n" (must have 4 digit after decimal dot)
    - "lox_w:#####.####\n" (must have 4 digit after decimal dot)
- CAN into teensy
    - FSM:::  ID: 0x11000000  DATA: ##0000007BBE0000 (7BBE0000 is the password to 48763) (## is the extInput into FSM)
    - P_ccmd:::  ID: 0x12000000  DATA: ################ (double)
        - https://gregstoll.com/~gregstoll/floattohex/
        - h1 h2 h3 h4 ... h13 h14 h15 h16
        - h15 h16 h13 h14 ... h3 h4 h1 h2
- teensy out to CAN
    - LNG:::   ID: 0x445      DATA: ################ (double)
    - LOX:::   ID: 0x444      DATA: ################ (double)

## Aldrin's Todo
- regenerate final pass of simulink algorithms
- rename all the enum to follow the format kStateName