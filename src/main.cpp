#include "account.hpp"

// Main loop.
int main() {
   Accounts db;
   Transactions tr(db);
   
   // Create BANK account as ID 1 if it does not exist yet. Set password to 'BANK'
   // as you cannot log into an account with an unhashed password.
   if (db.selectByName("BANK").id == INVALID_ID) {
      db.createAccount(account("BANK", "BANK", 0, 0));
   }

   // Log in or sign up.
   account acc = (get_consent("Would you like to log in [y] or sign up [n]? > ", get_blue())) ? login(db) : signup(db);

   println("\nWelcome, " + acc.name + "!", get_blue());
   println("What would you like to do today?", get_blue());

   // Action loop.
   while (true) {
      switch (get_key("Command (h for help) > ")) {
      
      case 'h': 
         help(); 
         break;
      case 'q':
         println("Quitting.", get_blue());
         return 0;
      case 'd':
         deposit(acc.id, tr);
         acc = db.selectById(acc.id).at(0);
         break;
      case 'w':
         withdraw(acc, tr);
         acc = db.selectById(acc.id).at(0);
         break;
      case 'e':
         editAccount(acc, db);

         // If user deleted account then reload the program.
         if (acc.name == "DELETED") return main();
         acc = db.selectById(acc.id).at(0);
         break;
      case 't':
         createTransaction(acc, db, tr);
         acc = db.selectById(acc.id).at(0);
         break;
      case 'r':
         lastTransaction(acc.id, tr);
         break;
      case 'l':
         allTransactions(acc.id, tr);
         break;
      case 'b':
         getBalance(acc.balance);
         break;
      case 'o':
         if (logout(acc)) return main();
         break;
      default:
         // Unknown command.
         println("Unknown command, try typing 'h' for commands!", get_red());
         break;
      }
   }
   return 0;
}