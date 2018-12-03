error(s, p1, ps) {
  extern printf, line, fout, flush, putchar, nerror;
  int f;

  nerror++;
  flush();
  f = fout;
  fout = 1;
  printf("%d: ", line);
  printf(s, p1, ps);
  putchar('\n');
  fout = f;
}
