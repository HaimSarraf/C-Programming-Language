#include <stdbool.h>
#include <stdio.h>

typedef struct animal {
  char *name;
  char *species;
} Animal;

typedef struct carnivore {
  Animal parent;
} Carnivore;

void animal_eats(Animal *self);
void carnivore_eats(Carnivore *self);
char *animal_get_name(Animal *self);
void animal_set_name(Animal *self, char *name);

#define eats(animal)                                                           \
  _Generic((animal),                                                           \
      Animal *: animal_eats,                                                   \
      Carnivore *: carnivore_eats,                                             \
      Cat *: cat_eats,                                                         \
      default: animal_eats)(animal)

typedef struct private { bool claws_out; }
Private;
typedef struct feline {
  Carnivore parent;
  Private claws_out;
} Feline;

_Bool feline_get_claws_out(Feline *self);
void feline_protract_claws(Feline *self);
void feline_retract_claws(Feline *self);

typedef struct cat {
  Feline parent;
} Cat;

void cat_purr(Cat *self);
void cat_eats(Cat *self);

int main() {
  Animal oldie = {.name = "Oldie", .species = "Miacid"};

  printf("This really old animal is %s of species %s \n", oldie.name,
         oldie.species);

  Carnivore sabre_tooth = {{.name = "Diego", .species = "Dinictis"}};

  printf("Sabre_Tooth example is %s from %s species.\n",
         sabre_tooth.parent.name, sabre_tooth.parent.species);

  carnivore_eats(&sabre_tooth);

  Cat kitty = {
    .parent = {
      .parent = {
        .parent = {
          .name="Whiskers", .species="Felis catus"
        }
      },
      .claws_out = {
        .claws_out = true
      }
    }
  };

  eats(&oldie);

  eats(&kitty);

  cat_purr(&kitty);

  return 0;
}

void animal_eats(Animal *self) { printf("%s eats everything\n", self->name); }

void carnivore_eats(Carnivore *self) {
  printf("%s from %s eats meat\n", self->parent.name, self->parent.species);
}

char *animal_get_name(Animal *self) { return self->name; }

void animal_set_name(Animal *self, char *name) { self->name = name; }

bool feline_get_claws_out(Feline *self) { return self->claws_out.claws_out; }
void feline_protract_claws(Feline *self) { self->claws_out.claws_out = true; }
void feline_retract_claws(Feline *self) { self->claws_out.claws_out = false; }
void cat_purr(Cat *self) {
  printf("%s purrs\n", animal_get_name(&self->parent.parent.parent));

  feline_retract_claws(&self->parent);
}
void cat_eats(Cat *self) {
  printf("%s eats mice\n", animal_get_name(&self->parent.parent.parent));
}
