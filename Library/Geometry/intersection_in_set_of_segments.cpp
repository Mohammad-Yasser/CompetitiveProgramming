// Check if any 2 segments from a set of given segments intersect.

using Segment = array<Point, 2>;

struct Event {
  int x, type, y, id;

  tuple<int, int, int, int> getTuple() const {
    return make_tuple(x, type, y, id);
  }

  bool operator<(const Event& other) const {
    return getTuple() < other.getTuple();
  }

  Event(int x, int type, int y, int id) : x(x), type(type), y(y), id(id) {}
};

struct SetComparator {
  static vector<Segment> segments;
  bool operator()(int a, int b) const {
    if (segments[a][0].x == segments[b][0].x) {
      return segments[a][0].y < segments[b][0].y;
    }
    if (segments[a][0] > segments[b][0]) {
      int dir = getDirection(segments[b][0], segments[b][1], segments[a][0]);
      return dir > 0;
    }
    int dir = getDirection(segments[a][0], segments[a][1], segments[b][0]);
    return dir < 0;
  }
};

vector<Segment> SetComparator::segments;

bool noIntersection(const vector<Segment>& segments) {
  int n = segments.size();
  vector<Event> events;
  for (int i = 0; i < n; ++i) {
    // Each segment endpoints must be sorted.
    assert(segments[i][0] < segments[i][1]);
    events.emplace_back(segments[i][0].x, 0, segments[i][0].y, i);
    events.emplace_back(segments[i][1].x, 1, segments[i][1].y, i);
  }

  sort(events.begin(), events.end());

  SetComparator::segments = segments;
  set<int, SetComparator> st;

  for (auto& event : events) {
    if (event.type == 0) {
      auto nxt = st.upper_bound(event.id);
      if (nxt != st.end()) {
        if (SegmentsIntersect(segments[event.id][0], segments[event.id][1],
                              segments[*nxt][0], segments[*nxt][1]))
          return false;
      }

      if (nxt != st.begin()) {
        --nxt;
        if (SegmentsIntersect(segments[event.id][0], segments[event.id][1],
                              segments[*nxt][0], segments[*nxt][1]))
          return false;
      }

      st.insert(event.id);

    } else {
      st.erase(event.id);
      auto nxt = st.upper_bound(event.id);
      if (nxt != st.end() && nxt != st.begin()) {
        auto before = nxt;
        --before;
        if (SegmentsIntersect(segments[*before][0], segments[*before][1],
                              segments[*nxt][0], segments[*nxt][1])) {
          return false;
        }
      }
    }
  }

  return true;
}
