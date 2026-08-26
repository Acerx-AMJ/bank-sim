#ifndef BANK_SIM_IO_HPP
#define BANK_SIM_IO_HPP

#include <iostream>
#include <string>

using namespace std::string_literals;
using namespace std::string_view_literals;

// Get color functions

constexpr std::string_view get_red()
{
   return "\033[38;2;222;63;42m";
}

constexpr std::string_view get_orange()
{
   return "\033[38;2;240;157;34m";
}

constexpr std::string_view get_green()
{
   return "\033[38;2;126;232;51m";
}

constexpr std::string_view get_blue()
{
   return "\033[38;2;58;122;224m";
}

constexpr std::string_view get_reset_code()
{
   return "\033[0m";
}

// Output functions

template<typename T>
void print(const T& printable, std::string_view color = ""sv)
{
   std::cout << color << printable << get_reset_code(); 
}

template<typename T>
void println(const T& printable, std::string_view color = ""sv)
{
   std::cout << color << printable << get_reset_code() << '\n';
}

// Terminal mode functions

void set_raw_terminal_mode();
void reset_terminal_mode();

// Input functions

std::string get_input(const std::string& prompt = ""s, std::string_view color = ""sv);

std::string get_hidden_input(const std::string& prompt = ""s, std::string_view color = ""sv);

int get_number(const std::string& prompt, std::string_view color = ""sv);

char get_key(const std::string& prompt, std::string_view color = ""sv);

bool get_consent(const std::string& prompt, std::string_view color = ""sv);

// Hash string function

std::string hash_string(const std::string& string);

#endif
