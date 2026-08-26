#pragma once
#include "database.hpp"

// Provide commands list to the user.
inline void help() {
   println(
      "> Q - quit\n> T - new transaction\n> R - last transaction\n"
      "> L - list all transactions\n> B - check balance\n"
      "> O - log out of your account\n> D - deposit money\n"
      "> W - withdraw money\n> E - edit account\n", get_blue()
   );
}

// Deposit some money into the account.
inline void deposit(int id, Transactions& tr) {
   int amount = get_number("Amount to deposit > ", get_blue());

   // Create a transaction from BANK to user.
   if (tr.createTransaction(transaction(amount, 1, id))) {
      println("Successfully deposited " + std::to_string(amount) + "$.", get_green());
   }
}

// Withdraw money from the account.
inline void withdraw(account& acc, Transactions& tr) {
   int amount = get_number("Amount to withdraw > ", get_blue());

   // Not enough money in bank account.
   if (acc.balance < amount) {
      println("You don't have enough money to withdraw " + std::to_string(amount) + "$. You only have " + std::to_string(acc.balance) + "$.", get_red());
      return;
   }

   // Create a transaction from user to BANK.
   if (tr.createTransaction(transaction(amount, acc.id, 1))) {
      println("Successfully withdraw " + std::to_string(amount) + "$.", get_green());
   }
}

// Update accounts age.
inline void editAge(int id, Accounts& db) {
   int age = get_number("Input your new age > ", get_blue());
      
   if (db.updateAge(age, id)) {
      println("Successfully updated age.", get_green());
   }
}

// Update accounts username.
inline void editUsername(int id, Accounts& db) {
   std::string username = get_input("Input your new username > ", get_blue());
      
   if (db.updateName(username, id)) {
      println("Successfully updated username.", get_green());
   }
}

// Update users password if they know the previous one.
inline void editPassword(account& acc, Accounts& db) {
   std::string pass = get_hidden_input("Input your old password > ", get_blue());

   // Passwords don't match.
   if (acc.pass != hash_string(pass)) {
      println("Incorrect password.", get_red());
      return;
   }

   std::string newPass = get_hidden_input("Input your new password > ", get_blue());

   // New password is not the correct size.
   if (newPass.size() < MIN_PASS_SIZE || newPass.size() > MAX_PASS_SIZE) {
      println("Password too long or too short.", get_red());
      return;
   }

   if (db.updatePass(hash_string(newPass), acc.id)) {
      println("Successfully updated password.", get_green());
   }
}

// Delete the account if the user gives consent.
inline void deleteAccount(account& acc, Accounts& db) {
   if (!get_consent("Are you sure that you want to delete your account? This cannot be undone. [y/n] > ", get_orange())) {
      println("Cancelled", get_red());
      return;
   }

   if (db.deleteAccount(acc)) {
      println("Successfully deleted account.", get_green());
   }
}

// Edit account properties.
inline void editAccount(account& acc, Accounts& db) {
   switch (get_key("Choose (A - age, N - name, P - password, D - delete) > ")) {
   
   case 'a':
      editAge(acc.id, db);
      break;
   case 'n':
      editUsername(acc.id, db);
      break;
   case 'p':
      editPassword(acc, db);
      break;
   case 'd':
      deleteAccount(acc, db);
      break;
   default:
      println("Unknown option.", get_red());
      break;
   }
}

// Send money to a different user.
inline void createTransaction(account& acc, Accounts& db, Transactions& tr) {
   // Get receivers account.
   std::string username = get_input("Username to send the money to > ", get_blue());
   account receiver = db.selectByName(username);

   // Receiver does not exist.
   if (receiver.id == INVALID_ID || receiver.name == "DELETED") {
      println("Could not find user '" + username + "'.", get_red());
      return;
   }

   // Get amount to be sent.
   int amount = get_number("Amount to send (you have " + std::to_string(acc.balance) + "$) > ", get_blue());

   // Amount sent is above the accounts balance.
   if (acc.balance < amount) {
      println("Cannot send more money than you own.", get_red());
      return;
   }

   // Create transaction and update account.
   if (tr.createTransaction(transaction(amount, acc.id, receiver.id))) {
      println("Successfully sent " + std::to_string(amount) + "$ to '" 
      + receiver.name + "'.", get_green());
   }
}

// Print the latest transaction.
inline void lastTransaction(int id, Transactions& tr) {
   transaction trans = tr.getLatestTransaction(id);
   std::string_view color = (trans.fromId == id) ? get_red() : get_green();
   println(trans.string(), color);
}

// Retrieve and print out all of the transactions.
inline void allTransactions(int id, Transactions& tr) {
   for (transaction trans : tr.getTransactions(id)) {
      std::string_view color = (trans.fromId == id) ? get_red() : get_green();
      println(trans.string(), color);
   }
}

// Print users ballance.
inline void getBalance(int balance) {
   std::string_view color = (balance < 1) ? get_red() : get_green();
   println("Balance: " + std::to_string(balance) + "$", color);
}

// Log out if the user consents.
inline bool logout(account& acc) {
   // Get consent from user.
   if (!get_consent("Are you sure you want to log out? [y/n] > ", get_orange())) {
      println("Cancelled.", get_red());
      return false;
   }

   // User logged out of their account.
   println("Logged out of '" + acc.string() + "'.\n", get_green());
   return true;
}