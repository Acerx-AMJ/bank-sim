# Bank simulator
Bank simulator that contains deposits, withdrawals and transactions to other accounts. It is fully local using SQLite3. It is also a nice project to play around with databases and learn commands.

## Building
This project depends on C++17, [SQLite3](https://www.sqlite.org/) and [OpenSSL](https://github.com/openssl/openssl). The preferred way to build it is using CMake:
```bash
cmake -B build
cmake --build build
```
The executable will be found in `build/bank`. The database folder must be in the same directory in which the program is ran in.

## Usage
Simply run the executable after building. You'll be prompted to either sign up or log in. I've set all accounts' passwords to `password`. I recommend you to create your own account at first (it's local, your data will only be stored on your own computer).

After signing up/logging in you can type `h` for all available commands.

The fun part is playing around with the database using `sqlite3`. Run it in the terminal and open the database:
```sql
sqlite> .open database/database.db
```

There are two tables: accounts and transactions. You can view them using the following two commands:
```sql
sqlite> select * from accounts;
...
sqlite> select * from transactions;
...
```

Feel free to modify and break the database. The most important part is that you have fun!

## Credits
This project was made by Daniel Vishnevsky and is licensed under MIT License. It was made in September of 2024 and published on October 2026 as an effort to make all of my projects open-source.
