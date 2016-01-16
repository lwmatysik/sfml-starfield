#include <SFML/Graphics.hpp>
#include <random>

const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HALF_HEIGHT = WINDOW_HEIGHT / 2;
const int WINDOW_HALF_WIDTH = WINDOW_WIDTH / 2;
const int DEPTH = 32;
const int NUM_STARS = 720;

struct star {
  int x;
  int y;
  double z;
} stars[NUM_STARS];

int main() {

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937_64::result_type> distxy(-25, 25);
  std::uniform_int_distribution<std::mt19937_64::result_type> distz(1, DEPTH);
    
  for (int i = 0; i < NUM_STARS; i++) {
    stars[i].x = distxy(rng);
    stars[i].y = distxy(rng);
    stars[i].z = distz(rng);
  }

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Starfield");
  sf::Vertex vertex;
  sf::VertexArray vertexArray(sf::Points, NUM_STARS);
  sf::CircleShape circleShape; 
  
  window.setFramerateLimit(60);
  window.clear(sf::Color::Black);
  window.display();

  while (window.isOpen()) {

    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
	window.close();
      }
    }

    window.clear(sf::Color::Black);
    vertexArray.clear();
    
    for (int i = 0; i < NUM_STARS; i++) {
      stars[i].z -= 0.1;

      if (stars[i].z <= 0) {
	stars[i].x = distxy(rng);
	stars[i].y = distxy(rng);
	stars[i].z = DEPTH;
      }

      float k = 256 / stars[i].z;
      float xPos = (stars[i].x * k) + WINDOW_HALF_WIDTH;
      float yPos = (stars[i].y * k) + WINDOW_HALF_HEIGHT;

      if (xPos >= 0 && xPos < WINDOW_WIDTH && yPos >= 0 && yPos < WINDOW_HEIGHT) {
	vertex.position = sf::Vector2f(xPos, yPos);
	vertexArray.append(vertex);	
       }
      
    }

    window.draw(vertexArray);
    window.display();
  }
 
  return 0;
}
