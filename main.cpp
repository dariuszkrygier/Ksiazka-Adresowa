#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>



using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, nrTelefonu, adres, mail;
};

string konwersjaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();
    return str;
}

int konwersjaStringNaInt (string wyraz)
{
    int liczba;
    istringstream iss(wyraz);
    iss >> liczba;
    return liczba;
}

void dzielenieWyrazuNaCzesciIzapisanieDoWektora (std::string const &str, const char delim,
        std::vector<std::string> &out)
{
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim))
    {
        out.push_back(s);
    }
}


void zapisywanieKontaktowDoPliku (vector <Kontakt> &kontakty)
{
    fstream plik;
    plik.open ("ksiazka adresowa.txt", ios::out);

    for (int i = 0; i < kontakty.size(); i++)
    {
        plik << konwersjaIntNaString(kontakty[i].id) << "|";
        plik << kontakty[i].imie << "|";
        plik << kontakty[i].nazwisko << "|";
        plik << kontakty[i].nrTelefonu << "|";
        plik << kontakty[i].adres << "|";
        plik << kontakty[i].mail << "|" << endl;
    }
    plik.close();
}

void wczytajKontaktyZPliku (vector <Kontakt> &kontakty)
{
    fstream plik;
    plik.open ("ksiazka adresowa.txt", ios::in);
    Kontakt nowyKontakt;
    if (plik.good() == false)
    {
        cout << "Plik z kontaktami nie istnieje!" << endl;
        Sleep(2000);
        system ("cls");
    }

    string wierszWPliku;
    int nrWierszaWPliku = 1;
    std::vector<std::string> splittedwords;
    const char delim = '|';


    while (getline (plik, wierszWPliku))

    {
        switch (nrWierszaWPliku)
        {
        case 1:

            dzielenieWyrazuNaCzesciIzapisanieDoWektora(wierszWPliku, delim, splittedwords);

            nowyKontakt.id = konwersjaStringNaInt(splittedwords[0]);
            nowyKontakt.imie = splittedwords[1];
            nowyKontakt.nazwisko = splittedwords[2];
            nowyKontakt.nrTelefonu = splittedwords[3];
            nowyKontakt.adres = splittedwords[4];
            nowyKontakt.mail = splittedwords[5];
            kontakty.push_back(nowyKontakt);
            splittedwords.clear();
            break;
        }

        if (nrWierszaWPliku == 1)
        {
            nrWierszaWPliku = 0;
        }
        nrWierszaWPliku++;
    }

    plik.close();

}

void dodawanieKontaktu (vector <Kontakt> &kontakty)
{

    cin.sync();
    Kontakt nowyKontakt;


    if (kontakty.size() == 0)
    {
        nowyKontakt.id = 1;
    }
    else
    {
        for (vector<Kontakt>::iterator itr = kontakty.begin(), koniec=kontakty.end(); itr!=koniec; ++itr)
        {
            nowyKontakt.id = itr -> id + 1;
        }
    }


    cout << "Podaj imie:" << endl;
    getline(cin, nowyKontakt.imie);
    cout << "Podaj nazwisko:" << endl;
    getline(cin, nowyKontakt.nazwisko);
    cout << "Podaj nr telefonu:" << endl;
    getline(cin, nowyKontakt.nrTelefonu);
    cout << "Podaj adres zamieszkania:" << endl;
    getline(cin, nowyKontakt.adres);
    cout << "Podaj maila:" << endl;
    getline(cin, nowyKontakt.mail);

    kontakty.push_back(nowyKontakt);

    cout << "Kontakt zostal dodany." << endl;
    Sleep(1000);
}

