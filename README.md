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

The previous `bash std::hash` has been replaced with FNV-1a, which is a deterministic hashing algorithm that produces consistent output across all operating systems and compilers. This fixes the issue of needing to delete the database and run the `bash INSERTS` yourself.

## Technology

- **Language:** C++17
- **Database:** SQLite3
- **Platform:** macOS

