/***
Last modified by: $Author: lukasz.mozgala $
on: $Date: 2018-03-21 13:10:30 +0100 (Śr, 21 mar 2018) $
in revision: $Revision: 81660 $
***/

#if !defined __COMMON_H__
#define __COMMON_H__

#define NOWE_ROZKAZY

// Typy pokojówek
#define POK_OFF 0
#define POK_BIMETAL 1
#define POK_TECH 2
#define POK_TECH_ALGORYTM 3


#include "states.h"

#include "events.h"

// Typy trybu letniego
#define TRYB_LETNI_Z_DOGRZANIEM 	1
#define TRYB_LETNI_BEZ_DOGRZANIA 	2
#define TRYB_LETNI_DEFAULT			3
// Tryby pracy
#define TRYB_GRZANIE_DOMU 0
#define TRYB_PRIORYTET_BOJLERA 1
#define TRYB_POMPY_ROWNOLEGLE 2
#define TRYB_LATO 3
#define TRYB_BEZ_POMP 4
#define TRYB_Z_BUFOREM 5

// Kierunki zaworu
#define ZAWOR_LEWO 1
#define ZAWOR_PRAWO 2
#define ZAWOR_STOP 4

// Tryby pracy zaworu
#define TRYB_ZAWOR_PODSTAWOWY 0
#define TRYB_ZAWOR_PROSTA_POKOJOWKA 1
#define TRYB_ZAWOR_POKOJOWKA_202 2
#define TRYB_ZAWOR_POGODOWKA 3

//Typy zaworu
#define TYP_ZAWOR_CO 1
#define TYP_ZAWOR_PODLOGOWY 2

// Typy pomp dodatkowych
#define TYP_POMPA_PODLOGOWA 1
#define TYP_POMPA_BUFOR 2
#define TYP_POMPA_CO 3
#define TYP_POMPA_CYRKULACYJNA 4
#define TYP_POMPA_WYLACZONA 5
#define TYP_POMPA_CWU 6
#define TYP_POMPA_PRZEPUSTNICA 7

// Rodzaje paliwa
#define PALIWO_WEGIEL 1
#define PALIWO_MIAL 0
#define PALIWO_DREWNO 2

// B��dy GSM
#define GSM_BLEDNY_PIN 1
#define GSM_ZABLOKOWANA_KARTA 2
#define GSM_NIE_GOTOWY 3
#define GSM_BRAK_SIM 4
#define GSM_SMS_BLAD_WYSYLANIA 5

// Statusy pochodz�ce ze strony systemu bazodanowego
#define ETHER_STATUS_NONE 0
#define ETHER_STATUS_MODUL_NIE_PODLACZONY 1

// Statusy pochodz�ce z modu�u internetowego
#define ETHER_MODUL_NONE 0
#define ETHER_MODUL_BRAK_KOMUNIKACJI 1
#define ETHER_MODUL_BRAK_PAMIECI_ROZKAZOW 2

// Funkcje pompy zaworu
#define POMPA_ZAWORU_WYLACZONA 0
#define POMPA_ZAWORU_ZALACZONA_ZAWSZE 1
#define POMPA_ZAWORU_OD_PROGU 2

#if !defined NO_UART
#include "rozkazy.h"
#endif

//---definicje statusów zaworów
#define ZAWOR_PRACA 400
#define ZAWOR_PELNE_OTWIERANIE 401
#define ZAWOR_PELNE_ZAMYKANIE 402

//---definicje rodzaju pracy wykonywanej przez zawor
#define ZAWOR_ZATRZYMANY 0
#define ZAWOR_ZAMYKANIE 1
#define ZAWOR_RECZNA_ZAMYKANIE 2
#define ZAWOR_KALIBRACJA_ZAMYKANIE 3
#define ZAWOR_OTWIERANIE 4
#define ZAWOR_RECZNA_OTWIERANIE 5
#define ZAWOR_KALIBRACJA_OTWIERANIE 6

//---definicje statusow elektrozaworu
#define ELEKTROZAWOR_BRAK 0
#define ELEKTROZAWOR_OTWARTY 1
#define ELEKTROZAWOR_ZAMKNIETY 2

//--typy elektrozaworow
#define ELEKTROZAWOR_PROSTY 0
#define ELEKTROZAWOR_ROZBUDOWANY 1
#define ELEKTROZAWOR_CZUJNIK 2

