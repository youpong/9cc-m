copy(s)
char s[]; {
  extern tsp;
  char tsp[], otsp[];

  otsp = tsp;
  while(*tsp++ = *s++);
  return (otsp);
}
