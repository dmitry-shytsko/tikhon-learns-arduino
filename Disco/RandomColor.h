class RandomColor {
  private:
    int color;
    int dir;
    int shift;

  public:
    RandomColor(int colorShift) : shift{colorShift}, color{0}, dir{1} {}

    int next() {
      color = (color + dir * random(shift));

      if (color < 0) {
        color = 0;
        dir = 1;
      }

      if (color > 255) {
        color = 255;
        dir = -1;
      }

      return color;
    }
};