#define MODULE_TYPE_ST60 1
#define MODULE_TYPE_ST61 3
#define TYPE_ST60 MODULE_TYPE_ST60
#define TYPE_ST61 MODULE_TYPE_ST61
#define TYPE_ST62 4
#define TYPE_ST48 5
#define TYPE_ST47 6
#define TYPE_ST57 7
#define TYPE_ST709 8
#define TYP_STEROWNIKA_ST60 TYPE_ST60
#define TYP_STEROWNIKA_ST61 TYPE_ST61
#define TYP_STEROWNIKA_ST62 4
#define TYP_STEROWNIKA_ST48 5
#define TYP_STEROWNIKA_ST47 6
#define TYP_STEROWNIKA_ST57 7
#define TYP_STEROWNIKA_ST709 8
#define TYP_STEROWNIKA_ST37 9
#define TYP_STEROWNIKA_ST408 10
#define TYP_STEROWNIKA_ST431 11
#define TYP_STEROWNIKA_ST491 12
#define TYP_STEROWNIKA_ST95 13
#define TYP_STEROWNIKA_ST49 14
#define TYP_STEROWNIKA_ST432 15
#define TYP_STEROWNIKA_ST460 16
#define TYP_STEROWNIKA_ST880 17
#define TYP_STEROWNIKA_ST98 18
#define TYP_STEROWNIKA_ST450 19
#define TYP_STEROWNIKA_ST470 20
#define TYP_STEROWNIKA_ST480 21
#define TYP_STEROWNIKA_ST490 22
#define TYP_STEROWNIKA_ST798 23
#define TYP_STEROWNIKA_ST890 24
#define TYP_STEROWNIKA_ST390 25
#define TYP_STEROWNIKA_ST72 26
#define TYP_STEROWNIKA_ST462 27
#define TYP_STEROWNIKA_ST600 28
#define TYP_STEROWNIKA_ST266 29
#define TYP_STEROWNIKA_ST268 30 //listwa na 8 pokojowek
#define TYP_STEROWNIKA_ST340 31
#define TYP_STEROWNIKA_ST465 32
#define TYP_STEROWNIKA_ST580 33
#define TYP_STEROWNIKA_ST970 34//nowy pellet deforo
#define TYP_STEROWNIKA_ST971 35//nowy pellet irlandia
#define TYP_STEROWNIKA_ST974 35//nowy pellet gren
#define TYP_STEROWNIKA_ST976 35//nowy pellet kamen
#define TYP_STEROWNIKA_ST977 35//nowy pellet elektromet
#define TYP_STEROWNIKA_ST978 35//nowy pellet stalmark
#define TYP_STEROWNIKA_ST979 35//nowy pellet kolton
#define TYP_STEROWNIKA_ST263 36 //lista z czujnikami przewodowymi
#define TYP_STEROWNIKA_ST810 37
#define TYP_STEROWNIKA_ST307 38 //oczyszczalnia Wobet
#define TYP_STEROWNIKA_ST581 39//nowy pellet opop modul
#define TYP_STEROWNIKA_ST570 40
#define TYP_STEROWNIKA_ST821 41
#define TYP_STEROWNIKA_ST4000 42//urzadzenie wielofunkcyjne galmet
#define TYP_STEROWNIKA_ST571 43 //podajnik kolton
#define TYP_STEROWNIKA_ST9711 44//krzaczek
#define TYP_STEROWNIKA_ST9714 45//palnik
#define TYP_STEROWNIKA_ST813 46//zgazowania

