#pragma once
#include "pch.h"

wstring to_wstring(string s);

void error(const char *msg);

// asserts a condition e.g. testing a pointer or socket != INVALID_SOCKET or
// ret != SOCKET_ERROR. if false, uses GetLastError
// (equivalent to WSAGetLastError) to print an error and throw.
void check(bool condition);

// checks if an HRESULT failed. prints + throws if so.
void check(HRESULT hr);

// executes a shell command
int sys(string cmd);

// prints [info] + arguments + newline
template <class... T>
void info(T... t);

// prints arguments + newline
void printc();
template <class T, class... A>
void printc(T t, A... a);

#include "misc.tpp"