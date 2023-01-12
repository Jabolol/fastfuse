#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shared.h"
#include "../include/my_printf.h"

typedef struct leaf leaf_t;

typedef struct leaf {
    leaf_t *left;
    leaf_t *right;
    int32_t count;
    int32_t *value;
} leaf_t;

#define MAX_ARR_LEN 256

int main(void)
{
    char *my_str =
        "Albion Online es un mmorpg no lineal, en el que escribes tu propia "
        "historia sin limitarte a seguir un camino prefijado. Explora un "
        "amplio mundo abierto con 5 biomas únicos, todo cuánto hagas tendrá "
        "su repercusión en el mundo, con la economía orientada al jugador de "
        "Albion, los jugadores crean prácticamente todo el equipo a partir de "
        "los recursos que consiguen, el equipo que llevas define quién eres, "
        "cambia de arma y armadura para pasar de caballero a mago, o juega "
        "como una mezcla de ambas clases. Aventúrate en el mundo abierto "
        "frente a los habitantes y las criaturas de Albion, inicia "
        "expediciones o adéntrate en mazmorras en las que encontrarás "
        "enemigos aún más difíciles, enfréntate a otros jugadores en "
        "encuentros en el mundo abierto, lucha por los territorios o por "
        "ciudades enteras en batallas tácticas, relájate en tu isla privada, "
        "donde podrás construir un hogar, cultivar cosechas y criar animales, "
        "únete a un gremio, todo es mejor cuando se trabaja en grupo. "
        "Adéntrate ya en el mundo de Albion y escribe tu propia historia.";

    int32_t string_length = strlen(my_str);
    int32_t **array_map = calloc(MAX_ARR_LEN, sizeof(int32_t *));
    int32_t *pool = calloc(MAX_ARR_LEN, sizeof(int32_t));

    for (int i = 0; i < MAX_ARR_LEN; i++) {
        *(array_map + i) = pool + i;
    }

    for (int32_t i = 0; i < string_length; i++) {
        *(pool + (uint8_t) * (my_str + i)) += 1;
    }

    quicksort(array_map, 0, MAX_ARR_LEN - 1);

    int32_t *first_non_zero = NULL;
    int32_t *last_ordered = pool + MAX_ARR_LEN - 1;
    int32_t new_length = MAX_ARR_LEN;
    int32_t first_index = -1;

    for (int32_t i = 0; i < MAX_ARR_LEN; i++) {
        if (**(array_map + i) == 0) {
            new_length -= 1;
            continue;
        };
        first_non_zero = *(array_map + i + 1);
        first_index = i;
        break;
    }

    /*
    [
          [0, 1, 2, 3, 4, 5]
           [1, 2, 3, 4, 5]
             [3, 3, 4, 5]
              [6, 4, 5]
                [9, 6]
                 [15]
    ]
    */

    int32_t len = new_length;
    int32_t **new_array = calloc(len * (len + 1) / 2, sizeof(int32_t *));

    for (int32_t i = 0; i < new_length; i++, len--) {
        if (i != 0)
            _quicksort(*(new_array + i - 1), 0, len - 1);
        *(new_array + i) = calloc(len, sizeof(int32_t));
        if (i == 0) {
            for (int z = first_index; z < MAX_ARR_LEN; z++) {
                *(*(new_array + i) + (z - first_index)) = **(array_map + z);
            }
        }
        for (int32_t j = 0; i != 0 && j < len; j++) {
            if (j == 0) {
                *(*(new_array + i) + j) =
                    *(*(new_array + i - 1)) + *(*(new_array + i - 1) + 1);
                continue;
            }
            *(*(new_array + i) + j) = *(*(new_array + i - 1) + j + 1);
        }
    }

    int32_t aux_len = new_length;
    for (int32_t i = 0; i < new_length; i++, aux_len--) {
        fflush(stdout);
        for (int32_t j = 0; j < aux_len; j++) {
            printf("%d ", *(*(new_array + i) + j));
        }
        fprintf(stdout, "\n");
        fflush(stdout);
    }

    free(pool);
    free(array_map);
    free(new_array);
    return EXIT_SUCCESS;
}
