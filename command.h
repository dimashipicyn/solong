//
//  command.h
//
//  Created by Dmitry Shipicyn on 11.07.2022.
//

#ifndef command_h
#define command_h

#include <stdint.h>

typedef struct s_command
{
    int8_t forw;
    int8_t back;
    int8_t left;
    int8_t right;
    int8_t fire;
} t_command;

t_command command();

#endif /* command_h */
