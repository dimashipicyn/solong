//
//  command.c
//
//  Created by Dmitry Shipicyn on 11.07.2022.
//

#include "command.h"

t_command command(void (*execute)(t_entity* entity))
{
    return (t_command){execute};
}

void command_execute(t_command command, t_entity* entity, t_game_ctx* game_ctx)
{
    if (command.execute) {
        command.execute(entity, game_ctx);
    }
}
