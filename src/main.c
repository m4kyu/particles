#include <raylib.h>
#include <stdlib.h>


#define WIDTH 600
#define HEIGHT 400

#define SPEED 5

#define PARTICLES 50
#define COLORS 5


struct Particle {
  Vector2 pos;
  Vector2 vel;
  
  float radius;
  float mass;

  Color color;
};



const Color colors[COLORS] = {RED, GREEN, BLUE, YELLOW, ORANGE};
static struct Particle particles[PARTICLES];

void updateParticles(); 

int main() {
  InitWindow(WIDTH, HEIGHT, "Particles");
  SetTargetFPS(60);

  for (int i = 0; i < PARTICLES; i++) {
      particles[i] = (struct Particle){
        (Vector2){(rand() % WIDTH) + 10, (rand() % HEIGHT) + 10},
        (Vector2){(rand() % 2) == 1 ? -SPEED : SPEED, (rand() % 2) == 1 ? -SPEED : SPEED},
        5,
        10,
        colors[rand() % COLORS]
    };
  }

  while (!WindowShouldClose()) {
    updateParticles();


    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < PARTICLES; i++) {
      DrawCircleV(particles[i].pos, particles[i].radius, particles[i].color);
    }

    DrawFPS(0, 0);
    EndDrawing();
  } 

  CloseWindow();


  return 0;
}


void updateParticles() {
  for (int i = 0; i < PARTICLES; i++) {
    particles[i].pos.x += particles[i].vel.x;
    particles[i].pos.y += particles[i].vel.y;


    if (particles[i].pos.x + particles[i].radius >= WIDTH) {
      particles[i].pos.x = WIDTH - particles[i].radius;
      particles[i].vel.x *= -1;
    } else if (particles[i].pos.x - particles[i].radius <= 0) {
      particles[i].pos.x = 0 + particles[i].radius;
      particles[i].vel.x *= -1;
    }

    if (particles[i].pos.y + particles[i].radius >= HEIGHT) {
      particles[i].pos.y = HEIGHT - particles[i].radius;
      particles[i].vel.y *= -1;
    } else if (particles[i].pos.y - particles[i].radius <= 0) {
      particles[i].pos.y = 0 + particles[i].radius;
      particles[i].vel.y *= -1;
    }

  }
  
}


