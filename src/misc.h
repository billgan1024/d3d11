#pragma once
#include "pch.h"

wstring to_wstring(string s);

void error(const char *msg);

void check(bool condition);

void check(HRESULT hr);

int sys(string cmd);

template <class... T>
void info(T... t);

template <class T, class... A>
void printc(T t, A... a);

void printc();

#include "misc.tpp"