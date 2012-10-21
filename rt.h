struct point {
  float x, y, z;
};

struct triangle {
  struct point a, b, c;
};

int read_triangles(char *filename, struct triangle **tris, int *num);

int ray_trace(struct triangle *tris, int num, int *bitmap);

int write_bmp(char *filename, int *bitmap);
