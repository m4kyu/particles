#include <raylib.h>


#define WIDTH 600
#define HEIGHT 400


struct Particle {
  Vector2 pos;
  Vector2 vel;
  
  float radius;
  float mass;

  Color color;
};

void updateParticle(struct Particle *part); 


int main() {
  InitWindow(WIDTH, HEIGHT, "Particles");
  SetTargetFPS(60);


  struct Particle particle = {
    (Vector2){100, 100},
    (Vector2){5, 5},
    5,
    10,
    RED
  };

  while (!WindowShouldClose()) {
    updateParticle(&particle);


    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircleV(particle.pos, particle.radius, particle.color);
    DrawFPS(0, 0);
    EndDrawing();
  } 

  CloseWindow();


  return 0;
}


void updateParticle(struct Particle *part) {
  part->pos.x += part->vel.x;
  part->pos.y += part->vel.y;


  if (part->pos.x + part->radius >= WIDTH) {
    part->pos.x = WIDTH - part->radius;
    part->vel.x *= -1;
  } else if (part->pos.x - part->radius <= 0) {
    part->pos.x = 0 + part->radius;
    part->vel.x *= -1;
  }

  if (part->pos.y + part->radius >= HEIGHT) {
    part->pos.y = HEIGHT - part->radius;
    part->vel.y *= -1;
  } else if (part->pos.y - part->radius <= 0) {
    part->pos.y = 0 + part->radius;
    part->vel.y *= -1;
  }

}