//---definicje identyfikatorow firm
#define FIRMA_ZEBIEC 1          // Zębiec
#define FIRMA_ZAREZERWOWANE 2   // ZAREZERWOWANE
#define FIRMA_DEFRO 3           // Defro
#define FIRMA_KOLTON 4          // Kołton
#define FIRMA_STALMARK 5        // Stalmark
#define FIRMA_TECH 6            // TECH
#define FIRMA_WATT 7            // WATT
#define FIRMA_SAS 8             // SAS
#define FIRMA_GALMET 9          // Galmet
#define FIRMA_REGESS 10         // Regess
#define FIRMA_ELEKTROMET 11     // Elektromet
#define FIRMA_LESTER 12         // Lester
#define FIRMA_VIADRUS 13        // Viadrus
#define FIRMA_SOLIMPEX 14       // Solimpex
#define FIRMA_DIMPLEX 15        // Dimplex
#define FIRMA_POLEKO 16         // POLEKO
#define FIRMA_COOLWEX 17        // Coolwex
#define FIRMA_TERMOTECH 18      // Termo-Tech
#define FIRMA_KALVIS 19         // Kalvis
#define FIRMA_OEG 20            // OEG
#define FIRMA_KRZACZEK 21       // Krzaczek
#define FIRMA_SKORUT 22         // Skorut
#define FIRMA_WANAS 23          // WANAS
#define FIRMA_SOLVER 24         // Solver
#define FIRMA_OPOP 25           // OPOP
#define FIRMA_KAMEN 26          // Kamen
#define FIRMA_GREN 27           // Greń
#define FIRMA_MODERATOR 28      // Moderator
#define FIRMA_KIPI 29           // KIPI
#define FIRMA_DREWMET 30        // DREW-MET
#define FIRMA_DOSPEL 31         // Dospel
#define FIRMA_EKOEFEKT 32       // EKOEFEKT
#define FIRMA_COOL 33           // COOL
#define FIRMA_OEM 34            // OEM
#define FIRMA_LUMEN 35          // Lumen
#define FIRMA_ENSOL 36          // Ensol
#define FIRMA_KOSPEL 37         // Kospel
#define FIRMA_BUDMET 38         // Budmet
#define FIRMA_MASTER 39         // Master
#define FIRMA_POLYPIPE 40       // Polypipe
#define FIRMA_BADO 41           // BADO
#define FIRMA_STALMAX 42        // Stalmax
#define FIRMA_TQD 43            // TQD
#define FIRMA_NMT 44		// NMT Heizsysteme
#define FIRMA_SUNEX 45		// Sunex
#define FIRMA_ALLTHERM 46	// Alltherm
#define FIRMA_VALVEX 47		// Valvex
#define FIRMA_EVENES 48		// Evenes
#define FIRMA_VERANO 49		// Verano
#define FIRMA_KOTLOSPAW 50  // Kotłospaw
#define FIRMA_DAKON 51 		// Dakon
#define FIRMA_VENMA 52 		// Venma
#define FIRMA_ZK_DESIGN 53  // ZK Design
#define FIRMA_JAGA 54		// JAGA
#define FIRMA_LECHMA 55     // Lechma
#define FIRMA_EPLUCON 56     // Eplucon
#define FIRMA_TYPHOON 57     // Lechma
#define FIRMA_KAMPMANN 58	//Kampmann
#define FIRMA_PLONKA 59	    //Płonka
#define FIRMA_PUSTE_ID 60 	// Puste id firmy dla internetu
#define FIRMA_AFRISO 61 	// AFRISO
#define FIRMA_OGNIK 62      // Ognik
#define FIRMA_ELIAS 63
#define FIRMA_BRASTAL 64    //Brastal
#define FIRMA_MAKROTERM 65    	//Makroterm
#define FIRMA_METALFACH 66    	//Metal Fach
#define FIRMA_TERMOTECHNIKA 67  //TERMOTECHNIKA
#define FIRMA_PAW 68            // PAW
#define FIRMA_MAGA 69            // Maga
#define FIRMA_VIESSMANN 70            // Viessmann
#define FIRMA_ISAN 71			//ISAN
#define FIRMA_POLYTHERM 72			//Polytherm
#define FIRMA_GROBELNY 73			//Grobelny

