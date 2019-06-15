#ifndef HERO_HPP
#define HERO_HPP
                         // a = (2*h) / t^2
#define ACCELERATION 622 //весь экран при свободном падении проходит за 1.5 секунды
                         // v = (2*h) / sqrt(n*t)
#define BIRD_SPEED   361 //поднимает птицу за одно нажатие на 1/10 часть экрана

#define INV_SECONDS 1

class Hero
  {
  public:

    double x_;
    double y_;
	
	double alfa_;
	
	int death_time_;
	Text* d_time_;
	char* str_;

    double speed_;
    double acceleration_;

    double inv_time_ = 100;

    Sprite* sprite_;
    Sound* sound_;

    Hero(int x, int y, Texture& texture, SoundBuffer & s_buffer)
      {
        x_ = x;
        y_ = y;
		
		alfa_ = 0;
		
		death_time_ = 0;

        speed_ = 0;
        acceleration_ = ACCELERATION;

        sprite_ = new Sprite;
        sprite_->setTexture(texture);

        sound_ = new Sound;
        sound_->setBuffer(s_buffer);
		
		str_ = (char*)calloc(100, sizeof(char));

        std::cout << "construct hero" << std::endl;
      }

    bool inv()
      {
        if(inv_time_ > INV_SECONDS)
          {
            inv_time_ = 0;
            return true;
          }

        return false;
      }

    void update(bool button_is_press, double time)
      {
        time = time / 1000000;

        if(button_is_press) speed_ = -BIRD_SPEED;

        speed_ += acceleration_ * time;

        y_ += speed_ * time;
		
		if(y_ > 700 || y_ < 0)
			{
				y_ = 350;
				speed_ = 0;
				d_time_++;
			}

        inv_time_ += time;

        sprite_->setPosition(x_, y_);
		
		
		double new_alfa = 30 * atan(speed_ / BIRD_SPEED_X);
		
		sprite_->rotate(new_alfa - alfa_);
		
		alfa_ = new_alfa;
      }

    void draw(RenderWindow &window, Font & font)
      {
        window.draw(*sprite_);
		
		sprintf(str_, "death time %d", death_time_);
		
		d_time_ = create_menu_text(font, str_, 0, 0, 50);
		
		window.draw(*d_time_);
      }

    ~Hero()
      {
        delete(sprite_);
        std::cout << "destruct hero" << std::endl;
      }
  };

#endif
