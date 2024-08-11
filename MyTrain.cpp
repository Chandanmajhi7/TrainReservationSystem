#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Train {
private:
    int trainNo, noFafSeat, noFasSeat, noFsSeat, noAcSeat, noSsSeat;
    string trainName, startingPoint, destination;

public:
    Train() : trainNo(0), noFafSeat(0), noFasSeat(0), noFsSeat(0), noAcSeat(0), noSsSeat(0),
              trainName("/0"), startingPoint("/0"), destination("/0") {}

    void input();
    void display() const;
    int getTrainNo() const { return trainNo; }
    int getFafSeat() const { return noFafSeat; }
    int getFasSeat() const { return noFasSeat; }
    int getFsSeat() const { return noFsSeat; }
    int getAcSeat() const { return noAcSeat; }
    int getSsSeat() const { return noSsSeat; }
};

void Train::input() {
    cout << "ENTER THE TRAIN NUMBER: ";
    cin >> trainNo;
    cout << "ENTER THE NUMBER OF A/C FIRST CLASS SEATS: ";
    cin >> noFafSeat;
    cout << "ENTER THE NUMBER OF A/C SECOND CLASS SEATS: ";
    cin >> noFasSeat;
    cout << "ENTER THE NUMBER OF FIRST CLASS SLEEPER SEATS: ";
    cin >> noFsSeat;
    cout << "ENTER THE NUMBER OF A/C CHAIR CAR SEATS: ";
    cin >> noAcSeat;
    cout << "ENTER THE NUMBER OF SECOND CLASS SLEEPER SEATS: ";
    cin >> noSsSeat;
    cin.ignore(); // Clear the newline character left by cin

    cout << "ENTER THE TRAIN NAME: ";
    getline(cin, trainName);
    cout << "ENTER THE STARTING POINT: ";
    getline(cin, startingPoint);
    cout << "ENTER THE DESTINATION: ";
    getline(cin, destination);

    // Save train details to file
    ofstream fout("Train1.dat", ios::binary | ios::trunc);
    if (!fout) {
        cerr << "ERROR CREATING TRAIN FILE!" << endl;
        return;
    }
    fout.write(reinterpret_cast<const char*>(this), sizeof(Train));
    fout.close();
}

void Train::display() const {
    ifstream fin("Train1.dat", ios::binary);
    if (!fin) {
        cerr << "ERROR OPENING TRAIN FILE!" << endl;
        return;
    }

    if (fin.read(reinterpret_cast<char*>(const_cast<Train*>(this)), sizeof(Train))) {
        cout << "TRAIN NUMBER: " << trainNo << endl;
        cout << "TRAIN NAME: " << trainName << endl;
        cout << "NUMBER OF A/C FIRST CLASS SEATS: " << noFafSeat << endl;
        cout << "NUMBER OF A/C SECOND CLASS SEATS: " << noFasSeat << endl;
        cout << "NUMBER OF FIRST CLASS SLEEPER SEATS: " << noFsSeat << endl;
        cout << "NUMBER OF A/C CHAIR CAR SEATS: " << noAcSeat << endl;
        cout << "NUMBER OF SECOND CLASS SLEEPER SEATS: " << noSsSeat << endl;
        cout << "STARTING POINT: " << startingPoint << endl;
        cout << "DESTINATION: " << destination << endl;
    } else {
        cerr << "NO TRAIN DETAILS FOUND!" << endl;
    }
    fin.close();
}

class Ticket {
private:
    int resNo, toAf, noFaf, toAs, noFas, toFs, noFs, toAc, noAc, toSs, noSs, age;
    string status, name;

public:
    Ticket() : resNo(0), toAf(0), noFaf(0), toAs(0), noFas(0), toFs(0), noFs(0), toAc(0),
               noAc(0), toSs(0), noSs(0), age(0), status("/0"), name("/0") {}

    void reservation();
    void cancellation();
    void display() const;
    int getResNo() const { return resNo; }
};

