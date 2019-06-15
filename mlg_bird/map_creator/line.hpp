#ifndef LINE_HPP
#define LINE_HPP

RectangleShape* create_line(int x, int y)
  {
    RectangleShape* rect_ = new RectangleShape(Vector2f(0, 700));

    rect_->setPosition(x, y);
    rect_->setOutlineThickness(1.f);
    rect_->setFillColor(Color(0, 0, 0));
    rect_->setOutlineColor(Color(0, 0, 0));

    return rect_;
  }

RectangleShape* create_yellow_line(int x, int y)
  {
    RectangleShape* rect_ = new RectangleShape(Vector2f(0, 700));

    rect_->setPosition(x, y);
    rect_->setOutlineThickness(1.f);
    rect_->setFillColor(Color(200, 0, 0));
    rect_->setOutlineColor(Color(200, 0, 0));

    return rect_;
  }

#endif
