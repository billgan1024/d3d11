#pragma once
#include "pch.h"

#define countof(a) (sizeof(a) / sizeof(a[0]))

wstring to_wstring(string);

void error(const char *);

void check(bool);

void check(HRESULT);

int sys(string);

template <class... T>
void info(T...);

template <class T, class... A>
void printc(T, A...);

void printc();

#include "misc.tpp"
