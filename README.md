# NHS Patient Data System

## Details:

This program was a project assigned to me by my university as part of my Fundamentals of Software Development module.

## Features:

- **Role-based access control** - Patient, Nurse, Doctor, Pharmacist
- **Patient registration** - Secure registration with hashed password storage
- **Medical records** - Store and view patient conditions (Cancer, Diabetes, Smoking)
- **Treatment cost calculations** - Daily, weekly, monthly and yearly costs in GBP and USD
- **Patient statistics** - Average ages and frequencies across conditions
- **Prescription management** — View, add and edit patient prescriptions
- **SQLite database** — All data persisted using an embedded SQLite database

## How to Run

**Build:**
```bash
make build
```

**Run:**
```bash
./nhs
```

## Default Test Accounts

| Username | Password | Role |
|---|---|---|
| doctor1 | password123 | Doctor |
| nurse1 | password123 | Nurse |
| pharmacist1 | password123 | Pharmacist |
| user1 | password123 | Patient |

Patients can self-register through the main menu.

## Note on Password Hashing

Passwords are hashed using `std::hash`. If the pre populated test accounts don't work on your system, run the following to get the correct hash for `password123` on your machine:
```bash
cat << 'EOF' > test_hash.cpp
#include <iostream>
#include <functional>
#include <string>
using namespace std;
int main() {
    hash<string> hasher;
    cout << to_string(hasher("password123")) << endl;
}
EOF
g++ test_hash.cpp -o test_hash && ./test_hash
```

Then delete `nhs.db` and reinsert the staff accounts using the output value:
```bash
sqlite3 nhs.db
```
```sql
INSERT INTO Users (username, passwordHash, role, createdAt) VALUES ('doctor1', 'YOUR_HASH_HERE', 'Doctor', datetime('now'));
INSERT INTO Users (username, passwordHash, role, createdAt) VALUES ('nurse1', 'YOUR_HASH_HERE', 'Nurse', datetime('now'));
INSERT INTO Users (username, passwordHash, role, createdAt) VALUES ('pharmacist1', 'YOUR_HASH_HERE', 'Pharmacist', datetime('now'));
```

Replace `YOUR_HASH_HERE` with the value output from the test above.

## Technology

- **Language:** C++17
- **Database:** SQLite3
- **Platform:** macOS