void wyswietlanieKontaktowWgImienia (vector <Kontakt> &kontakty)
{
    string imie;
    int iloscZnalezionychKontaktow = 0;
    cout << "Podaj imie wg ktorego maja byc wyswietlone kontakty: ";
    cin.sync();
    getline(cin, imie);
    int i = 0;

    while(i < kontakty.size())
    {
        if (kontakty[i].imie == imie)
        {
            cout << kontakty[i].id << "|";
            cout << kontakty[i].imie << "|";
            cout << kontakty[i].nazwisko << "|";
            cout << kontakty[i].nrTelefonu << "|";
            cout << kontakty[i].adres << "|";
            cout << kontakty[i].mail << "|" << endl;
            iloscZnalezionychKontaktow++;
        }
        i++;
    }
    if (iloscZnalezionychKontaktow == 0)
    {
        cout << "Brak kontaktow z podanym imieniem." << endl;
    }
}
void wyswietlanieKontaktowWgNazwiska (vector <Kontakt> &kontakty)
{
    string nazwisko;
    int iloscZnalezionychKontaktow = 0;
    cout << "Podaj nazwisko wg ktorego maja byc wyswietlone kontakty: ";
    cin.sync();
    getline(cin, nazwisko);
    int i = 0;

    while (i < kontakty.size())
    {
        if (kontakty[i].nazwisko == nazwisko)
        {
            cout << kontakty[i].id << "|";
            cout << kontakty[i].imie << "|";
            cout << kontakty[i].nazwisko << "|";
            cout << kontakty[i].nrTelefonu << "|";
            cout << kontakty[i].adres << "|";
            cout << kontakty[i].mail << "|" << endl;
            iloscZnalezionychKontaktow++;
        }
        i++;
    }
    if (iloscZnalezionychKontaktow == 0)
    {
        cout << "Brak kontaktow z podanym nazwiskiem." << endl;
    }
}

void wyswietlanieWszystkichKontaktow (vector <Kontakt> &kontakty)
{

    cout << "Twoje wszystkie kontakty: " << endl;



    for (vector<Kontakt>::iterator itr = kontakty.begin(), koniec=kontakty.end(); itr!=koniec; ++itr)
    {
        cout << (*itr).id << "|";
        cout << (*itr).imie << "|";
        cout << (*itr).nazwisko << "|";
        cout << (*itr).nrTelefonu << "|";
        cout << (*itr).adres << "|";
        cout << (*itr).mail << "|" << endl;
    }
    if (kontakty.empty())
    {
        cout << "Brak kontaktow w Twojej bazie danych." << endl;
    }
}



void edycjaKontaktuMenu()
{
    system ("cls");
    cout << "1. Imie." << endl;
    cout << "2. Nazwisko." << endl;
    cout << "3. Nr telefonu." << endl;
    cout << "4. Adres." << endl;
    cout << "5. Email." << endl;
    cout << "6. Powrot do menu." << endl;
}

void edytowanieKontaktu (vector <Kontakt> &kontakty)
{
    int idKontaktuDoEdycji = 0;
    char wyborWmenuEdycjaKontaktow = 0;
    cout << "Podaj ID kontaktu do edycji: ";
    cin >> idKontaktuDoEdycji;
    int iloscZnalezionychKontaktow = 0;
    for (vector<Kontakt>::iterator itr = kontakty.begin(), koniec=kontakty.end(); itr!=koniec; ++itr)
    {
        if  (itr->id == idKontaktuDoEdycji)
        {
            edycjaKontaktuMenu();
            cin >> wyborWmenuEdycjaKontaktow;
            iloscZnalezionychKontaktow++;
            if (wyborWmenuEdycjaKontaktow == '1')
            {
                cin.sync();
                cout << "Imie kontaktu o ID = " << itr->id << " : " << itr->imie <<endl;
                string noweImie = "";
                cout << "Wpisz nowe imie:"<<endl;
                getline(cin, noweImie) ;
                itr -> imie = noweImie;
                zapisywanieKontaktowDoPliku (kontakty);
                cout << "Imie zostalo zmienione pomyslnie!" << endl;
                Sleep(2000);

            }
            else if (wyborWmenuEdycjaKontaktow == '2')
            {
                cin.sync();
                cout << "Nazwisko kontaktu o ID = " << itr->id << " : " << itr->nazwisko<<endl;
                string noweNazwisko = "";
                cout << "Wpisz nowe nazwisko:"<<endl;
                getline(cin, noweNazwisko) ;
                itr -> nazwisko = noweNazwisko;
                zapisywanieKontaktowDoPliku (kontakty);
                cout << "Nazwisko zostalo zmienione pomyslnie!" << endl;
                Sleep(2000);
            }
            else if (wyborWmenuEdycjaKontaktow == '3')
            {
                cin.sync();
                cout << "Nr telefonu kontaktu o ID = " << itr->id << " : " << itr -> nrTelefonu<<endl;
                string nowyNrTelefonu = "";
                cout << "Wpisz nowy nr telefonu:"<<endl;
                getline(cin, nowyNrTelefonu) ;
                itr -> nrTelefonu = nowyNrTelefonu;
                zapisywanieKontaktowDoPliku (kontakty);
                cout << "Nr telefonu zostal zmieniony pomyslnie!" << endl;
                Sleep(2000);
            }
            else if (wyborWmenuEdycjaKontaktow == '4')
            {
                cin.sync();
                cout << "Adres kontaktu o ID = " << itr -> id << " : " << itr -> adres<<endl;
                string nowyAdres = "";
                cout << "Wpisz nowy adres:"<<endl;
                getline(cin, nowyAdres) ;
                itr -> adres = nowyAdres;
                zapisywanieKontaktowDoPliku (kontakty);
                cout << "Adres zostal zmieniony pomyslnie!" << endl;
                Sleep(2000);
            }
            else if (wyborWmenuEdycjaKontaktow == '5')
            {
                cin.sync();
                cout << "Email kontaktu o ID = " << itr -> id << " : " << itr -> mail<<endl;
                string nowyMail = "";
                cout << "Wpisz nowy email:"<<endl;
                getline(cin, nowyMail) ;
                itr -> mail = nowyMail;
                zapisywanieKontaktowDoPliku (kontakty);
                cout << "Email zostal zmieniony pomyslnie!" << endl;
                Sleep(2000);
            }
            else if (wyborWmenuEdycjaKontaktow == '6')
            {
                break;
            }
        }

    }
    if (iloscZnalezionychKontaktow == 0)
    {
        cout << "Brak kontaktow z podanym numerem ID." << endl;
        Sleep(1500);
    }
}

