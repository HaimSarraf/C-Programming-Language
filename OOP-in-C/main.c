#include <stdio.h>

#define class struct
typedef class animal Animal;

struct animal {
  char *name;
  char *species;
};

typedef class carnivoire{
    Animal parent;
} Carnivoire;

int main() {
    struct animal oldie = {.name = "Oldie" , .species="Miacid"};

    printf("This really old animal is %s of species %s \n", oldie.name, oldie.species);    

    Carnivoire sabre_tooth = {{.name = "Diego" , .species = "Dinictis"}};

    printf("Sabre_Tooth example is %s from %s species.\n", sabre_tooth.parent.name , sabre_tooth.parent.species);
}