void Ticket::reservation() {
    Train tr;
    ifstream fin("Train1.dat", ios::binary);
    if (!fin) {
        cerr << "ERROR OPENING TRAIN FILE!" << endl;
        return;
    }

    cout << "ENTER THE TRAIN NO: ";
    int tno;
    cin >> tno;

    bool found = false;
    while (fin.read(reinterpret_cast<char*>(&tr), sizeof(Train))) {
        if (tno == tr.getTrainNo()) {
            found = true;
            noFaf = tr.getFafSeat();
            noFas = tr.getFasSeat();
            noFs = tr.getFsSeat();
            noAc = tr.getAcSeat();
            noSs = tr.getSsSeat();
            break;
        }
    }
    fin.close();

    if (found) {
        ofstream file("Ticket1.dat", ios::binary | ios::app);
        if (!file) {
            cerr << "ERROR CREATING TICKET FILE!" << endl;
            return;
        }

        cout << "NAME: ";
        cin.ignore(); // Clear the newline character left by cin
        getline(cin, name);
        cout << "AGE: ";
        cin >> age;
        cout << "SELECT THE CLASS WHICH YOU WISH TO TRAVEL:\n";
        cout << "1. A/C FIRST CLASS\n";
        cout << "2. A/C SECOND CLASS\n";
        cout << "3. FIRST CLASS SLEEPER\n";
        cout << "4. A/C CHAIR CAR\n";
        cout << "5. SECOND CLASS SLEEPER\n";
        cout << "ENTER YOUR CHOICE: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                toAf++;
                resNo = rand();
                status = (noFaf - toAf > 0) ? "confirmed" : "pending";
                break;
            case 2:
                toAs++;
                resNo = rand();
                status = (noFas - toAs > 0) ? "confirmed" : "pending";
                break;
            case 3:
                toFs++;
                resNo = rand();
                status = (noFs - toFs > 0) ? "confirmed" : "pending";
                break;
            case 4:
                toAc++;
                resNo = rand();
                status = (noAc - toAc > 0) ? "confirmed" : "pending";
                break;
            case 5:
                toSs++;
                resNo = rand();
                status = (noSs - toSs > 0) ? "confirmed" : "pending";
                break;
            default:
                cerr << "INVALID CHOICE!" << endl;
                return;
        }

        file.write(reinterpret_cast<const char*>(this), sizeof(Ticket));
        cout << "STATUS: " << status << endl;
        cout << "RESERVATION NO: " << resNo << endl;
        file.close();
    } else {
        cerr << "ERROR IN THE TRAIN NUMBER ENTERED!" << endl;
    }
}

void Ticket::cancellation() {
    ifstream fin("Ticket1.dat", ios::binary);
    if (!fin) {
        cerr << "ERROR OPENING TICKET FILE!" << endl;
        return;
    }

    ofstream file("Temp1.dat", ios::binary | ios::app);
    if (!file) {
        cerr << "ERROR CREATING TEMP FILE!" << endl;
        return;
    }

    cout << "ENTER THE RESERVATION NO: ";
    int r;
    cin >> r;

    bool found = false;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Ticket))) {
        if (getResNo() != r) {
            file.write(reinterpret_cast<const char*>(this), sizeof(Ticket));
        } else {
            found = true;
        }
    }
    fin.close();
    file.close();

    remove("Ticket1.dat");
    rename("Temp1.dat", "Ticket1.dat");

    if (found) {
        cout << "RESERVATION CANCELLED" << endl;
    } else {
        cout << "NO SUCH RESERVATION MADE!" << endl;
    }
}

void Ticket::display() const {
    ifstream file("Ticket1.dat", ios::binary);
    if (!file) {
        cerr << "ERROR OPENING TICKET FILE!" << endl;
        return;
    }

    cout << "ENTER THE RESERVATION NO: ";
    int n;
    cin >> n;

    bool found = false;
    Ticket temp; // Use a non-const temporary Ticket object for reading

    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Ticket))) {
        if (n == temp.getResNo()) {
            found = true;
            cout << "RESERVATION NUMBER: " << temp.getResNo() << endl;
            cout << "NAME: " << temp.name << endl;
            cout << "AGE: " << temp.age << endl;
            cout << "STATUS: " << temp.status << endl;
            break;
        }
    }
    if (!found) {
        cerr << "NO RESERVATION FOUND!" << endl;
    }
    file.close();
}

int main() {
    Train tr;
    Ticket tick;
    int choice;

    do {
        cout << "WELCOME\nRAILWAY TICKET RESERVATION\n==========================\n";
        cout << "1. TRAIN DETAILS\n2. UPDATE TRAIN DETAILS\n3. RESERVING A TICKET\n";
        cout << "4. CANCELLING A TICKET\n5. DISPLAY THE PRESENT TICKET STATUS\n6. EXIT\n";
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tr.display();
                break;
            case 2:
                tr.input();
                break;
            case 3:
                tick.reservation();
                break;
            case 4:
                tick.cancellation();
                break;
            case 5:
                tick.display();
                break;
            case 6:
                exit(0);
            default:
                cerr << "INVALID CHOICE!" << endl;
        }
    } while (choice != 6);

    return 0;
}
