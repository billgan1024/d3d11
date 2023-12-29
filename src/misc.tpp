
template <class... T>
void info(T... t) {
  cout << "\033[34m[info]\033[0m ";
  printc(t...);
}

template <class T, class... A>
void printc(T t, A... a) {
  cout << t << " ";
  printc(a...);
}
