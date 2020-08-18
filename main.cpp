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
    int id, idPomocniczeUzytkownika;
    string imie, nazwisko, nrTelefonu, adres, mail;
};
struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
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
    plik.open ("kontakty.txt", ios::out);

    for (int i = 0; i < kontakty.size(); i++)
    {
        plik << konwersjaIntNaString(kontakty[i].id) << "|";
        plik << konwersjaIntNaString(kontakty[i].idPomocniczeUzytkownika) << "|";
        plik << kontakty[i].imie << "|";
        plik << kontakty[i].nazwisko << "|";
        plik << kontakty[i].nrTelefonu << "|";
        plik << kontakty[i].adres << "|";
        plik << kontakty[i].mail << "|" << endl;
    }
    plik.close();
}

void zapisywanieUzytkownikowDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    plik.open ("uzytkownicy.txt", ios::out);

    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        plik << konwersjaIntNaString(uzytkownicy[i].idUzytkownika) << "|";
        plik << uzytkownicy[i].nazwa << "|";
        plik << uzytkownicy[i].haslo << endl;
    }
    plik.close();
}

void wczytajKontaktyZPliku (vector <Kontakt> &kontakty)
{
    fstream plik;
    plik.open ("kontakty.txt", ios::in);
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
            nowyKontakt.idPomocniczeUzytkownika = konwersjaStringNaInt(splittedwords[1]);
            nowyKontakt.imie = splittedwords[2];
            nowyKontakt.nazwisko = splittedwords[3];
            nowyKontakt.nrTelefonu = splittedwords[4];
            nowyKontakt.adres = splittedwords[5];
            nowyKontakt.mail = splittedwords[6];
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

void wczytajUzytkownikowZPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    plik.open ("uzytkownicy.txt", ios::in);
    Uzytkownik nowyUzytkownik;
    if (plik.good() == false)
    {
        cout << "Plik z uzytkownikami nie istnieje!" << endl;
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

            nowyUzytkownik.idUzytkownika = konwersjaStringNaInt(splittedwords[0]);
            nowyUzytkownik.nazwa = splittedwords[1];
            nowyUzytkownik.haslo = splittedwords[2];
            uzytkownicy.push_back(nowyUzytkownik);
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

void dodawanieKontaktu (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika)
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

    nowyKontakt.idPomocniczeUzytkownika = idZalogowanegoUzytkownika;
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

void wyswietlanieKontaktowWgImienia (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{
    string imie;
    int iloscZnalezionychKontaktow = 0;
    cout << "Podaj imie wg ktorego maja byc wyswietlone kontakty: ";
    cin.sync();
    getline(cin, imie);
    int i = 0;

    while(i < kontakty.size())
    {
        if (kontakty[i].imie == imie && kontakty[i].idPomocniczeUzytkownika == idZalogowanegoUzytkownika)
        {
            cout << kontakty[i].id << "|";
            cout << idZalogowanegoUzytkownika << "|";
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
void wyswietlanieKontaktowWgNazwiska (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{
    string nazwisko;
    int iloscZnalezionychKontaktow = 0;
    cout << "Podaj nazwisko wg ktorego maja byc wyswietlone kontakty: ";
    cin.sync();
    getline(cin, nazwisko);
    int i = 0;

    while (i < kontakty.size())
    {
        if (kontakty[i].nazwisko == nazwisko && kontakty[i].idPomocniczeUzytkownika == idZalogowanegoUzytkownika)
        {
            cout << kontakty[i].id << "|";
            cout << kontakty[i].idPomocniczeUzytkownika << "|";
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

void wyswietlanieWszystkichKontaktow (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{

    cout << "Twoje wszystkie kontakty: " << endl;



    for (vector<Kontakt>::iterator itr = kontakty.begin(), koniec=kontakty.end(); itr!=koniec; ++itr)
    {
        if (itr->idPomocniczeUzytkownika == idZalogowanegoUzytkownika)
        {
            cout << (*itr).id << "|";
            cout << (*itr).idPomocniczeUzytkownika << "|";
            cout << (*itr).imie << "|";
            cout << (*itr).nazwisko << "|";
            cout << (*itr).nrTelefonu << "|";
            cout << (*itr).adres << "|";
            cout << (*itr).mail << "|" << endl;
        }

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

void menuPoczatkowe()
{
    system ("cls");
    cout << "1. Rejestracja." << endl;
    cout << "2. Logowanie." << endl;
    cout << "9. Zakoncz program." << endl;
}


void edytowanieKontaktu (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{
    int idKontaktuDoEdycji = 0;
    char wyborWmenuEdycjaKontaktow = 0;
    cout << "Podaj ID kontaktu do edycji: ";
    cin >> idKontaktuDoEdycji;
    int iloscZnalezionychKontaktow = 0;
    for (vector<Kontakt>::iterator itr = kontakty.begin(), koniec=kontakty.end(); itr!=koniec; ++itr)
    {
        if  (itr->id == idKontaktuDoEdycji && itr->idPomocniczeUzytkownika == idZalogowanegoUzytkownika)
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

void usuwanieKontaktu (vector <Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{
    int idKontaktuDoUsuniecia=0;
    cout << "Podaj ID kontaktu do usuniecia: ";
    cin >> idKontaktuDoUsuniecia;
    char usunKontakt = 0;
    int iloscZnalezionychKontaktow=0;


    for (vector<Kontakt>::iterator itr = kontakty.begin(), koniec=kontakty.end(); itr!=koniec; ++itr)
    {
        if  (itr->id == idKontaktuDoUsuniecia && itr->idPomocniczeUzytkownika == idZalogowanegoUzytkownika)
        {
            cout << itr->id << "|";
            cout << itr->idPomocniczeUzytkownika << "|";
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

void rejestracja (vector <Uzytkownik> &uzytkownicy)
{
    string nazwa, haslo;
    Uzytkownik nowyUzytkownik;
    cin.sync();
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> nazwa;

    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(), koniec=uzytkownicy.end(); itr!=koniec; ++itr)
    {
        if (itr -> nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
        }
    }
    nowyUzytkownik.nazwa = nazwa;

    cout << "Podaj haslo: " << endl;
    cin >> haslo;
    nowyUzytkownik.haslo = haslo;

    if (uzytkownicy.size() == 0)
    {
        nowyUzytkownik.idUzytkownika = 1;
    }
    else
    {
        {
            nowyUzytkownik.idUzytkownika = uzytkownicy.size() + 1;
        }
    }
    uzytkownicy.push_back(nowyUzytkownik);
    cout << "Konto zalozone." << endl;
    Sleep(1000);
}

int logowanie (vector <Uzytkownik> &uzytkownicy)
{
    string nazwa, haslo;
    cout << "Podaj nazwe: ";
    cin >> nazwa;

    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(), koniec=uzytkownicy.end(); itr!=koniec; ++itr)
    {
        if  (itr->nazwa == nazwa)
        {
            for (int proba=0; proba<3; proba++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proba <<": ";
                cin >> haslo;
                if (itr->haslo == haslo)
                {
                    cout << "Zalogowales sie.";
                    Sleep(1000);
                    return itr -> idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba.";
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem." << endl;
    Sleep(1500);
    return logowanie(uzytkownicy);
}

void zmianaHasla (vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione.";
            Sleep(1000);
            zapisywanieUzytkownikowDoPliku (uzytkownicy);
        }
    }
}

int edytowanieWMenuKsiazkaAdresowa (vector <Kontakt> &kontakty, vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    while (idZalogowanegoUzytkownika != 0)
    {
        system ("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj kontakt." << endl;
        cout << "2. Wyswietl kontakty wg imienia." << endl;
        cout << "3. Wyswietl kontakty wg nazwiska." << endl;
        cout << "4. Wyswietl wszystkie kontakty." << endl;
        cout << "5. Edytuj kontakty." << endl;
        cout << "6. Usun kontakty." << endl;
        cout << "7. Zmiana hasla." << endl;
        cout << "9. Wyloguj." << endl;
        char wybor;
        cin >> wybor;
        if (wybor == '1')
        {
            dodawanieKontaktu (kontakty, idZalogowanegoUzytkownika);
            zapisywanieKontaktowDoPliku (kontakty);
        }
        else if (wybor == '2')
        {
            wyswietlanieKontaktowWgImienia (kontakty, idZalogowanegoUzytkownika);
            system ("pause");
        }
        else if (wybor == '3')
        {
            wyswietlanieKontaktowWgNazwiska (kontakty, idZalogowanegoUzytkownika);
            system ("pause");
        }
        else if (wybor == '4')
        {
            wyswietlanieWszystkichKontaktow (kontakty, idZalogowanegoUzytkownika);
            system ("pause");
        }
        else if (wybor == '5')
        {
            edytowanieKontaktu(kontakty, idZalogowanegoUzytkownika);
        }

        else if (wybor == '6')
        {
            usuwanieKontaktu(kontakty, idZalogowanegoUzytkownika);
        }
        else if (wybor == '7')
        {
            zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
        }
        else if (wybor == '9')
        {
            idZalogowanegoUzytkownika=0;
            return idZalogowanegoUzytkownika;
        }
    }
}

int main()
{

    vector <Kontakt> kontakty;
    vector <Uzytkownik> uzytkownicy;
    vector<Kontakt>::iterator itr = kontakty.begin();
    char wybor;
    int idZalogowanegoUzytkownika = 0;
    wczytajKontaktyZPliku(kontakty);
    wczytajUzytkownikowZPliku(uzytkownicy);
    int idZalogowanegoUzytkownikaPomocnicze = 0;

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            menuPoczatkowe();
            cin >> wybor;
            if (wybor == '1')
            {
                rejestracja(uzytkownicy);
                zapisywanieUzytkownikowDoPliku(uzytkownicy);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie (uzytkownicy);
                idZalogowanegoUzytkownika = edytowanieWMenuKsiazkaAdresowa (kontakty, uzytkownicy, idZalogowanegoUzytkownika);
            }
            else if (wybor == '9')
            {
                exit(0);
            }
        }
    }

    return 0;
}
