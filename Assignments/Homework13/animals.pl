/* Question 3.1 */
category(jack, canidae).
category(lucy, felidae).

details(jack, dog_type).
details(jack, dog_age).
details(lucy, cat_type).
details(lucy, cat_age).

type(dog_type, labrador).
type(dog_type, black).
type(cat_type, persian).
type(cat_type, white).

age(dog_age, 5).
age(cat_age, 2).

/* Question 3.2 */
info(X, Y) :-
  category(X, Y);
  details(X, Y).

/* Question 3.3 */
bio(X, Y) :-
  details(X, Z),
  type(Z, Y);
  details(X, Z),
  age(Z, Y).