#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>


#define WIDTH 800 
#define HEIGHT 500 

#define SPEED 5

#define PARTICLES 15 
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

  srand(time(NULL));
  for (int i = 0; i < PARTICLES; i++) {
      particles[i] = (struct Particle){
        (Vector2){(rand() % WIDTH) + 10, (rand() % HEIGHT) + 10},
        (Vector2){(rand() % 2) == 1 ? -SPEED : SPEED, (rand() % 2) == 1 ? -SPEED : SPEED},
        20,
        (rand() % 50) + 10,
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
  static int num = 0;
  num++;
  if (num <= 2) 
    return;
  for (int i = 0; i < PARTICLES; i++) {
    particles[i].pos.x += particles[i].vel.x;
    particles[i].pos.y += particles[i].vel.y;


    for (int j = 0; j < PARTICLES; j++) {
      if (i == j)
        continue;

      float dist = sqrtf(powf(particles[i].pos.x - particles[j].pos.x, 2) + powf(particles[i].pos.y - particles[j].pos.y, 2));
      if (dist <= particles[i].radius + particles[j].radius) {
        Vector2 n = {(particles[j].pos.x - particles[i].pos.x) / dist, (particles[j].pos.y - particles[i].pos.y) / dist};
        float p = 2 * (particles[i].vel.x * n.x + particles[i].vel.y * n.y - particles[j].vel.x * n.x - particles[j].vel.y * n.y) / (particles[i].mass + particles[j].mass); 

        particles[i].vel = (Vector2){particles[i].vel.x - p * particles[i].mass * n.x, particles[i].vel.y - p * particles[i].mass * n.y};
        particles[j].vel = (Vector2){particles[j].vel.x + p * particles[j].mass * n.x, particles[j].vel.y + p * particles[j].mass * n.y};
        
        Vector2 mid = {(particles[i].pos.x + particles[j].pos.x) / 2, (particles[i].pos.y + particles[j].pos.y) / 2};

        Vector2 diff1 = {particles[i].pos.x - particles[j].pos.x, particles[i].pos.y - particles[j].pos.y};
        Vector2 diff2 = {particles[j].pos.x - particles[i].pos.x, particles[j].pos.y - particles[i].pos.y};
        particles[i].pos.x = mid.x + particles[i].radius * diff1.x / dist; 
        particles[i].pos.y = mid.y + particles[i].radius * diff1.y / dist; 
        particles[j].pos.x = mid.x + particles[j].radius * diff2.x / dist; 
        particles[j].pos.y = mid.y + particles[j].radius * diff2.y / dist; 
        
      }
    }


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


