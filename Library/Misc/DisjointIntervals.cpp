
struct Shape {
  int l, r;
  int h;
  Shape(int l = 0, int r = 0, int h = 0) : l(l), r(r), h(h) {}
  Long contribution = 0;  // 2 * (r - l) + abs(h - left_neighbour.h)
  bool operator<(const Shape& other) const {
    return tie(l, r, h) < tie(other.l, other.r, other.h);
  }
  Shape merge(const Shape& other) const {
    Shape res = *this;
    res.l = min(res.l, other.l);
    res.r = max(res.r, other.r);
    res.h = max(res.h, other.h);
    return res;
  }
};

void addShape(Shape& shape, set<Shape>& shapes, Long& union_perimeter) {
  bool got_right_neighbour = false;
  while (true) {
    auto it = shapes.lower_bound(Shape(shape.l + 1, 0, 0));
    if (it == begin(shapes)) {
      shape.contribution += 2 * shape.h;
      break;
    }
    it = prev(it);
    if (it->r < shape.l) {
      shape.contribution += 2 * shape.h;
      break;
    }
    union_perimeter -= it->contribution;
    Shape neighbour = *it;
    shapes.erase(it);

    if (neighbour.r > shape.r) {
      got_right_neighbour = true;
      Shape right = neighbour;
      right.l = shape.r;
      right.contribution = 2 * (right.r - right.l);
      union_perimeter += right.contribution;
      shapes.emplace(right);
    }
    if (neighbour.l < shape.l) {
      Shape left = neighbour;
      left.r = shape.l;
      left.contribution -= 2 * (neighbour.r - left.r);
      union_perimeter += left.contribution;
      shape.contribution += 2 * abs(shape.h - left.h);
      shapes.emplace(left);
      break;
    }
  }
  if (!got_right_neighbour) {
    while (true) {
      auto it = shapes.lower_bound(Shape(shape.l, 0, 0));
      if (it == end(shapes) || it->l > shape.r) {
        break;
      }
      assert(it->l != shape.l);
      auto neighbour = *it;
      shapes.erase(it);
      union_perimeter -= neighbour.contribution;
      if (neighbour.r > shape.r) {
        got_right_neighbour = true;
        Shape right = neighbour;
        right.l = shape.r;
        right.contribution = 2 * (right.r - right.l);
        union_perimeter += right.contribution;
        shapes.emplace(right);
        break;
      }
    }
  }
  shape.contribution += 2 * (shape.r - shape.l);
  union_perimeter += shape.contribution;
  shapes.emplace(shape);
}