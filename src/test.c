#include "test.h"

// void d() {
//     printf("Obstacles : %d <> last : %p\n", level.obstacles.size, level.obstacles.tail);
//     Node* iter = level.obstacles.head;
//     while (iter != NULL) {
//         printf("%p ->", (void*) iter);
//         iter = iter->next;
//     }
//     printf("\n\n");

//     // printf("Bonus : %d <> last : %p\n", level.bonus_amount, level.last_bonus);
//     // iter = level.bonus_list;
//     // while (iter != NULL) {
//     //     printf("%p ->", (void*) iter);
//     //     iter = iter->next;
//     // }
//     // printf("\n\n");
// }


// void test_scenery() {
//     printf("=== Level Initialisation ===\n");
//     scenery_init();
//     //scenery_append_obstacle(new_ball());
//     //scenery_append_obstacle(new_ball());
//     printf("=== Added 2 Elems ===\n");
//     d();

//     scenery_remove_first_obstacle();
//     printf("=== Removed 1 Elems ===\n");
//     d();
//     //scenery_append_obstacle(new_ball());
//     //scenery_append_obstacle(new_ball());
//     printf("=== Added 2 Elems ===\n");
//     d();
//     scenery_clear();
//     printf("=== Level Clear ===\n");
//     d();
//     /*int result = scenery_append_obstacle(new_ball());
//     printf("%d\n", result);
//     if (result == -1) printf("Can not add on unitialized level !\n");*/

//     scenery_init();
//     printf("=== Level reInitialisation ===\n");
    

//     d();
//     scenery_clear();
//     exit(EXIT_SUCCESS);
// }