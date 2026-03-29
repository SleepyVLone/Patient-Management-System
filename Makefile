build:
	clang -c -o sqlite3.o sqlite3.c
	clang++ -std=c++17 -g sqlite3.o main.cpp mainMenu.cpp login.cpp registerPatient.cpp patientMenu.cpp nurseMenu.cpp doctorMenu.cpp pharmacistMenu.cpp calculateStatistics.cpp calculateTreatmentCosts.cpp createPharmacistAccount.cpp editPrescriptions.cpp hashPassword.cpp modifyMedication.cpp searchPatients.cpp updatePatientInformation.cpp viewMyRecord.cpp viewPatientDetails.cpp viewPrescriptions.cpp database.cpp -o nhs

run:
	./nhs

clean:
	rm -f nhs sqlite3.o