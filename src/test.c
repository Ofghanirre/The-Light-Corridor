#include "test.h"

void d() {
    printf("Obstacles : %d <> last : %p\n", scenery.obstacles.size, scenery.obstacles.tail);
    Node* iter = scenery.obstacles.head;
    while (iter != NULL) {
        printf("%p ->", (void*) iter);
        iter = iter->next;
    }
    printf("\n\n");

    // printf("Bonus : %d <> last : %p\n", scenery.bonus_amount, scenery.last_bonus);
    // iter = scenery.bonus_list;
    // while (iter != NULL) {
    //     printf("%p ->", (void*) iter);
    //     iter = iter->next;
    // }
    // printf("\n\n");
}

void test_scenery() {
    printf("=== Scenery Initialisation ===\n");
    scenery_init();
    //scenery_append_obstacle(new_ball());
    //scenery_append_obstacle(new_ball());
    printf("=== Added 2 Elems ===\n");
    d();

    scenery_remove_first_obstacle();
    printf("=== Removed 1 Elems ===\n");
    d();
    //scenery_append_obstacle(new_ball());
    //scenery_append_obstacle(new_ball());
    printf("=== Added 2 Elems ===\n");
    d();
    scenery_clear();
    printf("=== Scenery Clear ===\n");
    d();
    /*int result = scenery_append_obstacle(new_ball());
    printf("%d\n", result);
    if (result == -1) printf("Can not add on unitialized scenery !\n");*/

    scenery_init();
    printf("=== Scenery reInitialisation ===\n");
    

    d();
    scenery_clear();
    exit(EXIT_SUCCESS);
}