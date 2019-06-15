#ifndef WIND_HPP
#define WIND_HPP

class Wind
  {
  public:
    RectangleShape* rect_;
    Text* head_;

    int x_;
    int y_;

    int width_;
    int height_;

    Wind(int x, int y, int width, int height, Font & font, char* head, int font_size);
   ~Wind();

    void draw(RenderWindow & window);
  };

Wind::Wind(int x, int y, int width, int height, Font & font, char* head, int font_size)
  {
    rect_ = new RectangleShape(Vector2f(width, height));

    rect_->setPosition(x, y);
    rect_->setOutlineThickness(3.f);
    rect_->setFillColor(Color(250, 250, 250));
    rect_->setOutlineColor(Color(0, 0, 0));

    head_ = new Text(head, font, font_size);

    head_->setColor(sf::Color::Black);
    head_->setPosition(x, y);

    std::cout << "wind create" << std::endl;
  }

Wind::~Wind()
  {
    delete rect_;
    delete head_;
    std::cout << "wind destruct" << std::endl;
  }

void Wind::draw(RenderWindow & window)
  {
    window.draw(*rect_);
    window.draw(*head_);
  }

#endif
