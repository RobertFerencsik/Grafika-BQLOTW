#include <stdio.h>

typedef struct {
    double length;
    double width;
    double height;
} Cuboid;

void set_size(Cuboid *c, double l, double w, double h) {
    if (l > 0 && w > 0 && h > 0) {
        c->length = l;
        c->width = w;
        c->height = h;
    } else {
        printf("Error: the size of the sides must be positive\n");
    }
}

double calculate_volume(const Cuboid *c) {
    return c->length * c->width * c->height;
}

double calculate_surface(const Cuboid *c) {
	return c->length * c->width * 2 + c->length * c->height * 2 + c->width * c->height * 2;
}

void print_cuboid(const Cuboid *c) {
    printf("Cuboid sizes: %.2f x %.2f x %.2f\n", c->length, c->width, c->height);
    printf("volume: %.2f\n", calculate_volume(c));
	printf("Surface: %.2f\n", calculate_surface(c));
}

int cuboid_has_square_side(const Cuboid *c){
	if(c->length == c->width || c->height == c->length || c->height == c->width)
		return 1;
	return 0;
}

int main() {
    Cuboid myCuboid;

    double l, w, h;
    printf("Give the three sides of the cuboid (forexample. 3.5 2.0 4.0): ");
    if (scanf("%lf %lf %lf", &l, &w, &h) != 3) {
        printf("Hibás bemenet!\n");
        return 1;
    }

    set_size(&myCuboid, l, w, h);
    print_cuboid(&myCuboid);
	
	if(cuboid_has_square_side(&myCuboid))
		printf("there is square sides in the cuboid\n");
	else 
		printf("there is no square sides in the cuboid\n");

    return 0;
}
