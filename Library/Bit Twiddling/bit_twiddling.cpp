// Iterate all subsets of a bitmask in increasing order
for ( int sub = 0 ; sub = sub - bitmask & bitmask ; ) {
  // do something
}

// To avoid iterating on the reversed submasks: (e.g. if you consider 0111 the same as 1000)
for ( int sub = 0 ; (sub ^ mask) != (sub - mask & mask) && (sub = sub - bitmask & bitmask) ; ) {
  // do something
}

// Iterate all subsets of a bitmask in decreasing order
for(int sub = (mask-1) & bitmask ; sub > 0 ; sub = (sub-1) & bitmask )  {
  // do something 
}

// https://cp-algorithms.com/algebra/all-submasks.html
// Time Complexity: O(3^n)