void usuwanieKontaktu (vector <Kontakt> &kontakty)
{
    int idKontaktuDoUsuniecia=0;
    cout << "Podaj ID kontaktu do usuniecia: ";
    cin >> idKontaktuDoUsuniecia;
    char usunKontakt = 0;
    int iloscZnalezionychKontaktow=0;


    for (vector<Kontakt>::iterator itr = kontakty.begin(), koniec=kontakty.end(); itr!=koniec; ++itr)
    {
        if  (itr->id == idKontaktuDoUsuniecia)
        {
            cout << itr->id << "|";
            cout << itr->imie << "|";
            cout << itr->nazwisko << "|";
            cout << itr->nrTelefonu << "|";
            cout << itr->adres << "|";
            cout << itr->mail << "|" << endl;
            iloscZnalezionychKontaktow++;

            cout << "Nacisnij t aby usunac kontakt. ";
            cin >> usunKontakt;
            if (usunKontakt == 't')
            {
                kontakty.erase(itr);
                zapisywanieKontaktowDoPliku (kontakty);
            }
            break;
        }
    }

    if (iloscZnalezionychKontaktow == 0)
    {
        cout << "Brak kontaktu z podanym numerem ID." << endl;
        Sleep(1500);
    }
}

int main()
{

    vector <Kontakt> kontakty;
    vector<Kontakt>::iterator itr = kontakty.begin();
    char wybor;
    wczytajKontaktyZPliku(kontakty);

    while(1)
    {
        system ("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj kontakt." << endl;
        cout << "2. Wyswietl kontakty wg imienia." << endl;
        cout << "3. Wyswietl kontakty wg nazwiska." << endl;
        cout << "4. Wyswietl wszystkie kontakty." << endl;
        cout << "5. Edytuj kontakty." << endl;
        cout << "6. Usun kontakty." << endl;
        cout << "9. Zakoncz program." << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            dodawanieKontaktu (kontakty);
            zapisywanieKontaktowDoPliku (kontakty);
        }
        else if (wybor == '2')
        {
            wyswietlanieKontaktowWgImienia (kontakty);
            system ("pause");
        }
        else if (wybor == '3')
        {
            wyswietlanieKontaktowWgNazwiska (kontakty);
            system ("pause");
        }
        else if (wybor == '4')
        {
            wyswietlanieWszystkichKontaktow (kontakty);
            system ("pause");
        }
        else if (wybor == '5')
        {
            edytowanieKontaktu(kontakty);
        }

        else if (wybor == '6')
        {
            usuwanieKontaktu(kontakty);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
