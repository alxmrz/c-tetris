#include "element.h"
#include "configuration.h"
#include "event.h"
#include "game.h"
#include "graphics.h"

int main(int argc, char **args) {
    View *view = create_view();
    if (view == NULL) {
        return ERROR_CODE;
    }

    Game *game = create_new_game();
    if (game == NULL) {
        delete_view(view);

        return ERROR_CODE;
    }

    while (game->is_running) {
        update_game(game);
        handle_events(game);

        if (game->is_restart_needed) {
            delete_game(game);
            game = create_new_game();
        }

        render_view(view, game);

        delay_game(game);
    }

    delete_game(game);
    delete_view(view);

    return SUCCESS_CODE;
}
