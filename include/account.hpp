#include "actions.hpp"

account login(Accounts&);
account signup(Accounts&);

// Log into an existing account.
inline account login(Accounts& db) {
   account acc;

   while (true) {
      // Get username and password from user.
      std::string username = get_input("Input your username (s to sign up instead) > ", get_blue());

      if (username == "s" || username == "S") 
         return signup(db);

      std::string password = get_hidden_input("Input your password > ", get_blue());
      acc = db.selectByName(username);

      // Account does not exist.
      if (acc.id == INVALID_ID) {
         println("Account with the given username does not exist.", get_red());
         continue;
      }

      // Check if passwords match.
      if (acc.pass == hash_string(password)) {
         println("Logged into '" + acc.string() + "'.", get_green());
         return acc;
      } 
      else println("Incorrect password.", get_red());
   }

   return account();
}

// Create a brand new account.
inline account signup(Accounts& db) {
   account acc;

   while (acc.id == INVALID_ID) {
      // Get a new username, password and age from the user.
      std::string username = get_input("Input a new username (l to login instead) > ", get_blue()).c_str();

      if (username == "l" || username == "L") 
         return login(db);

      std::string password = get_hidden_input("Input a password > ", get_blue());
      int age = get_number("Input your age > ", get_blue());

      // Password is within the length bounds.
      if (password.size() < MIN_PASS_SIZE || password.size() > MAX_PASS_SIZE) {
         println("Password is either too short or too long.", get_red());
         continue;
      }

      // Handle all of the other edge cases in the create account function, the
      // password length cannot be checked there because it has to be hashed and
      // hashed string length is fixed.
      if (db.createAccount(account(username, hash_string(password), age, 0))) {
         acc = db.selectByName(username);
         println("Signed up as '" + acc.string() + "'.", get_green());
         return acc;
      }
   }

   return account();
}