// Adresy modułów występujących pojedynczo
#define BROADCAST_ADDRESS 0xFFFF
#define ADDRESS_ST60 0xFFFE
#define ADDRESS_ST62 0xFFFD
#define ADDRESS_ST201 0xFFFC
#define ADDRESS_ST60_POMPY 0xFFFB
#define ADDRESS_ST202 0xFFFA
#define ADDRESS_ST66_RUSZT 0xFFF9
#define ADDRESS_GSM 0xFFF8
#define ADDRESS_SONDA 0xFFF7
#define ADDRESS_ZAWOR_ST41 0xFFF6
#define ADDRESS_ST97_DEFRO 0xFFF5
#define ADDRESS_ETHERNET 0xFFF4
#define ADDRESS_SOLAR 0xFFF3
#define ADDRESS_ST600 0xFFF2
#define ADDRESS_ZAWOR_WBUDOWANY_1 0xFFF1
#define ADDRESS_ZAWOR_WBUDOWANY_2 0xFFF0
#define ADDRESS_CHLODNICTWO_LCD 0xFFEF
#define ADDRESS_ST600_SCREEN 0xFFEE
#define ADDRESS_RECUPERATOR_LCD 0xFFED
#define ADDRESS_RECUPERATOR_SOLAR_LCD 0xFFEC
#define ADDRESS_SAUNA_LCD 0xFFEB
#define ADDRESS_POMPA_CIEPLA_ST532_COOL 0xFFEA
#define ADDRESS_ST5305_KOLTON 0xFFE9
#define ADDRESS_WOLNY_ADRES_5 0xFFE8
#define ADDRESS_WOLNY_ADRES_6 0xFFE7
#define ADDRESS_WOLNY_ADRES_7 0xFFE6
#define ADDRESS_WOLNY_ADRES_8 0xFFE5
#define ADDRESS_ELEKTROZAWOR_POK_MATKA 0xFFE4
#define ADDRESS_POMPA_CIEPLA_WYSWIETLACZ 0xFFE3
#define ADDRESS_ETHERNET_V2 0xFFE2
#define ADDRESS_CZUJNIK_CISNIENIA 0xFFE1
#define ADDRESS_KASKADA 0xFFE0
#define ADDRESS_WENT_WYCIAG 0xFFDF
#define ADDRESS_WENT_WYCIAG_CUG 0xFFDE
#define ADDRESS_LADOWACZ_PELLETU 0xFFDD
#define ADDRESS_LADOWACZ_PELLETU_WYSWIETLACZ 0xFFDC
#define ADDRESS_CZUJNIK_TLENKU_WEGLA 0xFFDB
#define ADDRESS_CZUJNIK_TEMPERATURY_IR 0xFFDA
#define ADDRESS_LISTWA_STREFA_1 0xFFD9
#define ADDRESS_LISTWA_STREFA_2 0xFFD8
#define ADDRESS_LISTWA_STREFA_3 0xFFD7
#define ADDRESS_LISTWA_STREFA_4 0xFFD6
#define ADDRESS_LISTWA_STREFA_5 0xFFD5
#define ADDRESS_LISTWA_STREFA_6 0xFFD4
#define ADDRESS_LISTWA_STREFA_7 0xFFD3
#define ADDRESS_LISTWA_STREFA_8 0xFFD2
#define ADDRESS_KONWERTER_MBUS_RS 0xFFD1
#define ADDRESS_PANEL_KONTROLNY_L9 0xFFD0
#define ADDRESS_MIERNIK_MOCY 0xFFCF

#define ADDRESS_KOMINEK 0xFF00    //kiedys mi sie zle dodalo ten adres, niech zawsze bedzie na dole dopoki nie będzie mniejszych adresow - zeby nie zapomniec


// Typy krańcówek
#define TK_KRANCOWKA 1
#define TK_HALLOTRON 2

// ochrona powrotu i kotla
#define OCHRONA_WYL 0
#define OCHRONA_POW 1
#define OCHRONA_KOT 2

// urządzenie dodatkowe dla solara
#define SOLAR_PERYFERIUM_WYLACZONE 0
#define SOLAR_PERYFERIUM_POMPA_CYRKULACYJNA 1
#define SOLAR_PERYFERIUM_GRZALKA 2
#define SOLAR_PERYFERIUM_ROZPALANIE_KOTLA 3
#define SOLAR_PERYFERIUM_WYCHLADZANIE_PRZEZ_CWU 4
#define SOLAR_PERYFERIUM_STYK_ZGODNY_POMPA 5
#define SOLAR_PERYFERIUM_STYK_PRZECIWNY_POMPA 6

// tryby pracy solara
#define SOLAR_TRYB_AUTOMATYCZNY 0
#define SOLAR_TRYB_ODMRAZANIE 1
#define SOLAR_TRYB_URLOPOWY 2
#define SOLAR_TRYB_LEGIONELLA 3

