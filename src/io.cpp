#include "io.hpp"

#include <openssl/sha.h>
#include <termios.h>
#include <unistd.h>
#include <iomanip>
#include <limits>
#include <sstream>

termios original_mode;

// Terminal mode functions

void set_raw_terminal_mode()
{
   tcgetattr(STDIN_FILENO, &original_mode);

   termios raw_mode;
   tcgetattr(STDIN_FILENO, &raw_mode);
   raw_mode.c_lflag &= ~(ECHO | ICANON);

   tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
}

void reset_terminal_mode()
{
   tcsetattr(STDIN_FILENO, TCSANOW, &original_mode);
}

// Input functions

std::string get_input(const std::string& prompt, std::string_view color)
{
   print(prompt, color);
   std::string input {};
   std::getline(std::cin >> std::ws, input);
   return input;
}

std::string get_hidden_input(const std::string& prompt, std::string_view color)
{
   print(prompt, color);
   set_raw_terminal_mode();

   std::string input {};
   std::getline(std::cin >> std::ws, input);

   reset_terminal_mode();
   std::cout << '\n';
   return input;
}

int get_number(const std::string& prompt, std::string_view color)
{
   print(prompt, color);
   int number = 0;

   while (!(std::cin >> number))
   {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      print("Invalid input. Please tru again > "s, get_red());
   }
   get_input();
   return number;
}

char get_key(const std::string& prompt, std::string_view color)
{
   print(prompt, color);
   set_raw_terminal_mode();

   char key = std::tolower(getchar());
   reset_terminal_mode();

   println(key);
   return key;
}

bool get_consent(const std::string& prompt, std::string_view color)
{
   return get_key(prompt, color) == 'y';
}

// Hash string function

std::string hash_string(const std::string& string)
{
   unsigned char hash[SHA256_DIGEST_LENGTH];
   static_assert(sizeof(hash) == SHA256_DIGEST_LENGTH, "Size of hash must be the SHA256_DIGEST_LENGTH constant!");

   SHA256((unsigned char*)string.c_str(), string.size(), hash);
   std::stringstream stream;

   for (size_t i = 0; i < sizeof(hash); ++i)
      stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
   return stream.str();
}
