//
// struct.c
//
// Created by Anthony Sainez on 3 February 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

struct point {
    int x;
    int y;
};

void PrintPoint(struct point p) {
    printf("(%d,%d)\n", p.x, p.y);
}

int main() {
    struct point p1 = {0, 10}; // x = 0, y = 10
    PrintPoint(p1);
    
    struct point *p;

    printf("x is %d\n", (*p).x);
    printf("x is %d\n", p->x); // identical to above line
}