// definicje schematów solara
#define SOLAR_SCHEMAT_PODSTAWOWY 0
#define SOLAR_SCHEMAT_1ZBIORNIK_SEKWENCJA 1
#define SOLAR_SCHEMAT_2SOLARY_2POMPY 2
#define SOLAR_SCHEMAT_2SOLARY_ZAWOR 3
#define SOLAR_SCHEMAT_DOGRZEWANIE_KOTLEM 4
#define SOLAR_SCHEMAT_2ZBIORNIKI_ZAWOR 5
#define SOLAR_SCHEMAT_2ZBIORNIKI_2POMPY 6
#define SOLAR_SCHEMAT_2ZBIORNIKI_SEKWENCJA 7
#define SOLAR_SCHEMAT_WYMIENNIK_CIEPLA 8
#define SOLAR_SCHEMAT_PIEC_2FUNKCYJNY 9
#define SOLAR_SCHEMAT_DOGRZEWANIE_POWROTU_CO 10
#define SOLAR_SCHEMAT_2SOLARY_2POMPY_ZAWOR 11
#define SOLAR_SCHEMAT_2SOLARY_2ZBIORNIKI_SEKWENCJA 12 // w st460 schemat 13
#define SOLAR_SCHEMAT_DOGRZEWANIE_POWROTU_CO_ZABEZPIECZENIE 13 // w st460 schemat 14
#define SOLAR_SCHEMAT_2SOLARY_2ZBIORNIKI_2ZAWORY 14  // w st460 schemat 15
#define SOLAR_SCHEMAT_2SOLARY_2POMPY_CO 15 // w st462_skorut schemat 12
#define SOLAR_SCHEMAT_2SOLARY_ZAWOR_2ZBIORNIKI 16 // w s462_skorut schemat 13
#define SOLAR_SCHEMAT_SKORUT_SCH4 17 // w s462_skorut schemat 14
#define SOLAR_SCHEMAT_SKORUT_SCH5 18 // w s462_skorut schemat 15
#define SOLAR_SCHEMAT_SKORUT_SCH3 19 // w s462_skorut schemat 16
#define SOLAR_SCHEMAT_LUNEN_1 20
#define SOLAR_SCHEMAT_DODATKOWY_ODBIORNIK 21

//schmaty pracy kominka
#define KOMINEK_SCHEMAT_2POMPY 0
#define KOMINEK_SCHEMAT_INTEGRATOR 1
#define KOMINEK_SCHEMAT_ZWOR_BEZ_CWU 2
#define KOMINEK_SCHEMAT_ZWOR_Z_CWU 3

//urzadzenie reg. powietrze
#define NAWIEW_PRZEPUSTNICA 0
#define NAWIEW_WENTYLATOR 1

//klasy sterownikow
#define KLASA_STEROWNIK_POKOJOWY 1
#define KLASA_STEROWNIK_GSM 2
#define KLASA_STEROWNIK_ETHERNET 3
#define KLASA_STEROWNIK_ZAWOR 4

// flagi dla rozkazu MODUL_INT_DOCELOWY_KLIENT określające docelowego klienta dla danych przesyłanych do modułu internetowego. Według tej flagi moduł internetowy będzie rozsyłał rozkazy do klientów.
#define DOCELOWY_KLIENT_BRAK 0
#define DOCELOWY_KLIENT_STEROWNIK_GLOWNY 1
#define DOCELOWY_KLIENT_STRONA_WEWNETRZNA 2
#define DOCELOWY_KLIENT_STRONA_ZEWNETRZNA 4
#define DOCELOWY_KLIENT_MODUL_INTERNETOWY 8
#define DOCELOWY_KLIENT_WSZYSTKIE ((DOCELOWY_KLIENT_STEROWNIK_GLOWNY | DOCELOWY_KLIENT_STRONA_WEWNETRZNA | DOCELOWY_KLIENT_STRONA_ZEWNETRZNA | DOCELOWY_KLIENT_MODUL_INTERNETOWY))

#define MOC_UKLADU_LOW 1
#define MOC_UKLADU_MIDDLE 2
#define MOC_UKLADU_HIGH 3

//Zrodlo ciepla do antyzamarzania dla pompy ciepla
#define ZRODLO_CIEPLA_ANTYZAMARZANIE_GRZALKA 0
#define ZRODLO_CIEPLA_ANTYZAMARZANIE_POMPA_CIEPLA 1

//Tygodniówka
#define TYGODNIOWKA_WYLACZONA 0
#define TYGODNIOWKA_POZA_ZAKRESEM 1
#define TYGODNIOWKA_AKTYWNA 2

// Flagi dla rozkazu FLAGI_ROZPALANIA_WYGASZANIA_POKOJOWKA
#define FLAGA_POKOJOWKA_WYGASZANIE_WIDOCZNE 1
#define FLAGA_POKOJOWKA_WYGASZANIE_MOZLIWE 2
#define FLAGA_POKOJOWKA_ROZPALANIE_WIDOCZNE 256
#define FLAGA_POKOJOWKA_ROZPALANIE_MOZLIWE 512

#endif
