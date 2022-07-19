//
//  command.h
//
//  Created by Dmitry Shipicyn on 11.07.2022.
//

#ifndef command_h
#define command_h

#include "entity.h"
#include <stdint.h>

typedef struct s_command
{
    void (*execute)(t_entity* entity, t_game_ctx* game_ctx);
} t_command;

t_command command(void (*execute)(t_entity* entity));
void command_execute(t_command command, t_entity* entity, t_game_ctx* game_ctx);

#endif /* command_h */
