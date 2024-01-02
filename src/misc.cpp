#include "misc.h"
void error(const char *msg) {
  // print out [error] in red (not bold)
  cout << "\033[31m[error]\033[0m " << msg << endl;
  MessageBox(nullptr, msg, "Error", MB_OK);
  throw msg;
}

// note that strings are just a buffer of bytes
// string is ASCII while wstring is UTF-8 (each character is 1-4 bytes, but it's
// prefix-free and backwards compatible with ASCII)
wstring to_wstring(string s) {
  return wstring{s.begin(), s.end()};
}

void check(bool b) {
  if (!b) {
    check(HRESULT_FROM_WIN32(GetLastError()));
  }
}

void check(HRESULT hr) {
  if (FAILED(hr)) {
    error(_com_error{hr}.ErrorMessage());
  }
}

int sys(string cmd) {
  return 0;
}

void printc() {
  cout << endl;
}
